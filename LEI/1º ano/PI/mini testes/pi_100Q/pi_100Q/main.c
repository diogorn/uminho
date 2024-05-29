//
//  main.c
//
//  Created by Diogo Neto
//

#include <stdio.h>
#include <stdlib.h>

typedef struct lligada {
    int valor;
    struct lligada *prox;
}* LInt;
int length (LInt l){
    int tamanho=0;
    while (l) {
        l = l->prox;
        tamanho++;
    }
    return tamanho;
}
void freeL (LInt l){
    
}

int main(int argc, const char * argv[]) {
    // Create a sample linked list
        LInt cabeça = malloc(sizeof(struct lligada));
        LInt f1 = malloc(sizeof(struct lligada));
        LInt f2 = malloc(sizeof(struct lligada));

        cabeça->valor = 1;
        cabeça->prox = f1;

        f1->valor = 2;
        f1->prox = f2;

        f2->valor = 3;
        f2->prox = NULL;
    
    // Call the length function to get the number of elements
        int listLength = length(cabeça);
        printf("Tamanho da lista: %d\n", listLength);

        // Free the allocated memory
        free(cabeça);
        free(f1);
        free(f2);
    return 0;
}
