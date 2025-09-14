import sys
from sqllex import states, literals, tokens

"""
SQUERY -> Query num ListaIds ListaLinhas
Query -> SELECT Colunas FROM if
Colunas -> '*' 
          | ListaColunas
ListaColunas -> ListaColunas ',' id
                | id
ListaIds -> ListaIds ',' id
            | id

ListaLinhas -> ListaLinhas coluna
            | coluna
Coluna -> ColunaNum
        | ColunaStr
"""

import ply.yacc as yacc
from sqllex import tokens, literals

def p_SQuery(p):
    "SQuery: Query num ListaIds ListaLinhas"

def p_Query(p):
    "Query: SELECT Colunas FROM id"
    
def p_Colunas(p):
    "Colunas: '*'"

def p_Colunas_ListaColunas(p):
    "Colunas: ListaColunas"

def p_ListaColunas(p):
    "ListaColunas: ListaColunas ',' id"

def p_ListaColunas_id(p):
    "ListaColunas: id"

def p_ListaIds(p):
    "ListaIds: ListaIds id"

def p_ListaIds_id(p):
    "ListaIds: id"

def p_ListaLinhas(p):
    "ListaLinhas: ListaLinhas ListaVal"

def p_ListaVal(p):
    "ListaVal: ListaVal coluna"

def p_ListaVal_coluna(p):
    "ListaVal: coluna"

def p_coluna_Num(p):
    "coluna: ColunaNum"
 
def p_coluna_Str(p):
    "coluna: ColunaStr"


def p_error(p):
    print(f"Syntax error at '{p.value}'")
    parse.success = False

parse = yacc.yacc(debug=True)
 

