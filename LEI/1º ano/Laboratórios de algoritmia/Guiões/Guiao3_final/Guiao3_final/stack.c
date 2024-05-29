#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
// conversoes de tipos
double GET_AS_DOUBLE(Data d){
    switch (d.tipo) {
        case CHAR: return d.CHAR;
        case LONG: return d.LONG;
        case DOUBLE: return d.DOUBLE;
        default: assert(0 && "inconvertivel");
    }
}

long GET_AS_LONG(Data d){
    switch (d.tipo) {
        case CHAR: return d.CHAR;
        case LONG: return d.LONG;
        case DOUBLE: return d.DOUBLE;
        default: assert(0 && "inconvertivel");
    }
}

char GET_AS_CHAR(Data d){
    switch (d.tipo) {
        case CHAR: return d.CHAR;
        case LONG: return d.LONG;
        case DOUBLE: return d.DOUBLE;
        default: assert(0 && "inconvertivel");
    }
}

int has_type (Data elem, int bytes){
    return (elem.tipo & bytes);
}
// Funções que retribuem infos da stack
MyStack *inicia_MyStack(){
    MyStack *p = (MyStack *) calloc(1, sizeof(MyStack));
    p->size = 100;
    p->stack = (Data *) calloc(p->size, sizeof(Data));
    return p;
}
// está inutilizada !! Delete ¿?
int is_empty(MyStack *p) {
  return p->n_elementos == 0;
}

Data topo(MyStack *p) {
  return p->stack[p->n_elementos - 1];
}

void PRINT_STACK(MyStack *p) {
    for (int i=0; i < p->n_elementos; i++){
        Data elem = p->stack[i];
        TYPE wichType = elem.tipo;
        
        switch(wichType){
            case LONG:
                printf("%ld", elem.LONG);
                break;
            case DOUBLE:
                printf("%g", elem.DOUBLE);
                break;
            case CHAR:
                printf("%c", elem.CHAR);
                break;
            case STRING:
                printf("%s", elem.STRING);
                break;
        }
    }
    printf("\n");
}


// operações na stack
Data POP(MyStack *p) {
  p->n_elementos--;
  return p->stack[p->n_elementos];
}

void PUSH(MyStack *p, Data elem) {
  if(p->size == p->n_elementos) {
    p->size += 100;
    p->stack = (Data *) realloc(p->stack, p->size * sizeof(Data));
  }
  p->stack[p->n_elementos] = elem;
  p->n_elementos++;
}

// recebe um long e devolve um Data
Data make_long (long l){
    Data x;
    x.tipo = LONG;
    x.LONG = l;
    return x;
}
// double -> Data
Data make_double (double d){
    Data x;
    x.tipo = DOUBLE;
    x.DOUBLE = d;
    return x;
}
// char -> Data
Data make_char (char c){
    Data x;
    x.tipo = CHAR;
    x.CHAR = c;
    
    return x;
}

// copia o topo da stack da variável
// :
// mudança de nome: conteudo -> add valor
void add_valor (MyStack *p, char letra)  {
    Data x = topo(p);
    if (has_type(x, LONG)) {
        p->array[letra-'A'] = x;
    } else if (has_type(x, DOUBLE)){
        p->array[letra-'A'] = x;
    } else if (has_type(x, CHAR)){
        p->array[letra-'A'] = x;
    }
}

// Push do conteudo da variavel
// mudança de nome: da_valor -> variaveis
void variaveis(MyStack *p, char letra){
    Data x =  p->array[letra-'A'];
    
    if (has_type(x, LONG)) {
        PUSH_LONG(p, x.LONG);
    } else if (has_type(x, DOUBLE)){
        PUSH_DOUBLE(p, x.DOUBLE);
    } else if (has_type(x, CHAR)){
        PUSH_CHAR(p, x.CHAR);
    } else if (has_type(x, STRING)){
        PUSH_STRING(p, x.STRING);
    }
}

void variaveis_pre_definidas(MyStack *p){
    for (int i=0; i<=5; i++) {
        p->array[i] = make_long(10+i);
    }
    for (int i=23; i<26;i++){
        p->array[i] = make_long(i-23);
    }
    p->array[13] = make_char('\n');
    p->array[18] = make_char(' ');
}



// macros

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

