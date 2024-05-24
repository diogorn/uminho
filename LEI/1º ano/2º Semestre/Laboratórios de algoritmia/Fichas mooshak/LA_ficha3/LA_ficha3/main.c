//
//  main.c
//  LA_ficha3
//
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void asteriscos (int a){
    
    while (a>0) {
        putchar('*');
        a--;
    }
    
}

void pontos (int b){
    while (b>0){
        putchar('.');
        b--;

    }
}

int main (){
    
    int d;
    printf("Dimenção: ");
    assert(scanf("%d", &d) == 1);
    
    int l;
    for (l=1; l<=d; l++) {
        asteriscos(l);      // primeira sequencia de *
        pontos((d*2)-2*l);  // relação dos pontos com a linha || d = 3 \ l1 = .... \l2=..
        asteriscos(l);
        putchar('\n');
    }
    
    for (l =d-1; l>0; l--) { //  invertido (d-1 é para eliminar uma linhas de asteriscos
        asteriscos(l);
        pontos((d*2)-2*l);
        asteriscos(l);
        putchar('\n');
    }
    
    return 0;
}


//  *..  ..*
//  **.  .**
//  ***  ***      linhas = (2*n)-1 | colunas = 2*n

//  **.  .**
//  *..  ..*
