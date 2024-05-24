/**
 * @file Este ficheiro contém todas as funções associadas à stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

/**
 * \brief Esta função converte outros tipos diferentes de double para double
 * @param d Elemento d de determinado tipo que será convertido para double
 * @returns double Retorna valores em double
 */
double GET_AS_DOUBLE(Data d){
    switch (d.tipo) {
        case CHAR: return d.CHAR;
        case LONG: return d.LONG;
        case DOUBLE: return d.DOUBLE;
        default: assert(0 && "inconvertivel");
    }
}
/**
 * \brief Esta função converte outros tipos diferentes de long para long
 * @param d Elemento d de determinado tipo que será convertido para long
 * @returns long Retorna valores em long
 */
long GET_AS_LONG(Data d){
    switch (d.tipo) {
        case CHAR: return d.CHAR;
        case LONG: return d.LONG;
        case DOUBLE: return d.DOUBLE;
        default: assert(0 && "inconvertivel");
    }
}
/**
 * \brief Esta função converte outros tipos diferentes de char para char
 * @param d Elemento d de determinado tipo que será convertido para char
 * @returns Retorna valores em char
 */
char GET_AS_CHAR(Data d){
    switch (d.tipo) {
        case CHAR: return d.CHAR;
        case LONG: return d.LONG;
        case DOUBLE: return d.DOUBLE;
        default: assert(0 && "inconvertivel");
    }
}
/**
 * \brief A função has_type indica o tipo do elemento e o número de bytes utilizados
 *
 * @param elem Elemento de um determinado tipo Data
 * @param bytes Número de bytes utilizados pelo elemento
 * @returns Retorna o tipo do elemento analisado e os bytes respetivos
 */
int has_type (Data elem, int bytes){
    return (elem.tipo & bytes);
}
/**
 * \brief Função que retribui informações sobre a estrutura Stack
 * @returns p apontador para a MyStack*
 */
MyStack *inicia_MyStack(void){
    MyStack *p = (MyStack *) calloc(1, sizeof(MyStack));
    p->size = 100;
    p->stack = (Data *) calloc(p->size, sizeof(Data));
    return p;
}
/**
 * \brief Retira o elemento que está no topo da stack
 * @param p Apontador para a stack
 * @returns Retorna a stack sem o elemento do topo
 */
Data topo(MyStack *p) {
  return p->stack[p->n_elementos - 1];
}
/**
 * \brief Função que imprime a stack
 * @param p Apontador para a stack
 */
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
/**
 * \brief Responsável por desempilhar elementos numa stack
 * @param p Apontador para a stack
 * @returns Data Retorna a stack alterada
 */
Data POP(MyStack *p) {
  p->n_elementos--;
  return p->stack[p->n_elementos];
}
/**
 * \brief Responsável por empilhar elementos na stack
 * @param p Apomtador para a stack
 * @param elem Um dado elemento de um dado tipo
 */
void PUSH(MyStack *p, Data elem) {
  if(p->size == p->n_elementos) {
    p->size += 100;
    p->stack = (Data *) realloc(p->stack, p->size * sizeof(Data));
  }
  p->stack[p->n_elementos] = elem;
  p->n_elementos++;
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

 
