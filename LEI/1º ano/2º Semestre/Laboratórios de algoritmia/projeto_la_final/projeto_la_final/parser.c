/**
 * @file Este ficheiro contém a função parser
 */
#include "parser.h"
#include "stack.h"
#include "mat.h"
/**
 * \brief A função parser faz o parser de uma dada linha atribuida como argumento
 *
 * @param line É a linha que foi lida e da qual se vai fazer o parser
 */
void parser (char *line){
    
    MyStack *p = inicia_MyStack ();
    variaveis_pre_definidas(p);
    
    char *delimita = " \t\n";
    
    for (char *token = strtok(line, delimita); token != NULL; token = strtok(NULL,delimita)){
        char *sobra1;
        char *sobra2;
        
        long val_l = strtol(token, &sobra1, 10);
        double val_d = strtod(token, &sobra2);
    
        if(strlen(sobra1) == 0){
                    PUSH_LONG(p, val_l);
        } else if(strlen(sobra2) == 0){
                    PUSH_DOUBLE(p, val_d);
        } else {
            switch (*token) {
                case '+':
                    soma(p);
                    break;
                case '-':
                    subtracao(p);
                    break;
                case '*':
                    multiplicacao(p);
                    break;
                case '/':
                    divisao(p);
                    break;
                case '#':
                    expoente(p);
                    break;
                case '&':
                    e_comercial(p);
                    break;
                case '|':
                    ou_barra(p);
                    break;
                case '^':
                    my_xor(p);
                    break;
                case '~':
                    my_not(p);
                    break;
                case '%':
                    resto_div(p);
                    break;
                case '(':
                    incrementar(p);
                    break;
                case ')':
                    decrementar(p);
                    break;
                case '_':
                    duplicar(p);
                    break;
                case ';':
                    my_pop(p);
                    break;
                case '\\':
                    trocar_2(p);
                    break;
                case '@':
                    roda_3(p);
                    break;
                case '$':
                    copia(p);
                    break;
                case 'l':
                    ler_linha(p);
                    break;
                case 'p':
                    imprimeTopo(p);
                    break;
                case 'i':
                    converte_int(p);
                    break;
                case 'f':
                    converteFloat(p);
                    break;
                case 'c':
                    converteChar(p);
                    break;
                case '=':
                    igual(p);
                    break;
                case '<':
                    menor(p);
                    break;
                case '>':
                    maior(p);
                    break;
                case '!':
                    negacao(p);
                    break;
                case 'e':
                    switch (token[1]) {
                        case '&':
                            e_shortcut(p);
                            break;
                        case '|':
                            ou_shortcut(p);
                            break;
                        case '<':
                            menor_entre_2(p);
                            break;
                        case '>':
                            maior_entre_2(p);
                            break;
                        default:
                            break;
                    }
                    break;
                case '?':
                    ifThenElse(p);
                    break;
                case 'A':
                    variaveis(p, 'A');
                    break;
                case 'B':
                    variaveis(p, 'B');
                    break;
                case 'C':
                    variaveis(p, 'C');
                    break;
                case 'D':
                    variaveis(p, 'D');
                    break;
                case 'E':
                    variaveis(p, 'E');
                    break;
                case 'F':
                    variaveis(p, 'F');
                    break;
                case 'G':
                    variaveis(p, 'G');
                    break;
                case 'H':
                    variaveis(p, 'H');
                    break;
                case 'I':
                    variaveis(p, 'I');
                    break;
                case 'J':
                    variaveis(p, 'J');
                    break;
                case 'K':
                    variaveis(p, 'K');
                    break;
                case 'L':
                    variaveis(p, 'L');
                    break;
                case 'M':
                    variaveis(p, 'M');
                    break;
                case 'N':
                    variaveis(p, 'N');
                    break;
                case 'O':
                    variaveis(p, 'O');
                    break;
                case 'P':
                    variaveis(p, 'P');
                    break;
                case 'Q':
                    variaveis(p, 'Q');
                    break;
                case 'R':
                    variaveis(p, 'R');
                    break;
                case 'S':
                    variaveis(p, 'S');
                    break;
                case 'T':
                    variaveis(p, 'T');
                    break;
                case 'U':
                    variaveis(p, 'U');
                    break;
                case 'V':
                    variaveis(p, 'V');
                    break;
                case 'W':
                    variaveis(p, 'W');
                    break;
                case 'X':
                    variaveis(p, 'X');
                    break;
                case 'Y':
                    variaveis(p, 'Y');
                    break;
                case 'Z':
                    variaveis(p, 'Z');
                    break;
                case ':':
                    switch (token[1]) {
                        case 'A':
                            add_valor(p, 'A');
                            break;
                        case 'B':
                            add_valor(p, 'B');
                            break;
                        case 'C':
                            add_valor(p, 'C');
                            break;
                        case 'D':
                            add_valor(p, 'D');
                            break;
                        case 'E':
                            add_valor(p, 'E');
                            break;
                        case 'F':
                            add_valor(p, 'F');
                            break;
                        case 'G':
                            add_valor(p, 'G');
                            break;
                        case 'H':
                            add_valor(p, 'H');
                            break;
                        case 'I':
                            add_valor(p, 'I');
                            break;
                        case 'J':
                            add_valor(p, 'J');
                            break;
                        case 'K':
                            add_valor(p, 'K');
                            break;
                        case 'L':
                            add_valor(p, 'L');
                            break;
                        case 'M':
                            add_valor(p, 'M');
                            break;
                        case 'N':
                            add_valor(p, 'N');
                            break;
                        case 'O':
                            add_valor(p, 'O');
                            break;
                        case 'P':
                            add_valor(p, 'P');
                            break;
                        case 'Q':
                            add_valor(p, 'Q');
                            break;
                        case 'R':
                            add_valor(p, 'R');
                            break;
                        case 'S':
                            add_valor(p, 'S');
                            break;
                        case 'T':
                            add_valor(p, 'T');
                            break;
                        case 'U':
                            add_valor(p, 'U');
                            break;
                        case 'V':
                            add_valor(p, 'V');
                            break;
                        case 'W':
                            add_valor(p, 'W');
                            break;
                        case 'X':
                            add_valor(p, 'X');
                            break;
                        case 'Y':
                            add_valor(p, 'Y');
                            break;
                        case 'Z':
                            add_valor(p, 'Z');
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
    }
    PRINT_STACK(p);
}
