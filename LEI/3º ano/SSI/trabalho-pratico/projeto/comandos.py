import os
import base64
import uuid
from base64 import b64decode, b64encode
from protocolo import *
from utils import *
from cryptography.hazmat.primitives import serialization
from Server import ServerWorker
from cryptography.x509 import load_pem_x509_certificate
from utils import validar_certificado

ficheiros = {}
cofres = {
    "users": {},
    "groups": {}
}
grupos = {}

def executar_comando(dados: dict, utilizador_id: str, certificado_cliente=None) -> dict:
    comando_raw = dados.get("comando", "").strip()
    assinatura = dados.get("assinatura", None)
    partes = comando_raw.split()
    if not partes:
        return {"erro": "Comando vazio."}

    comando = partes[0].lower()
    argumentos = partes[1:]

    comandos_criticos = {"add", "delete", "replace", "share", "revoke", "sharekey"}
    if comando in comandos_criticos:
        if not assinatura:
            return {"erro": f"O comando '{comando}' requer uma assinatura."}
        cert_path = os.path.join("data", "certificados", f"{utilizador_id}.crt")
        if not os.path.exists(cert_path):
            return {"erro": "Certificado do utilizador não encontrado para validação com a CA."}
        with open(cert_path, "rb") as f:
            cert_bytes = f.read()
        try:
            cert = load_pem_x509_certificate(cert_bytes)
        except Exception:
            return {"erro": "Certificado inválido ou corrompido."}
        if not validar_certificado(cert):
            return {"erro": "Certificado não validado pela CA."}
        chave_publica = cert.public_key()
        dados_para_verificar = {"comando": comando_raw}
        if not verificar(dados_para_verificar, assinatura, chave_publica):
            return {"erro": f"Assinatura inválida para o comando '{comando}'."}

    if comando == "add":
        return comando_add(argumentos, utilizador_id, dados)
    elif comando == "list":
        return comando_list(argumentos, utilizador_id)
    elif comando == "read":
        return comando_read(argumentos, utilizador_id)
    elif comando == "share":
        return comando_share(argumentos, utilizador_id)
    elif comando == "delete":
        return comando_delete(argumentos, utilizador_id)
    elif comando == "replace":
        return comando_replace(argumentos, utilizador_id, dados)
    elif comando == "details":
        return comando_details(argumentos, utilizador_id)
    elif comando == "revoke":
        return comando_revoke(argumentos, utilizador_id)
    elif comando == "sharekey":
        return comando_share_key(argumentos, utilizador_id, dados)
    elif comando == "getkey":
        return comando_getkey(argumentos, utilizador_id)
    elif comando == "group":
        if not argumentos:
            return {"erro": "Missing subcommand for group."}
        sub = argumentos[0].lower()
        args = argumentos[1:]
        if sub == "create":
            return comando_group_create(args, utilizador_id)
        elif sub == "delete":
            return comando_group_delete(args, utilizador_id)
        elif sub == "add-user":
            return comando_group_add_user(args, utilizador_id)
        elif sub == "delete-user":
            return comando_group_delete_user(args, utilizador_id)
        elif sub == "list":
            return comando_group_list(args, utilizador_id)
        elif sub == "add":
            return comando_group_add(args, utilizador_id, dados)
        elif sub == "members":
            # Subcomando especial: retorna membros do grupo e respetivos certificados
            if len(args) < 1:
                return {"erro": "Uso: group members <group-id>"}
            gid = args[0]
            g = grupos.get(gid)
            if not g:
                return {"erro": f"Group {gid} not found."}
            members = list(g["members"].keys())
            certs = {}
            for membro in members:
                cert_path = os.path.join("data", "certificados", f"{membro}.crt")
                if os.path.exists(cert_path):
                    with open(cert_path, "rb") as f:
                        cert_bytes = f.read()
                    certs[membro] = b64encode(cert_bytes).decode()
                else:
                    # Certificado não encontrado: ignora ou retorna erro?
                    certs[membro] = None
            return {"group_members": members, "certs": certs}
        else:
            return {"erro": f"Unknown group subcommand: {sub}"}
    else:
        return {"erro": f"Comando desconhecido: {comando_raw}"}


def comando_getkey(args, user):
    if len(args) != 1:
        return {"erro": "Uso: getkey <file-id>"}
    fid = args[0]
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"Ficheiro '{fid}' não encontrado."}
    if user not in entry.get("envelopes", {}):
        return {"erro": "Sem envelope disponível para o utilizador."}
    envelope = entry["envelopes"][user]
    return {
        "envelope_key": b64encode(envelope).decode(),
        "nome": entry["nome"]
    }

