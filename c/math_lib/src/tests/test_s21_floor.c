#include "test_s21_math.h"

START_TEST(floor_1) {
  double testValue1 = -5.7;
  double testValue2 = 5.1;
  double testValue3 = 12.4;
  double testValue4 = 0.0;
  double testValue5 = -1.0 / INFINITY;
  ck_assert_ldouble_eq_tol(s21_floor(testValue1), floor(testValue1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_floor(testValue2), floor(testValue2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_floor(testValue3), floor(testValue3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_floor(testValue4), floor(testValue4), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_floor(testValue5), floor(testValue5), TEST_EPS);
  for (double i = -2.01; i <= 1.01; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_floor(i), floor(i), TEST_EPS);
  }
}

START_TEST(floor_2) {
  double testValue1 = S21_INF;
  double testValue2 = S21_NEG_INF;
  double testValue3 = S21_NAN;
  ck_assert_ldouble_infinite(s21_floor(testValue1));
  ck_assert_ldouble_infinite(floorl(testValue1));
  ck_assert_ldouble_infinite(s21_floor(testValue2));
  ck_assert_ldouble_infinite(floorl(testValue2));
  ck_assert_ldouble_nan(s21_floor(testValue3));
  ck_assert_ldouble_nan(floorl(testValue3));
}

Suite *test_s21_floor(void) {
  Suite *s = suite_create("--== S21_FLOOR ==--");
  TCase *tc = tcase_create("s21_floor_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);

  suite_add_tcase(s, tc);
  return s;
}
