#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

typedef struct {
    pid_t pid;
    char *prompt;
} Req;
// 0 -> stdin
// 1 -> stdout

void SOGPT(char *prompt) {
    int pipeFilter[2];
    pipe(pipeFilter);
    if (fork() == 0) {
        dup2(pipeFilter[1], 1);
        close(pipeFilter[0]);
        close(pipeFilter[1]);
        execlp("filter", "filter", prompt, NULL);
        _exit(1);

    }
    close(pipeFilter[1]);
    // execute 
    int pipeExecute[2];
    pipe(pipeExecute);

    if (fork() == 0){
        dup2(pipeFilter[0], 0); 
        dup2(pipeExecute[1], 1);
        close(pipeExecute[0]);
        close(pipeExecute[1]);
        execlp("execute", "execute", prompt, NULL);
        _exit(1);
    }
    close(pipeExecute[1]);
     close(pipeFilter[0]);

 // n processos 


    //metge

    int pipeMerge[2];
    pipe(pipeMerge);
    if( fork == 0){
        dup2(pipeExecute[0], 0);
        dup2(pipeMerge[1], 1);
        close(pipeMerge[0]);
        close(pipeMerge[1]);
        execlp("merge", "merge", prompt, NULL);
        _exit(1);
    }
     close(pipeExecute[0    qeWA<SDFYGUYIO0'P]);

}
int main (int argc, char * argv[]) {
    Req q;
    q.pid=getpid();
    q.prompt=strdup(argv[1]);
    char fifoc_name[30];
    sprintf(fifoc_name, "fifo_client_%d", q.pid);
    mkfifo(fifoc_name, 0666);
    int fds = open("fifo_server", O_WRONLY);
    write(fds, &q, sizeof(q));
    close(fds);

    int req_id;
    int fdc = open(fifoc_name, O_RDONLY);!
    read(fdc, &req_id, sizeof(int));
    printf("Request %d completed\n", req_id);
    close(fdc);

    unlink(fifoc_name);
    return 0;
}