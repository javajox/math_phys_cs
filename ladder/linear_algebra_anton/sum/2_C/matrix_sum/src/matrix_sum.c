#include <stdio.h>
#include <stdlib.h>

int **create2DArray(int rows, int cols) {
    int **arr = malloc(rows * sizeof(int *));

    if (arr == NULL) {
        printf("Error allocating memory!\n");
    }

    for (int i = 0; i < rows; i++) {
        arr[i] = malloc(cols * sizeof(int));
        if (arr[i] == NULL) {
            printf("Error allocating memory!\n");
            exit(1);
        }
    }
    return arr;
}

void destroy2DArray(int **arr) {
    free(arr);
}

void initialize2DArray(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }
}

void print2DArray(int **arr, int rows, int cols) {
    printf("The data in array is :\n");

    for (int i = 0; i < rows; i++) {
        printf("Row - %d\n", i);
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int **sum(int **arr1, int **arr2, int rows, int cols) {
    int **result = create2DArray(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = arr1[i][j] + arr2[i][j];
        }
    }

    return result;
}