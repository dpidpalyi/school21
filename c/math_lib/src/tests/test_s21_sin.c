#include "test_s21_math.h"

START_TEST(test_s21_sin_for) {
  for (double x = 0.99; x > -0.99; x -= 0.01)
    ck_assert_ldouble_eq_tol(s21_sin(x), sinl(x), S21_EPS);
}

START_TEST(test_s21_sin_pos) {
  double x = 0.5;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_pos_PI_2) {
  double x = S21_PI / 2;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_pos_PI) {
  double x = S21_PI;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_pos_mult_PI) {
  double x = 100 * S21_PI;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_pos_inf) {
  double x = INFINITY;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_sin_zero) {
  double x = 0.0;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_neg) {
  double x = -1.2;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_neg_PI) {
  double x = -S21_PI;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_neg_PI_2) {
  double x = -S21_PI / 2;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sin_neg_mult_PI) {
  double x = -100 * S21_PI;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}
START_TEST(test_s21_sin_neg_inf) {
  double x = -INFINITY;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_sin_nan) {
  double x = NAN;
  long double want = sinl(x);
  long double got = s21_sin(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

Suite *test_s21_sin(void) {
  Suite *s = suite_create("--== S21_SIN ==--");
  TCase *tc = tcase_create("s21_sin_tc");

  tcase_add_test(tc, test_s21_sin_for);
  tcase_add_test(tc, test_s21_sin_pos);
  tcase_add_test(tc, test_s21_sin_pos_PI_2);
  tcase_add_test(tc, test_s21_sin_pos_PI);
  tcase_add_test(tc, test_s21_sin_pos_mult_PI);
  tcase_add_test(tc, test_s21_sin_pos_inf);
  tcase_add_test(tc, test_s21_sin_zero);
  tcase_add_test(tc, test_s21_sin_neg);
  tcase_add_test(tc, test_s21_sin_neg_PI_2);
  tcase_add_test(tc, test_s21_sin_neg_PI);
  tcase_add_test(tc, test_s21_sin_neg_mult_PI);
  tcase_add_test(tc, test_s21_sin_neg_inf);
  tcase_add_test(tc, test_s21_sin_nan);
  suite_add_tcase(s, tc);

  return s;
}
