#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <assert.h>
#define SIZE 10240

MyStack inicia_Stack (){
    MyStack p;
    p.topo = -1;
    return p;
}

void PRINT_STACK(MyStack *p){
    int i;
    for (i=0; i <= p->topo; i++){
        printf("%ld",p->a[i]);
    }
    printf("\n");
}

int vazia (MyStack p){
    if(p.topo == -1){
        return 1;
    } else {
        return 0;
    }
}

int cheia (MyStack p){
    if(p.topo == SIZE-1){
        return 1;
    } else {
        return 0;
    }
}

void PUSH (MyStack *p, long x){
    if(cheia(*p) == 1){
        printf ("Pilha Cheia!");
    } else {
        p->topo++;
        p->a[p->topo] = x; //vamos guardar a variavel x e guardar dentro da pilha na posição topo
    }
}

long POP (MyStack *p){
    long aux; // recebe o valor da pilha para depois retornar
    assert (!vazia (*p));
     
        
    aux = p->a[p->topo];
        p->topo--;
    
    return aux;
}
