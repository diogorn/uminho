#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void ex31 (){
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);
}

void ex33 (){
    // criar 10 filhos sequencialmente
    // criar um filho -> espera que ele termine -> 10 vezes
    pid_t pid;
    int status;
    for(int i = 0; i < 10; i++){
        if((pid = fork()) == 0){
            printf("(filho): %d\n", getpid());
            _exit(i);
        } else {
            pid_t terminated_pid = wait(&status);

            if(WIFEXITED(status)){
                printf("(pai): %d\n", terminated_pid);
                printf("status: %d\n", WEXITSTATUS(status));
            } else {
                printf("Erro\n");
            }
        }
    }
}

void ex34(){
    // criar 10 filhos concorrentes
    // o pai espera que todos os filhos terminem
    pid_t pid;
    int status;

    for(int i=1; i<=10;i++){
       //printf("res: %d\n", res); 
       if((pid = fork()) == 0){ 
            printf("Filho: #%d : %d\n",i, getpid()); 
            _exit(i+1);
        } 
    }
    for(int i=1; i<=10;i++){
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
           printf("[pai] recebi o valor %d do filho %d\n", WEXITSTATUS(status), terminated_pid);
        } else {
            printf("Erro\n");
        }
    } 

}

void ex35(){

}

int main () {
    ex34();

    return 0;
}