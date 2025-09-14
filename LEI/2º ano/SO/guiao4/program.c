#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 100000

void ex2a(){
    int fildes[2];

    pipe(fildes);
    write(fildes[1], "Hello", 3);

    char buff[3];
    read(fildes[0], buff, 3);

    printf("buff: %s\n", buff);

    // enviar inteiro de pai para filho
    pid_t pid = fork();
    if(pid == 0){

        printf("Filho\n");
        int i;
        read(fildes[0], &i, sizeof(int));
        printf("i: %d\n", i);
        _exit(0);
    } else{
        printf("Pai\n");
        int i = 300;
        write(fildes[1], &i, sizeof(int));
    }
}


int ex2b(int argc, char const* argv[]){
    int fildes[2];
    int status;

   // modificar anterior para que o filho envie um inteiro para o pai
    pipe(fildes);
    pid_t pid = fork();
    if(pid == 0){
        printf("Filho\n");
        int i = 300;
        write(fildes[1], &i, sizeof(int));
        _exit(0); // terminar o processo filho sem executar o código que está a seguir
    } else{
        // pai
        printf("Pai\n");
        int i;
        sleep(10);
        read(fildes[0], &i, sizeof(int));
        printf("i: %d\n", i);

        wait(&status);
    }
    return 0;
   
}

int ex3(int argc, char const* argv[]){
   // o filho envia 10000 interiros
   int fildes[2];
   int status;

   pipe(fildes);
   pid_t pid = fork();
   if(pid == 0){
        close(fildes[0]);
       printf("Filho\n");
        for( int i = 0; i < MAX; i++){
            write(fildes[1], &i, sizeof(int));
            printf("[FILHO] escrevi i: %d\n", i);
        }
        close(fildes[1]);
        // close tira o apontador 
        
       _exit(0); // terminar o processo filho sem executar o código que está a seguir
   } else{
       // pai
       printf("Pai\n");
       close(fildes[1]);
       int i;
      // sleep(5);
       while (read(fildes[0], &i, sizeof(int)) > 0){
           read(fildes[0], &i, sizeof(int));
           printf("[PAI] escrevi i: %d\n", i);
       }
         close(fildes[0]);

       wait(&status);
   }
   // read bloqueia quando não há nada para ler
   // write bloqueia quando não há espaço para escrever
   return 0;
}


int main(int argc, char const* argv[]){
    ex3(argc, argv);
    return 0;
    
}
