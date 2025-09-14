import json
import os
import sys
import ply.lex as lex
from datetime import datetime

# Definindo os tokens
tokens = [
    'CMD',   
    'PCODE', 
    'COIN',  
    'FLOAT', 
    'NUM',   
    'COMMA', 
    'DOT'    
]



def t_CMD(t):
    r'(LISTAR|MOEDA|SELECIONAR|SAIR|ADICIONAR|REMOVER)'
    t.value = t.value.upper()  # Força a conversão para maiúsculas
    return t


def t_PCODE(t):
    r'[A-Z]\d{1,2}'
    return t

# Token para moedas: reconhece valores como 2e, 1e, 50c, 20c, 10c, 5c
def t_COIN(t):
    r'(2e|1e|50c|20c|10c|5c)'
    t.value = t.value.lower()  # Força a conversão para minúsculas
    return t


# Token para números com ponto (preços)
def t_FLOAT(t):
    r'\d+\.\d+'
    t.value = float(t.value)
    return t

# Token para números inteiros (quantidades)
def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

# Outros tokens simples
t_COMMA = r','
t_DOT = r'\.'

t_ignore = ' \t'

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_error(t):
    print("Token inválido:", t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()

# Funções para carregar e salvar o stock de produtos
STOCK_FILE = "stock.json"

def load_stock():
    if os.path.exists(STOCK_FILE):
        with open(STOCK_FILE, 'r', encoding='utf-8') as f:
            return json.load(f)
    else:
        return []

def save_stock(stock):
    with open(STOCK_FILE, 'w', encoding='utf-8') as f:
        json.dump(stock, f, indent=4)

def display_stock(stock):
    print("Stock carregado, Estado atualizado.")
    print("Bom dia. Estou disponível para atender o seu pedido.")
    print()
    print("cod    | nome                 | quantidade | preço")
    print("----------------------------------------------")
    for prod in stock:
        print(f"{prod['cod']:<7} | {prod['nome']:<20} | {prod['quant']:<5} | {prod['preco']}€")

# Dicionário de valores das moedas (em cêntimos)
COIN_VALUES = {
    '1e': 100,
    '2e': 200,
    '50c': 50,
    '20c': 20,
    '10c': 10,
    '5c': 5
}

def coin_value(coin):
    return COIN_VALUES.get(coin, 0)

def compute_change(balance):
    change = {}
    for coin, value in sorted(COIN_VALUES.items(), key=lambda x: -x[1]):
        if balance >= value:
            count = balance // value
            balance %= value
            change[coin] = count
    return change

def print_maq_message(message, include_date=False):
    if include_date:
        current_time = datetime.now().strftime("%Y-%m-%d")
        print(f"maq: {current_time}, {message}")
    else:
        print("maq: " + message)

def process_command(token_list, stock, balance):
    if not token_list:
        return balance
    first = token_list[0]
    if first.type != "CMD":
        print_maq_message("Comando inválido.")
        return balance

    cmd = first.value

    if cmd == "LISTAR":
        display_stock(stock)

    elif cmd == "MOEDA":
        for tok in token_list[1:]:
            if tok.type == "COIN":
                balance += coin_value(tok.value)
        print_maq_message(f"Saldo = {balance // 100}e{balance % 100:02d}c")

    elif cmd == "SELECIONAR":
        if len(token_list) < 2 or token_list[1].type != "PCODE":
            print_maq_message("Indique o código do produto")
            return balance
        pcode = token_list[1].value
        product = next((p for p in stock if p["cod"] == pcode), None)
        if product is None:
            print_maq_message("Produto não encontrado.")
        elif product["quant"] <= 0:
            print_maq_message("Produto esgotado.")
        else:
            price_cents = int(round(product["preco"] * 100))
            if balance < price_cents:
                print_maq_message(f"Saldo insuficiente para satisfazer o seu pedido")
                print_maq_message(f"Saldo = {balance // 100}e{balance % 100:02d}c; Pedido = {price_cents // 100}e{price_cents % 100:02d}c")
            else:
                product["quant"] -= 1
                balance -= price_cents
                print_maq_message(f"Pode retirar o produto dispensado \"{product['nome']}\"")
                print_maq_message(f"Saldo = {balance // 100}e{balance % 100:02d}c")

    elif cmd == "ADICIONAR":
        if len(token_list) < 3 or token_list[1].type != "PCODE" or token_list[2].type != "NUM":
            print_maq_message("Uso: ADICIONAR <Código> <Quantidade> [Preço]")
            return balance
        pcode = token_list[1].value
        quantity = token_list[2].value
        price = None
        if len(token_list) >= 4 and token_list[3].type in ("FLOAT", "NUM"):
            price = float(token_list[3].value)
        product = next((p for p in stock if p["cod"] == pcode), None)
        if product:
            product["quant"] += quantity
            if price is not None:
                product["preco"] = price
            print_maq_message(f"Produto {product['nome']} atualizado: nova quantidade {product['quant']} e preço {product['preco']}€")
        else:
            name = input("Nome do novo produto: ").strip()
            if price is None:
                price = float(input("Preço do novo produto: "))
            new_product = {"cod": pcode, "nome": name, "quant": quantity, "preco": price}
            stock.append(new_product)
            print_maq_message(f"Produto '{name}' adicionado ao stock.")
        save_stock(stock)

    elif cmd == "REMOVER":
        if len(token_list) < 2 or token_list[1].type != "PCODE":
            print_maq_message("Uso: REMOVER <Código>")
            return balance
        pcode = token_list[1].value
        new_stock = [p for p in stock if p["cod"] != pcode]
        if len(new_stock) == len(stock):
            print_maq_message("Produto não encontrado.")
        else:
            stock[:] = new_stock
            print_maq_message(f"Produto {pcode} removido do stock.")
        save_stock(stock)

    elif cmd == "SAIR":
        save_stock(stock)
        troco = compute_change(balance)
        if troco:
            troco_str = ", ".join(f"{cnt}x {coin}" for coin, cnt in troco.items())
            print_maq_message(f"Pode retirar o troco: {troco_str}.")
        print_maq_message("Até à próxima")
        sys.exit(0)
    else:
        print_maq_message("Comando desconhecido.")

    return balance

def main():
    stock = load_stock()
    balance = 0
    print_maq_message("Stock carregado, Estado atualizado.", include_date=True)
    while True:
        try:
            line = input(">> ")
        except EOFError:
            break
        if not line.strip():
            continue
        lexer.input(line)
        token_list = list(lexer)
        balance = process_command(token_list, stock, balance)
        save_stock(stock)

if __name__ == "__main__":
    main()
