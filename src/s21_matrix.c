#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t newMatrix;
    if (rows != 0 && columns != 0) {
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
    } else {
        newMatrix.matrix = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < 2; i++)
            *(newMatrix.matrix + i) = (double*)malloc(2 * sizeof(double));
        newMatrix.rows = 2;
        newMatrix.columns = 2;
        newMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return newMatrix;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = 1;
    if (A->rows != B->rows || A->columns != B -> columns ||
        A->matrix_type == INCORRECT_MATRIX || B->matrix_type == INCORRECT_MATRIX)
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
    matrix_t result = s21_create_matrix(A->rows, A->columns);;
    if (A->rows != B->rows || A->columns != B->columns ||
        A->matrix_type == INCORRECT_MATRIX || B->matrix_type == INCORRECT_MATRIX) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A-> columns; j++)
                result.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
        type_matrix(&result);
    }
    return result;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result = s21_create_matrix(A->rows, A->columns);;
    if (A->rows != B->rows || A->columns != B -> columns ||
        A->matrix_type == INCORRECT_MATRIX || B->matrix_type == INCORRECT_MATRIX) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
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
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A-> columns; j++)
            result.matrix[i][j] = A->matrix[i][j] * number;
    }
    type_matrix(&result);
    return result;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t result = s21_create_matrix(A->rows, B->columns);
    if (A->columns != B->rows ||
        A->matrix_type == INCORRECT_MATRIX || B->matrix_type == INCORRECT_MATRIX) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
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
    matrix_t result = s21_create_matrix(A->columns, A->rows);
    for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++)
            result.matrix[i][j] = A->matrix[j][i];
    }
    type_matrix(&result);
    return result;
}

matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t result = s21_create_matrix(A->rows, A->rows);
    if (A->rows != A->columns || A->rows < 2 || A->columns < 2 ||
        A->matrix_type == INCORRECT_MATRIX) {
        result.matrix_type = INCORRECT_MATRIX;
    } else {
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
    double result = 0;
    if (A->rows != A->columns || A->rows < 2 || A->columns < 2) {
        result = NAN;
    } else if (A->rows == 2) {
        result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        for (int i = 0; i < A->rows; i++) {
            matrix_t buffer;
            buffer = mini_matrix(i, 0, A);
            result += pow(-1, i + 2) * A->matrix[i][0] * s21_determinant(&buffer);
            s21_remove_matrix(&buffer);
        }
    }
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
    matrix_t result;
    double determinant = s21_determinant(A);
    if (determinant != 0 && determinant != NAN && A->rows == A->columns) {
        matrix_t calc = s21_calc_complements(A);
        matrix_t transpose = s21_transpose(&calc);
        result = s21_mult_number(&transpose, 1 / determinant);
        type_matrix(&result);
        s21_remove_matrix(&calc);
        s21_remove_matrix(&transpose);
    } else {
        result = s21_create_matrix(A->rows, A->columns);
        result.matrix_type = INCORRECT_MATRIX;
    }
    return result;
}
