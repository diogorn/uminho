#include <stdio.h>
#include <stdlib.h>

void controller(int N, char** commands){
    // criar N filhos para os N comandos
    pid_t pid;
    pid_t pids[N];
    int status;
    for(int i = 0; i < N; i++){
        pid = fork();
         // cada filho corre o seu comando até ele ser 0
        if(pid == 0){
            int res = 1;
            int counter = 0;
            while (res != 0){
                res = mysystem(commands[i]);
                counter++;

            }
            _exit(counter);
        }   
        pids[i] = pid;
    }

    for(int i = 0; i < N; i++){
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            printf("[pai] - o comando %s enviou o valor %d\n", commands[i], WEXITSTATUS(status));
        } else{
            printf("[pai] erro\n");
        }
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

int main (int argc, char** argv){
    char *commands[argc-1];

    return 0;
}