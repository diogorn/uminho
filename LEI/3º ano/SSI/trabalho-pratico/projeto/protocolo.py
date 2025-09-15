import json
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import base64
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
from utils import *

def construir_mensagem(dados: dict, chave: bytes) -> bytes:
    """
     Recebe um dicionário de dados e uma chave AES.
     Retorna a mensagem cifrada (nonce + ciphertext).
    """
    texto = json.dumps(dados).encode()
    nonce, ciphertext = aes_encrypt(chave, texto)
    return nonce + ciphertext

def interpretar_mensagem(mensagem: bytes, chave: bytes) -> dict:
    """
    Recebe uma mensagem cifrada (nonce + ciphertext) e a chave AES.
    Retorna o dicionário descifrado.
    """
    nonce = mensagem[:16]
    ciphertext = mensagem[16:]
    plaintext = aes_decrypt(chave, nonce, ciphertext)
    return json.loads(plaintext.decode())

# assinatura e verificação
def assinar(conteudo, chave_privada, b64=True):
    """
    Assina um conteúdo (bytes, str ou dict) com a chave privada.
    Retorna assinatura em base64 (default) ou bytes.
    """
    if isinstance(conteudo, dict):
        conteudo = json.dumps(conteudo, sort_keys=True).encode()
    elif isinstance(conteudo, str):
        conteudo = conteudo.encode()
    elif not isinstance(conteudo, bytes):
        raise TypeError("Conteúdo deve ser bytes, str ou dict.")

    assinatura = chave_privada.sign(
        conteudo,
        padding.PKCS1v15(),
        hashes.SHA256()
    )
    print("[DEBUG] Conteúdo assinado com sucesso.")
    return base64.b64encode(assinatura).decode() if b64 else assinatura

def verificar(conteudo, assinatura, chave_publica, b64=True):
    """
    Verifica a assinatura (em base64 ou bytes) de um conteúdo (bytes, str ou dict) com a chave pública.
    Retorna True se válida, False caso contrário.
    """
    if isinstance(conteudo, dict):
        conteudo = json.dumps(conteudo, sort_keys=True).encode()
    elif isinstance(conteudo, str):
        conteudo = conteudo.encode()
    elif not isinstance(conteudo, bytes):
        raise TypeError("Conteúdo deve ser bytes, str ou dict.")

    if b64:
        assinatura = base64.b64decode(assinatura)

    try:
        chave_publica.verify(
            assinatura,
            conteudo,
            padding.PKCS1v15(),
            hashes.SHA256()
        )
        print("[DEBUG] Assinatura verificada com sucesso.")
        return True
    except Exception:
        print("[DEBUG] Falha na verificação da assinatura.")
        return False