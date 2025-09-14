import ply.lex as lex 

literals = ['(', ')', '*', '+']
tokens = ('num')

def t_num(t):
    r'\d+'
    t.value = int(t.value)
    return t

t_ignore = ' \t\n'


def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()