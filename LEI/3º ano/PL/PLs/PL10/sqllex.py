""" 
SQuery -> Query num Cabecalho Conteudo
Query -> SELECT colunas From Tabela
Colunas -> '*'
        | ListaColunas

ListaColunas -> ListaColunas ',' coluna
        | coluna

Coluna -> ListaIDs
ListaIDs -> ListaIDs iD
        | iD

Conteudo


"""

import sys
import ply.lex as lex

states = [('IDS', 'exclusive'), ('LINHAS', 'exclusive')]
literals = ['*', ',']
tokens = ['SELECT', 'FROM', 'tabela', 'colunaSTR', 'colunaNUM', 'id', 'num']


def t_SELECT(t):
        r'SELECT'
        return t
def t_FROM(t):
        r'FROM'
        return t
def t_id(t):
        r'a-zA-Z]\w*'
        return t

def t_LINHAS_colunaSTR(t):
        r'\'[a-zA-Z]\w*\''
        return t
def t_LINHAS_colunaNUM(t):
        r'\d+(\.\d+)?'
        return t
def t_IDS_id(t):
    r'[a-zA-Z]\w*'
    return t

def t_num(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_ANY_newline(t):
        r'\n+'
        t.lexer.linha += 1
        print(f'Linha: {t.lexer.linha}')
        if t.lexer.linha == 3:
                t.lexer.begin('IDS')
        elif t.lexer.linha == 4:
                t.lexer.begin('LINHAS')
        

t_ANY_ignore = ' \t'

def t_ANY_error(t):
        print(f"Illegal character '{t.value[0]}'")
        t.lexer.skip(1)

lexer = lex.lex()