import asyncio
import os
import sys
from base64 import b64decode, b64encode
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding as asym_padding, dh
from cryptography.hazmat.primitives.serialization.pkcs12 import load_key_and_certificates
from cryptography.x509 import load_pem_x509_certificate
from protocolo import *
from utils import *
import uuid

conn_port = 7777
max_msg_size = 9999

from comandosparse import process_comando

class Client:
    def __init__(self, addr=None):
        self.addr = addr
        self.msg_cnt = 0
        self.shared_key = None
        self.private_key = None
        self.cert = None

async def tcp_echo_client():
    reader, writer = await asyncio.open_connection('127.0.0.1', conn_port)

    p12_path = sys.argv[1]
    with open(p12_path, "rb") as f:
        p12_data = f.read()
    private_key, certificate, _ = load_key_and_certificates(p12_data, b"")

    parameters = get_dh_parameters()
    client_private_key = parameters.generate_private_key()
    client_public_key = client_private_key.public_key()
    client_gx = client_public_key.public_numbers().y

    writer.write(client_gx.to_bytes(256, 'big'))
    await writer.drain()

    server_gy_bytes = await reader.read(256)
    nonce = await reader.read(16)
    encrypted_signature = await reader.read(256)
    cert_len_bytes = await reader.read(4)
    cert_len = int.from_bytes(cert_len_bytes, 'big')
    server_cert_bytes = await reader.read(cert_len)
    server_cert = load_pem_x509_certificate(server_cert_bytes)

    if not validar_certificado(server_cert):
        print("[CLIENT] Certificado do servidor inválido (não assinado pela CA).")
        writer.close()
        return
    print("[CLIENT] Certificado do servidor validado com sucesso pela CA.")

    server_gy = int.from_bytes(server_gy_bytes, 'big')
    shared_key = client_private_key.exchange(
        dh.DHPublicNumbers(server_gy, parameters.parameter_numbers()).public_key()
    )
    shared_key = shared_key[:32]

    print("[CLIENT] Shared DH key established")

    signature = aes_decrypt(shared_key, nonce, encrypted_signature)

    gx_gy_pair = client_gx.to_bytes(256, 'big') + server_gy_bytes
    server_public_key = server_cert.public_key()

    if not verificar(gx_gy_pair, signature, server_public_key, b64=False):
        writer.close()
        return

    signature = assinar(gx_gy_pair, private_key, b64=False)
    nonce, ciphertext = aes_encrypt(shared_key, signature)

    cert_bytes = certificate.public_bytes(serialization.Encoding.PEM)
    writer.write(nonce)
    writer.write(ciphertext)
    writer.write(len(cert_bytes).to_bytes(4, 'big'))
    writer.write(cert_bytes)
    await writer.drain()

    addr = writer.get_extra_info('peername')
    client = Client(addr)
    client.private_key = private_key
    client.shared_key = shared_key
    client.cert = certificate

    # apos a conexao, atribuir process do client para process_comando importado
    client.process = lambda msg: process_comando(client, msg)
    while True:
        msg = await reader.read(max_msg_size)
        if not msg:
            break
        response = client.process(msg)
        while response:
            writer.write(response)
            await writer.drain()
            msg = await reader.read(max_msg_size)
            if not msg:
                break
            response = client.process(msg)
    print('Socket closed!')
    writer.close()
    await writer.wait_closed()

def run_client():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(tcp_echo_client())

if __name__ == "__main__":
    run_client()