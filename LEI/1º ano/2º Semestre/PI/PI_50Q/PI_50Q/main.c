//
//  main.c
//
//  Created by Diogo Neto
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1
void maiorzero (void){
    int n=-1;
    int max=0;
    puts("Insira sequencia e termine com 0: ");
    while (n!=0) {
        scanf("%d",&n);
        if(n>max) max = n;
    }
    printf("maior: %d\n",max);
}
//2
void mediazero(void){
    float media=0;
    int n=-1,lidos=0;
    puts("Insira sequencia e termine com 0: ");
    while (n!=0) {
        scanf("%d",&n);
        lidos++;
        media +=n;
    }
    media/=lidos;
    printf("media: %2.f\n", media);
}
//3
void maior2zero (void){
    int max=0, max2 = 0,n=-1;
    puts("Insira sequencia e termine com 0: ");
    while (n!=0) {
        scanf("%d",&n);
        if(n>max){
            max2 = max;
            max = n;
        }
    }
    printf("maior: %d\n2º maior: %d\n",max, max2);
    
}
//4
int bitsUm (unsigned int n){
    int bits1 = 0;
    while (n!=0) {
        if(n%2 == 1){
            bits1++;
        }
        n/=2;
    }
    return bits1;
}
//5
int trailingZ (unsigned int n){
    int bits0 = 0;
    while (n!=0) {
        if(n%2 == 0){
            bits0++;
        }
        n/=2;
    }
    return bits0;
}
//6
int qDig6 (unsigned int n){
    int i=1;
    while (n<10) {
        i++;
        n/=10;
    }
    return i;
}
//7
char *strcat7 (char s1[], char s2[]){
    char newstr[strlen(s1) + strlen(s2)];
    int i, j;

    for (i = 0; i < strlen(s1); i++){
        newstr[i] = s1[i];
    }

    for (j = 0; j < strlen(s2); j++){
        newstr[i + j] = s2[j];
    }

    newstr[strlen(s1) + strlen(s2)] = '\0';

    printf("%s\n", newstr);

    return 0;
}
//8
char *strcpy8 (char *dest, char source[]){
    int i;
    for (i=0; source[i] != '\0'; i++) {
        dest[i] = source[i];
    }
    dest[i]= '\0';
    return source;
}
//9
int strcmp9 (char s1[], char s2[]){
    int i=0,j=0;
    int si=0, sj=0;
    while (s1[i]!='\0') {
        si+=s1[i];
        printf("s1 %c %d\n", s1[i], si);
        i++;
    }
    while (s2[j]!='\0') {
        sj+=s2[j];
        printf("s2 %c %d\n", s2[j], sj);
        j++;
    }
    return si-sj;

}
// 10
// não está certinho
char *strstr10(char s1[], char s2[]) {
    int i = 0, j = 0, n = 0;
    while (s1[i] != '\0') {
        if (s1[i] == s2[j]) {
            n++;
            i++;
            j++;
            if (s2[j] == '\0') {
                return &s1[i-n];
            }
        } else {
            n = 0;
            j = 0;
            i++;
        }
    }
    return NULL;
}
//11
void strrev11(char s[]) {
    int N = strlen(s);
    int i = 0, j = N - 1;
    char aux;
    while (i < N/2) {
        aux = s[i];
        s[i] = s[j];
        s[j] = aux;
        i++;
        j--;
    }
    printf("%s\n", s);
}
//12
void strnoV12 (char s[]){
    char lowerVowels[]={'a','e','i','o','u'};
    char capsVowels[]={'A','E','I','O','U'};
    for (int i=0; s[i]!='\0'; i++) {
        if(strchr(lowerVowels,s[i])){
            s[i] = ' ';
        }
    }
    for (int i=0; s[i]!='\0'; i++) {
        if(strchr(capsVowels,s[i])){
            s[i] = ' ';
        }
    }
    printf("%s\n", s);
}

//13
void truncW13 (char t[], int n){
    int n2=0, j=0;
    char t2[strlen(t)];
    for (int i=0; t[i]; i++) {
        if (t[i]==' '){
            n2=0;
            t2[j]=' ';
            j++;
        } else if(n2<n){
            t2[j]=t[i];
            j++;
            n2++;
        }
    }
    t2[j]='\0';
    printf("%s\n", t2);
}

//14
char charMaisfreq (char s[]) {
    int n=0, N = strlen(s), counter=0;
    char freq = '\0';
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if(s[i]==s[j]){
                counter++;
            }
        }
        if(counter>n){
            n = counter;
            freq = s[i];
        }
        counter=0;
    }
    printf("o primeiro char mais freq é |> %c <| com %d aparições\n", freq, n);
    return freq;
}
//15
int iguaisConsecutivos (char s[]) {
    int n=0, counter =1, N=strlen(s),i;
    char maisConseq='\0';
    for (i=0; i<N; i++) {
        if(s[i]==s[i+1]){
            counter++;
        } else {
            counter=1;
        }
        if(counter>n){
            n=counter;
            maisConseq=s[i];
        }
    }
    printf("%c com %d repetições\n", maisConseq, n);
    return n;
}
//16
/*
int difConsecutiv§
    int n=0, counter =1, N=strlen(s),i;
    for (i=0; i<N; i++) {
        if(s[i]!=s[i+1]){
            counter++;
        } else {
            counter=1;
        }
        if(counter>n){
            n=counter;
        }
    }
    printf("difs conseq %d \n", n);
    return n;
}
//17

int maiorPrefixo (char s1 [], char s2 []){
    char
    for (int i=0; s2[i]; i++) {
        for (int j=0; s1[j]; j++) {
            if(s2[i]==s1[jj]){
                
            }
        }
    }
}
*/
int contaPal (char s[]){
    int i=0, counter=0;
    while (s[i]) {
        if(s[i+1]=='\0'){
            counter++;
        }else if (s[i]==' ' && s[i+1]!=' ' ){
            counter++;
        }
        i++;
    }
    return counter;
}
int main(int argc, const char * argv[]) {
//    scanzero();
//    mediazero();
//    maior2zero();
//    printf("bits a 1: %d\n",bitsUm(10));
//    printf("bits a 0: %d\n",trailingZ(10));
//    printf("digitos necessarios: %d\n",qDig6(440));
//    char *s1= "ola, tudo?", *s2= "";
//    strcat7(s1, s2);
//    strcpy7(s1, s2);
//    printf("diferença lexicográfica: %d \n", strcmp9(s1, s2));
//    char s1[] = "ola";
//    printf("s2 começa em s1 no indice: %d\n", strstr10(s1, s2)-s1);
//    strrev11(s1); // passar sem pointer
//    strnoV12(s1);
//    truncW13("liberdade, igualdade e fraternidade", 4);
//    charMaisfreq("");
//    iguaisConsecutivos("aabcccaac") ;
    printf("%d\n",contaPal("a a bb a"));
    
    return 0;
}