def comando_add(argumentos: list, utilizador_id: str, dados: dict) -> dict:
    if not argumentos:
        return {"erro": "Falta o nome do ficheiro (ex: add ficheiro.txt)"}
    nome_ficheiro = argumentos[0]
    info_ficheiro = dados.get("ficheiro")
    if not info_ficheiro:
        return {"erro": "Falta a informação do ficheiro."}

    file_id = str(uuid.uuid4())
    dados_ficheiro = b64decode(info_ficheiro["dados"])
    envelope_key = b64decode(info_ficheiro["envelope_key"])

    base_dir = os.path.join("data/users", utilizador_id)
    os.makedirs(base_dir, exist_ok=True)
    file_path = os.path.join(base_dir, f"{file_id}.blob")
    with open(file_path, "wb") as f:
        f.write(dados_ficheiro)
    print(f"[DEBUG] Ficheiro gravado em disco: {file_path}")

    ficheiros[file_id] = {
        "nome": info_ficheiro["nome"],
        "dono": utilizador_id,
        "envelopes": {utilizador_id: envelope_key},
        "permissoes": {utilizador_id: "RW"},
        "path": file_path
    }
    cofres["users"].setdefault(utilizador_id, {"ficheiros": []})["ficheiros"].append(file_id)
    return {"resultado": f"Ficheiro '{nome_ficheiro}' armazenado com ID: {file_id}"}

def comando_list(args, user):
    if not args:
        target = user
    elif args[0] == "-u" and len(args) == 2:
        target = args[1]
    elif args[0] == "-g" and len(args) == 2:
        target = args[1]
    else:
        return {"erro": "Uso: list [-u user-id | -g group-id]"}
    tipo = "groups" if target in grupos else "users"
    result = []
    if tipo == "users":
        user_data = cofres[tipo].get(target, {})
        result.append("== Ficheiros próprios ==")
        for fid in user_data.get("ficheiros", []):
            result.append(f"- {fid}")
        result.append("== Ficheiros partilhados ==")
        for fid, origem in user_data.get("ficheirosDeTerceiros", {}).items():
            result.append(f"- {fid} (partilhado por {origem})")
        result.append("== Ficheiros de grupos ==")
        for gid, ginfo in grupos.items():
            if target in ginfo["members"]:
                for fid, fdata in ficheiros.items():
                    if fdata["dono"] == gid:
                        result.append(f"- {fid} (grupo {gid})")
    else:
        result = cofres[tipo].get(target, {}).get("ficheiros", [])
    return {"ficheiros": result}

def comando_read(argumentos: list, utilizador_id: str) -> dict:
    if not argumentos:
        return {"erro": "Falta o ID do ficheiro (ex: read <file-id>)"}
    file_id = argumentos[0]
    if file_id not in ficheiros:
        return {"erro": f"Ficheiro com ID '{file_id}' não encontrado."}
    entry = ficheiros[file_id]
    perm = entry["permissoes"].get(utilizador_id)
    if perm not in ("R", "RW"):
        return {"erro": "Sem permissão de leitura para este ficheiro."}
    if utilizador_id not in entry.get("envelopes", {}):
        return {"erro": "Chave de envelope em falta para o utilizador."}
    with open(entry["path"], "rb") as f:
        conteudo = f.read()
    return {
        "ficheiro": {
            "nome": entry["nome"],
            "dados": b64encode(conteudo).decode(),
            "envelope_key": b64encode(entry["envelopes"][utilizador_id]).decode()
        }
    }

def comando_share(args, user):
    if len(args) != 3:
        return {"erro": "Uso: share <file-id> <user-id> <perm>."}
    fid, target, perm = args
    perm = perm.upper()
    if perm not in ("R","RW"):
        return {"erro": "Permission must be 'R' or 'RW'."}
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"File '{fid}' not found."}
    dono = entry["dono"]
    # impedir partilha de ficheiros de grupos
    if dono in grupos:
        return {"erro": "Não é permitido partilhar ficheiros de grupos."}
    #  so dono do ficheiro pode partilhar
    if dono != user and not (dono in grupos and grupos[dono]["creator"] == user):
        return {"erro": "Sem permissão para partilhar este ficheiro."}
    # o utilizador destino existe ou tenta carregar certificado
    if target in ServerWorker.utilizadores:
        target_cert = ServerWorker.utilizadores[target].get("certificado")
    else:
        cert_path = os.path.join("data", "certificados", f"{target}.crt")
        if os.path.exists(cert_path):
            with open(cert_path, "rb") as f:
                cert_bytes = f.read()
            try:
                target_cert = load_pem_x509_certificate(cert_bytes)
            except Exception:
                return {"erro": f"Certificado do utilizador '{target}' está corrompido."}
        else:
            return {"erro": f"Utilizador '{target}' não encontrado."}
    if not target_cert:
        return {"erro": "Certificado do destino não disponível."}
    cert_bytes = target_cert.public_bytes(serialization.Encoding.PEM)
    cert_b64 = b64encode(cert_bytes).decode()
    owner_key = entry.get("envelopes", {}).get(user)
    if not owner_key:
        return {"erro": "Envelope de chave do ficheiro não encontrado."}
    return {"share": {
        "file_id": fid,
        "nome": entry["nome"],
        "envelope": b64encode(owner_key).decode(),
        "cert_dest": cert_b64,
        "target": target,
        "perm": perm
    }}

