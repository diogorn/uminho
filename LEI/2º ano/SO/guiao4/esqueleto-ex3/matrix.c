#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(0);

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

void lookupNumber(int** matrix, int value, int* vector){

    //TODO
    //Hint - use the Minfo struct from matrix.h!

    int fildes[2];
    pipe(fildes);
    pid_t pid;
    
    // filho por cada linha
    for(int i = 0; i < ROWS; i++){
        pid = fork();
        if(pid == 0){
            close(fildes[0]);
            Minfo info;
            info.line_nr = i;
            info.ocur_nr = 0;
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value){
                    info.ocur_nr++;
                }
            }
            write(fildes[1], &info, sizeof(Minfo));
            close(fildes[1]);
            _exit(0);
        } else {
            close(fildes[1]);
            Minfo info;
            while (read(fildes[0], &info, sizeof(Minfo)) > 0) {
                vector[info.line_nr] = info.ocur_nr;
            }
            
            close(fildes[0]);
            
        }
    }  

}