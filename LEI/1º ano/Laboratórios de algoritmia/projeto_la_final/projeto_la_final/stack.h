/**
  *@file Ficheiro                 !!!!!!!!!!!!!!!!!!!!!!           .
  *\brief Neste ficheiro está presente mascáras, estruturas de dados e de stack,bem omo funções utilizadas na stack.
  *@returns                    !!!!!!!!!!!!!!!!!!!!!!!!!!
 */
#ifndef stack_h
#define stack_h

#define SIZE 10240
/**
 * Struct que enumera os tipos e que vai aplicá-los na struct data.
 */
typedef enum tipo{
    LONG = 1,    /**< Tipo Long com o valor 1 (2⁰) associado */
    DOUBLE = 2,  /**< Tipo Double com o valor 2 (2¹) associado */
    CHAR = 4,    /**< Tipo Char com o valor 4 (2²) associado */
    STRING = 8   /**< Tipo String com o valor 8 (2³) associado */

}TYPE;

/**
 * Uma struct que nos dá os tipos de dados que estamos a usar na stack
 */
typedef struct TipoDados{
    TYPE tipo;
    long LONG;
    double DOUBLE;
    char CHAR;
    char *STRING;
}Data ;
/**
 * \struct Stack
 * \brief Esta estrutura representa a Stack
 */
typedef struct Pilha{
    Data array[26];
    Data *stack;
    int size;
    int n_elementos;
}MyStack;


/**
 * \brief Definição dos protótipos das funções utilizadas na stack.
 */
MyStack *inicia_MyStack(void);
Data topo(MyStack *p);
void PRINT_STACK(MyStack *p);

Data POP(MyStack *p);
void PUSH(MyStack *p, Data elem);

int has_type(Data elem, int bytes);
double GET_AS_DOUBLE(Data d);
long GET_AS_LONG(Data d);
char GET_AS_CHAR(Data d);


/**
 * \brief Definição de uma macro para os operadores da stack.
 */
#define MyStack_OPERATION_PROTO(_tipo, _name)   \
  void PUSH_##_name(MyStack *p, _tipo val);     \
_tipo POP_##_name(MyStack *p);
MyStack_OPERATION_PROTO(long, LONG)
MyStack_OPERATION_PROTO(double, DOUBLE)
MyStack_OPERATION_PROTO(char, CHAR)
MyStack_OPERATION_PROTO(char *, STRING)


#endif /* stack_h */
