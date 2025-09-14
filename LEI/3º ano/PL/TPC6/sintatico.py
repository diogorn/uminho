import ply.yacc as yacc
from lexico import tokens

# production rules
# exp -> exp + exp
# p[0] -> p[1] p[2] p[3]
def p_global(p):
    """
    S : Exp
    """
    print("Resultado: ", p[1])


def p_exp_add(p):
    """
    Exp : Exp ADD Termo
    """
    p[0] = p[1] + p[3]

def p_exp_sub(p):
    """
    Exp : Exp SUB Termo
    """
    p[0] = p[1] - p[3]

def p_exp_termo(p):
    """
    Exp : Termo
    """
    p[0] = p[1]

# regras para multiplicação e divisão com termos para prioridades
def p_termo_mul(p):
    """
    Termo : Termo MUL Fator
    """
    p[0] = p[1] * p[3]

def p_termo_div(p):
    """
    Termo : Termo DIV Fator
    """
    p[0] = p[1] / p[3]

def p_termo_fator(p):
    """
    Termo : Fator
    """
    p[0] = p[1]

def p_fator_num(p):
    """
    Fator : NUM
    """
    p[0] = int(p[1])

def p_error(p):
    print('Erro sintatico: ', p)
    parser.success = False

parser = yacc.yacc()

import sys
for linha in sys.stdin:
    parser.success = True
    parser.parse(linha)
    if parser.success:
        print("frase válida", linha)
    else:
        print("frase inválida")