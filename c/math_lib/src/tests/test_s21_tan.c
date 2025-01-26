#include "test_s21_math.h"

START_TEST(test_s21_tan_for) {
  for (double x = 0.99; x > -0.99; x -= 0.01)
    ck_assert_ldouble_eq_tol(s21_tan(x), tanl(x), S21_EPS);
}

START_TEST(test_s21_tan_pos) {
  double x = 0.5;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_pos2) {
  double x = 5;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_pos_PI_2) {
  double x = S21_PI / 2;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, 1);
}

START_TEST(test_s21_tan_pos_mult_PI) {
  double x = 100 * S21_PI;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_pos_inf) {
  double x = INFINITY;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_tan_zero) {
  double x = 0.0;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_neg) {
  double x = -1.2;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_neg2) {
  double x = -4;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_neg_PI_2) {
  double x = -S21_PI / 2;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, 1);
}

START_TEST(test_s21_tan_neg_mult_PI) {
  double x = -100 * S21_PI;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_tan_neg_inf) {
  double x = -INFINITY;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

START_TEST(test_s21_tan_nan) {
  double x = NAN;
  long double want = tanl(x);
  long double got = s21_tan(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

Suite *test_s21_tan(void) {
  Suite *s = suite_create("--== S21_TAN ==--");
  TCase *tc = tcase_create("s21_tan_tc");

  tcase_add_test(tc, test_s21_tan_for);
  tcase_add_test(tc, test_s21_tan_pos);
  tcase_add_test(tc, test_s21_tan_pos2);
  tcase_add_test(tc, test_s21_tan_pos_PI_2);
  tcase_add_test(tc, test_s21_tan_pos_mult_PI);
  tcase_add_test(tc, test_s21_tan_pos_inf);
  tcase_add_test(tc, test_s21_tan_zero);
  tcase_add_test(tc, test_s21_tan_neg);
  tcase_add_test(tc, test_s21_tan_neg2);
  tcase_add_test(tc, test_s21_tan_neg_PI_2);
  tcase_add_test(tc, test_s21_tan_neg_mult_PI);
  tcase_add_test(tc, test_s21_tan_neg_inf);
  tcase_add_test(tc, test_s21_tan_nan);
  suite_add_tcase(s, tc);

  return s;
}
