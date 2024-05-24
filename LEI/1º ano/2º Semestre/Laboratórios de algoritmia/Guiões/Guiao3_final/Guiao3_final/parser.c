#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "parser.h"
#include "stack.h"

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
            Data x = POP(p);
            Data y = POP(p);
            if (has_type(x, LONG) & has_type(y, LONG)) {
                long lx = GET_AS_LONG(x);
                long ly = GET_AS_LONG(y);
                PUSH_LONG(p, ly+lx);
            } else {
               double dx = GET_AS_DOUBLE(x);
               double dy =  GET_AS_DOUBLE(y);
                PUSH_DOUBLE(p, dy+dx);
            }
        } else if (strcmp(token, "-") == 0){
            Data x = POP(p);
            Data y = POP(p);
            if (has_type(x, LONG) & has_type(y, LONG)) {
                long lx = GET_AS_LONG(x);
                long ly = GET_AS_LONG(y);
                PUSH_LONG(p, ly-lx);
            } else {
               double dx = GET_AS_DOUBLE(x);
               double dy =  GET_AS_DOUBLE(y);
                PUSH_DOUBLE(p, dy-dx);
            }
        } else if (strcmp(token, "*") == 0){
            Data x = POP(p);
            Data y = POP(p);
            if (has_type(x, LONG) & has_type(y, LONG)) {
                long lx = GET_AS_LONG(x);
                long ly = GET_AS_LONG(y);
                PUSH_LONG(p, ly*lx);
            } else {
               double dx = GET_AS_DOUBLE(x);
               double dy =  GET_AS_DOUBLE(y);
                PUSH_DOUBLE(p, dy*dx);
            }
        } else if (strcmp(token, "/") == 0){
            Data x = POP(p);
            Data y = POP(p);
            if (has_type(x, LONG) & has_type(y, LONG)) {
                long lx = GET_AS_LONG(x);
                long ly = GET_AS_LONG(y);
                PUSH_LONG(p, ly/lx);
            } else {
               double dx = GET_AS_DOUBLE(x);
               double dy =  GET_AS_DOUBLE(y);
                PUSH_DOUBLE(p, dy/dx);
            }
        } else if (strcmp(token, "#") == 0){
            Data x = POP(p);
            Data y = POP(p);
            if (has_type(x, LONG) & has_type(y, LONG)) {
                long lx = GET_AS_LONG(x);
                long ly = GET_AS_LONG(y);
                PUSH_LONG(p, pow(ly,lx));
            } else {
               double dx = GET_AS_DOUBLE(x);
               double dy =  GET_AS_DOUBLE(y);
                PUSH_DOUBLE(p, pow(dy, dx));
            }
        } else if (strcmp(token, "&") == 0){
            Data x = POP(p);
            long dx = GET_AS_LONG(x);
            Data y = POP(p);
            long dy =  GET_AS_LONG(y);;
            PUSH_LONG(p, dx&dy);
        } else if (strcmp(token, "|") == 0){
            Data x = POP(p);
            long lx = GET_AS_LONG(x);
            Data y = POP(p);
            long ly =  GET_AS_LONG(y);
            PUSH_LONG(p, lx|ly);
        } else if (strcmp(token, "^") == 0){
            Data x = POP(p);
            long lx = GET_AS_LONG(x);
            Data y = POP(p);
            long ly =  GET_AS_LONG(y);
            PUSH_LONG(p, lx^ly);
        } else if (strcmp(token, "~") == 0){
            Data x = POP(p);
            long lx = GET_AS_LONG(x);
            PUSH_DOUBLE(p, ~ lx);
        } else if (strcmp(token, "%")==0){
            Data x = POP(p);
            long lx = GET_AS_LONG(x);
            Data y = POP(p);
            long ly =  GET_AS_LONG(y);
            PUSH_LONG(p,(ly%lx));
        } else if (strcmp(token, "(")==0){
            Data x = POP(p);
            if (has_type(x, LONG)) {
                long lx = GET_AS_LONG(x);
                PUSH_LONG(p, lx-1);
            } else if ( has_type(x, DOUBLE)){
               double dx = GET_AS_DOUBLE(x);
                PUSH_DOUBLE(p, dx-1);
            } else if (has_type(x, CHAR)){
                char cx = GET_AS_CHAR(x);
                PUSH_CHAR(p, cx-1);
            }
        } else if (strcmp(token, ")")==0){
            Data x = POP(p);
            if (has_type(x, LONG)) {
                long lx = GET_AS_LONG(x);
                PUSH_LONG(p, lx+1);
            } else if ( has_type(x, DOUBLE)){
               double dx = GET_AS_DOUBLE(x);
                PUSH_DOUBLE(p, dx+1);
            } else if (has_type(x, CHAR)){
                char cx = GET_AS_CHAR(x);
                PUSH_CHAR(p, cx+1);
            }
//            manipulação da stack -- GUIAO 2
        } else if (strcmp(token, "_") == 0){
            Data x = POP(p);
            PUSH(p, x);
            PUSH(p, x);
        } else if (strcmp(token, ";") == 0){
            p->n_elementos--;
        } else if (strcmp(token, "\\") == 0){
            Data x = POP(p);
            Data y = POP(p);
            PUSH(p, x);
            PUSH(p, y);
        } else if (strcmp(token, "@") == 0){
            Data x = POP(p);
            Data y = POP(p);
            Data z = POP(p);
            PUSH(p, y);
            PUSH(p, x);
            PUSH(p, z);
        } else if (strcmp(token, "$") == 0){
            long posicaoDoN = GET_AS_LONG(POP(p));
            long idx = p->n_elementos-1 - posicaoDoN;
            Data valor  = p->stack[idx];
            PUSH(p, valor);
//            le linhas e tipos
        } else if (strcmp(token, "l") == 0){
            char readline[SIZE];
            char *l = strdup(fgets(readline, SIZE, stdin));
            PUSH_STRING(p, l);
        } else if (strcmp(token, "p") == 0){
            Data x = topo(p);
            TYPE wichType = x.tipo;
            
                switch(wichType){
                    case LONG:
                        printf("%ld", x.LONG);
                        break;
                    case DOUBLE:
                        printf("%g", x.DOUBLE);
                        break;
                    case CHAR:
                        printf("%c", x.CHAR);
                        break;
                    case STRING:
                        printf("%s", x.STRING);
                        break;
                }
            printf("\n");
            
        } else if (strcmp(token, "i") == 0){
            if (has_type(topo(p), STRING)) {
                char *sx = POP_STRING(p);
                PUSH_LONG(p, atoi(sx));
            } else {
                long lx = GET_AS_LONG(POP(p));
                PUSH_LONG(p, lx);
            }
        } else if (strcmp(token, "f") == 0){
            if (has_type(topo(p), STRING)) {
                char *sx = POP_STRING(p);
                PUSH_DOUBLE(p, atof(sx));
            } else {
                double dx = GET_AS_DOUBLE(POP(p));
                PUSH_DOUBLE(p, dx);
            }
        } else if (strcmp(token, "c") == 0){
            Data x = POP(p);
            char cx = GET_AS_CHAR(x);
            PUSH_CHAR(p, cx);
//            logica -- GUIAO 3
        } else if (strcmp(token, "=")==0) {
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dx == dy) {
                PUSH_DOUBLE(p, 1);
            } else {
                PUSH_DOUBLE(p, 0);
            }
        } else if (strcmp(token, "<")==0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dy < dx) {
                PUSH_LONG(p, 1);
            } else {
                PUSH_LONG(p, 0);
            }
        } else if (strcmp(token, ">")==0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dy > dx) {
                PUSH_LONG(p, 1);
            } else {
                PUSH_LONG(p, 0);
            }
        } else if (strcmp(token, "!") == 0){
            Data x = POP(p);
            long lx = GET_AS_LONG(x);
            if (lx == 0) {
                PUSH_LONG (p, 1);
            } else {
                PUSH_LONG (p, 0);
            }
        } else if (strcmp(token, "e&") == 0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dy == 0) {
                PUSH_DOUBLE(p, 0);
            } else {
                PUSH_DOUBLE(p, dx);
            }
        } else if (strcmp(token, "e|") == 0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dy != 0) {
                PUSH_DOUBLE(p, dy);
            } else {
                PUSH_DOUBLE(p, dx);
            }
            
        } else if (strcmp(token, "e<") == 0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dy<dx) {
                PUSH_DOUBLE(p, dy);
            } else {
                PUSH_DOUBLE(p, dx);
            }
        } else if (strcmp(token, "e>") == 0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            if (dy>dx) {
                PUSH_DOUBLE(p, dy);
            } else {
                PUSH_DOUBLE(p, dx);
            }
        } else if (strcmp(token, "?") == 0){
            Data x = POP(p);
            double dx = GET_AS_DOUBLE(x);
            Data y = POP(p);
            double dy = GET_AS_DOUBLE(y);
            Data z = POP(p);
            double dz = GET_AS_DOUBLE(z);
            if (dz != 0){
                PUSH_DOUBLE(p, dy);
            }else {
                PUSH_DOUBLE(p, dx);
            }
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

