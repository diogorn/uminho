#ifndef stack_h
#define stack_h

#include <stdio.h>

#define SIZE 10240

typedef enum tipo{
    LONG=1, DOUBLE=2, CHAR=4, STRING=8

}TYPE;

typedef struct TipoDados{
    TYPE tipo;
    long LONG;
    double DOUBLE;
    char CHAR;
    char *STRING;
}Data ;

typedef struct Pilha{
    Data array[26];
    Data *stack;
    int size;
    int n_elementos;
}MyStack;



MyStack *inicia_MyStack();
int is_empty(MyStack *p); // inutil ¿?
Data topo(MyStack *p);
void PRINT_STACK(MyStack *p);

Data POP(MyStack *p);
void PUSH(MyStack *p, Data elem);

// identifica tipo
int has_type(Data elem, int bytes);
//conversores de Data->long/double/char
double GET_AS_DOUBLE(Data d);
long GET_AS_LONG(Data d);
char GET_AS_CHAR(Data d);

// Recebe long/double/char ->Data
Data make_long (long l);
Data make_double (double d);
Data make_char (char c);

void add_valor (MyStack *p, char letra);
void variaveis(MyStack *p, char letra);
void variaveis_pre_definidas(MyStack *p);


// macros
#define MyStack_OPERATION_PROTO(_tipo, _name)   \
  void PUSH_##_name(MyStack *p, _tipo val);     \
_tipo POP_##_name(MyStack *p);
MyStack_OPERATION_PROTO(long, LONG)
MyStack_OPERATION_PROTO(double, DOUBLE)
MyStack_OPERATION_PROTO(char, CHAR)
MyStack_OPERATION_PROTO(char *, STRING)


#endif /* stack_h */
