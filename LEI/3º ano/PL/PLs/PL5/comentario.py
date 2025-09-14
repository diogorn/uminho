import ply.lex as lex
import sys
states = (
    ('comentario', 'exclusive'),
)

t_ANY_ignore = ' \t\n' 

tokens = (

    'QUALQUER', 
    'AC',
    'FC',

)

def t_AC(t):
    r'\/\*'
    t.lexer.begin('comentario')
    return t


def t_QUALQUER(t):
    r'.+'
    return t


def t_comentario_FC(t):
    r'\*\/'
    t.lexer.begin('INITIAL')
    return t


def t_comentario_QUALQUER(t):
    r'.+'
    pass

def t_ANY_error(t):
    print(f"Carácter ilegal: {t.value[0]}")
    t.lexer.skip(1)


lexer = lex.lex()

for linha in sys.stdin:
    lexer.input(linha)
    for tok in lexer:
        print(tok)