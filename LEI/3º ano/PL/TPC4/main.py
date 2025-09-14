import re

def lex_analyzer(query):
    token_patterns = [
        ('RESERVED_WORD', r'\b(SELECT|WHERE|LIMIT|A)\b'),
        ('VAR', r'\?[a-zA-Z_][a-zA-Z0-9_]*'),
        ('PREFIX_REF', r'[a-zA-Z_][a-zA-Z0-9_]*:[a-zA-Z_][a-zA-Z0-9_]*'),
        ('STRING', r'"[^"]*"(@[a-zA-Z]+)?'), 
        ('NUMBER', r'\d+'),
        ('SYMBOL', r'[\{\}\.\:\@]'),
        ('NEWLINE', r'\n'),
        ('WHITESPACE', r'[ \t]+'),
        ('UNKNOWN', r'.'),
    ]

    regex_pattern = '|'.join([f'(?P<{name}>{pattern})' for name, pattern in token_patterns])
    tokens = []
    line_num = 1

    for match in re.finditer(regex_pattern, query, re.IGNORECASE):
        kind = match.lastgroup
        value = match.group()

        if kind == 'RESERVED_WORD':
            tokens.append(("RESERVED_WORD", value.upper(), line_num, match.span()))
        elif kind == 'VAR':
            tokens.append(("VAR", value, line_num, match.span()))
        elif kind == 'PREFIX_REF':
            tokens.append(("PREFIX_REF", value, line_num, match.span()))
        elif kind == 'STRING':
            tokens.append(("STRING", value, line_num, match.span()))
        elif kind == 'NUMBER':
            tokens.append(("NUMBER", int(value), line_num, match.span()))
        elif kind == 'SYMBOL':
            tokens.append(("SYMBOL", value, line_num, match.span()))
        elif kind == 'NEWLINE':
            line_num += 1
        elif kind == 'WHITESPACE':
            continue  # Ignorar espaços
        else:
            tokens.append(("UNKNOWN", value, line_num, match.span()))

    return tokens

def process_query():
    query_text = """select ?nome ?desc where {
        ?s a dbo:MusicalArtist.
        ?s foaf:name "Chuck Berry"@en .
        ?w dbo:artist ?s.
        ?w foaf:name ?nome.
        ?w dbo:abstract ?desc.
    } LIMIT 1000
    """
    token_list = lex_analyzer(query_text)
    for token in token_list:
        print(token)

process_query()