#include "test_s21_matrix.h"

START_TEST(test_s21_create_matrix_0) {
  // A(0, 0)
  matrix_t A = {};
  int got_int = s21_create_matrix(0, 0, &A);

  ck_assert_int_eq(ERROR, got_int);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_1) {
  // A(-1, 1)
  matrix_t A = {};
  int got_int = s21_create_matrix(-1, 1, &A);

  ck_assert_int_eq(ERROR, got_int);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_2) {
  // A(1, 1)
  matrix_t A = {};
  int got_int = s21_create_matrix(1, 1, &A);

  ck_assert_int_eq(OK, got_int);
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(1, A.rows);
  ck_assert_int_eq(1, A.columns);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_3) {
  // A(5, 1)
  matrix_t A = {};
  int got_int = s21_create_matrix(5, 1, &A);

  ck_assert_int_eq(OK, got_int);
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(5, A.rows);
  ck_assert_int_eq(1, A.columns);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_4) {
  // A(1, 10)
  matrix_t A = {};
  int got_int = s21_create_matrix(1, 10, &A);

  ck_assert_int_eq(OK, got_int);
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(1, A.rows);
  ck_assert_int_eq(10, A.columns);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_5) {
  // A(100, 100)
  matrix_t A = {};
  int got_int = s21_create_matrix(100, 100, &A);

  ck_assert_int_eq(OK, got_int);
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(100, A.rows);
  ck_assert_int_eq(100, A.columns);
  s21_remove_matrix(&A);
}
END_TEST

Suite *test_s21_create_matrix(void) {
  Suite *s = suite_create("===== S21_CREATE_MATRIX =====");
  TCase *tc = tcase_create("s21_create_matrix");

  tcase_add_test(tc, test_s21_create_matrix_0);
  tcase_add_test(tc, test_s21_create_matrix_1);
  tcase_add_test(tc, test_s21_create_matrix_2);
  tcase_add_test(tc, test_s21_create_matrix_3);
  tcase_add_test(tc, test_s21_create_matrix_4);
  tcase_add_test(tc, test_s21_create_matrix_5);
  suite_add_tcase(s, tc);

  return s;
}
