import ply.lex as lex

states = [('TEXTO', 'exclusive')]
literals = ['<', '>', '/', '=']
tokens = [ 'DCA', 'DCF', 'AAGENDA', 'FAGENDA', 'ENTRADA', 'FENTRADA', 'GRUPO', 'REF', 'ANOME', 'FNOME', 'AEMAIL', 'FEMAIL', 'ATELEFONE', 'FTELEFONE', 'ID', 'vatrib']

def t_DCA(t):
    r'\<\?\s*xml'
    return t

def t_DCF(t):
    r'\?\>'
    return t

def t_AAGENDA(t):
    r'\<\s*agenda\s*\>'
    return t

def t_FAGENDA(t):
    r'\<\/\s*agenda\s*\>'
    return t

def t_ANOME(t):
    r'\<\s*nome\s*\>'
    t.lexer.begin('TEXTO')
    return t

def t_TEXTO_FNOME(t):
    r'\<\/\s*nome\s*\>'
    t.lexer.begin('INITIAL')
    return t

def t_AEMAIL(t):
    r'\<\s*email\s*\>'
    t.lexer.begin('TEXTO')
    return t

def t_FEMAIL(t):
    r'\<\/\s*email\s*\>'
    return t

def t_ATELEFONE(t):
    r'\<\s*telefone\s*\>'
    t.lexer.begin('TEXTO')
    return t

def t_FTELEFONE(t):
    r'\<\/\s*telefone\s*\>'
    t.lexer.begin('INITIAL')
    return t

def t_ENTRADA(t):
    r'entrada'
    return t

def t_GRUPO(t):
    r'grupo'
    return t

def t_REF(t):
    r'ref'
    return t



def t_FENTRADA(t):
    r'\<\/\s*entrada\s*\>'
    return t
     
def t_ID(t):
    r'[_a-zA-Z]]\w*'
    return t

def t_vatrib(t):
    r'\"[^\"]*?\"'
    t.value = t.value[1:-1]
    return t

def t_TEXTO_string(t):
    r'[^<]*?'
    return t


t_ignore = ' \t\n'

def t_ANY_error(p):
        print("Illegal character '%s'" % p.value[0])
        p.lexer.skip(1)

lexer = lex.lex()