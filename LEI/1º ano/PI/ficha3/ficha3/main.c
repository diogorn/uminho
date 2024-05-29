//
//  main.c
//  ficha3
//
//  Created by Diogo Neto 
//

#include <stdio.h>
#define Nsize 10
/*
 //2
 void swapM (int *x, int *y){
 //    & -> retorna enderaço em memória
 //    * -> retorna o valor do objeto apontado
 int aux = *x;
 *x = *y;
 *y = aux;
 }
 //3
 void swap(int v[], int i, int j){
 swapM(&v[i], &v[j]);
 }
 //4
 int soma (int v[], int N){
 int res=0;
 for(int i = 0; i<N; i++){
 res += v[i];
 }
 return res;
 }
 //5
 void inverteArray (int v[], int N){
 for (int i=0, j=N-1; i<N && j>0; i++,j--) {
 swap(v, v[i], v[j]);
 }
 }
 
 int main(int argc, const char * argv[]) {
 int v[5] = {1,2,3,4,5};
 inverteArray(v, 5);
 for (int i = 0; i<5; i++) {
 printf("i:%d\tconteudo:%d\n",i, v[i]) ;
 }
 //    printf("%d\n",soma(v, 5));
 return 0;
 }
*/
 
//2
void swapM2(int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}
void swapV(int v[], int i, int j){
    swapM2(&v[i], &v[j]);
}
int soma (int v[],int N){
    int res=0;
    for (int i=0; i<N; i++) {
        res += v[i];
    }
    return res;
}
void invertArray1(int v[], int N){
    for (int i=0, j=N-1; i<N/2; i++,j--) { // -> se n for N/2 ele inverte 2x
        swapM2(&v[i], &v[j]);
    }
}
void invertArray2(int v[], int N){
    for(int i = 0, j=N-1; i<N/2;i++,j--){
        swapV(v, i, j);
    }
}
int maximum6 (int v[], int N, int *m){
    for (int i=0; i<N; i++) {
        if(*m < v[i]){
            *m = v[i];
        }
    }
    return 0;
}
void quadrados (int q[], int N){
    for (int i=0; i<Nsize; i++) {
        q[i]= i*i;
    }
}
void pascal (int v[], int N){
    
}
int main(int argc, const char * argv[]) {
    int ex=7;
    int v[Nsize]={1,2,3,4,5,6,7,8,9,10};
    int empty[Nsize];

//    printf("exercicio: ");
//    scanf("%d", &ex);
    switch (ex) {
        case 2:
        {
            int x=5,y=3;
            printf("x: %d y: %d\n",x,y);
            swapM2(&x, &y);
            printf("x: %d y: %d\n",x,y);
        }
            break;
        case 3:
        {
            swapV(v, 0, 9);
        }
            break;
        case 4:
            printf("soma: %d\n", soma(v, Nsize));
            break;
        case 51:
            invertArray1(v, Nsize);
            break;
        case 52:
            invertArray2(v, Nsize);
            break;
        case 6:
        {
//            não vai funcionar se o array for vazio
            int max = v[0];
            int *m = &max;
            maximum6(v, Nsize, m);
            printf("Maior valor no vetor: %d\n", *m);
        }
            break;
        case 7:
            quadrados(empty, Nsize);
            break;
        default:
            break;
    }
    for (int i=0; i<Nsize; i++) {
        printf("%d ",empty[i]);
    }
    puts("\n");
    return 0;
}
