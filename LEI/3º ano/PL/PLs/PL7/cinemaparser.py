import ply.yacc as yacc
from cinemalexer import tokens, literals


def p_Cinema(p):
    "Cinema : '[' Lista ']'"

def p_Lista_lista(p):
    "Lista : Lista ',' Filme"

def p_Lista_elem(p):
    "Lista : Filme"

def p_Filme(p):
    "Filme : '{' Titulo ',' Ano ',' Elenco ',' Generos '}'"
    p.parser.nfilmes += 1

def p_Titulo(p):
    "Titulo : TITTLE string"

def p_Ano(p):
    "Ano : YEAR num"

def p_Elenco(p):
    "Elenco : CAST '[' ListaAtor ']'"

def p_ListaAtor_lista(p):
    "ListaAtor : ListaAtor ',' string"

def p_ListaAtor_elem(p):
    "ListaAtor : string"

def p_Generos(p):
    "Generos : GENRES '[' ListaGeneros ']'"

def p_ListaGeneros_lista(p):
    "ListaGeneros : ListaGeneros ',' string"

def p_ListaGeneros_elem(p):
    "ListaGeneros : string"


def p_error(p):
    print('Erro sintatico: ', p)
    parser.success = False 


parser = yacc.yacc(debug=True)


import sys
texto = sys.stdin.read()
parser.success = True
parser.nfilmes = 0
parser.parse(texto)
if parser.success:
    print("frase válida")
    print("número de filmes: ", parser.nfilmes)
else:
    print("frase inválida")