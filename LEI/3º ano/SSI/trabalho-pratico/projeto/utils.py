from cryptography.hazmat.primitives import serialization
import os
import json
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import dh
from cryptography.x509 import load_pem_x509_certificate

def save_json(path, data):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        json.dump(data, f, indent=2)

def load_json(path):
    if os.path.exists(path):
        with open(path, 'r') as f:
            return json.load(f)
    return None

def extract_cert_fields(cert):
    subject = cert.subject
    def get(oid):
        attrs = subject.get_attributes_for_oid(oid)
        return attrs[0].value if attrs else None
    return (
        get(NameOID.PSEUDONYM),
        get(NameOID.COMMON_NAME),
        get(NameOID.ORGANIZATIONAL_UNIT_NAME)
    )

def get_dh_parameters():
    # Parâmetros Diffie-Hellman estáticos (2048-bit MODP Group)
    p_hex = (
        "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD1"
        "29024E088A67CC74020BBEA63B139B22514A08798E3404DD"
        "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245"
        "E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
        "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE65381"
        "FFFFFFFFFFFFFFFF"
    )
    p = int(p_hex, 16)
    g = 2
    return dh.DHParameterNumbers(p, g).parameters()

def aes_encrypt(key, plaintext):
    nonce = os.urandom(16)
    cipher = Cipher(algorithms.AES(key), modes.CFB(nonce))
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(plaintext) + encryptor.finalize()
    return nonce, ciphertext

def aes_decrypt(key, nonce, ciphertext):
    cipher = Cipher(algorithms.AES(key), modes.CFB(nonce))
    decryptor = cipher.decryptor()
    return decryptor.update(ciphertext) + decryptor.finalize()

def validar_certificado(cert, caminho_ca="../projCA/VAULT_CA.crt"):
    with open(caminho_ca, "rb") as f:
        ca_cert = load_pem_x509_certificate(f.read())
    ca_public_key = ca_cert.public_key()
    try:
        ca_public_key.verify(
            cert.signature,
            cert.tbs_certificate_bytes,
            padding.PKCS1v15(),
            cert.signature_hash_algorithm,
        )
        return True
    except Exception:
        return False

def concat_dh_values(gx: int, gy: int) -> bytes:
    return gx.to_bytes(256, 'big') + gy.to_bytes(256, 'big')

def key_envelop(file_key, chave_publica):
    return chave_publica.encrypt(
        file_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )