import ply.yacc as yacc
from lex import tokens
import sys
import argparse

symbol_table_stack = [{}] # stack vars  
current_scope_level = 0 # distingue global e local
stack_pointer = 0 
local_offset = 0 
label_counter = 0
current_function = None
function_table = {} # simbols de funções

def new_label():
    global label_counter
    label_counter += 1
    return f"L{label_counter}"

def add_symbol(name, sym_type, is_array=False, array_range=None, is_local=False, offset=None):
    global stack_pointer, local_offset
    name = name.lower()
    if name in symbol_table_stack[current_scope_level]:
        return None 
    symbol = {'type': sym_type, 'is_array': is_array}
    if is_local:
        if is_array:
            print("Error: Arrays not supported as local variables")
            return None
        symbol['offset'] = local_offset
        symbol['is_local'] = True
        local_offset += 1
    else:
        if is_array:
            low, high = array_range
            size = high - low + 1
            symbol['range'] = array_range
            symbol['size'] = size
            symbol['offset'] = stack_pointer
            stack_pointer += size
        else:
            symbol['offset'] = stack_pointer if offset is None else offset
            if offset is None:
                stack_pointer += 1
    symbol_table_stack[current_scope_level][name] = symbol
    return symbol

def get_symbol(name):
    name = name.lower()
    for scope in reversed(symbol_table_stack):
        if name in scope:
            return scope[name]
    return None

def p_Program(p):
    '''Program : PROGRAM ID SEMICOLON Block DOT'''
    p[0] = f"START\n{p[4]}STOP\n"

def p_Block(p):
    '''Block : Declarations CompoundStatement'''
    p[0] = f"{p[1]}{p[2]}"

def p_Declarations(p):
    '''Declarations : VarDeclarationPart FunctionDeclarations'''
    p[0] = f"{p[1]}{p[2]}"

def p_VarDeclarationPart(p):
    '''VarDeclarationPart : VAR VarDeclarationList
                          | empty'''
    p[0] = p[2] if len(p) == 3 else ""

def p_VarDeclarationList(p):
    '''VarDeclarationList : VarDeclaration
                          | VarDeclarationList VarDeclaration'''
    p[0] = p[1] if len(p) == 2 else f"{p[1]}{p[2]}"

def p_VarDeclaration(p):
    '''VarDeclaration : IdList COLON Type SEMICOLON'''
    ids = p[1]
    var_type = p[3]
    code = ""
    for var_name in ids:
        if current_function is not None:
            if isinstance(var_type, tuple) and var_type[0] == 'array':
                print("Error: Arrays not supported as local variables")
                p[0] = ""
                return
            add_symbol(var_name, var_type, is_local=True)
        else:
            if isinstance(var_type, tuple) and var_type[0] == 'array':
                base_type = var_type[1]
                array_range = var_type[2]
                symbol = add_symbol(var_name, base_type, is_array=True, array_range=array_range)
                if symbol:
                    for i in range(array_range[1] - array_range[0] + 1):
                        code += f"PUSHI 0\nSTOREG {symbol['offset'] + i}\n"
            else:
                symbol = add_symbol(var_name, var_type)
                if symbol:
                    code += f"PUSHI 0\nSTOREG {symbol['offset']}\n"
    p[0] = code

def p_IdList(p):
    '''IdList : ID
              | ID COMMA IdList'''
    p[0] = [p[1]] if len(p) == 2 else [p[1]] + p[3]

def p_Type(p):
    '''Type : BasicType
            | ArrayType'''
    p[0] = p[1]

def p_BasicType(p):
    '''BasicType : INTEGER
                 | STRING
                 | BOOLEAN'''
    p[0] = p[1].lower()

def p_ArrayType(p):
    '''ArrayType : ARRAY LBRACKET NUMBER DOTDOT NUMBER RBRACKET OF BasicType'''
    low = int(p[3])
    high = int(p[5])
    base_type = p[8].lower()
    p[0] = ('array', base_type, (low, high))

def p_FunctionDeclarations(p):
    '''FunctionDeclarations : FunctionDeclaration FunctionDeclarations
                            | empty'''
    p[0] = p[1] + p[2] if len(p) == 3 else ""

def p_FunctionDeclaration(p):
    '''FunctionDeclaration : FUNCTION ID LPAREN FormalParameters RPAREN COLON BasicType SEMICOLON Declarations CompoundStatement'''
    global current_function, local_offset
    func_name = p[2].lower()
    params = p[4]
    return_type = p[7].lower()
    local_decls = p[9]
    body = p[10]
    func_label = new_label()
    function_table[func_name] = {'label': func_label, 'params': params, 'return_type': return_type}
    old_offset = local_offset
    local_offset = 1
    symbol_table_stack.append({})
    current_scope_level += 1
    current_function = func_name
    number_of_params = len(params)
    return_offset = -(number_of_params + 1)
    add_symbol(func_name, return_type, is_local=False, offset=return_offset)
    for i, param in enumerate(params):
        param_name, param_type = param
        offset = -number_of_params + i
        add_symbol(param_name, param_type, is_local=False, offset=offset)
    local_decls_code = local_decls
    number_of_locals = local_offset - 1
    func_code = f"{func_label}:\nPUSHN {number_of_locals}\n{local_decls_code}{body}RETURN\n"
    symbol_table_stack.pop()
    current_scope_level -= 1
    local_offset = old_offset
    current_function = None
    p[0] = func_code

def p_FormalParameters(p):
    '''FormalParameters : ID COLON Type
                        | ID COLON Type SEMICOLON FormalParameters
                        | empty'''
    if len(p) == 2:
        p[0] = []
    elif len(p) == 4:
        p[0] = [(p[1], p[3])]
    else:
        p[0] = [(p[1], p[3])] + p[5]

def p_CompoundStatement(p):
    '''CompoundStatement : BEGIN StatementList END'''
    p[0] = p[2]

def p_StatementList(p): 
    '''StatementList : Statement
                     | StatementList SEMICOLON Statement'''
    p[0] = p[1] if len(p) == 2 else f"{p[1]}{p[3]}"

def p_Statement(p):
    '''Statement : AssignmentStatement
                 | WriteStatement
                 | ReadStatement
                 | IfStatement
                 | WhileStatement
                 | ForStatement
                 | CompoundStatement
                 | empty'''
    p[0] = p[1]

def p_ReadStatement(p):
    '''ReadStatement : READLN LPAREN ArrayAccess RPAREN
                     | READLN LPAREN ID RPAREN'''
    if p[3][0] == 'array_access':
        var_name, index_code, index_type = p[3][1:]
        symbol = get_symbol(var_name)
        if not symbol or not symbol.get('is_array'):
            print(f"Error: '{var_name}' is not an array")
            p[0] = ""
            return
        if index_type != 'integer':
            print(f"Error: Array index must be integer")
            p[0] = ""
            return
        if symbol['type'] != 'integer':
            print(f"Error: Array elements must be integer for READLN")
            p[0] = ""
            return
        low = symbol['range'][0]
        offset = symbol['offset']
        p[0] = f"PUSHGP\n{index_code}PUSHI {low}\nSUB\nPUSHI {offset}\nADD\nPADD\nREAD\nATOI\nSTORE 0\n"
    else:
        var_name = p[3].lower()
        symbol = get_symbol(var_name)
        if not symbol:
            print(f"Error: Variable '{var_name}' not declared")
            p[0] = ""
            return
        if symbol.get('is_array'):
            print(f"Error: '{var_name}' is an array; use array indexing")
            p[0] = ""
            return
        if symbol['type'] != 'integer':
            print(f"Error: Variable must be integer for READLN")
            p[0] = ""
            return
        offset = symbol['offset']
        p[0] = f"READ\nATOI\nSTOREG {offset}\n"

def p_AssignmentStatement(p):
    '''AssignmentStatement : ID ASSIGN Expression
                          | ArrayAccess ASSIGN Expression'''
    global current_function
    if p[1][0] == 'array_access':
        var_name, index_code, index_type = p[1][1:]
        expr_code, expr_type = p[3]
        symbol = get_symbol(var_name)
        if not symbol or not symbol.get('is_array'):
            print(f"Error: '{var_name}' is not an array")
            p[0] = ""
            return
        if index_type != 'integer':
            print(f"Error: Array index must be integer")
            p[0] = ""
            return
        if symbol['type'] != expr_type:
            print(f"Error: Type mismatch in array assignment")
            p[0] = ""
            return
        low = symbol['range'][0]
        offset = symbol['offset']
        p[0] = f"PUSHGP\n{index_code}PUSHI {low}\nSUB\nPUSHI {offset}\nADD\nPADD\n{expr_code}STORE 0\n"
    else:
        var_name = p[1].lower()
        expr_code, expr_type = p[3]
        symbol = get_symbol(var_name)
        if not symbol:
            print(f"Error: Variable '{var_name}' not declared")
            p[0] = ""
            return
        if symbol.get('is_array'):
            print(f"Error: '{var_name}' is an array; use array indexing")
            p[0] = ""
            return
        if symbol['type'] != expr_type:
            print(f"Error: Type mismatch in assignment")
            p[0] = ""
            return
        offset = symbol['offset']
        if var_name == current_function:
            number_of_params = len(function_table[current_function]['params'])
            p[0] = f"{expr_code}STOREL -{number_of_params + 1}\n"
        elif symbol.get('is_local'):
            p[0] = f"{expr_code}STOREL {offset}\n"
        else:
            p[0] = f"{expr_code}STOREG {offset}\n"

def p_WriteStatement(p):
    '''WriteStatement : WRITELN LPAREN ExpressionList RPAREN'''
    code = ""
    for expr in p[3]:
        expr_code, expr_type = expr
        if expr_type == 'integer':
            code += f"{expr_code}WRITEI\n"
        elif expr_type == 'string':
            code += f"{expr_code}WRITES\n"
        else:
            print(f"Error: Unsupported type '{expr_type}' for WRITELN")
            p[0] = ""
            return
    p[0] = code

def p_ExpressionList(p):
    '''ExpressionList : Expression
                      | ExpressionList COMMA Expression'''
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[3]]


def p_IfStatement_then(p):
    '''IfStatement : IF Expression THEN Statement'''
    cond_code, cond_type = p[2]
    if cond_type != 'boolean':
        print("Error: Condition must be boolean")
        p[0] = ""
        return
    then_code = p[4]
    end_label = new_label()
    p[0] = f"{cond_code}JZ {end_label}\n{then_code}{end_label}:\n"

def p_IfStatement_else(p):
    '''IfStatement : IF Expression THEN Statement ELSE Statement'''
    cond_code, cond_type = p[2]
    if cond_type != 'boolean':
        print("Error: Condition must be boolean")
        p[0] = ""
        return
    then_code = p[4]
    else_code = p[6]
    else_label = new_label()
    end_label = new_label()
    p[0] = f"{cond_code}JZ {else_label}\n{then_code}JUMP {end_label}\n{else_label}:\n{else_code}{end_label}:\n"

def p_WhileStatement(p):
    '''WhileStatement : WHILE Expression DO Statement'''
    start_label = new_label()
    end_label = new_label()
    print(p[2])
    cond_code, cond_type = p[2]
    if cond_type != 'boolean':
        print("Error: While condition must be boolean")
        p[0] = ""
        return
    body_code = p[4]
    p[0] = f"{start_label}:\n{cond_code}JZ {end_label}\n{body_code}JUMP {start_label}\n{end_label}:\n"

def p_ForStatement(p):
    '''ForStatement : FOR ID ASSIGN Expression TO Expression DO Statement'''
    var_name = p[2].lower()
    init_code, init_type = p[4]
    end_code, end_type = p[6]
    body_code = p[8]
    symbol = get_symbol(var_name)
    if not symbol:
        print(f"Error: Variable '{var_name}' not declared")
        p[0] = ""
        return
    if symbol.get('is_array'):
        print(f"Error: Loop variable '{var_name}' cannot be an array")
        p[0] = ""
        return
    if init_type != 'integer' or end_type != 'integer':
        print(f"Error: FOR loop bounds must be integers")
        p[0] = ""
        return
    if symbol['type'] != 'integer':
        print(f"Error: Loop variable must be integer")
        p[0] = ""
        return
    offset = symbol['offset']
    start_label = new_label()
    end_label = new_label()
    load_op = 'PUSHL' if symbol.get('is_local') else 'PUSHG'
    store_op = 'STOREL' if symbol.get('is_local') else 'STOREG'
    p[0] = (
        f"{init_code}{store_op} {offset}\n"
        f"{start_label}:\n"
        f"{load_op} {offset}\n"
        f"{end_code}"
        f"INFEQ\n"
        f"JZ {end_label}\n"
        f"{body_code}"
        f"{load_op} {offset}\n"
        f"PUSHI 1\n"
        f"ADD\n"
        f"{store_op} {offset}\n"
        f"JUMP {start_label}\n"
        f"{end_label}:\n"
    )


def p_Expression(p):
    '''Expression : ExprBool'''
    p[0] = p[1]

# ExprBool : Expr | Expr OpRel Expr
def p_ExprBool_expr(p):
    '''ExprBool : Expr'''
    p[0] = p[1]

def p_ExprBool_rel(p):
    '''ExprBool : Expr OpRel Expr'''
    code1, type1 = p[1]
    op, opstr = p[2]
    code3, type3 = p[3]
    if type1 == type3 and type1 in ('integer', 'boolean'):
        op_code = {'=': 'EQUAL', '<>': 'NOTEQUAL', '<': 'INF', '<=': 'INFEQ', '>': 'SUP', '>=': 'SUPEQ'}[opstr]
        p[0] = (f"{code1}{code3}{op_code}\n", 'boolean')
    else:
        print("Error: Type mismatch in relational expression")
        p[0] = ("", 'error')

# OpRel : EQ | NEQ | LT | LTE | GT | GTE
def p_OpRel(p):
    '''OpRel : EQ
             | NEQ
             | LT
             | LTE
             | GT
             | GTE'''
    p[0] = (p[1], p[1])

# Expr : Termo | Expr OpAd Termo
def p_Expr_termo(p):
    '''Expr : Termo'''
    p[0] = p[1]

def p_Expr_opad(p):
    '''Expr : Expr OpAd Termo'''
    code1, type1 = p[1]
    op, opstr = p[2]
    code3, type3 = p[3]
    if opstr in ('+', '-') and type1 == 'integer' and type3 == 'integer':
        op_code = {'+': 'ADD', '-': 'SUB'}[opstr]
        p[0] = (f"{code1}{code3}{op_code}\n", 'integer')
    elif opstr == 'or' and type1 == 'boolean' and type3 == 'boolean':
        # boolean OR: (a OR b) <=> a + b >= 1
        p[0] = (f"{code1}{code3}ADD\nPUSHI 1\nSUPEQ\n", 'boolean')
    else:
        print("Error: Type mismatch in additive expression")
        p[0] = ("", 'error')

# OpAd : PLUS | MINUS | OR
def p_OpAd_plus(p):
    '''OpAd : PLUS'''
    p[0] = (p[1], '+')
def p_OpAd_minus(p):
    '''OpAd : MINUS'''
    p[0] = (p[1], '-')
def p_OpAd_or(p):
    '''OpAd : OR'''
    p[0] = (p[1], 'or')

# Termo : Fator | Termo OpMul Fator
def p_Termo_fator(p):
    '''Termo : Fator'''
    p[0] = p[1]

def p_Termo_opmul(p):
    '''Termo : Termo OpMul Fator'''
    code1, type1 = p[1]
    op, opstr = p[2]
    code3, type3 = p[3]
    if opstr in ('*', 'div', 'mod') and type1 == 'integer' and type3 == 'integer':
        op_code = {'*': 'MUL', 'div': 'DIV', 'mod': 'MOD'}[opstr]
        p[0] = (f"{code1}{code3}{op_code}\n", 'integer')
    elif opstr == 'and' and type1 == 'boolean' and type3 == 'boolean':
        # boolean AND: (a AND b) <=> a + b == 2
        p[0] = (f"{code1}{code3}ADD\nPUSHI 2\nEQUAL\n", 'boolean')
    else:
        print("Error: Type mismatch in multiplicative expression")
        p[0] = ("", 'error')

# OpMul : TIMES | DIV | MOD | AND
def p_OpMul_times(p):
    '''OpMul : TIMES'''
    p[0] = (p[1], '*')
def p_OpMul_div(p):
    '''OpMul : DIV'''
    p[0] = (p[1], 'div')
def p_OpMul_mod(p):
    '''OpMul : MOD'''
    p[0] = (p[1], 'mod')
def p_OpMul_and(p):
    '''OpMul : AND'''
    p[0] = (p[1], 'and')

# Fator : Const | Var | LPAREN ExprBool RPAREN | Expression_function_call
def p_Fator_const(p):
    '''Fator : Const'''
    p[0] = p[1]

