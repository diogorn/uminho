import ply.lex as lex 

tokens = ['TIT', 'SUBTIT', 'BODY', 'STRING']


t_TIT = r'#'
t_SUBTIT = r'##'
t_BODY = r'###'

t_ignore = " \t\n"

def t_error(p):
        print("Illegal character '%s'" % p.value[0])
        p.lexer.skip(1)


lexer = lex.lex()