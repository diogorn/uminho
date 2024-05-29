/**
 * @file Este ficheiro contém a função principal do programa
 */

#include <stdio.h>
#include "parser.h"

#define SIZE 10240

/**
 * \brief Função principal do programa.
 *
 * @returns Devolve o valor 0
 */

int main (){
    char line[SIZE];
    
    parser(fgets(line, SIZE, stdin));
    
    return 0;
}

