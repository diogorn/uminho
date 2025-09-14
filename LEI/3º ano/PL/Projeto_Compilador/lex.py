import ply.lex as lex

tokens = [
    'PROGRAM', 'VAR', 'BEGIN', 'END', 
    # ciclos e condicionais
    'IF', 'THEN', 'ELSE', 'WHILE', 'DO', 'FOR', 'TO', 
    # funções
    'FUNCTION', 'DIV', 'MOD', 'LENGTH',
    # tipos
    'INTEGER', 'STRING', 'BOOLEAN',
    # bools
    'TRUE', 'FALSE',
    # in&out
    'WRITELN', 'WRITE', 'READLN', 'READ',
    # aritmeticos e relacionais
    'PLUS', 'MINUS', 'TIMES', 'ASSIGN',
    'GT', 'LT', 'EQ', 'NEQ', 'GTE', 'LTE',
    # literals
    'SEMICOLON', 'DOT', 'COLON', 'COMMA', 'LPAREN', 'RPAREN', 'LBRACKET', 'RBRACKET', 'DOTDOT', 'STRING_LITERAL',
    # lógicos
    'AND', 'OR', 'NOT',
    'ARRAY', 'OF',
    'ID', 'NUMBER'
]

t_ignore = ' \r\n\t'
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_ASSIGN = r':='
t_EQ = r'='
t_NEQ = r'<>'
t_GT = r'>'
t_LT = r'<'
t_GTE = r'>='
t_LTE = r'<='
t_COMMA = r','
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_SEMICOLON = r';'
t_DOT = r'\.'
t_COLON = r':'
t_DOTDOT = r'\.\.'

def t_STRING_LITERAL(t):
    r"'[^']*'"
    t.value = t.value[1:-1]
    return t

# Reserved words as tokens
def t_MOD(t):
    r'mod'
    return t

def t_DIV(t):
    r'div'
    return t

def t_COMMENT(t):
    r'(\{.*?\})|(\(\*.*?\*\))'
    pass 

def t_NUMBER(t):
    r'\d+\.\d+|\d+' 
    if '.' in t.value:
        t.value = float(t.value)
    else:
        t.value = int(t.value)
    return t

def t_ARRAY(t):
    r'array'
    return t

def t_OF(t):
    r'of'
    return t

def t_PROGRAM(t):
    r'program'
    return t

def t_VAR(t):
    r'var'
    return t

def t_BEGIN(t):
    r'begin'
    return t

def t_END(t):
    r'end'
    return t

def t_IF(t):
    r'if'
    return t

def t_THEN(t):
    r'then'
    return t

def t_ELSE(t):
    r'else'
    return t

def t_WHILE(t):
    r'while'
    return t

def t_DO(t):
    r'do'
    return t

def t_FOR(t):
    r'for'
    return t

def t_TO(t):
    r'to'
    return t

def t_FUNCTION(t):
    r'function'
    return t

def t_INTEGER(t):
    r'integer'
    return t

def t_STRING(t):
    r'string'
    return t

def t_BOOLEAN(t):
    r'boolean'
    return t

def t_TRUE(t):
    r'true'
    return t

def t_FALSE(t):
    r'false'
    return t

def t_WRITELN(t):
    r'writeln'
    return t

def t_WRITE(t):
    r'write'
    return t

def t_READLN(t):
    r'readln'
    return t

def t_READ(t):
    r'read'
    return t

def t_AND(t):
    r'and'
    return t

def t_OR(t):
    r'or'
    return t

# NOT logical operator
def t_NOT(t):
    r'not'
    return t

def t_LENGTH(t):
    r'length'
    return t

def t_ID(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    return t

def t_error(t):
    print(f'Illegal character: {t.value[0]}')
    t.lexer.skip(1)

lexer = lex.lex()
