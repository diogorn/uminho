#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    // search for value
    int value = 8;
    int result = valueExists(matrix, value);
    if (result == 0) {
        printf("Value %d exists in matrix.\n", value);
    } else {
        printf("Value %d does not exist in matrix.\n", value);
    }

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}