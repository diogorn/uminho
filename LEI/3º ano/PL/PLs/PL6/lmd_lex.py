"""
T = {'tit', 'subtit', 'doc', '(', ')', string}
P = {
    Documento -> '(' Doc Lista ')' 
    Lista -> Elem Lista 
            | Elem
    Elem -> '(' TIT String ')'
            | '(' SUBTIT' String ')'
            | String
}
"""

import ply.lex as lex 

tokens = ['TIT','SUBTIT', 'DOC', 'PA', 'PF', 'STRING']

t_TIT = r'tit'
t_SUBTIT = r'subtit'
t_DOC = r'doc'
t_PA = r'\('
t_PF = r'\)'
t_STRING = r'\"[^"]*?\"'


def t_STRING(t):
        r'\"[^"]*?\"'
        t.value = t.value[1:-1]
        return t

t_ignore = " \t\n"

def t_error(p):
        print("Illegal character '%s'" % p.value[0])
        p.lexer.skip(1)


lexer = lex.lex()