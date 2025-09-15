import asyncio
import os
import sys
import json
import base64
from datetime import datetime
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import dh, padding
from cryptography.hazmat.primitives.serialization.pkcs12 import load_key_and_certificates
from cryptography.x509 import load_pem_x509_certificate
from protocolo import *
from comandos import *
from utils import *

conn_cnt = 0
conn_port = 7777
max_msg_size = 9999

class ServerWorker:
    utilizadores = {}

    def __init__(self, cnt, addr=None):
        self.id = cnt
        self.addr = addr
        self.msg_cnt = 0
        self.shared_key = None
        self.nonces_usados = set()

    def guardar_estado(path="data"):
        os.makedirs(path, exist_ok=True)
        # Guardar utilizadores
        save_json(os.path.join(path, "utilizadores.json"), {
            pseudonym: {"id": u["id"], "nome": u["nome"]}
            for pseudonym, u in ServerWorker.utilizadores.items()
        })
        # Guardar ficheiros 
        save_json(os.path.join(path, "ficheiros.json"), {
            k: {
                "nome": v["nome"], "dono": v["dono"],
                "envelopes": {user: base64.b64encode(env).decode()
                              for user, env in v.get("envelopes", {}).items()},
                "permissoes": v["permissoes"], "path": v["path"]
            } for k, v in ficheiros.items()
        })
        # Guardar cofres
        save_json(os.path.join(path, "cofres.json"), cofres)
        # Guardar grupos
        save_json(os.path.join(path, "grupos.json"), grupos)

    def carregar_estado(path="data"):
        utilizadores_path = os.path.join(path, "utilizadores.json")
        users = load_json(utilizadores_path) or {}
        for pseudonym, u in users.items():
            ServerWorker.utilizadores[pseudonym] = {
                "id": u["id"],
                "nome": u["nome"],
                "shared_key": None,
                "certificado": None,
                "comandos": []
            }
        f_data = load_json(os.path.join(path, "ficheiros.json")) or {}
        for k, v in f_data.items():
            # Decodificar envelopes
            envelopes = {user: base64.b64decode(env_b64) for user, env_b64 in v.get("envelopes", {}).items()}
            ficheiros[k] = {
                "nome": v["nome"],
                "dono": v["dono"],
                "envelopes": envelopes,
                "permissoes": v["permissoes"],
                "path": v["path"]
            }
        cofres_data = load_json(os.path.join(path, "cofres.json")) or {}
        cofres.update(cofres_data)
        grupos_data = load_json(os.path.join(path, "grupos.json")) or {}
        grupos.update(grupos_data)
        print(f"[INFO] Estado carregado de {utilizadores_path}")

    def process(self, msg):
        self.msg_cnt += 1
        if not msg or len(msg) < 16:
            print("Mensagem inválida.")
            return None

        try:
            dados = interpretar_mensagem(msg, self.shared_key)
        except Exception as e:
            print(f"[{self.id}] Erro ao decifrar mensagem: {e}")
            return None

        nonce = dados.get("nonce")
        if not nonce:
            return construir_mensagem({"erro": "Nonce em falta."}, self.shared_key)
        if nonce in self.nonces_usados:
            return construir_mensagem({"erro": "Nonce repetido, possível replay attack."}, self.shared_key)
        self.nonces_usados.add(nonce)

        comando_txt = dados.get("comando", "").strip()
        print(f"[{self.id}] Cliente {self.pseudonym}>> '{comando_txt}'")
        timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        comando_log_path = os.path.join("data", "logs", f"{self.pseudonym}_{timestamp}.log")
        os.makedirs(os.path.dirname(comando_log_path), exist_ok=True)
        with open(comando_log_path, "a") as log_file:
            json.dump(dados, log_file)
            log_file.write("\n")

        resposta = executar_comando(dados, self.pseudonym, ServerWorker.utilizadores[self.pseudonym]["certificado"])
        if isinstance(resposta, dict):
            resposta_dict = resposta
        else:
            resposta_dict = {"resposta": resposta}

        return construir_mensagem(resposta_dict, self.shared_key)

