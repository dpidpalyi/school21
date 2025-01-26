#include "test_s21_matrix.h"

START_TEST(test_s21_mult_matrix_0) {
  // A(0, 0), B(0, 0)
  matrix_t A = {};
  matrix_t B = {};
  matrix_t WANT = {};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  int got_int = s21_mult_matrix(&A, &B, &WANT);
  ck_assert_int_eq(ERROR, got_int);
}
END_TEST

START_TEST(test_s21_mult_matrix_1) {
  // A(1, 1), B(2, 2)
  matrix_t A = {};
  matrix_t B = {};
  matrix_t WANT = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 2, &B);

  int got_int = s21_mult_matrix(&A, &B, &WANT);
  ck_assert_int_eq(CALC_ERROR, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_2) {
  // A(1, 1), B(1, 1)
  matrix_t A = {};
  matrix_t B = {};
  matrix_t WANT = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 2.;
  B.matrix[0][0] = 3.;

  int got_int = s21_mult_matrix(&A, &B, &WANT);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(WANT.matrix[0][0], 6., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&WANT);
}
END_TEST

START_TEST(test_s21_mult_matrix_3) {
  // A(3, 2), B(2, 3)
  matrix_t A = {};
  matrix_t B = {};
  matrix_t WANT = {};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  A.matrix[0][0] = 1.;
  A.matrix[1][0] = 2.;
  A.matrix[2][0] = 3.;
  A.matrix[0][1] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[2][1] = 6.;
  B.matrix[0][0] = 1.;
  B.matrix[1][0] = 2.;
  B.matrix[0][1] = -1.;
  B.matrix[1][1] = 3.;
  B.matrix[0][2] = 1.;
  B.matrix[1][2] = 4.;

  int got_int = s21_mult_matrix(&A, &B, &WANT);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(WANT.matrix[0][0], 9., EPS);
  ck_assert_double_eq_tol(WANT.matrix[1][0], 12., EPS);
  ck_assert_double_eq_tol(WANT.matrix[2][0], 15., EPS);
  ck_assert_double_eq_tol(WANT.matrix[0][1], 11., EPS);
  ck_assert_double_eq_tol(WANT.matrix[1][1], 13., EPS);
  ck_assert_double_eq_tol(WANT.matrix[2][1], 15., EPS);
  ck_assert_double_eq_tol(WANT.matrix[0][2], 17., EPS);
  ck_assert_double_eq_tol(WANT.matrix[1][2], 22., EPS);
  ck_assert_double_eq_tol(WANT.matrix[2][2], 27., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&WANT);
}
END_TEST

Suite *test_s21_mult_matrix(void) {
  Suite *s = suite_create("===== S21_MULT_MATRIX =====");
  TCase *tc = tcase_create("s21_mult_matrix");

  tcase_add_test(tc, test_s21_mult_matrix_0);
  tcase_add_test(tc, test_s21_mult_matrix_1);
  tcase_add_test(tc, test_s21_mult_matrix_2);
  tcase_add_test(tc, test_s21_mult_matrix_3);
  suite_add_tcase(s, tc);

  return s;
}
