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
matrix_t s21_transpose(matrix_t *A);
matrix_t s21_calc_complements(matrix_t *A);
double s21_determinant(matrix_t *A);
matrix_t mini_matrix(int n, int m, int *A);
double get_minor(matrix_t *A);

int main() {
    matrix_t matrix1, matrix2, matrix3;
    int n = 3, m = 2;
    matrix1 = s21_create_matrix(n, m);
    matrix2 = s21_create_matrix(m, n);
    matrix1.matrix[0][0] = 1;
    matrix1.matrix[1][0] = 2;
    matrix1.matrix[2][0] = 3;
    matrix1.matrix[0][1] = 4;
    matrix1.matrix[1][1] = 5;
    matrix1.matrix[2][1] = 6;

    matrix2.matrix[0][0] = 1;
    matrix2.matrix[0][1] = -1;
    matrix2.matrix[0][2] = 1;
    matrix2.matrix[1][0] = 2;
    matrix2.matrix[1][1] = 3;
    matrix2.matrix[1][2] = 4;

    //matrix3 = s21_mult_matrix(&matrix1, &matrix2);
    matrix3 = s21_transpose(&matrix1);
    //printf("eq:%d\n", s21_eq_matrix(&matrix1, &matrix2));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%f ", matrix3.matrix[i][j]); 
        printf("\n");
    }
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
        result = s21_create_matrix(A->rows, A->columns);
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
        result = s21_create_matrix(A->rows, A->columns);
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
    result = s21_create_matrix(A->rows, A->columns);
    result.matrix_type = CORRECT_MATRIX;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A-> columns; j++)
            result.matrix[i][j] = A->matrix[i][j] * number;
    }
    return result;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result;
    if (A->columns != B->rows) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        result = s21_create_matrix(A->rows, B->columns);
        result.matrix_type = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++) {
                    result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    return result;
}

matrix_t s21_transpose(matrix_t *A) {
    matrix_t result;
    result = s21_create_matrix(A->columns, A->rows);
    result.matrix_type = CORRECT_MATRIX;
    for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++)
            result.matrix[i][j] = A->matrix[j][i];
    }
    return result;
}

matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t result;
    matrix_t buffer;
    double minor;
    if (A->rows != A->columns) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        if (A->rows == 2) {
            minor = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->rows; j++) {
                    result.matrix[i][j] = get_minor(i, j, *A) * pow(-1, i + j);
                }
            }
        }
    }
    return result;
}

double get_minor(matrix_t *A) {
    double determinant;
    matrix_t buffer;
    buffer = mini_matrix(n, m, &A);
    determinant = s21_determinant(&buffer);
    return determinant;
}

double s21_determinant(matrix_t *A) {
    double result;
    matrix_t buffer;
    if (A->rows != A->columns) {
        result = NAN;
    } else if (A->rows == 2) {
        result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        for (int i = 0; i < A->rows; i++) {
           buffer = mini_matrix(i, 0, A);
           result = pow(-1, i + j) * s21_determinant(&buffer);
        }
    }
    return result;
}

matrix_t mini_matrix(int n, int m, int *A) {
    matrix_t result;
    result = s21_create_matrix(A->rows - 1, A->rows - 1);
    int l = 0, k = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->rows; j++) {
            if (j != m) {
                buffer.matrix[k][l] = A->matrix[i][j];
                l += 1;
            }
        }
        if (i != n) k += 1;
    }
    return result;
}