#include "test_s21_math.h"

START_TEST(log_1) {
  double testValue1 = S21_EXP;
  double testValue2 = 10;
  double testValue3 = 3;
  ck_assert_ldouble_eq_tol(s21_log(testValue1), logl(testValue1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_log(testValue2), logl(testValue2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_log(testValue3), logl(testValue3), TEST_EPS);
  for (double i = 0.1; i < 100.0; i += 0.1) {
    ck_assert_ldouble_eq_tol(s21_log(i), logl(i), TEST_EPS);
  }
}

START_TEST(log_2) {
  double testValue1 = -1;
  double testValue2 = 0;
  double testValue3 = 0.00001;
  ck_assert_ldouble_nan(s21_log(testValue1));
  ck_assert_ldouble_nan(logl(testValue1));
  ck_assert_ldouble_infinite(s21_log(testValue2));
  ck_assert_ldouble_infinite(logl(testValue2));
  ck_assert_ldouble_eq_tol(s21_log(testValue3), logl(testValue3), TEST_EPS);
  ck_assert_ldouble_nan(s21_log(S21_NAN));
  ck_assert_ldouble_nan(logl(S21_NAN));
  ck_assert_ldouble_infinite(s21_log(S21_INF));
  ck_assert_ldouble_infinite(logl(S21_INF));
  ck_assert_ldouble_nan(s21_log(S21_NEG_INF));
  ck_assert_ldouble_nan(logl(S21_NEG_INF));
}

Suite *test_s21_log(void) {
  Suite *s = suite_create("--== S21_LOG ==--");
  TCase *tc = tcase_create("s21_log_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, log_1);
  tcase_add_test(tc, log_2);

  suite_add_tcase(s, tc);
  return s;
}
