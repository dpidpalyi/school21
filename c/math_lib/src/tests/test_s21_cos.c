#include "test_s21_math.h"

START_TEST(test_s21_cos_pos_for) {
  for (double x = 0.99; x > -0.99; x -= 0.01)
    ck_assert_ldouble_eq_tol(s21_cos(x), cosl(x), S21_EPS);
}

START_TEST(test_s21_cos_pos) {
  double x = 0.5;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_pos_PI) {
  double x = S21_PI;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_pos_PI_2) {
  double x = S21_PI / 2;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_pos_mult_PI) {
  double x = 100 * S21_PI;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_pos_inf) {
  double x = INFINITY;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_cos_zero) {
  double x = 0.0;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_neg) {
  double x = -1.2;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_neg_PI) {
  double x = -S21_PI;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_neg_PI_2) {
  double x = -S21_PI / 2;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_cos_neg_mult_PI) {
  double x = -100 * S21_PI;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}
START_TEST(test_s21_cos_neg_inf) {
  double x = -INFINITY;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_cos_nan) {
  double x = NAN;
  long double want = cosl(x);
  long double got = s21_cos(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

Suite *test_s21_cos(void) {
  Suite *s = suite_create("--== S21_COS ==--");
  TCase *tc = tcase_create("s21_cos_tc");

  tcase_add_test(tc, test_s21_cos_pos_for);
  tcase_add_test(tc, test_s21_cos_pos);
  tcase_add_test(tc, test_s21_cos_pos_PI);
  tcase_add_test(tc, test_s21_cos_pos_PI_2);
  tcase_add_test(tc, test_s21_cos_pos_mult_PI);
  tcase_add_test(tc, test_s21_cos_pos_inf);
  tcase_add_test(tc, test_s21_cos_zero);
  tcase_add_test(tc, test_s21_cos_neg);
  tcase_add_test(tc, test_s21_cos_neg_PI);
  tcase_add_test(tc, test_s21_cos_neg_PI_2);
  tcase_add_test(tc, test_s21_cos_neg_mult_PI);
  tcase_add_test(tc, test_s21_cos_neg_inf);
  tcase_add_test(tc, test_s21_cos_nan);
  suite_add_tcase(s, tc);

  return s;
}
