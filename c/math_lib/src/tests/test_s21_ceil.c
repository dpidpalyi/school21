#include "test_s21_math.h"

START_TEST(ceil_1) {
  double testValue1 = -5.7;
  double testValue2 = -0.1;
  double testValue3 = 12.4;
  ck_assert_ldouble_eq_tol(s21_ceil(testValue1), ceil(testValue1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_ceil(testValue2), ceil(testValue2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_ceil(testValue3), ceil(testValue3), TEST_EPS);
  for (double i = -1.01; i <= 1.01; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_ceil(i), ceil(i), TEST_EPS);
  }
}

START_TEST(ceil_2) {
  double testValue1 = S21_INF;
  double testValue2 = S21_NEG_INF;
  double testValue3 = S21_NAN;
  ck_assert_ldouble_infinite(s21_ceil(testValue1));
  ck_assert_ldouble_infinite(s21_ceil(testValue2));
  ck_assert_ldouble_nan(s21_ceil(testValue3));
}

Suite *test_s21_ceil(void) {
  Suite *s = suite_create("--== S21_CEIL ==--");
  TCase *tc = tcase_create("s21_ceil_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, ceil_1);
  tcase_add_test(tc, ceil_2);

  suite_add_tcase(s, tc);
  return s;
}
