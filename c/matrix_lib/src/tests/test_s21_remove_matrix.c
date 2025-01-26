#include "test_s21_matrix.h"

START_TEST(test_s21_remove_matrix_0) {
  // A(1, 1)
  matrix_t A = {};
  s21_create_matrix(1, 1, &A);

  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(0, A.rows);
  ck_assert_int_eq(0, A.columns);
}
END_TEST

START_TEST(test_s21_remove_matrix_1) {
  // A(10, 1)
  matrix_t A = {};
  s21_create_matrix(10, 1, &A);

  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(0, A.rows);
  ck_assert_int_eq(0, A.columns);
}
END_TEST

START_TEST(test_s21_remove_matrix_2) {
  // A(1, 7)
  matrix_t A = {};
  s21_create_matrix(1, 7, &A);

  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(0, A.rows);
  ck_assert_int_eq(0, A.columns);
}
END_TEST

START_TEST(test_s21_remove_matrix_3) {
  // A(100, 100)
  matrix_t A = {};
  s21_create_matrix(100, 100, &A);

  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(0, A.rows);
  ck_assert_int_eq(0, A.columns);
}
END_TEST

Suite *test_s21_remove_matrix(void) {
  Suite *s = suite_create("===== S21_REMOVE_MATRIX =====");
  TCase *tc = tcase_create("s21_remove_matrix");

  tcase_add_test(tc, test_s21_remove_matrix_0);
  tcase_add_test(tc, test_s21_remove_matrix_1);
  tcase_add_test(tc, test_s21_remove_matrix_2);
  tcase_add_test(tc, test_s21_remove_matrix_3);
  suite_add_tcase(s, tc);

  return s;
}
