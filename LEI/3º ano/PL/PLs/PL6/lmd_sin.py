import ply.yacc as yacc
from lmd_lex import tokens

def p_gramatical(p):
    """
    Documento : PA DOC Lista PF
    Lista : Elem Lista
            | Elem
    Elem : PA TIT STRING PF
            | PA SUBTIT STRING PF
            | STRING
    """



def p_error(p):
    print('erro sintatico ', p)
    parser.success = False

parser = yacc.yacc()

import sys
texto = sys.stdin.read()
parser.sucess = True
parser.parse(texto)
if parser.success:
        print("frase válida", texto)
else:
        print("frase inválida")