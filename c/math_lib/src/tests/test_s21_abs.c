#include "test_s21_math.h"

START_TEST(abs_pos_inf) {
  int x = INT_MAX;
  ck_assert_int_eq(s21_abs(x), abs(x));
}

START_TEST(abs_1) {
  int x = 5;
  ck_assert_int_eq(s21_abs(x), abs(x));
}

START_TEST(abs_2) {
  int x = 0;
  ck_assert_int_eq(s21_abs(x), abs(x));
}

START_TEST(abs_3) {
  int x = -5;
  ck_assert_int_eq(s21_abs(x), abs(x));
}

START_TEST(abs_neg_inf) {
  int x = INT_MIN;
  ck_assert_int_eq(s21_abs(x), abs(x));
}

Suite *test_s21_abs(void) {
  Suite *s = suite_create("--== S21_ABS ==--");
  TCase *tc = tcase_create("s21_abs_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, abs_pos_inf);
  tcase_add_test(tc, abs_1);
  tcase_add_test(tc, abs_2);
  tcase_add_test(tc, abs_3);
  tcase_add_test(tc, abs_neg_inf);

  suite_add_tcase(s, tc);
  return s;
}
