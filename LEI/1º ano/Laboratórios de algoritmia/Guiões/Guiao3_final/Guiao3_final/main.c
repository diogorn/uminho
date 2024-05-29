#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "parser.h"

#define SIZE 10240

int main (){
    char line[SIZE];
    
    parser(fgets(line, SIZE, stdin));
    
    return 0;
}

