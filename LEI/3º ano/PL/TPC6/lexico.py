import ply.lex as lex

# ply.yacc

tokens = ['NUM','ADD','SUB','DIV','MUL']

t_ADD = r'\+'
t_SUB = r'-'
t_DIV = r'/'
t_MUL = r'\*'
t_NUM = r'\d+'
t_ignore = ' \t\n'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lexer = lex.lex()