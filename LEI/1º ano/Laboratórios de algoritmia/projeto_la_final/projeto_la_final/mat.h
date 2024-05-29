#ifndef mat_h
#define mat_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "stack.h"

void soma (MyStack *p);
void subtracao (MyStack *p);
void multiplicacao (MyStack *p);
void divisao (MyStack *p);
void expoente (MyStack *p);
void e_comercial (MyStack *p);
void ou_barra (MyStack *p);
void my_xor (MyStack *p);
void my_not (MyStack *p);
void resto_div (MyStack *p);
void decrementar (MyStack *p);
void incrementar (MyStack *p);
void duplicar (MyStack *p);
void my_pop (MyStack *p);
void trocar_2 (MyStack *p);
void roda_3 (MyStack *p);
void copia (MyStack *p);
void ler_linha (MyStack *p);
void imprimeTopo (MyStack *p);
void converte_int (MyStack *p);
void converteFloat (MyStack *p);
void converteChar (MyStack *p);
void igual (MyStack *p);
void menor (MyStack *p);
void maior (MyStack *p);
void negacao (MyStack *p);
void e_shortcut (MyStack *p);
void ou_shortcut (MyStack *p);
void menor_entre_2 (MyStack *p);
void maior_entre_2 (MyStack *p);
void ifThenElse (MyStack *p);

Data make_long (long l);
Data make_char (char c);

void add_valor (MyStack *p, char letra);
void variaveis(MyStack *p, char letra);
void variaveis_pre_definidas(MyStack *p);


#endif /* mat_h */
