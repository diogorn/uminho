/**
 * @file Ficheiro que contém as operações matemáticas, lógicas, conversores, expressões de input/output e da stack
 */
#include "mat.h"
#include "stack.h"
#include <math.h>

/**
 * \brief Faz a soma de dois elementos
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Faz a subtração de dois elementos
 *
 * @param p Apontador para a stack
 */
void subtracao (MyStack *p){
    Data x = POP(p);
    Data y = POP(p);

    if (has_type(x, LONG) & has_type(y, LONG)) {
        long lx = GET_AS_LONG(x);
        long ly = GET_AS_LONG(y);
        PUSH_LONG(p, lx-ly);
    } else {
        double dx = GET_AS_DOUBLE(x);
        double dy =  GET_AS_DOUBLE(y);
        PUSH_DOUBLE(p, dx-dy);
    }
}
/**
 * \brief Faz a multiplicação de dois elementos
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Divide um elemento pelo outro
 *
 * @param p Apontador para a stack
 */
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
        PUSH_DOUBLE(p, dx/dy);
    }
}
/**
 * \brief Eleva a variável dx à variável dy
 *
 * @param p Apontador para a stack
 */
void expoente (MyStack *p){
    Data x = POP(p);
    Data y = POP(p);
    if (has_type(x, LONG) & has_type(y, LONG)) {
        long lx = GET_AS_LONG(x);
        long ly = GET_AS_LONG(y);
        PUSH_LONG(p, pow(lx,ly));
    } else {
        double dx = GET_AS_DOUBLE(x);
        double dy =  GET_AS_DOUBLE(y);
        PUSH_DOUBLE(p, pow(dx, dy));
    }
}
/**
 * \brief Faz o "E" lógico entre doia valores, em que o 0 é verdadeiro e o 1 é falso
 *
 * @param p Apontador para a stack
 */
void e_comercial (MyStack *p){
    Data x = POP(p);
    long dx = GET_AS_LONG(x);
    Data y = POP(p);
    long dy =  GET_AS_LONG(y);;
    PUSH_LONG(p, dx&dy);
}
/**
 * \brief Faz o "Ou" lógico entre doia valores, em que o 0 é verdadeiro e o 1 é falso
 *
 * @param p Apontador para a stack
 */
void ou_barra (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    Data y = POP(p);
    long ly =  GET_AS_LONG(y);
    PUSH_LONG(p, lx|ly);
}
/**
 * \brief
 *
 * @param p Apontador para a stack
 */
void my_xor (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    Data y = POP(p);
    long ly =  GET_AS_LONG(y);
    PUSH_LONG(p, lx^ly);
}
/**
 * \brief Faz a negação do elemento
 *
 * @param p Apontador para a stack
 */
void my_not (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    PUSH_DOUBLE(p, ~ lx);
}
/**
 * \brief Determina o resto da divisão entre dois elementos
 *
 * @param p Apontador para a stack
 */
void resto_div (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    Data y = POP(p);
    long ly =  GET_AS_LONG(y);
    PUSH_LONG(p,(ly%lx));
}
/**
 * \brief Decrementa 1 unidade ao elemento
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Incrementa 1 unidade ao elemento
 *
 * @param p Apontador para a stack
 */
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
/**
 *\brief Duplica o elemento, isto é, dá push duas vezes desse elemento na stack de forma que apareça em duplicado
 *
 * @param p Apontador para a stack
 */
void duplicar (MyStack *p){
    Data x = POP(p);
    PUSH(p, x);
    PUSH(p, x);
}
/**
 * \brief Dá pop do último elemento da stack
 *
 * @param p Apontador para a stack
 */
void my_pop (MyStack *p){
    p->n_elementos--;
}
/**
 * \brief Troca os dois elementos do topo da stack
 *
 * @param p Apontador para a stack
 */
void trocar_2 (MyStack *p){
    Data x = POP(p);
    Data y = POP(p);
    PUSH(p, x);
    PUSH(p, y);
//    *(int*)0 = 0;
}
/**
 * \brief Roda os 3 elementos no topo da stack
 *
 * @param p Apontador para a stack
 */
