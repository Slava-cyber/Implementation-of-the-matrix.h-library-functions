#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_mult_number(matrix_t *A, double number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);

int main() {
    matrix_t matrix1, matrix2;
    int n = 3, m = 4;
    matrix1 = s21_create_matrix(n, m);
    matrix2 = s21_create_matrix(n, m);
    // matrix1.matrix[2][2] = 3.1234534;
    // matrix2.matrix[2][2] = 3.1234534;
    printf("eq:%d\n", s21_eq_matrix(&matrix1, &matrix2));
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++)
    //         printf("%f ", matrix1.matrix[i][j]); 
    //     printf("\n");
    // }
    return 0;
}

matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t newMatrix;
    
    newMatrix.matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
        *(newMatrix.matrix + i) = (double*)malloc(columns * sizeof(double));
    newMatrix.rows = rows;
    newMatrix.columns = columns;
    newMatrix.matrix_type = ZERO_MATRIX;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            *(*(newMatrix.matrix + i) + j) = 0;
    }
    return newMatrix;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix + i);
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = 1;
    if (A->rows != B->rows || A->columns != B -> columns)
        result  = 0;
    if (result) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A-> columns; j++) {
                double wholeA, wholeB;
                double fractionA, fractionB;
                fractionA = modf(A->matrix[i][j], &wholeA) * 10e6;
                fractionB = modf(B->matrix[i][j], &wholeB) * 10e6;
                fractionA = modf(fractionA, &wholeA);
                fractionB = modf(fractionB, &wholeB);
                if (wholeA != wholeB)
                    result = 0;
            }
        }
    }
    return result;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result;
    if (A->rows != B->rows || A->columns != B -> columns) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        result.matrix = s21_create_matrix(A->rows, A->columns);
        result.rows = A->rows;
        result.columns = A->columns;
        result.matrix_type = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A-> columns; j++)
                result.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }
    return result;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result;
    if (A->rows != B->rows || A->columns != B -> columns) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        result.matrix = s21_create_matrix(A->rows, A->columns);
        result.rows = A->rows;
        result.columns = A->columns;
        result.matrix_type = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A-> columns; j++)
                result.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
    }
    return result;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
    matrix_t result;
    result.matrix = s21_create_matrix(A->rows, A->columns);
    result.rows = A->rows;
    result.columns = A->columns;
    result.matrix_type = CORRECT_MATRIX;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A-> columns; j++)
            result.matrix[i][j] = A->matrix[i][j] * number;
    }
    return result;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {

}