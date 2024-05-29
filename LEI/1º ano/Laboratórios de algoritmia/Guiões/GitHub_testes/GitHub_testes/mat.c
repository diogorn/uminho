#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "stack.h"
#include "mat.h" // NOSSA math
#include <math.h> // inclui a MATH definida no C

void soma (MyStack *p){
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
}

void subtracao (MyStack *p){
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
}

void multiplicacao (MyStack *p){
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
}

void divisao (MyStack *p){
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
}

void expoente (MyStack *p){
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
}

void e_comercial (MyStack *p){
    Data x = POP(p);
    long dx = GET_AS_LONG(x);
    Data y = POP(p);
    long dy =  GET_AS_LONG(y);;
    PUSH_LONG(p, dx&dy);
}

void ou_barra (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    Data y = POP(p);
    long ly =  GET_AS_LONG(y);
    PUSH_LONG(p, lx|ly);
}

void my_xor (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    Data y = POP(p);
    long ly =  GET_AS_LONG(y);
    PUSH_LONG(p, lx^ly);
}

void my_not (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    PUSH_DOUBLE(p, ~ lx);
}

void resto_div (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    Data y = POP(p);
    long ly =  GET_AS_LONG(y);
    PUSH_LONG(p,(ly%lx));
}

void decrementar (MyStack *p){
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
}

void incrementar (MyStack *p){
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
}

void duplicar (MyStack *p){
    Data x = POP(p);
    PUSH(p, x);
    PUSH(p, x);
}

void my_pop (MyStack *p){
    p->n_elementos--;
}

void trocar_2 (MyStack *p){
    Data x = POP(p);
    Data y = POP(p);
    PUSH(p, x);
    PUSH(p, y);
}

void roda_3 (MyStack *p){
    Data x = POP(p);
    Data y = POP(p);
    Data z = POP(p);
    PUSH(p, y);
    PUSH(p, x);
    PUSH(p, z);
}

void copia (MyStack *p){
    long posicaoDoN = GET_AS_LONG(POP(p));
    long idx = p->n_elementos-1 - posicaoDoN;
    
    Data valor  = p->stack[idx];
    PUSH(p, valor);
}

void ler_linha (MyStack *p){
    char readline[SIZE];
    char *l = strdup(fgets(readline, SIZE, stdin));
    PUSH_STRING(p, l);
}

void imprimeTopo (MyStack *p){
//    Data x = POP(p);
//    PUSH(p, x);
//    PRINT_TOP(x);
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
    
}

void converte_int (MyStack *p){
    if (has_type(topo(p), STRING)) {
        char *sx = POP_STRING(p);
        PUSH_LONG(p, atoi(sx));
    } else {
        long lx = GET_AS_LONG(POP(p));
        PUSH_LONG(p, lx);
    }
}

void converteFloat (MyStack *p){
    if (has_type(topo(p), STRING)) {
        char *sx = POP_STRING(p);
        PUSH_DOUBLE(p, atof(sx));
    } else {
        double dx = GET_AS_DOUBLE(POP(p));
        PUSH_DOUBLE(p, dx);
    }
}

void converteChar (MyStack *p){
    Data x = POP(p);
    char cx = GET_AS_CHAR(x);
    PUSH_CHAR(p, cx);
}

void igual (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dx == dy) {
        PUSH_DOUBLE(p, 1);
    } else {
        PUSH_DOUBLE(p, 0);
    }
}

void menor (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dy < dx) {
        PUSH_LONG(p, 1);
    } else {
        PUSH_LONG(p, 0);
    }
}

void maior (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dy > dx) {
        PUSH_LONG(p, 1);
    } else {
        PUSH_LONG(p, 0);
    }
}

void negacao (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    if (lx == 0) {
        PUSH_LONG (p, 1);
    } else {
        PUSH_LONG (p, 0);
    }
}

void e_shortcut (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dy == 0) {
        PUSH_DOUBLE(p, 0);
    } else {
        PUSH_DOUBLE(p, dx);
}
}

void ou_shortcut (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dy != 0) {
        PUSH_DOUBLE(p, dy);
    } else {
        PUSH_DOUBLE(p, dx);
    }
}

void menor_entre_2 (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dy<dx) {
        PUSH_DOUBLE(p, dy);
    } else {
        PUSH_DOUBLE(p, dx);
    }
}
    
void maior_entre_2 (MyStack *p){
    Data x = POP(p);
    double dx = GET_AS_DOUBLE(x);
    Data y = POP(p);
    double dy = GET_AS_DOUBLE(y);
    if (dy>dx) {
        PUSH_DOUBLE(p, dy);
    } else {
        PUSH_DOUBLE(p, dx);
    }
}

void ifThenElse (MyStack *p){
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
}

#define MyStack_OPERATION(_tipo, _name)         \
  void PUSH_##_name(MyStack *p, _tipo val) {    \
    Data elem;                                  \
    elem.tipo = _name;                          \
    elem._name = val;                           \
    PUSH(p, elem);                              \
  }                                             \
  _tipo POP_##_name(MyStack *p) {               \
    Data elem = POP(p);                         \
    assert(elem.tipo == _name);                 \
    return elem._name;                          \
  }

MyStack_OPERATION(long, LONG)
MyStack_OPERATION(double, DOUBLE)
MyStack_OPERATION(char, CHAR)
MyStack_OPERATION(char *, STRING)