void roda_3 (MyStack *p){
    Data x = POP(p);
    Data y = POP(p);
    Data z = POP(p);
    PUSH(p, y);
    PUSH(p, x);
    PUSH(p, z);
}
/**
 * \brief Copia n-ésimo elemento para o topo da stack0 é o topo da stack
 *
 * @param p Apontador para a stack
 */
void copia (MyStack *p){
    long posicaoDoN = GET_AS_LONG(POP(p));
    long idx = p->n_elementos-1 - posicaoDoN;
    
    Data valor  = p->stack[idx];
    PUSH(p, valor);
}
/**
 * \brief Lê uma linha
 *
 * @param p Apontador para a stack
 */
void ler_linha (MyStack *p){
    char readline[SIZE];
    char *l = strdup(fgets(readline, SIZE, stdin));
    PUSH_STRING(p, l);
}
/**
 * \brief Imprime o topo da stack
 *
 * @param p Apontador para a stack
 */
void imprimeTopo (MyStack *p){
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
/**
 * \brief Converte o topo da stack num inteiro
 *
 * @param p Apontador para a stack
 */
void converte_int (MyStack *p){
    if (has_type(topo(p), STRING)) {
        char *sx = POP_STRING(p);
        PUSH_LONG(p, atoi(sx));
    } else {
        long lx = GET_AS_LONG(POP(p));
        PUSH_LONG(p, lx);
    }
}
/**
 * \brief Converter o topo da stack num float
 *
 * @param p Apontador para a stack
 */
void converteFloat (MyStack *p){
    if (has_type(topo(p), STRING)) {
        char *sx = POP_STRING(p);
        PUSH_DOUBLE(p, atof(sx));
    } else {
        double dx = GET_AS_DOUBLE(POP(p));
        PUSH_DOUBLE(p, dx);
    }
}
/**
 * \brief Converter o topo da stack num char
 *
 * @param p Apontador para a stack
 */
void converteChar (MyStack *p){
    Data x = POP(p);
    char cx = GET_AS_CHAR(x);
    PUSH_CHAR(p, cx);
}
/**
 * \brief Determina se os dois elementos são iguais, caso negativo retorna 0
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Indica o menor entre dois elementos
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Indica o maior de dois elementos
 *
 * @param p Apontador para a stack
 */

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
/**
 * \brief Faz a negação do último elemento da stack
 *
 * @param p Apontador para a stack
 */
void negacao (MyStack *p){
    Data x = POP(p);
    long lx = GET_AS_LONG(x);
    if (lx == 0) {
        PUSH_LONG (p, 1);
    } else {
        PUSH_LONG (p, 0);
    }
}
/**
 * \brief Retorna 1 se os bits dos dois operandos forem 1. Caso um dos bits seja 0 retorna 0.
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Retorna 1 se pelo menos um bit dos dois operandos for 1
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Indica o menor entre os dois últimos elementos da stack
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Indica o maior entre os dois últimos elementos da stack
 *
 * @param p Apontador para a stack
 */
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
/**
 * \brief Retorna o parâmetro do then se a condição for falsa. Caso contrário retorna o que está no parametro else.
 *
 * @param p Apontador para a stack
 */
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

// recebe um long e devolve um Data
/**
 * \brief A função make_long tranforma um elemento do tipo long num elemento do tipo Data
 * @param l Variável do tipo long
 * @returns Um valor do tipo data
 */
Data make_long (long l){
    Data x;
    x.tipo = LONG;
    x.LONG = l;
    return x;
}
/**
 * \brief A função make_long tranforma um elemento do tipo char num elemento do tipo Data
 * @param l Variável do tipo long
 * @returns Um valor do tipo data
 */
Data make_char (char c){
    Data x;
    x.tipo = CHAR;
    x.CHAR = c;
    
    return x;
}
/**
 * \brief A função add_valor copia o topo da Stack à variável
 *
 * @param p Apontador para a stack
 * @param letra Um argumento do tipo char
 */
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
/**
 * \brief Esta função faz o push do conteúdo da variável
 *
 * @param p Apontador para a stack
 * @param letra Um argumento do tipo char
 */
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
/**
 * \brief Esta função identifica as variáveis pré-definidas atribuindo-lhes os valores correspondetes, por omissão
 *
 * @param p Apontador para a stack
 */
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