def comando_share_key(args, user, dados):
    if len(args) != 3:
        return {"erro": "Uso: sharekey <file-id> <user-id> <perm>."}
    fid, target, perm = args
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"File '{fid}' not found."}
    dono = entry["dono"]
    # so o dono do ficheiro
    if dono != user and not (dono in grupos and grupos[dono]["creator"] == user):
        return {"erro": "Sem permissão para partilhar este ficheiro."}
    envelope_b64 = dados.get("envelope_key")
    if not envelope_b64:
        return {"erro": "Envelope key ausente no comando shareKey."}
    env = b64decode(envelope_b64)
    entry["permissoes"][target] = perm
    cofres["users"].setdefault(target, {"ficheiros": [], "ficheirosDeTerceiros": {}})
    cofres["users"][target]["ficheirosDeTerceiros"][fid] = user
    if "envelopes" not in entry:
        entry["envelopes"] = {}
    entry["envelopes"][target] = env
    return {"resultado": f"File {fid} shared with {target} ({perm})."}

def comando_delete(args, user):
    if len(args) != 1:
        return {"erro": "Uso: delete <file-id>"}
    fid = args[0]
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"File '{fid}' not found."}
    dono = entry["dono"]
    # so dono
    if dono == user or (dono in grupos and grupos[dono]["creator"] == user):
        try:
            os.remove(entry["path"])
        except OSError:
            pass
        del ficheiros[fid]
        for u in list(cofres["users"]):
            if fid in cofres["users"][u].get("ficheiros", []):
                cofres["users"][u]["ficheiros"].remove(fid)
        # limpa dos ficheirosDeTerceiros de cada utilizador
        for u in list(cofres["users"]):
            user_cofre = cofres["users"][u]
            if fid in user_cofre.get("ficheirosDeTerceiros", {}):
                del user_cofre["ficheirosDeTerceiros"][fid]
        for g in list(cofres["groups"]):
            if fid in cofres["groups"][g].get("ficheiros", []):
                cofres["groups"][g]["ficheiros"].remove(fid)
        return {"resultado": f"File {fid} removed from the system."}
    else:
        return {"erro": "nao tem permissão para apagar este ficheiro."}

def comando_replace(args, user, dados):
    if len(args) != 2:
        return {"erro": "Uso: replace <file-id> <file-path>"}
    fid = args[0]
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"File '{fid}' not found."}
    perm = entry["permissoes"].get(user)
    if perm != "RW":
        return {"erro": " sem permissão de escrita para este ficheiro."}
    ficheiro_info = dados.get("ficheiro")
    if not ficheiro_info or "dados" not in ficheiro_info:
        return {"erro": "Dados cifrados do ficheiro em falta."}
    dados_ficheiro = b64decode(ficheiro_info["dados"])
    # escreve o novo conteúdo cifrado no ficheiro
    with open(entry["path"], "wb") as f:
        f.write(dados_ficheiro)
    # n substituir envelopes - reutilizar o existente
    return {"resultado": f"File {fid} replaced successfully."}

def comando_details(args, user):
    if len(args) != 1:
        return {"erro": "Uso: details <file-id>"}
    fid = args[0]
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"File '{fid}' not found."}
    if user not in entry["permissoes"]:
        return {"erro": "sem permissão para ver detalhes."}
    return {
        "nome": entry["nome"],
        "dono": entry["dono"],
        "permissoes": entry["permissoes"]
    }

def comando_revoke(args, user):
    if len(args) != 2:
        return {"erro": "Uso: revoke <file-id> <user-id>"}
    fid, target = args
    entry = ficheiros.get(fid)
    if not entry:
        return {"erro": f"File '{fid}' not found"}
    dono = entry["dono"]
    if dono != user and not (dono in grupos and grupos[dono]["creator"] == user):
        return {"erro": "Sem permissão para revogar este ficheiro."}
    entry["permissoes"].pop(target, None)
    if fid in cofres["users"].get(target, {}).get("ficheiros", []):
        cofres["users"][target]["ficheiros"].remove(fid)
    if "envelopes" in entry:
        entry["envelopes"].pop(target, None)
    if fid in cofres["users"].get(target, {}).get("ficheirosDeTerceiros", {}):
        del cofres["users"][target]["ficheirosDeTerceiros"][fid]
    return {"resultado": f"Permissions of {target} on {fid} have been revoked."}

