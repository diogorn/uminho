#include <stdio.h>  // esta biblioteca define algumas funções e macros (como NULL) relativas às operações de imput/output
#include <assert.h> // esta biblioteca define uma função (assert) utilizada para verificar suposições feitas pelo programa. Sempre que a expressão passada como argumento é falsa, escreve uma mensagem de diagnostico
#include <stdlib.h> // esta biblioteca possui funções envolvendo alocação de memória, controle de processos e conversões
#include <string.h> // esta biblioteca cria funções que permitem manipular strings e caracteres

#include "parser.h"
#include "stack.h"

#define SIZE 10240 // definimos uma macro para o tamanho da linha, neste caso 10204 caracteres


int main() {
    char linha[SIZE]; // definimos uma variavel do tipo char com o tamanho definido na macro
    
    assert( fgets(linha, SIZE, stdin) != NULL); // Lê a sequência de caractres ate encontrar o caracter NULL
    assert( linha[strlen(linha) - 1] == '\n'); //Lê uma sequência de caracteres até encontrar um \n. O limite é sempre um caractere a menos que o especificado porque no final é incluso um caractere NULL para terminar a string.
    
    parser(linha);  //coloca a linha obtida na função parser
    
    return 0;
}



