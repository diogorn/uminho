#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void ex1(){
     // execl("/bin/ls", "ls", "-l", NULL);
    // execlp("ls", "ls", "-l", NULL);
    char *args[3];
    args[0] = "ls";
    args[1] = "-l";
    args[2] = NULL;
    //execv("/bin/ls", args);
    // execvp("ls", args);

    // o exec substitui o processo atual pelo processo que queremos executar, logo o código abaixo do exec não é executado
    printf("Hello World que nao foi dito\n");
}

void ex2(){
   // criar filho
   // executar comando ls -l
    // esperar pelo filho
    int staus;
    int pid = fork();
    if(pid == 0){
        // filho
        execl("/bin/ls", "ls", "-l", NULL);
        _exit(0);
    } else{
        // pai
        pid_t terminated_pid = wait(&staus);
        if(WIFEXITED(staus)){
            printf("[pai] recebi o valor %d\n, do filho %d", WEXITSTATUS(staus), terminated_pid);
        } else{
            printf("[pai] erro\n");
    }
    printf("Pai\n");
    }
}
int mysystem(const char* command){
    int res = -1;
    int status;

    char* cmd = strdup(command);
    char* token;

    char* args[20];

    int i = 0;
    while((token = strsep(&cmd, " ")) != NULL){
        printf("token: %s\n", token);
        args[i] = token;
        i++;
    }

    args[i] = NULL;

    pid_t pid;
    pid = fork();

    if(pid == 0){
        // filho
        execvp(args[0], args);
        _exit(-1); // se o exec falhar o filho avisar o pai
        perror("execvp failed");
    } else {
        // pai
       wait(&status);
        if(WIFEXITED(status)){
            printf("[pai] - recebi o valor %d\n", WEXITSTATUS(status));
            res = WEXITSTATUS(status);
            if (res == 255){
               res = -1;
            }
        } else{
            printf("[pai] - erro\n");
    }
    return res;

    }
}

int main() {
    ex2();
   
}