import ply.lex as lex

input = '''
? a
? b 
c = a*b/2
d = f(c,2)
'''

tokens = (
    'NUM',
    'MUL',
    'DIV',
    'PA',
    'PF',
    'READ',
    'ATRIB',
    'VIRG',
    'ID')

# regular expressions rules for a simple tokens
t_READ = r'\?'
t_ATRIB = r'='
t_MUL = r'\*'
t_DIV = r'\/'
t_PA = r'\('
t_PF = r'\)'
t_VIRG = r','

def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_ID(t):
    r'[a-ZA-Z_]\w*'
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)


# A string containing ignored characters (spaces and tabs)
t_ignore = ' \t'

# error handling rule
def t_error(t):
    print("Illegal character {t.value[0]}")
    t.lexer.skip(1)

#build the lexer
lexer = lex.lex()

lexer.input(input)
for tok in lexer:
    print(tok)

