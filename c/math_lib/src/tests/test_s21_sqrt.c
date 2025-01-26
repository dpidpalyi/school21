#include "test_s21_math.h"

START_TEST(test_s21_sqrt_for) {
  for (double x = 0.99; x > S21_EPS; x -= 0.01)
    ck_assert_ldouble_eq_tol(s21_sqrt(x), sqrtl(x), S21_EPS);
}

START_TEST(test_s21_sqrt_pos_1) {
  double x = 9.0;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_pos_2) {
  double x = 123.456789;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_pos_3) {
  double x = DBL_MIN;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_pos_4) {
  double x = 1e-20;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_pos_inf) {
  double x = INFINITY;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_infinite(want);
  ck_assert_ldouble_infinite(got);
}

START_TEST(test_s21_sqrt_pos_zero) {
  double x = +0.0;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_zero) {
  double x = 0.0;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_neg_zero) {
  double x = -0.0;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_sqrt_neg) {
  double x = -9.0;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_sqrt_nan) {
  double x = NAN;
  long double want = sqrtl(x);
  long double got = s21_sqrt(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

Suite *test_s21_sqrt(void) {
  Suite *s = suite_create("--== S21_SQRT ==--");
  TCase *tc = tcase_create("s21_sqrt_tc");

  tcase_add_test(tc, test_s21_sqrt_for);
  tcase_add_test(tc, test_s21_sqrt_pos_1);
  tcase_add_test(tc, test_s21_sqrt_pos_2);
  tcase_add_test(tc, test_s21_sqrt_pos_3);
  tcase_add_test(tc, test_s21_sqrt_pos_4);
  tcase_add_test(tc, test_s21_sqrt_pos_inf);
  tcase_add_test(tc, test_s21_sqrt_pos_zero);
  tcase_add_test(tc, test_s21_sqrt_zero);
  tcase_add_test(tc, test_s21_sqrt_neg_zero);
  tcase_add_test(tc, test_s21_sqrt_neg);
  tcase_add_test(tc, test_s21_sqrt_nan);
  suite_add_tcase(s, tc);

  return s;
}
