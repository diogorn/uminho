import ply.yacc as yacc
from exp_lex import tokens


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
    Exp : Exp ADD Exp
    """
    # a ultima ação só é executada apos a redução do elem à direita (NUM -> EXP)
    p[0] = p[1] + p[3]

def p_exp_sub(p):
    """
    Exp : Exp SUB Exp
    """
    p[0] = p[1] - p[3]
def p_exp_num(p):
    """
    Exp : NUM
    """
    p[0] = int(p[1])



def p_error(p):
    print('Erro sintatico: ', p)
    parser.success = False

# build the parser
parser = yacc.yacc()


# read line from input and parse it
import sys
for linha in sys.stdin:
    parser.success = True
    parser.parse(linha)
    if parser.success:
        print("frase válida", linha)
    else:
        print("frase inválida")