def p_Fator_var(p):
    '''Fator : Var'''
    p[0] = p[1]

def p_Fator_group(p):
    '''Fator : LPAREN ExprBool RPAREN'''
    p[0] = p[2]

def p_Fator_function_call(p):
    '''Fator : Expression_function_call'''
    p[0] = p[1]

# Logical NOT for boolean expressions
def p_Fator_not(p):
    '''Fator : NOT Fator'''
    code, typ = p[2]
    if typ != 'boolean':
        print("Error: NOT applied to non-boolean")
        p[0] = ("", 'error')
    else:
        # NOT x ≡ x == 0
        p[0] = (f"{code}PUSHI 0\nEQUAL\n", 'boolean')

# Const : NUMBER | STRING_LITERAL | TRUE | FALSE
def p_Const_number(p):
    '''Const : NUMBER'''
    p[0] = (f"PUSHI {p[1]}\n", 'integer')
def p_Const_string(p):
    '''Const : STRING_LITERAL'''
    p[0] = (f"PUSHS \"{p[1]}\"\n", "string")
def p_Const_true(p):
    '''Const : TRUE'''
    p[0] = ("PUSHI 1\n", 'boolean')
def p_Const_false(p):
    '''Const : FALSE'''
    p[0] = ("PUSHI 0\n", 'boolean')

# Var : ID | ID LBRACKET ExprBool RBRACKET
def p_Var_id(p):
    '''Var : ID'''
    var_name = p[1].lower()
    symbol = get_symbol(var_name)
    if not symbol:
        print(f"Error: Undeclared variable '{var_name}'")
        p[0] = ("", 'error')
        return
    if symbol.get('is_array'):
        print(f"Error: '{var_name}' is an array; use array indexing")
        p[0] = ("", 'error')
        return
    op = 'PUSHL' if symbol.get('is_local') else 'PUSHG'
    p[0] = (f"{op} {symbol['offset']}\n", symbol['type'])

def p_Var_array(p):
    '''Var : ID LBRACKET ExprBool RBRACKET'''
    var_name = p[1].lower()
    index_code, index_type = p[3]
    symbol = get_symbol(var_name)
    if not symbol:
        print(f"Error: Undeclared variable '{var_name}'")
        p[0] = ("", 'error')
        return
    if symbol.get('is_array'):
        if index_type != 'integer':
            print(f"Error: Array index must be integer")
            p[0] = ("", 'error')
            return
        low = symbol['range'][0]
        offset = symbol['offset']
        code = f"PUSHGP\n{index_code}PUSHI {low}\nSUB\nPUSHI {offset}\nADD\nPADD\nLOAD 0\n"
        p[0] = (code, symbol['type'])
    elif symbol['type'] == 'string':
        if index_type != 'integer':
            print(f"Error: String index must be integer")
            p[0] = ("", 'error')
            return
        load_op = 'PUSHL' if symbol.get('is_local') else 'PUSHG'
        code = f"{load_op} {symbol['offset']}\n{index_code}PUSHI 1\nSUB\nCHARAT\n"
        p[0] = (code, 'integer')
    else:
        print(f"Error: '{var_name}' is not an array or string")
        p[0] = ("", 'error')

# Expression_function_call : ID LPAREN ActualParameters RPAREN | LENGTH LPAREN ExprBool RPAREN
def p_Expression_function_call(p):
    '''Expression_function_call : ID LPAREN ActualParameters RPAREN
                                | LENGTH LPAREN ExprBool RPAREN'''
    if p[1].lower() == 'length':
        expr_code, expr_type = p[3]
        if expr_type != 'string':
            print("Error: length() argument must be a string")
            p[0] = ("", 'error')
            return
        p[0] = (f"{expr_code}STRLEN\n", 'integer')
    else:
        func_name = p[1].lower()
        if func_name not in function_table:
            print(f"Error: Undeclared function '{func_name}'")
            p[0] = ("", 'error')
            return
        func_info = function_table[func_name]
        args = p[3]
        if len(args) != len(func_info['params']):
            print(f"Error: Argument count mismatch for '{func_name}'")
            p[0] = ("", 'error')
            return
        arg_code = ""
        for arg, param in zip(args, func_info['params']):
            arg_code += arg[0]
            if arg[1] != param[1]:
                print(f"Error: Type mismatch in argument for '{func_name}'")
                p[0] = ("", 'error')
                return
        call_code = f"PUSHI 0\n{arg_code}PUSHA {func_info['label']}\nCALL\n"
        p[0] = (call_code, func_info['return_type'])

