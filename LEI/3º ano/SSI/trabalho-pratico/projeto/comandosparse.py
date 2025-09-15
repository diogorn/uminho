# Nova função: process_comando(client, msg)
import uuid
from base64 import b64decode, b64encode
from protocolo import *
from utils import *
from cryptography.x509 import load_pem_x509_certificate
from cryptography.hazmat.primitives.asymmetric import padding as asym_padding
import os
import sys

def process_comando(client, msg=b""):
    client.msg_cnt += 1
    if not msg:
        print("Mensagem inválida.")
        return None

    try:
        dados = interpretar_mensagem(msg, client.shared_key)
    except Exception as e:
        print(f"[CLIENT] Erro ao decifrar mensagem: {e}")
        return None

    if hasattr(client, "pending_group_add") and "group_members" in dados:
        info = client.pending_group_add
        gid = info["gid"]
        nome_ficheiro = info["nome_ficheiro"]
        file_key = info["file_key"]
        nonce_file = info["nonce_file"]
        dados_cifrados = info["dados_cifrados"]
        message = info["message"]
        del client.pending_group_add
        members = dados.get("group_members", [])
        certs_b64 = dados.get("certs", {})
        envelopes = {}
        for membro in members:
            cert_b64 = certs_b64.get(membro)
            if not cert_b64:
                print(f"[CLIENT] Certificado para membro '{membro}' não recebido.")
                return None
            try:
                cert_dest = load_pem_x509_certificate(b64decode(cert_b64))
            except Exception:
                print(f"[CLIENT] Certificado do membro '{membro}' está corrompido.")
                return None
            envelope = key_envelop(file_key, cert_dest.public_key())
            envelopes[membro] = b64encode(envelope).decode()
        ficheiro_info = {
            "nome": os.path.basename(nome_ficheiro),
            "dados": b64encode(nonce_file + dados_cifrados).decode(),
            "envelopes": envelopes
        }
        message["ficheiro"] = ficheiro_info
        return construir_mensagem(message, client.shared_key)

    # Verificar resposta de share (fase 1)
    if "share" in dados:
        info = dados["share"]
        envelope_b64 = info.get("envelope")
        cert_dest_b64 = info.get("cert_dest")
        target = info.get("target")
        perm = info.get("perm")
        file_id = info.get("file_id")
        if not envelope_b64 or not cert_dest_b64 or not target or not perm or not file_id:
            print("[CLIENT] Resposta partilha inválida.")
            return None
        envelope = b64decode(envelope_b64)
        try:
            file_key = client.private_key.decrypt(
                envelope,
                asym_padding.OAEP(
                    mgf=asym_padding.MGF1(hashes.SHA256()),
                    algorithm=hashes.SHA256(),
                    label=None
                )
            )
        except Exception as e:
            print(f"[CLIENT] Erro ao decifrar envelope do ficheiro: {e}")
            return None
        try:
            cert_dest = load_pem_x509_certificate(b64decode(cert_dest_b64))
        except Exception as e:
            print(f"[CLIENT] Erro ao carregar certificado do destinatário: {e}")
            return None
        dest_pub = cert_dest.public_key()
        new_envelope = key_envelop(file_key, dest_pub)
        new_env_b64 = b64encode(new_envelope).decode()
        share_cmd = f"sharekey {file_id} {target} {perm}"
        assinatura2 = assinar({"comando": share_cmd}, client.private_key)
        nonce2 = str(uuid.uuid4())
        msg2 = {
            "comando": share_cmd,
            "assinatura": assinatura2,
            "nonce": nonce2,
            "envelope_key": new_env_b64
        }
        return construir_mensagem(msg2, client.shared_key)

    # Após receber resposta do comando read interno, prossegue automaticamente com replace
    if "ficheiro" in dados and hasattr(client, "pending_replace"):
        info = dados["ficheiro"]
        envelope_b64 = info.get("envelope_key")
        envelope = b64decode(envelope_b64)
        try:
            file_key = client.private_key.decrypt(
                envelope,
                asym_padding.OAEP(
                    mgf=asym_padding.MGF1(hashes.SHA256()),
                    algorithm=hashes.SHA256(),
                    label=None
                )
            )
        except Exception as e:
            print(f"[CLIENT] Erro ao decifrar envelope para replace: {e}")
            del client.pending_replace
            return None

        caminho = client.pending_replace["caminho"]
        fid = client.pending_replace["fid"]
        del client.pending_replace

        try:
            with open(caminho, "rb") as f:
                conteudo = f.read()
        except FileNotFoundError:
            print(f"[CLIENT] Ficheiro '{caminho}' não encontrado.")
            return None

        nonce_file, dados_cifrados = aes_encrypt(file_key, conteudo)
        ficheiro_info = {
            "dados": b64encode(nonce_file + dados_cifrados).decode()
        }
        nonce_replace = str(uuid.uuid4())
        replace_cmd = f"replace {fid} {os.path.basename(caminho)}"
        assinatura_replace = assinar({"comando": replace_cmd}, client.private_key)
        msg_replace = {
            "comando": replace_cmd,
            "assinatura": assinatura_replace,
            "nonce": nonce_replace,
            "ficheiro": ficheiro_info
        }
        print("[CLIENT] 'replace' com chave original obtida.")
        return construir_mensagem(msg_replace, client.shared_key)

  
    if "ficheiro" in dados:
        info = dados["ficheiro"]
        envelope_b64 = info.get("envelope_key")
        if not envelope_b64:
            print("[CLIENT] Envelope key faltando.")
            return None
        envelope = b64decode(envelope_b64)
        try:
            file_key = client.private_key.decrypt(
                envelope,
                asym_padding.OAEP(
                    mgf=asym_padding.MGF1(hashes.SHA256()),
                    algorithm=hashes.SHA256(),
                    label=None
                )
            )
        except Exception as e:
            print(f"[CLIENT] Erro ao decifrar chave simétrica: {e}")
            return None
        data_enc = b64decode(info["dados"])
        nonce = data_enc[:16]
        ciphertext = data_enc[16:]
        plaintext = aes_decrypt(file_key, nonce, ciphertext)
        decoded_text = plaintext.decode(errors="ignore").splitlines()
        max_len = max(len(line) for line in decoded_text) if decoded_text else 0
        print(f"file name: {info['nome']}")
        print("|" + "-" * (max_len + 2) + "|")
        for line in decoded_text:
            print(f"| {line.ljust(max_len)} |")
        print("|" + "-" * (max_len + 2) + "|")
    else:
        if "ficheiros" in dados:
            arquivos = dados["ficheiros"]
            print("Ficheiros disponíveis:")
            for fid in arquivos:
                print(f"- {fid}")
        elif "groups" in dados:
            grupos = dados["groups"]
            print("Grupos disponíveis:")
            for g in grupos:
                print(f"- {g}")
        elif "nome" in dados and "dono" in dados and "permissoes" in dados:
            print("Detalhes do ficheiro:")
            print(f"- Nome: {dados['nome']}")
            print(f"- Dono: {dados['dono']}")
            print("- Permissões:")
            for user, p in dados["permissoes"].items():
                print(f"  {user}: {p}")
        else:
            resposta = dados.get("resposta") or dados.get("resultado") or dados.get("erro", "")
            print(f"Received ({client.msg_cnt}): {resposta}")

    # Ler próximo comando do utilizador
    comando = input(">> ").strip()
    if comando.lower() in ["exit"]:
        print("Sessão terminada.")
        sys.exit(0)

    parts = comando.split()
    cmd = parts[0].lower()
    nonce = str(uuid.uuid4())
    message = {"comando": comando, "nonce": nonce}
    # Adicionar assinatura se for comando critico
    if cmd in ["add", "delete", "replace", "share", "revoke", "sharekey"]:
        assinatura = assinar({"comando": comando}, client.private_key)
        message["assinatura"] = assinatura

    if cmd == "replace":
        if len(parts) < 3:
            print("[CLIENT] Uso: replace <file-id> <file-path>")
            return None
        fid = parts[1]
        caminho = parts[2]
        client.pending_replace = {"fid": fid, "caminho": caminho}
        read_cmd = f"read {fid}"
        nonce_read = str(uuid.uuid4())
        assinatura_read = assinar({"comando": read_cmd}, client.private_key)
        msg_read = {
            "comando": read_cmd,
            "assinatura": assinatura_read,
            "nonce": nonce_read
        }
        print("[DEBUG] A obter chave original com comando 'read' interno...")
        return construir_mensagem(msg_read, client.shared_key)

    if cmd == "group" and len(parts) >= 4 and parts[1] == "add":
        gid = parts[2]
        nome_ficheiro = parts[3]
        try:
            with open(nome_ficheiro, "rb") as f:
                conteudo = f.read()
        except FileNotFoundError:
            print(f"[CLIENT] Ficheiro '{nome_ficheiro}' não encontrado.")
            return None
        file_key = os.urandom(32)
        nonce_file, dados_cifrados = aes_encrypt(file_key, conteudo)
        nonce_gm = str(uuid.uuid4())
        get_membros_cmd = f"group members {gid}"
        msg_membros = {
            "comando": get_membros_cmd,
            "nonce": nonce_gm
        }
        client.pending_group_add = {
            "gid": gid,
            "nome_ficheiro": nome_ficheiro,
            "file_key": file_key,
            "nonce_file": nonce_file,
            "dados_cifrados": dados_cifrados,
            "message": message
        }
        return construir_mensagem(msg_membros, client.shared_key)

    if cmd == "add":
        if len(parts) < 2:
            print("[CLIENT] Uso: add <file-path>")
            return None
        nome_ficheiro = parts[1]
        try:
            with open(nome_ficheiro, "rb") as f:
                conteudo = f.read()
        except FileNotFoundError:
            print(f"[CLIENT] Ficheiro '{nome_ficheiro}' não encontrado.")
            return None
        file_key = os.urandom(32)
        nonce_file, dados_cifrados = aes_encrypt(file_key, conteudo)
        public_key = client.cert.public_key()
        envelope_key = key_envelop(file_key, public_key)
        ficheiro_info = {
            "nome": os.path.basename(nome_ficheiro),
            "dados": b64encode(nonce_file + dados_cifrados).decode(),
            "envelope_key": b64encode(envelope_key).decode()
        }
        message["ficheiro"] = ficheiro_info
        return construir_mensagem(message, client.shared_key)

    if cmd == "share":
        return construir_mensagem(message, client.shared_key)

    return construir_mensagem(message, client.shared_key)