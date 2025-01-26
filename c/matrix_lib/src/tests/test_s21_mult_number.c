#include "test_s21_matrix.h"

START_TEST(test_s21_mult_number_0) {
  // A(0, 0), n = 1.
  matrix_t A = {};
  double n = 1.;
  matrix_t WANT = {};
  s21_create_matrix(0, 0, &A);

  int got_int = s21_mult_number(&A, n, &WANT);
  ck_assert_int_eq(ERROR, got_int);
}
END_TEST

START_TEST(test_s21_mult_number_1) {
  // A(1, 1), n = 2.
  matrix_t A = {};
  double n = 2.;
  matrix_t WANT = {};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 3.;

  int got_int = s21_mult_number(&A, n, &WANT);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(WANT.matrix[0][0], 6., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&WANT);
}
END_TEST

START_TEST(test_s21_mult_number_2) {
  // A(3, 1), n = -3.
  matrix_t A = {};
  double n = -3.;
  matrix_t WANT = {};
  s21_create_matrix(3, 1, &A);
  A.matrix[0][0] = 0.;
  A.matrix[1][0] = 1.;
  A.matrix[2][0] = 2.;

  int got_int = s21_mult_number(&A, n, &WANT);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(WANT.matrix[0][0], 0., EPS);
  ck_assert_double_eq_tol(WANT.matrix[1][0], -3., EPS);
  ck_assert_double_eq_tol(WANT.matrix[2][0], -6., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&WANT);
}
END_TEST

START_TEST(test_s21_mult_number_3) {
  // A(1, 3), n = 0.
  matrix_t A = {};
  double n = 0.;
  matrix_t WANT = {};
  s21_create_matrix(1, 3, &A);
  A.matrix[0][0] = 0.;
  A.matrix[0][1] = 1.;
  A.matrix[0][2] = 2.;

  int got_int = s21_mult_number(&A, n, &WANT);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(WANT.matrix[0][0], 0., EPS);
  ck_assert_double_eq_tol(WANT.matrix[0][1], 0., EPS);
  ck_assert_double_eq_tol(WANT.matrix[0][2], 0., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&WANT);
}
END_TEST

START_TEST(test_s21_mult_number_4) {
  // A(2, 2), n = 2.
  matrix_t A = {};
  double n = 2.;
  matrix_t WANT = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.;
  A.matrix[0][1] = 1.;
  A.matrix[1][0] = 2.;
  A.matrix[1][1] = 3.;

  int got_int = s21_mult_number(&A, n, &WANT);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(WANT.matrix[0][0], 0., EPS);
  ck_assert_double_eq_tol(WANT.matrix[0][1], 2., EPS);
  ck_assert_double_eq_tol(WANT.matrix[1][0], 4., EPS);
  ck_assert_double_eq_tol(WANT.matrix[1][1], 6., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&WANT);
}
END_TEST

Suite *test_s21_mult_number(void) {
  Suite *s = suite_create("===== S21_MULT_NUMBER =====");
  TCase *tc = tcase_create("s21_mult_number");

  tcase_add_test(tc, test_s21_mult_number_0);
  tcase_add_test(tc, test_s21_mult_number_1);
  tcase_add_test(tc, test_s21_mult_number_2);
  tcase_add_test(tc, test_s21_mult_number_3);
  tcase_add_test(tc, test_s21_mult_number_4);
  suite_add_tcase(s, tc);

  return s;
}
