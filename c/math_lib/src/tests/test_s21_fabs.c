#include "test_s21_math.h"

START_TEST(fabs_1) {
  double testValue1 = -5.503;
  double testValue2 = 5.0;
  double testValue3 = 0;
  double testValue4 = -0;
  ck_assert_ldouble_eq_tol(s21_fabs(testValue1), fabsl(testValue1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_fabs(testValue2), fabsl(testValue2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_fabs(testValue3), fabsl(testValue3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_fabs(testValue4), fabsl(testValue4), TEST_EPS);
}

START_TEST(fabs_2) {
  double testValue1 = S21_NAN;
  double testValue2 = INFINITY;
  double testValue3 = -INFINITY;
  ck_assert_ldouble_nan(s21_fabs(testValue1));
  ck_assert_ldouble_nan(fabsl(testValue1));
  ck_assert_ldouble_infinite(s21_fabs(testValue2));
  ck_assert_ldouble_infinite(fabsl(testValue2));
  ck_assert_ldouble_infinite(s21_fabs(testValue3));
  ck_assert_ldouble_infinite(fabsl(testValue3));
}

Suite *test_s21_fabs(void) {
  Suite *s = suite_create("--== S21_FABS ==--");
  TCase *tc = tcase_create("s21_fabs_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, fabs_1);
  tcase_add_test(tc, fabs_2);

  suite_add_tcase(s, tc);
  return s;
}
