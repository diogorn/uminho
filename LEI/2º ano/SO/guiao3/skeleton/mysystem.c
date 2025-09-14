#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {

	int res = -1;

	char* cmd = strdup(command);
	char* token;
	char* args[100];

	int i = 0;
	while (token = strsep(&cmd, " ")!= NULL){
		printf("token: %s\n", token);
		args[i] = token;
		i++;

	}
	
	args[i] = NULL;

	pid_t pid;
	pid = fork();

	if(pid == 0){
		//filho
		execvp(args[0], args);
	}

	printf("token: %s\n", token);
	printf("cmd: %s\n", cmd);

	return res;
}