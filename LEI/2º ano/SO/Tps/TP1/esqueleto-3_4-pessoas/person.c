#include "person.h"
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <_stdio.h>


#define FILENAME "file_person"

int insert_person(char* name, int age){
    // abrir o ficheiro para escrita
    int fd = open(FILENAME, O_CREAT | O_WRONLY | O_APPEND, 0600);
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return -1;
    }

    // criar o person com os parametros dados
    Person p;
    strcpy(p.name, name);
    p.age = age;

    write(fd, &p, sizeof(Person));


    return 0;
}

int list_persons(int N){
    // abrir o ficheiro para leitura
    int fd = open(FILENAME, O_RDONLY);
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return -1;
    }
    // ler os N primeiros persons do ficheiro
    int i = 0;
    char output[300];
    Person p;
    int output_size;
    while(i<N && read(fd, &p, sizeof(Person)) > 0){
        read(fd, &p, sizeof(Person));

        output_size = sprintf(output, "%s %d\n", p.name, p.age);
        write(1, output, output_size);
        i++;

    }


    return 0;
}

int person_change_age(char* name, int age){
    // abrir o ficheiro para leitura e escrita
    int fd = open(FILENAME, O_RDWR);
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return -1;
    }
    // procurar a pessoa com o nome dado e alterar a idade
    Person p;
    
    return 0;
}