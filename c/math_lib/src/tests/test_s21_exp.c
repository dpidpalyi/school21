#include "test_s21_math.h"

START_TEST(exp_1) {
  double testValue1 = -5;
  double testValue2 = 5;
  double testValue3 = 0.1;
  ck_assert_ldouble_eq_tol(s21_exp(testValue1), exp(testValue1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(testValue2), exp(testValue2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(testValue3), exp(testValue3), TEST_EPS);
}

START_TEST(exp_2) {
  double testValue1 = 243757437;
  double testValue2 = -24.4353425;
  double testValue3 = 0.0;
  for (double i = -20.0; i <= 20.00; i += 0.1) {
    ck_assert_ldouble_eq_tol(s21_exp(i), exp(i), TEST_EPS);
  }
  ck_assert_ldouble_infinite(s21_exp(testValue1));
  ck_assert_ldouble_eq_tol(s21_exp(testValue2), exp(testValue2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(testValue3), exp(testValue3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(testValue2), exp(testValue2), TEST_EPS);
}

START_TEST(exp_3) {
  ck_assert_ldouble_infinite(s21_exp(S21_INF));
  ck_assert_ldouble_eq(s21_exp(S21_INF), exp(S21_INF));
  ck_assert_ldouble_eq(s21_exp(S21_NEG_INF), exp(S21_NEG_INF));
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  ck_assert_ldouble_nan(exp(S21_NAN));
  ck_assert_ldouble_nan(s21_exp(-S21_NAN));
  ck_assert_ldouble_nan(exp(-S21_NAN));
}

Suite *test_s21_exp(void) {
  Suite *s = suite_create("--== S21_EXP ==--");
  TCase *tc = tcase_create("s21_exp_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, exp_1);
  tcase_add_test(tc, exp_2);
  tcase_add_test(tc, exp_3);

  suite_add_tcase(s, tc);
  return s;
}
