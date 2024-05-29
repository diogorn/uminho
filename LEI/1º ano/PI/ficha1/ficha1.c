#include "ficha1.h"

void quadrado (void){
    int n = 0;
    printf("insira dimensão: ");
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("#");
        }
        printf("\n");
    }
}

void xadrez (void){
    int n = 0, count=0;
    printf("insira dimensão: ");
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (count%2 ==0){
                printf("#");
            } else {
                printf("_");
            }
            count++;
        }
        printf("\n");
    }
}
