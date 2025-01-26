#include "test_s21_math.h"

START_TEST(test_s21_acos_for) {
  for (double x = 0.99; x > -0.99; x -= 0.01)
    ck_assert_ldouble_eq_tol(s21_acos(x), acosl(x), S21_EPS);
}

START_TEST(test_s21_acos_pos_one_less) {
  double x = 0.5;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_acos_pos_one_more) {
  double x = 10;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_acos_pos_one) {
  double x = 1.0;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_acos_zero) {
  double x = 0.0;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_acos_neg_one_less) {
  double x = -9.0;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_acos_neg_one_more) {
  double x = -0.7;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_acos_neg_one) {
  double x = -1.0;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_acos_nan) {
  double x = NAN;
  long double want = acosl(x);
  long double got = s21_acos(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

Suite *test_s21_acos(void) {
  Suite *s = suite_create("--== S21_ACOS ==--");
  TCase *tc = tcase_create("s21_acos_tc");

  tcase_add_test(tc, test_s21_acos_for);
  tcase_add_test(tc, test_s21_acos_pos_one_less);
  tcase_add_test(tc, test_s21_acos_pos_one_more);
  tcase_add_test(tc, test_s21_acos_pos_one);
  tcase_add_test(tc, test_s21_acos_zero);
  tcase_add_test(tc, test_s21_acos_neg_one_less);
  tcase_add_test(tc, test_s21_acos_neg_one_more);
  tcase_add_test(tc, test_s21_acos_neg_one);
  tcase_add_test(tc, test_s21_acos_nan);
  suite_add_tcase(s, tc);

  return s;
}
