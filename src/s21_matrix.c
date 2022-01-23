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
matrix_t s21_inverse_matrix(matrix_t *A);
    // вспомогательные функции
matrix_t mini_matrix(int n, int m, matrix_t *A);
double get_minor(int n, int m, matrix_t *A);
int type_matrix(matrix_t *A);


int main() {
    matrix_t matrix1, matrix2, matrix3;
    int n = 4, m = 2;
    matrix1 = s21_create_matrix(n, n);
    //matrix2 = s21_create_matrix(m, n);
    matrix1.matrix[0][0] = 1;
    matrix1.matrix[0][1] = 21;
    matrix1.matrix[0][2] = 32;
    matrix1.matrix[0][3] = 47;
    matrix1.matrix[1][0] = 2;
    matrix1.matrix[1][1] = 23;
    matrix1.matrix[1][2] = 3;
    matrix1.matrix[1][3] = 12;
    matrix1.matrix[2][0] = 5;
    matrix1.matrix[2][1] = 54;
    matrix1.matrix[2][2] = 4;
    matrix1.matrix[2][3] = 32;
    matrix1.matrix[3][0] = 89;
    matrix1.matrix[3][1] = 7;
    matrix1.matrix[3][2] = 61;
    matrix1.matrix[3][3] = 5;

    // matrix1.matrix[0][0] = 1;
    // matrix1.matrix[0][1] = 2;
    // matrix1.matrix[0][2] = 3;
    // matrix1.matrix[1][0] = 0;
    // matrix1.matrix[0][0] = 4;
    // matrix1.matrix[0][1] = -4;
    // matrix1.matrix[1][0] = 2;
    // matrix1.matrix[1][1] = 3;

    // matrix2.matrix[0][0] = 1;
    // matrix2.matrix[0][1] = -1;
    // matrix2.matrix[0][2] = 1;
    // matrix2.matrix[1][0] = 2;
    // matrix2.matrix[1][1] = 3;
    // matrix2.matrix[1][2] = 4;
    double deter;
    //matrix3 = s21_mult_matrix(&matrix1, &matrix2);
    deter = s21_determinant(&matrix1);
    printf("deter:%f\n", deter);
    //matrix3 = s21_calc_complements(&matrix1);
    //matrix3 = s21_inverse_matrix(&matrix1);
        for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%f ", matrix1.matrix[i][j]); 
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%f ", matrix3.matrix[i][j]); 
        printf("\n");
    }
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);
    s21_remove_matrix(&matrix3);
    
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
        //result.matrix_type = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A-> columns; j++)
                result.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
        type_matrix(&result);
    }
    return result;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result;
    if (A->rows != B->rows || A->columns != B -> columns) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        result = s21_create_matrix(A->rows, A->columns);
        //result.matrix_type = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A-> columns; j++)
                result.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
        type_matrix(&result);
    }
    return result;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
    matrix_t result;
    result = s21_create_matrix(A->rows, A->columns);
    //result.matrix_type = CORRECT_MATRIX;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A-> columns; j++)
            result.matrix[i][j] = A->matrix[i][j] * number;
    }
    type_matrix(&result);
    return result;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result;
    if (A->columns != B->rows) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        result = s21_create_matrix(A->rows, B->columns);
        //result.matrix_type = CORRECT_MATRIX;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < B->columns; j++) {
                for (int k = 0; k < A->columns; k++) {
                    result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
        type_matrix(&result);
    }
    return result;
}

matrix_t s21_transpose(matrix_t *A) {
    matrix_t result;
    result = s21_create_matrix(A->columns, A->rows);
    //result.matrix_type = CORRECT_MATRIX;
    for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++)
            result.matrix[i][j] = A->matrix[j][i];
    }
    type_matrix(&result);
    return result;
}

matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t result;
    double minor;
    if (A->rows != A->columns) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        result = s21_create_matrix(A->rows, A->rows);
        if (A->rows == 2) {
            result.matrix[0][0] = A->matrix[1][1];
            result.matrix[1][1] = A->matrix[0][0];
            result.matrix[0][1] = A->matrix[1][0] * (-1);
            result.matrix[1][0] = A->matrix[0][1] * (-1);
        } else {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->rows; j++) {
                    result.matrix[i][j] = get_minor(i, j, A) * pow(-1, i + j);
                }
            }
        }
        type_matrix(&result);
    }
    return result;
}

double get_minor(int n, int m, matrix_t *A) {
    double determinant;
    matrix_t buffer;
    buffer = mini_matrix(n, m, A);
    determinant = s21_determinant(&buffer);
    s21_remove_matrix(&buffer);
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
            result += pow(-1, i + 2) * A->matrix[i][0] * s21_determinant(&buffer);
              //s21_remove_matrix(&buffer);
        }
        //s21_remove_matrix(&buffer);
    }
    s21_remove_matrix(&buffer);
    return result;
}

matrix_t mini_matrix(int n, int m, matrix_t *A) {
    matrix_t result;
    result = s21_create_matrix(A->rows - 1, A->rows - 1);
    int l = 0, k = 0;
    for (int i = 0; i < A->rows; i++) {
        if (i != n) {
            for (int j = 0; j < A->rows; j++) {
                if (j != m) {
                    result.matrix[k][l] = A->matrix[i][j];
                    l += 1;
                }
            }
            k += 1;
            l = 0;
        }
    }
    return result;
}

int type_matrix(matrix_t *A) {
    int zero = 0, one = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (A->matrix[i][j] == 0)
                zero += 1;
            if (A->matrix[i][j] == 1 && i == j)
                one += 1;            
        }
    }
    if (zero == A->rows * A->columns) {
        A->matrix_type = ZERO_MATRIX;
    } else if (one == A->rows && A->rows == A->columns) {
        A->matrix_type = IDENTITY_MATRIX;
    } else {
        A->matrix_type = CORRECT_MATRIX;
    }
    return 1;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
    matrix_t result = s21_create_matrix(A->rows, A->columns);
    double determinant = s21_determinant(A);
    if (determinant != 0 && determinant != NAN) {
        result = s21_calc_complements(A);
        result = s21_transpose(A);
        result = s21_mult_number(&result, 1 / determinant);
    } else {
        result.matrix_type = INCORRECT_MATRIX;
    }
    return result;
}
