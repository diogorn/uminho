#include "matrix.h"



int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5

int valueExists(int **matrix, int value) {
  
    for(int i=0;i<ROWS;i++){
        if (fork() == 0) {
            for(int j=0;j<COLUMNS;j++){
                
                if(matrix[i][j]==value){
                    _exit(0);
                }
            }
            _exit(1);
        }
    }
    int status;
    int result = 1; // Por padrão, consideramos que o valor não foi encontrado
    for (int i = 0; i < ROWS; i++) {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            result = 0; // Se algum processo filho encontrou o valor, definir result como 0
            break;
        }
    }

    return result; // Retorna 0 se o valor foi encontrado, 1 caso contrário
}
   


// ex.6
void linesWithValue(int **matrix, int value) {
   pid_t pid;
   int status;
   int res = 0;

   pid_t pids[ROWS];
    for (int i = 0; i < ROWS; i++) {
        if ((pid = fork()) == 0) {
            // filho
            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) {
                    _exit(i); 
                }
            }
            sleep(10%(i+1)); 
            _exit(-1); 
        }
        pids[i] = pid;
        printf("[pai] - criei o filho %d\n", i);
    }

    for (int i = 0; i < ROWS; i++) {
        pid_t terminated_pid = waitpid(pids[i], &status,0);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 1) {
                res =1;
            }
        } else {
            printf("erro");
        }
    }
    
}