def comando_group_create(args, user_id):
    if not args:
        return {"erro": "Missing the group name."}
    name = " ".join(args)
    group_id = str(uuid.uuid4())
    grupos[group_id] = {
        "name": name,
        "creator": user_id,
        "members": {user_id: "RW"}
    }
    return {"resultado": f"Group '{name}' created with ID {group_id}"}

def comando_group_delete(args, user_id):
    if not args:
        return {"erro": "Falta o ID do grupo."}
    gid = args[0]
    g = grupos.get(gid)
    if not g:
        return {"erro": f"Group {gid} not found."}
    if g["creator"] != user_id:
        return {"erro": "Only the group creator can delete this group."}
    # remover todos os ficheiros do grupo
    to_remove = [fid for fid,v in ficheiros.items() if v["dono"] == gid]
    for fid in to_remove:
        try:
            os.remove(ficheiros[fid]["path"])
        except OSError:
            pass
        del ficheiros[fid]
    del grupos[gid]
    return {"resultado": f"Group {gid} deleted."}

def comando_group_add_user(args, user_id):
    if len(args) < 3:
        return {"erro": "Uso: group add-user <group-id> <user-id> <perm>."}
    gid, target, perm = args[0], args[1], args[2].upper()
    if perm not in ("R","RW"):
        return {"erro": "Permission must be 'R' or 'RW'."}
    g = grupos.get(gid)
    if not g:
        return {"erro": f"Group {gid} not found."}
    if g["creator"] != user_id:
        return {"erro": "Only the group creator can add members."}
    g["members"][target] = perm

    for fid, fdata in ficheiros.items():
        if fdata["dono"] == gid:
            fdata["permissoes"][target] = perm
            envelope = fdata["envelopes"].get(g["creator"])
            if envelope:
                fdata["envelopes"][target] = envelope
    return {"resultado": f"User {target} added to group {gid} with permission {perm}."}

def comando_group_delete_user(args, user_id):
    if len(args) < 2:
        return {"erro": "Uso: group delete-user <group-id> <user-id>."}
    gid, target = args[0], args[1]
    g = grupos.get(gid)
    if not g:
        return {"erro": f"Group {gid} not found."}
    if g["creator"] != user_id:
        return {"erro": "Only the group creator can remove members."}
    if target not in g["members"]:
        return {"erro": f"User {target} is not in group {gid}."}
    del g["members"][target]
    for fid, v in ficheiros.items():
        if v["dono"] == gid and target in v["permissoes"]:
            del v["permissoes"][target]
    return {"resultado": f"User {target} removed from group {gid}."}

def comando_group_list(args, user_id):
    result = []
    for gid, g in grupos.items():
        if user_id == g["creator"] or user_id in g["members"]:
            perm = g["members"].get(user_id, "RW" if g["creator"]==user_id else None)
            result.append(f"{gid} ({g['name']}): {perm}")
    return {"groups": result}

def comando_group_add(args, user_id, dados):
    if len(args) < 2:
        return {"erro": "Uso: group add <group-id> <file-path>."}
    gid, path = args[0], args[1]
    g = grupos.get(gid)
    if not g:
        return {"erro": f"Group {gid} not found."}
    perm = g["members"].get(user_id)
    if perm != "RW":
        return {"erro": "No write permission in this group."}

    ficheiro_info = dados.get("ficheiro")
    if not ficheiro_info:
        return {"erro": "Missing file data."}

    envelopes_info = ficheiro_info.get("envelopes")
    if not envelopes_info or not isinstance(envelopes_info, dict):
        return {"erro": "Missing or invalid envelopes dictionary."}

    file_id = str(uuid.uuid4())
    blob = b64decode(ficheiro_info["dados"])

    base = os.path.join("data/users", gid)
    os.makedirs(base, exist_ok=True)
    fpath = os.path.join(base, f"{file_id}.blob")
    with open(fpath, "wb") as f:
        f.write(blob)

     #aceita envelopes apenas para membros atuais do grupo
    envelopes = {
        uid: b64decode(env)
        for uid, env in envelopes_info.items()
        if uid in g["members"]
    }

    ficheiros[file_id] = {
        "nome": ficheiro_info["nome"],
        "dono": gid,
        "envelopes": envelopes,
        "permissoes": g["members"].copy(),
        "path": fpath
    }

    cofres["groups"].setdefault(gid, {"ficheiros": []})["ficheiros"].append(file_id)
    return {"resultado": f"File added to group {gid} with ID {file_id}."}