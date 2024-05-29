#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "parser.h"
#include "stack.h"
#include "mat.h"

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

//            operações stacl -- Guiao 1
        } else if (strcmp(token, "+") == 0){
            soma (p);

        } else if (strcmp(token, "-") == 0){
            subtracao (p);

        } else if (strcmp(token, "*") == 0){
            multiplicacao (p);

        } else if (strcmp(token, "/") == 0){
            divisao (p);

        } else if (strcmp(token, "#") == 0){
            expoente (p);

        } else if (strcmp(token, "&") == 0){
            e_comercial (p);

        } else if (strcmp(token, "|") == 0){
            ou_barra (p);

        } else if (strcmp(token, "^") == 0){
            my_xor (p);

        } else if (strcmp(token, "~") == 0){
            my_not (p);

        } else if (strcmp(token, "%")==0){
            resto_div (p);

        } else if (strcmp(token, "(")==0){
            decrementar (p);

        } else if (strcmp(token, ")")==0){
            incrementar (p);

//            manipulação da stack -- GUIAO 2
        } else if (strcmp(token, "_") == 0){
            duplicar (p);

        } else if (strcmp(token, ";") == 0){
            my_pop (p);

        } else if (strcmp(token, "\\") == 0){
            trocar_2 (p);

        } else if (strcmp(token, "@") == 0){
            roda_3 (p);

        } else if (strcmp(token, "$") == 0){
            copia (p);

//            le linhas e tipos
        } else if (strcmp(token, "l") == 0){
            ler_linha (p);

        } else if (strcmp(token, "p") == 0){
            imprimeTopo (p);
            
        } else if (strcmp(token, "i") == 0){
            converte_int (p);

        } else if (strcmp(token, "f") == 0){
            converteFloat (p);

        } else if (strcmp(token, "c") == 0){
            converteChar (p);
            
//            logica -- GUIAO 3
        } else if (strcmp(token, "=")==0) {
            igual (p);

        } else if (strcmp(token, "<")==0){
            menor (p);

        } else if (strcmp(token, ">")==0){
            maior (p);

        } else if (strcmp(token, "!") == 0){
            negacao (p);
            
        } else if (strcmp(token, "e&") == 0){
            e_shortcut (p);

        } else if (strcmp(token, "e|") == 0){
            ou_shortcut (p);

        } else if (strcmp(token, "e<") == 0){
            menor_entre_2 (p);

        } else if (strcmp(token, "e>") == 0){
            maior_entre_2 (p);

        } else if (strcmp(token, "?") == 0){
            ifThenElse (p);

//            Letras
        } else if (strcmp(token, "A") == 0){
            variaveis(p, 'A');
        } else if (strcmp(token, "B") == 0){
            variaveis(p, 'B');
        } else if (strcmp(token, "C") == 0){
            variaveis(p, 'C');
        } else if (strcmp(token, "D") == 0){
            variaveis(p, 'D');
        } else if (strcmp(token, "E") == 0){
            variaveis(p, 'E');
        } else if (strcmp(token, "F") == 0){
            variaveis(p, 'F');
        } else if (strcmp(token, "G") == 0){
            variaveis(p, 'G');
        } else if (strcmp(token, "H") == 0){
            variaveis(p, 'H');
        } else if (strcmp(token, "I") == 0){
            variaveis(p, 'I');
        } else if (strcmp(token, "J") == 0){
            variaveis(p, 'J');
        } else if (strcmp(token, "K") == 0){
            variaveis(p, 'K');
        } else if (strcmp(token, "L") == 0){
            variaveis(p, 'L');
        } else if (strcmp(token, "M") == 0){
            variaveis(p, 'M');
        } else if (strcmp(token, "N") == 0){
            variaveis(p, 'N');
        } else if (strcmp(token, "O") == 0){
            variaveis(p, 'O');
        } else if (strcmp(token, "P") == 0){
            variaveis(p, 'P');
        } else if (strcmp(token, "Q") == 0){
            variaveis(p, 'Q');
        } else if (strcmp(token, "R") == 0){
            variaveis(p, 'R');
        } else if (strcmp(token, "S") == 0){
            variaveis(p, 'S');
        } else if (strcmp(token, "T") == 0){
            variaveis(p, 'T');
        } else if (strcmp(token, "U") == 0){
            variaveis(p, 'U');
        } else if (strcmp(token, "V") == 0){
            variaveis(p, 'V');
        } else if (strcmp(token, "W") == 0){
            variaveis(p, 'W');
        } else if (strcmp(token, "X") == 0){
            variaveis(p, 'X');
        } else if (strcmp(token, "Y") == 0){
            variaveis(p, 'Y');
        } else if (strcmp(token, "Z") == 0){
            variaveis(p, 'Z');
//            alteração dos valores das variavies
        } else if (strcmp(token, ":A") == 0){
            add_valor(p, 'A');
        } else if (strcmp(token, ":B") == 0){
            add_valor(p, 'B');
        } else if (strcmp(token, ":C") == 0){
            add_valor(p, 'C');
        } else if (strcmp(token, ":D") == 0){
            add_valor(p, 'D');
        } else if (strcmp(token, ":E") == 0){
            add_valor(p, 'E');
        } else if (strcmp(token, ":F") == 0){
            add_valor(p, 'F');
        } else if (strcmp(token, ":G") == 0){
            add_valor(p, 'G');
        } else if (strcmp(token, ":H") == 0){
            add_valor(p, 'H');
        } else if (strcmp(token, ":I") == 0){
            add_valor(p, 'I');
        } else if (strcmp(token, ":J") == 0){
            add_valor(p, 'J');
        } else if (strcmp(token, ":K") == 0){
            add_valor(p, 'K');
        } else if (strcmp(token, ":L") == 0){
            add_valor(p, 'L');
        } else if (strcmp(token, ":M") == 0){
            add_valor(p, 'M');
        } else if (strcmp(token, ":N") == 0){
            add_valor(p, 'N');
        } else if (strcmp(token, ":O") == 0){
            add_valor(p, 'O');
        } else if (strcmp(token, ":P") == 0){
            add_valor(p, 'P');
        } else if (strcmp(token, ":Q") == 0){
            add_valor(p, 'Q');
        } else if (strcmp(token, ":R") == 0){
            add_valor(p, 'R');
        } else if (strcmp(token, ":S") == 0){
            add_valor(p, 'S');
        } else if (strcmp(token, ":T") == 0){
            add_valor(p, 'T');
        } else if (strcmp(token, ":U") == 0){
            add_valor(p, 'U');
        } else if (strcmp(token, ":U") == 0){
            add_valor(p, 'U');
        } else if (strcmp(token, ":V") == 0){
            add_valor(p, 'V');
        } else if (strcmp(token, ":W") == 0){
            add_valor(p, 'W');
        } else if (strcmp(token, ":X") == 0){
            add_valor(p, 'X');
        } else if (strcmp(token, ":Y") == 0){
            add_valor(p, 'Y');
        } else if (strcmp(token, ":Z") == 0){
            add_valor(p, 'Z');
        }
    }
    PRINT_STACK(p);
}
