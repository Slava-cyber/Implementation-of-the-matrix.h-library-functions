#include <check.h>
#include "s21_matrix.h"

START_TEST(test_create_matrix_1) {
  matrix_t A;
  int rows = 5, columns = 7;
  A = s21_create_matrix(rows, columns);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) ck_assert_uint_eq(A.matrix[i][j], 0.0);
  ck_assert_int_eq(A.matrix_type, 3);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_2) {
  matrix_t A;
  int rows = 0, columns = 0;
  A = s21_create_matrix(rows, columns);
  ck_assert_int_eq(A.matrix_type, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_1) {
  matrix_t A;
  matrix_t B;
  A = s21_create_matrix(2, 3);
  B = s21_create_matrix(2, 3);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_2) {
  matrix_t A;
  matrix_t B;
  A = s21_create_matrix(2, 3);
  B = s21_create_matrix(3, 2);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) A.matrix[i][j] = i + j;
  for (int i = 0; i < B.rows; i++)
    for (int j = 0; j < B.columns; j++) B.matrix[i][j] = i + j;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_3) {
  matrix_t A;
  matrix_t B;
  A = s21_create_matrix(10, 10);
  B = s21_create_matrix(10, 10);
  B.matrix_type = INCORRECT_MATRIX;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i * j;
    }
  }
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  A = s21_create_matrix(2, 3);
  B = s21_create_matrix(2, 3);
  C = s21_sum_matrix(&A, &B);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) ck_assert_uint_eq(C.matrix[i][j], 0.0);
  ck_assert_int_eq(C.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double test[] = {5.0, 0.0, 2.0, 0.0, 1.0, 1.0, -1.0, 1.0};
  A = s21_create_matrix(2, 4);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = 0.0;
  A.matrix[0][3] = 2.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 3.0;
  A.matrix[1][3] = 1.0;
  B = s21_create_matrix(2, 4);
  B.matrix[0][0] = 4.0;
  B.matrix[0][1] = -3.0;
  B.matrix[0][2] = 2.0;
  B.matrix[0][3] = -2.0;
  B.matrix[1][0] = -3.0;
  B.matrix[1][1] = 0.0;
  B.matrix[1][2] = -4.0;
  B.matrix[1][3] = 0.0;
  C = s21_sum_matrix(&A, &B);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double test[] = {1.0, 0.0, 0.0, 1.0};
  A = s21_create_matrix(2, 2);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 2.0;
  B = s21_create_matrix(2, 2);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = -3.0;
  B.matrix[1][0] = -5.0;
  B.matrix[1][1] = -1.0;
  C = s21_sum_matrix(&A, &B);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, IDENTITY_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  A = s21_create_matrix(2, 2);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 2.0;
  B = s21_create_matrix(2, 3);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = -3.0;
  B.matrix[0][2] = -3.0;
  B.matrix[1][0] = -5.0;
  B.matrix[1][1] = -1.0;
  B.matrix[1][2] = -1.0;
  C = s21_sum_matrix(&A, &B);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  A = s21_create_matrix(2, 3);
  B = s21_create_matrix(2, 3);
  C = s21_sub_matrix(&A, &B);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) ck_assert_uint_eq(C.matrix[i][j], 0.0);
  ck_assert_int_eq(C.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double test[] = {1.0, 6.0, -0.12, 4.12, 7.13, -12.35, 7.0, 1.0};
  A = s21_create_matrix(2, 4);
  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = 2.0;
  A.matrix[0][3] = 2.12;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = -12.23;
  A.matrix[1][2] = 3.0;
  A.matrix[1][3] = 1.0;
  B = s21_create_matrix(2, 4);
  B.matrix[0][0] = 4.0;
  B.matrix[0][1] = -3.0;
  B.matrix[0][2] = 2.12;
  B.matrix[0][3] = -2.0;
  B.matrix[1][0] = -3.13;
  B.matrix[1][1] = 0.12;
  B.matrix[1][2] = -4.0;
  B.matrix[1][3] = 0.0;
  C = s21_sub_matrix(&A, &B);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double test[9] = {1.0, 6.0, 10.0, 3.0};
  A = s21_create_matrix(2, 2);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 2.0;
  B = s21_create_matrix(2, 2);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = -3.0;
  B.matrix[1][0] = -5.0;
  B.matrix[1][1] = -1.0;
  C = s21_sub_matrix(&A, &B);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sub_matrix_4) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  A = s21_create_matrix(2, 2);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 2.0;
  B = s21_create_matrix(2, 3);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = -3.0;
  B.matrix[0][2] = -3.0;
  B.matrix[1][0] = -5.0;
  B.matrix[1][1] = -1.0;
  B.matrix[1][2] = -1.0;
  C = s21_sub_matrix(&A, &B);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mul_number_1) {
  matrix_t A;
  matrix_t C;
  double number = 12.12;
  A = s21_create_matrix(2, 3);
  C = s21_mult_number(&A, number);
  for (int i = 0; i < A.rows; i++)
    for (int j = 0; j < A.columns; j++) ck_assert_uint_eq(C.matrix[i][j], 0.0);
  ck_assert_int_eq(C.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mul_number_2) {
  matrix_t A;
  matrix_t C;
  double number = 12.12;
  double test[] = {12.12, 38.9052, -60.6, 25.6944};
  A = s21_create_matrix(2, 2);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.21;
  A.matrix[1][0] = -5.0;
  A.matrix[1][1] = 2.12;
  C = s21_mult_number(&A, number);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mul_matrix_1) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  A = s21_create_matrix(2, 3);
  B = s21_create_matrix(3, 4);
  C = s21_mult_matrix(&A, &B);
  for (int i = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) ck_assert_uint_eq(C.matrix[i][j], 0.0);
  ck_assert_int_eq(C.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mul_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  double test[] = {11.62, -20.76, -23.3176, 12.82};
  A = s21_create_matrix(2, 4);
  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = 2.0;
  A.matrix[0][3] = 2.12;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = -12.23;
  A.matrix[1][2] = 3.0;
  A.matrix[1][3] = 1.0;
  B = s21_create_matrix(4, 2);
  B.matrix[0][0] = 4.0;
  B.matrix[0][1] = -3.0;
  B.matrix[1][0] = 2.12;
  B.matrix[1][1] = -2.0;
  B.matrix[2][0] = -3.13;
  B.matrix[2][1] = 0.12;
  B.matrix[3][0] = -4.0;
  B.matrix[3][1] = 0.0;
  C = s21_mult_matrix(&A, &B);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mul_matrix_3) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  A = s21_create_matrix(2, 3);
  B = s21_create_matrix(5, 4);
  C = s21_mult_matrix(&A, &B);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_transpose_matrix_1) {
  matrix_t A;
  matrix_t C;
  A = s21_create_matrix(2, 3);
  C = s21_transpose(&A);
  for (int i = 0; i < C.rows; i++)
    for (int j = 0; j < C.columns; j++) ck_assert_uint_eq(C.matrix[i][j], 0.0);
  ck_assert_int_eq(C.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_transpose_matrix_2) {
  matrix_t A;
  matrix_t C;
  double test[] = {5, 4, 3, -12.23, 2, 3, 2.12, 1};
  A = s21_create_matrix(2, 4);
  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = 2.0;
  A.matrix[0][3] = 2.12;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = -12.23;
  A.matrix[1][2] = 3.0;
  A.matrix[1][3] = 1.0;
  C = s21_transpose(&A);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_calc_complements_1) {
  matrix_t A;
  matrix_t C;
  double test[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  C = s21_calc_complements(&A);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A;
  matrix_t C;
  double test[] = {350,  0,     -3250, 0,     500,  300,   0,   600,  0,
                   -700, -2320, 790,   -1480, 1580, -380,  140, -790, 280,
                   0,    200,   530,   0,     1850, -1580, 80};
  A = s21_create_matrix(5, 5);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;
  A.matrix[0][4] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[1][3] = 3.0;
  A.matrix[1][4] = 13.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  A.matrix[2][3] = 3.0;
  A.matrix[2][4] = 3.0;
  A.matrix[3][0] = 5.0;
  A.matrix[3][1] = 12.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;
  A.matrix[3][4] = 3.0;
  A.matrix[4][0] = 5.0;
  A.matrix[4][1] = 2.0;
  A.matrix[4][2] = 1.0;
  A.matrix[4][3] = 8.0;
  A.matrix[4][4] = 3.0;
  C = s21_calc_complements(&A);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t A;
  matrix_t C;
  A = s21_create_matrix(1, 1);
  C = s21_calc_complements(&A);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_calc_complements_4) {
  matrix_t A;
  matrix_t C;
  A = s21_create_matrix(1, 4);
  C = s21_calc_complements(&A);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_determinate_1) {
  matrix_t A;
  double determinate = 0;
  A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  determinate = s21_determinant(&A);
  ck_assert_double_eq(determinate, -40);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinate_2) {
  matrix_t A;
  double determinate = 0;
  A = s21_create_matrix(5, 5);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;
  A.matrix[0][4] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[1][3] = 3.0;
  A.matrix[1][4] = 13.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  A.matrix[2][3] = 3.0;
  A.matrix[2][4] = 3.0;
  A.matrix[3][0] = 5.0;
  A.matrix[3][1] = 12.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;
  A.matrix[3][4] = 3.0;
  A.matrix[4][0] = 5.0;
  A.matrix[4][1] = 2.0;
  A.matrix[4][2] = 1.0;
  A.matrix[4][3] = 8.0;
  A.matrix[4][4] = 3.0;
  determinate = s21_determinant(&A);
  ck_assert_double_eq(determinate, -7900);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinate_3) {
  matrix_t A;
  double determinate = 0;
  int check = 0;
  A = s21_create_matrix(3, 1);
  determinate = s21_determinant(&A);
  if (isnan(determinate) != 0) check = 1;
  ck_assert_int_eq(1, check);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_1) {
  matrix_t A;
  matrix_t C;
  A = s21_create_matrix(3, 3);
  double test[] = {0, -0.1, 0.2, -0.25, 0.35, 0.05, 0.5, -0.2, -0.1};
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  C = s21_inverse_matrix(&A);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A;
  matrix_t C;
  double test[] = {1, -1.5, 3.9,  -4,  0.1,  0,   0,  1, -1,
                   0, 2.5,  -3,   7.4, -8,   0.1, 0,  0, -0.2,
                   0, 0.2,  -2.5, 3.5, -9.1, 10,  0.4};
  A = s21_create_matrix(5, 5);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;
  A.matrix[0][4] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[1][3] = 3.0;
  A.matrix[1][4] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  A.matrix[2][3] = 3.0;
  A.matrix[2][4] = 3.0;
  A.matrix[3][0] = 5.0;
  A.matrix[3][1] = 1.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;
  A.matrix[3][4] = 3.0;
  A.matrix[4][0] = 5.0;
  A.matrix[4][1] = 2.0;
  A.matrix[4][2] = 1.0;
  A.matrix[4][3] = 8.0;
  A.matrix[4][4] = 3.0;
  C = s21_inverse_matrix(&A);
  for (int i = 0, k = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      ck_assert_uint_eq(C.matrix[i][j], test[k]);
      k += 1;
    }
  }
  ck_assert_int_eq(C.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_matrix_3) {
  matrix_t A;
  matrix_t C;
  A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = 2.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  C = s21_inverse_matrix(&A);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_inverse_matrix_4) {
  matrix_t A;
  matrix_t C;
  A = s21_create_matrix(2, 3);
  C = s21_inverse_matrix(&A);
  ck_assert_int_eq(C.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("fpeEGg");
  SRunner *sr = srunner_create(s1);
  int nf;

  TCase *tc1_1 = tcase_create("fpeEGg");
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_create_matrix_1);
  tcase_add_test(tc1_1, test_create_matrix_2);
  tcase_add_test(tc1_1, test_eq_matrix_1);
  tcase_add_test(tc1_1, test_eq_matrix_2);
  tcase_add_test(tc1_1, test_eq_matrix_3);
  tcase_add_test(tc1_1, test_sum_matrix_1);
  tcase_add_test(tc1_1, test_sum_matrix_2);
  tcase_add_test(tc1_1, test_sum_matrix_3);
  tcase_add_test(tc1_1, test_sum_matrix_4);
  tcase_add_test(tc1_1, test_sub_matrix_1);
  tcase_add_test(tc1_1, test_sub_matrix_2);
  tcase_add_test(tc1_1, test_sub_matrix_3);
  tcase_add_test(tc1_1, test_sub_matrix_4);
  tcase_add_test(tc1_1, test_mul_number_1);
  tcase_add_test(tc1_1, test_mul_number_2);
  tcase_add_test(tc1_1, test_mul_matrix_1);
  tcase_add_test(tc1_1, test_mul_matrix_2);
  tcase_add_test(tc1_1, test_mul_matrix_3);
  tcase_add_test(tc1_1, test_transpose_matrix_1);
  tcase_add_test(tc1_1, test_transpose_matrix_2);
  tcase_add_test(tc1_1, test_calc_complements_1);
  tcase_add_test(tc1_1, test_calc_complements_2);
  tcase_add_test(tc1_1, test_calc_complements_3);
  tcase_add_test(tc1_1, test_calc_complements_4);
  tcase_add_test(tc1_1, test_determinate_1);
  tcase_add_test(tc1_1, test_determinate_2);
  tcase_add_test(tc1_1, test_determinate_3);
  tcase_add_test(tc1_1, test_inverse_matrix_1);
  tcase_add_test(tc1_1, test_inverse_matrix_2);
  tcase_add_test(tc1_1, test_inverse_matrix_3);
  tcase_add_test(tc1_1, test_inverse_matrix_4);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
