#include "test_s21_matrix.h"

START_TEST(test_s21_determinant_0) {
  // A(0, 0)
  matrix_t A = {};
  double got;
  s21_create_matrix(0, 0, &A);

  int got_int = s21_determinant(&A, &got);
  ck_assert_int_eq(ERROR, got_int);
}
END_TEST

START_TEST(test_s21_determinant_1) {
  // A(2, 3)
  matrix_t A = {};
  double got;
  s21_create_matrix(2, 3, &A);

  int got_int = s21_determinant(&A, &got);
  ck_assert_int_eq(CALC_ERROR, got_int);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_2) {
  // A(1, 1)
  matrix_t A = {};
  double got;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 10.;

  int got_int = s21_determinant(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got, 10., EPS);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_3) {
  // A(2, 2)
  matrix_t A = {};
  double got;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 5.;
  A.matrix[0][1] = 4.;
  A.matrix[1][0] = 6.;
  A.matrix[1][1] = 5.;

  int got_int = s21_determinant(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got, 1., EPS);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_4) {
  // A(2, 2)
  matrix_t A = {};
  double got;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.;
  A.matrix[0][1] = 0.;
  A.matrix[1][0] = 0.;
  A.matrix[1][1] = 0.;

  int got_int = s21_determinant(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got, 0., EPS);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_5) {
  // A(3, 3)
  matrix_t A = {};
  double got;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 1.;
  A.matrix[1][0] = 3.;
  A.matrix[1][1] = 1.;
  A.matrix[1][2] = 2.;
  A.matrix[2][0] = 2.;
  A.matrix[2][1] = 1.;
  A.matrix[2][2] = 0.;

  int got_int = s21_determinant(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got, 7., EPS);
  s21_remove_matrix(&A);
}
END_TEST

Suite *test_s21_determinant(void) {
  Suite *s = suite_create("===== S21_DETERMINANT =====");
  TCase *tc = tcase_create("s21_determinant");

  tcase_add_test(tc, test_s21_determinant_0);
  tcase_add_test(tc, test_s21_determinant_1);
  tcase_add_test(tc, test_s21_determinant_2);
  tcase_add_test(tc, test_s21_determinant_3);
  tcase_add_test(tc, test_s21_determinant_4);
  tcase_add_test(tc, test_s21_determinant_5);
  suite_add_tcase(s, tc);

  return s;
}
