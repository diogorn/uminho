//
//  main.c
//  ficha2
//
//  Created by Diogo Neto
//

#include <stdio.h>
// 1
float multInt1 (int n, float m) {
    float r = 0;
    for (int i=0; i<n; i++) {
        r += m;
    }
    return r;
}

// 2
float multInt2 (int n, float m){
    float r = 0;
    int operações = 0 ;
    while (n != 0) {
        if(n%2 == 1){
            r += m;
            operações++;
        }
        n /= 2;
        m *=2;
    }
    printf("operações: %d\n", operações);
    return r;
}

// 3
int mdc1 (int a, int b){
    int menor = a < b ? a : b; // encontra o menor número
        int mdc = 1;
        for (int i = 1; i <= menor; i++) {
            if (a % i == 0 && b % i == 0) {
                mdc = i;
            }
        }
    
    return mdc;
}
// 4
int mdc2 (int a, int b){
    int mdc = 1;
    while ((a != 0) && (b !=0)) {
        if (a-b == 0){
            a -= b;
            mdc = a+b;
            
        } else if(a>b){
            a -= b;
        } else if (b>a){
            b -= a;
        }
    }
    
    return mdc;
}

// 5

int mdc3 (int a, int b){
    int mdc = 1;
    while ((a != 0) && (b != 0)) {
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        if (a == 0) {
            mdc = b;
        } else {
            mdc = a;
        }
    
    return mdc;
}

// 6
int fib1 (int n){
    if (n<2){
        return n; ////?????
    } else {
        return fib1(n-1) + fib1(n-2);
    }
}

int main(int argc, const char * argv[]) {
    printf("%.2f\n", multInt2(81, 423));
//    printf("%d\n", fib1(10));
    return 0;
}
