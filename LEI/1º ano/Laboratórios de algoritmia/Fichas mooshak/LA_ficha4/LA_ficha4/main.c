#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void caulefolha(int algarismo[], int n){
    int i, o, folhas;
    for (i = 0; i < n; i++) {
        for (o = i + 1; o < n; o++) {
            if (algarismo[i] > algarismo [o]) {
                folhas = algarismo[i];
                algarismo[i] = algarismo [o];
                algarismo [o] = folhas;
            }
        }
    }
}

int main () {
    int folhas[50], n = 0, counter;
    counter = 1;

    while (n != -1){
        assert(scanf("%d", &n) == 1);
        folhas[counter] = n;
        counter++;
    }
    caulefolha(folhas,counter);

    int i;
    for (i=0; i<10; i++){
        printf("%d|", i);
        int i2;
        for(i2 = 2; i2 <= counter - 1; i2++){
            if ((folhas[i2]/10) == i){
                printf("%d", folhas[i2]%10);
            }
        }
        printf("\n");
    }
return 0;
}


