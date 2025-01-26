#include "test_s21_matrix.h"

START_TEST(test_s21_eq_matrix_0) {
  // A(0, 0), B(0, 0)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, got_int);
}
END_TEST

START_TEST(test_s21_eq_matrix_1) {
  // A(1, 1), B(1, 2)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 2, &B);

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_2) {
  // A(1, 1), B(1, 1)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 0.;
  B.matrix[0][0] = 0.;

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(SUCCESS, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_3) {
  // A(1, 1), B(1, 1)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.;
  B.matrix[0][0] = 0.;

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_4) {
  // A(1, 1), B(1, 1)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.123456789;
  B.matrix[0][0] = 1.123456789;

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(SUCCESS, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_5) {
  // A(1, 1), B(1, 1)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.123456889;
  B.matrix[0][0] = 1.123456789;

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_6) {
  // A(2, 2), B(2, 2)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 1.;
  A.matrix[1][0] = 1.;
  A.matrix[1][1] = 1.;
  B.matrix[0][0] = 1.;
  B.matrix[0][1] = 1.;
  B.matrix[1][0] = 1.;
  B.matrix[1][1] = 1.;

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(SUCCESS, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_7) {
  // A(2, 2), B(2, 2)
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 1.;
  A.matrix[1][0] = 1.;
  A.matrix[1][1] = 1.;
  B.matrix[0][0] = 1.;
  B.matrix[0][1] = 1.;
  B.matrix[1][0] = 1.;
  B.matrix[1][1] = 1.000001;

  int got_int = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, got_int);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_s21_eq_matrix(void) {
  Suite *s = suite_create("===== S21_EQ_MATRIX =====");
  TCase *tc = tcase_create("s21_eq_matrix");

  tcase_add_test(tc, test_s21_eq_matrix_0);
  tcase_add_test(tc, test_s21_eq_matrix_1);
  tcase_add_test(tc, test_s21_eq_matrix_2);
  tcase_add_test(tc, test_s21_eq_matrix_3);
  tcase_add_test(tc, test_s21_eq_matrix_4);
  tcase_add_test(tc, test_s21_eq_matrix_5);
  tcase_add_test(tc, test_s21_eq_matrix_6);
  tcase_add_test(tc, test_s21_eq_matrix_7);
  suite_add_tcase(s, tc);

  return s;
}
