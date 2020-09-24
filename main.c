#include <stdio.h>
#include <stdlib.h>

int EvenNumberInput(int x){
    if ( x % 2 == 0){
        return 1;
    }
    return 0;
}

// PrintMatrix
void printMatrix(int matrixInput, int **matrix){
    // printing the array below
    for ( int i=0; i < matrixInput; i++){
        for( int j=0; j < matrixInput; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Deallocate the matrix
void destroyMatrix(int matrixInput, int **matrix ){
    int n = matrixInput;
    for (int i = 0; i < n; i++ ){
        int* curr = matrix[i];
        free(curr);
    }
}

// Only odd inputs for generate magic square
void generateMagicSquare( int matrixOddGrid ){
    int **matrix;
    int matrixInput = matrixOddGrid;
    int i,j,counter;
    int temp,aux;

    // Set matrix to zeros
    matrix = (int **)calloc(matrixInput, sizeof(int *));
    for (i=0; i < matrixInput; i++) {
        matrix[i] = (int *) calloc(matrixInput, sizeof(int));
    }
    i = 0;
    j = matrixInput / 2;
    counter = 1;

    while( counter <= (matrixInput * matrixInput ) ) {
        if( matrix[i][j] != 0 ) {
            i = temp + 1; j = aux;
            matrix[i][j] = counter;
            counter++;
        }
        else {
            matrix[i][j] = counter;
            counter++;
        }

        // Store previous value i and j
        temp = i; aux = j;
        --i; ++j;

        // Check limits
        if(i<0) {
            if(j >= matrixInput){
                i = matrixInput + i;
                j = matrixInput - j;
            }
            else {
                i = matrixInput + i;
            }
        }
        else if( matrixInput == j ) {
            j = matrixInput - j;
        }
    }
    printMatrix( matrixInput, matrix );
    destroyMatrix( matrixInput, matrix);
}

// _____MAIN_____
int main( int argc, char *argv[argc+1]) {

    //File name from arguments
    if (argc != 2 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data
    int matrixGrid;

    // Work on the logic
    while ( fscanf( fp, "%d\n", &matrixGrid ) != EOF ){

        // Check if even matrix
        if ( EvenNumberInput( matrixGrid ) ){
            printf("error\n");
            continue;
        }

        generateMagicSquare(matrixGrid);

    }

    // Close the file
    fclose(fp);

    return EXIT_SUCCESS;
}