async def handle_echo(reader, writer):
    global conn_cnt
    conn_cnt += 1
    addr = writer.get_extra_info('peername')
    srvwrk = ServerWorker(conn_cnt, addr)

    # Carregar certificado do servidor e chave privada
    with open(sys.argv[1], "rb") as f:
        p12_data = f.read()
    private_key, certificate, _ = load_key_and_certificates(p12_data, b"")

    parameters = get_dh_parameters()
    server_private_key = parameters.generate_private_key()
    server_public_key = server_private_key.public_key()

    # Receber g^x do cliente
    client_gx_bytes = await reader.read(max_msg_size)
    client_gx = int.from_bytes(client_gx_bytes, byteorder='big')

    # Gerar g^y e chave partilhada
    server_gy = server_public_key.public_numbers().y
    shared_key = server_private_key.exchange(
        dh.DHPublicNumbers(client_gx, parameters.parameter_numbers()).public_key()
    )
    srvwrk.shared_key = shared_key[:32]

    print(f"[{srvwrk.id}] Shared DH key established")

    # Assinar (g^x||g^y) e enviar (g^y, assinatura, certificado)
    gx_gy_pair = concat_dh_values(client_gx, server_gy)
    signature = assinar(gx_gy_pair, private_key, b64=False)
    nonce, encrypted_signature = aes_encrypt(srvwrk.shared_key, signature)

    writer.write(server_gy.to_bytes(256, 'big'))
    cert_bytes = certificate.public_bytes(serialization.Encoding.PEM)
    writer.write(nonce)
    writer.write(encrypted_signature)
    writer.write(len(cert_bytes).to_bytes(4, 'big'))
    writer.write(cert_bytes)
    await writer.drain()

    # Receber resposta do cliente (assinatura, certificado do cliente)
    client_nonce = await reader.read(16)
    client_encrypted_sig = await reader.read(256)
    client_cert_len_bytes = await reader.read(4)
    client_cert_len = int.from_bytes(client_cert_len_bytes, 'big')
    client_cert_bytes = await reader.read(client_cert_len)
    client_cert = load_pem_x509_certificate(client_cert_bytes)

    if not validar_certificado(client_cert):
        print(f"[{srvwrk.id}] Certificado do cliente inválido (não assinado pela CA).")
        writer.close()
        return
    print(f"[{srvwrk.id}] Certificado do cliente validado pela CA.")

    client_public_key = client_cert.public_key()
    try:
        client_signature = aes_decrypt(srvwrk.shared_key, client_nonce, client_encrypted_sig)
    except Exception:
        print(f"[{srvwrk.id}] Erro ao desencriptar a assinatura do cliente.")
        writer.close()
        return

    if not verificar(gx_gy_pair, client_signature, client_public_key, b64=False):
        print(f"[{srvwrk.id}] Assinatura do cliente inválida.")
        writer.close()
        return

    pseudonym, cn_attr, ou_attr = extract_cert_fields(client_cert)
    if not pseudonym or not ou_attr or ou_attr != "SSI VAULT SERVICE":
        print(f"[{srvwrk.id}] Certificado inválido: OU ou PSEUDONYM incorretos.")
        writer.close()
        return

    nome_completo = cn_attr if cn_attr else pseudonym
    srvwrk.pseudonym = pseudonym

    # Registra ou atualizar utilizador
    if pseudonym not in ServerWorker.utilizadores:
        ServerWorker.utilizadores[pseudonym] = {
            "id": srvwrk.id,
            "nome": nome_completo,
            "certificado": client_cert,
            "shared_key": srvwrk.shared_key,
            "comandos": []
        }
        certs_dir = os.path.join("data", "certificados")
        os.makedirs(certs_dir, exist_ok=True)
        cert_path = os.path.join(certs_dir, f"{pseudonym}.crt")
        with open(cert_path, "wb") as cert_file:
            cert_file.write(client_cert.public_bytes(serialization.Encoding.PEM))
        print(f"[{srvwrk.id}] Utilizador registado como '{pseudonym}' ({nome_completo})")
    else:
        ServerWorker.utilizadores[pseudonym]["certificado"] = client_cert
        ServerWorker.utilizadores[pseudonym]["shared_key"] = srvwrk.shared_key
        print(f"[{srvwrk.id}] Login efetuado como '{pseudonym}' ({nome_completo})")

    # Servir comandos
    msg_inicial = {"resposta": "[Conexão segura]\n Introduzir comandos:"}
    encrypted = construir_mensagem(msg_inicial, srvwrk.shared_key)
    writer.write(encrypted)
    await writer.drain()
    data = await reader.read(max_msg_size)
    while True:
        if not data:
            break
        data = srvwrk.process(data)
        if not data:
            break
        writer.write(data)
        await writer.drain()
        data = await reader.read(max_msg_size)

    print(f"[{srvwrk.id}] Connection closed")
    writer.close()

def run_server():
    loop = asyncio.get_event_loop()
    if len(sys.argv) > 2:
        ServerWorker.carregar_estado(sys.argv[2])
    coro = asyncio.start_server(handle_echo, '127.0.0.1', conn_port)
    server = loop.run_until_complete(coro)
    print(f'Serving on {server.sockets[0].getsockname()}')
    print('(type ^C to finish)\n')
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        pass
    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()
    resposta = input("[INFO] Deseja guardar o estado? (s/n) ")
    if resposta.lower() == 's':
        ServerWorker.guardar_estado("data")
        print("[INFO] Estado guardado em data")
    print('\nFINISHED!')

if __name__ == "__main__":
    run_server()