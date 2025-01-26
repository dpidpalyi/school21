#include "test_s21_matrix.h"

START_TEST(test_s21_inverse_matrix_0) {
  // A(0, 0)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(0, 0, &A);

  int got_int = s21_inverse_matrix(&A, &got);
  ck_assert_int_eq(ERROR, got_int);
}
END_TEST

START_TEST(test_s21_inverse_matrix_1) {
  // A(2, 3)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(2, 3, &A);

  int got_int = s21_inverse_matrix(&A, &got);
  ck_assert_int_eq(CALC_ERROR, got_int);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  // A(1, 1)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0.;

  int got_int = s21_inverse_matrix(&A, &got);
  ck_assert_int_eq(CALC_ERROR, got_int);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  // A(1, 1)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.;

  int got_int = s21_inverse_matrix(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], 1., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(test_s21_inverse_matrix_4) {
  // A(3, 3)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;

  int got_int = s21_inverse_matrix(&A, &got);
  ck_assert_int_eq(CALC_ERROR, got_int);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_5) {
  // A(3, 3)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2.;
  A.matrix[0][1] = 5.;
  A.matrix[0][2] = 7.;
  A.matrix[1][0] = 6.;
  A.matrix[1][1] = 3.;
  A.matrix[1][2] = 4.;
  A.matrix[2][0] = 5.;
  A.matrix[2][1] = -2.;
  A.matrix[2][2] = -3.;

  int got_int = s21_inverse_matrix(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], 1., EPS);
  ck_assert_double_eq_tol(got.matrix[0][1], -1., EPS);
  ck_assert_double_eq_tol(got.matrix[0][2], 1., EPS);
  ck_assert_double_eq_tol(got.matrix[1][0], -38., EPS);
  ck_assert_double_eq_tol(got.matrix[1][1], 41., EPS);
  ck_assert_double_eq_tol(got.matrix[1][2], -34., EPS);
  ck_assert_double_eq_tol(got.matrix[2][0], 27., EPS);
  ck_assert_double_eq_tol(got.matrix[2][1], -29., EPS);
  ck_assert_double_eq_tol(got.matrix[2][2], 24., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

Suite *test_s21_inverse_matrix(void) {
  Suite *s = suite_create("===== S21_INVERSE_MATRIX =====");
  TCase *tc = tcase_create("s21_inverse_matrix");

  tcase_add_test(tc, test_s21_inverse_matrix_0);
  tcase_add_test(tc, test_s21_inverse_matrix_1);
  tcase_add_test(tc, test_s21_inverse_matrix_2);
  tcase_add_test(tc, test_s21_inverse_matrix_3);
  tcase_add_test(tc, test_s21_inverse_matrix_4);
  tcase_add_test(tc, test_s21_inverse_matrix_5);
  suite_add_tcase(s, tc);

  return s;
}