# Atualizar ActualParameters para usar ExprBool
def p_ActualParameters(p):
    '''ActualParameters : ExprBool
                        | ExprBool COMMA ActualParameters
                        | empty'''
    if len(p) == 2:
        p[0] = [] if p[1] == '' else [p[1]]
    else:
        p[0] = [p[1]] + p[3]

def p_ArrayAccess(p):
    '''ArrayAccess : ID LBRACKET Expression RBRACKET'''
    var_name = p[1].lower()
    index_code, index_type = p[3]
    p[0] = ('array_access', var_name, index_code, index_type)

def p_empty(p):
    '''empty :'''
    p[0] = ""

def p_error(p):
    print("Syntax error")

parser = yacc.yacc()
parser.exito = True

PREMADE_EXAMPLES = {
    "MaiorDe3": """
        program Maior3;
        var  
            num1, num2, num3, maior: integer;
        begin
            { Ler 3 números }
            writeln('Introduza o primeiro número: ');  
            readln(num1);
            writeln('Introduza o segundo número: ');  
            readln(num2);
            writeln('Introduza o terceiro número: ');  
            readln(num3);
            if num1 > num2 then
                if num1 > num3 then 
                    maior := num1
                else maior := num3
            elseif num2 > num3 
                then maior := num2
            else 
                maior := num3;
            writeln(maior);
        end.
    """,

    "Fatorial": """
        program Fatorial;
        var  
            n, i, fat: integer;
        begin  
            writeln('Introduza um número inteiro positivo:');  
            readln(n);
            fat := 1;
            for i := 1 to n do    
                fat := fat * i;
            writeln('Fatorial de ', n, ': ', fat);
        end.
    """,

    "NumeroPrimo": """
        program NumeroPrimo;
        var  
            num, i: integer;  
            primo: boolean;
        begin  
            writeln('Introduza um número inteiro positivo:');  
            readln(num);  
            primo := true;  
            i := 2;
            while (i <= (num div 2)) and primo do
                begin
                    if (num mod i) = 0 then            
                        primo := false;        
                    i := i + 1;
                end;
            if primo then    
                writeln(num, ' é um número primo')
            else    
                writeln(num, ' não é um número primo');
        end.
    """,

    "SomaArray": """
        program SomaArray;
        var  
            numeros: array[1..5] of integer;  
            i, soma: integer;
        begin  
            soma := 0;  
            writeln('Introduza 5 números inteiros:');
            for i := 1 to 5 do
            begin    
                writeln(i);
                readln(numeros[i]);    
                soma := soma + numeros[i];
            end;  
            writeln('A soma dos números é: ', soma);
        end.
    """, 
    "HelloWorld": """
    program HelloWorld;
        begin
        writeln('Ola, Mundo!');
    end.
    """
    
}

def main():
    parser_args = argparse.ArgumentParser(
        description="Compile Pascal‐like source code into intermediate instructions."
    )

    group = parser_args.add_mutually_exclusive_group()
    group.add_argument(
        "-e", "--example",
        choices=list(PREMADE_EXAMPLES.keys()),
        help="Name of a premade example to compile"
    )
    group.add_argument(
        "-f", "--file",
        metavar="PATH",
        help="Path to a source‐file to compile"
    )

    args = parser_args.parse_args()

    if args.example:
        source_code = PREMADE_EXAMPLES[args.example]
        print(f"*** Compiling example: {args.example} ***\n")
    elif args.file:
        try:
            with open(args.file, 'r', encoding='utf-8') as fp:
                source_code = fp.read()
            print(f"*** Compiling file: {args.file} ***\n")
        except IOError as e:
            print(f"Error: could not open file '{args.file}': {e}")
            sys.exit(1)
    else:
        print("*** Reading source code from stdin (terminate with EOF) ***\n")
        source_code = sys.stdin.read()


    result = parser.parse(source_code, debug=False)

    if result is None:
        print("Parsing returned None (likely a syntax error).")
        sys.exit(1)
    else:
        print("=== generated intermediate code ===\n")
        print(result)

if __name__ == "__main__":
    main()