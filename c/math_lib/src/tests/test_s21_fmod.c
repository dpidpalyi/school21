#include "test_s21_math.h"

START_TEST(fmod_1) {
  double testValueX1 = -8;
  double testValueY1 = 3;
  double testValueX2 = -10;
  double testValueY2 = 2;
  double testValueX3 = 164.2;
  double testValueY3 = 0.3;
  ck_assert_ldouble_eq_tol(s21_fmod(testValueX1, testValueY1),
                           fmodl(testValueX1, testValueY1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(testValueX2, testValueY2),
                           fmodl(testValueX2, testValueY2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_fmod(testValueX3, testValueY3),
                           fmodl(testValueX3, testValueY3), TEST_EPS);
}

START_TEST(fmod_2) {
  double testValueX1 = 0;
  double testValueY1 = 0;
  double testValueX2 = 3;
  double testValueY2 = 0;
  double testValueX3 = 100;
  double testValueY3 = -5;
  double testValueX4 = S21_INF;
  double testValueY4 = -5;
  double testValueX5 = 4;
  double testValueY5 = S21_NAN;
  ck_assert_ldouble_nan(s21_fmod(testValueX1, testValueY1));
  ck_assert_ldouble_nan(fmodl(testValueX1, testValueY1));
  ck_assert_ldouble_nan(s21_fmod(testValueX2, testValueY2));
  ck_assert_ldouble_nan(fmodl(testValueX2, testValueY2));
  ck_assert_ldouble_eq_tol(s21_fmod(testValueX3, testValueY3),
                           fmodl(testValueX3, testValueY3), TEST_EPS);
  ck_assert_ldouble_nan(s21_fmod(testValueX4, testValueY4));
  ck_assert_ldouble_nan(fmodl(testValueX4, testValueY4));
  ck_assert_ldouble_nan(s21_fmod(testValueX5, testValueY5));
  ck_assert_ldouble_nan(fmodl(testValueX5, testValueY5));
}

Suite *test_s21_fmod(void) {
  Suite *s = suite_create("--== S21_FMOD ==--");
  TCase *tc = tcase_create("s21_fmod_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, fmod_1);
  tcase_add_test(tc, fmod_2);

  suite_add_tcase(s, tc);
  return s;
}
