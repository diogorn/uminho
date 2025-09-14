#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/types.h>

#define buffersize 1024

int mycat (){
    char* buffer = malloc(sizeof(char)*buffersize);
    ssize_t byteslidos, byteswritten;
    while ((byteslidos = read(0,buffer, buffersize))>0){
        write(1,buffer, byteslidos);
    }

    if(byteslidos != byteswritten) return -1;

    free(buffer);
    return 0;
}
int mycat2(char const* filename){
    int fd = open(filename, O_RDONLY);
    // fd = 3 se o ficheiro for aberto com sucesso
    if(fd < 0){
        perror("Erro ao abrir o ficheiro");
        return -1;
    }
    char* buffer = (char*) malloc(sizeof(char) * buffersize);
    ssize_t byteslidos, byteswritten;
    while ((byteslidos = read(fd,buffer, buffersize))>0){ // read mudou de 0 para fd porque agora estamos a ler de um ficheiro
        write(1,buffer, byteslidos);
        if(byteslidos != byteswritten) return -1;
    }

    free(buffer);
    return 0;
}

int my_cp(char const* origem, char const* destino){
    int fd_src = open(origem, O_RDONLY);
    if(fd_src < 0){
        perror("Erro ao abrir o ficheiro de origem");
        return -1;
    }
    int fd_dest = open(destino, O_CREAT | O_WRONLY | O_TRUNC, 0600);

    if(fd_dest < 0){
        perror("Erro ao abrir o ficheiro de destino");
        return -1;
    }

    char* buffer = (char*) malloc(sizeof(char) * buffersize);
    ssize_t byteslidos, byteswritten;

    while (byteslidos = read(fd_src, buffer, buffersize) > 0){
        byteswritten = write(fd_dest, buffer, byteslidos);
        if(byteslidos != byteswritten) return -1;
    }

    free(buffer);
    close(fd_src);
    close(fd_dest);

    return 0;
}

int mainCp(int argc, char* argv[]){
    my_cp(argv[1], argv[2]);
    
    return 0;
}
int main(int argc, char* argv[]) {
    // stdout e stderr fazem o mesmo porem é por convenção
    // 1 -> stdout
    // 2 -> stderr
    //write(1, buffer, 6);
    //write(2, buffer, 6);
    // 0 -> stdin
    // read(0, buffer, 6);
    
    mycat2(argv[1]);

   return 0;
}

