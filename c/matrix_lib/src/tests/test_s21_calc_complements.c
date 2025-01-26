#include "test_s21_matrix.h"

START_TEST(test_s21_calc_complements_0) {
  // A(0, 0)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(0, 0, &A);

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(ERROR, got_int);
}
END_TEST

START_TEST(test_s21_calc_complements_1) {
  // A(2, 3)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(2, 3, &A);

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(CALC_ERROR, got_int);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complements_2) {
  // A(1, 1)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 10.;

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], 10., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(test_s21_calc_complements_3) {
  // A(2, 2)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 5.;
  A.matrix[0][1] = 4.;
  A.matrix[1][0] = 6.;
  A.matrix[1][1] = 5.;

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], 5., EPS);
  ck_assert_double_eq_tol(got.matrix[0][1], -6., EPS);
  ck_assert_double_eq_tol(got.matrix[1][0], -4., EPS);
  ck_assert_double_eq_tol(got.matrix[1][1], 5., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(test_s21_calc_complements_4) {
  // A(2, 2)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.;
  A.matrix[0][1] = 0.;
  A.matrix[1][0] = 0.;
  A.matrix[1][1] = 0.;

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], 0., EPS);
  ck_assert_double_eq_tol(got.matrix[0][1], 0., EPS);
  ck_assert_double_eq_tol(got.matrix[1][0], 0., EPS);
  ck_assert_double_eq_tol(got.matrix[1][1], 0., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(test_s21_calc_complements_5) {
  // A(3, 3)
  matrix_t A = {};
  matrix_t got = {};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 0.;
  A.matrix[1][1] = 4.;
  A.matrix[1][2] = 2.;
  A.matrix[2][0] = 5.;
  A.matrix[2][1] = 2.;
  A.matrix[2][2] = 1.;

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], 0., EPS);
  ck_assert_double_eq_tol(got.matrix[0][1], 10., EPS);
  ck_assert_double_eq_tol(got.matrix[0][2], -20., EPS);
  ck_assert_double_eq_tol(got.matrix[1][0], 4., EPS);
  ck_assert_double_eq_tol(got.matrix[1][1], -14., EPS);
  ck_assert_double_eq_tol(got.matrix[1][2], 8., EPS);
  ck_assert_double_eq_tol(got.matrix[2][0], -8., EPS);
  ck_assert_double_eq_tol(got.matrix[2][1], -2., EPS);
  ck_assert_double_eq_tol(got.matrix[2][2], 4., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

START_TEST(test_s21_calc_complements_6) {
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

  int got_int = s21_calc_complements(&A, &got);
  ck_assert_int_eq(OK, got_int);
  ck_assert_double_eq_tol(got.matrix[0][0], -1., EPS);
  ck_assert_double_eq_tol(got.matrix[0][1], 38., EPS);
  ck_assert_double_eq_tol(got.matrix[0][2], -27., EPS);
  ck_assert_double_eq_tol(got.matrix[1][0], 1., EPS);
  ck_assert_double_eq_tol(got.matrix[1][1], -41., EPS);
  ck_assert_double_eq_tol(got.matrix[1][2], 29., EPS);
  ck_assert_double_eq_tol(got.matrix[2][0], -1., EPS);
  ck_assert_double_eq_tol(got.matrix[2][1], 34., EPS);
  ck_assert_double_eq_tol(got.matrix[2][2], -24., EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&got);
}
END_TEST

Suite *test_s21_calc_complements(void) {
  Suite *s = suite_create("===== S21_CALC_COMPLEMENTS =====");
  TCase *tc = tcase_create("s21_calc_complements");

  tcase_add_test(tc, test_s21_calc_complements_0);
  tcase_add_test(tc, test_s21_calc_complements_1);
  tcase_add_test(tc, test_s21_calc_complements_2);
  tcase_add_test(tc, test_s21_calc_complements_3);
  tcase_add_test(tc, test_s21_calc_complements_4);
  tcase_add_test(tc, test_s21_calc_complements_5);
  tcase_add_test(tc, test_s21_calc_complements_6);
  suite_add_tcase(s, tc);

  return s;
}
