"""
T = { string, num, TITTLE, YEAR, CAST, GENRES, '[', ']', '{', '}', ',' }
maiusculas -> palavras reservadas
minusculas -> variaveis

T = {
    Cinema -> '[' ListFilmes, ']'
    ListFilmes -> ListFilmes ',' Filme
                | Filme
    Filme -> '{' Titulo ',' Ano ',' Elenco ',' Generos '}'
    Titulo -> TITTLE string
    Ano -> YEAR num
    Elenco -> CAST '[' ListaAtor ']'
    ListaAtor -> ListaAtor ',' string
                | string
    Generos -> GENRES '[' ListaGeneros ']'
    ListaGeneros -> ListaGeneros ',' string
                | string
}

# o ply.yacc fica mais eficiente com recursividade a esquerda
}

"""
import ply.lex as lex 

literals = ['{', '}', '[', ']', ','] 
tokens = ('string', 'num', 'TITTLE', 'YEAR', 'CAST', 'GENRES')

def t_TITTLE(t):
    r'\"title\"\s*:'
   # t.value = t.value[1:-1]
    return t

def t_YEAR(t):
    r'\"year\"\s*:'
    return t

def t_CAST(t):
    r'\"cast\"\s*:'
    return t

def t_GENRES(t):
    r'\"genres\"\s*:'
    return t

def t_num(t):
    r'\d+'
    return t

def t_string(t):
    r'\"[^"]*?\"'
    t.value = t.value[1:-1]
    return t


t_ignore = ' \t\n'


def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()