import ply.yacc as yacc
from functools import reduce
from sexp_lex import tokens, literals

def p_Sexp(p):
    "Sexp : '(' Op Lista ')'"
    if p[2] == '+':
        p[0] = sum(p[3])
    else:
        p[0] = reduce(lambda x, y: x*y, p[3])
    print("Valor: ", p[0])

def p_Op_add(p):
    "Op : '+'"
    p[0] = '+'

def p_Op_mult(p):
    "Op : '*'"
    p[0] = '*'

def p_Lista_lista(p):
    "Lista : Lista Elem"
    p[0] = p[1] + [p[2]]

def p_Lista_elem(p):
    "Lista : Elem"
    p[0] = [p[1]]

def p_Elem_num(p):
    "Elem : num"
    p[0] = p[1]

def p_Elem_sexp(p):
    "Elem : Sexp"
    p[0] = p[1]


def p_error(p):
    print('Erro sintatico: ', p)
    parser.success = False 


parser = yacc.yacc(debug=True)


import sys
texto = sys.stdin.read()
parser.success = True
parser.parse(texto)
if parser.success:
    print("frase válida")
    print("número de filmes: ", parser.nfilmes)
else:
    print("frase inválida")