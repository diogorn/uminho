import ply.lex as lex

# ply.yacc

tokens = ['NUM','ADD','SUB']

t_ADD = r'\+'
t_SUB = r'-'
t_NUM = r'\d+'

t_ignore = ' \t\n'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lexer = lex.lex()