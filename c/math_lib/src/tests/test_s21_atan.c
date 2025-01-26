#include "test_s21_math.h"


START_TEST(test_s21_atan_pos_one_less) {
  double x = 0.5;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_pos) {
  for (double x = 0.99; x > -0.99; x -= 0.01)
    ck_assert_ldouble_eq_tol(s21_atan(x), atanl(x), S21_EPS);
}

START_TEST(test_s21_atan_pos_big) {
  double x = INT_MAX;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_pos_one_more) {
  double x = 10;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_pos_one) {
  double x = 1.0;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_pos_inf) {
  double x = INFINITY;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_zero) {
  double x = 0.0;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_neg_one_less) {
  double x = -9.0;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_neg_one_more) {
  double x = -0.7;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_neg_big) {
  double x = INT_MIN;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_neg_one) {
  double x = -1.0;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_neg_inf) {
  double x = -INFINITY;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_eq_tol(got, want, S21_EPS);
}

START_TEST(test_s21_atan_nan) {
  double x = NAN;
  long double want = atanl(x);
  long double got = s21_atan(x);
  ck_assert_ldouble_nan(want);
  ck_assert_ldouble_nan(got);
}

Suite *test_s21_atan(void) {
  Suite *s = suite_create("--== S21_ATAN ==--");
  TCase *tc = tcase_create("s21_atan_tc");

  tcase_add_test(tc, test_s21_atan_pos_one_less);
  tcase_add_test(tc, test_s21_atan_pos);
  tcase_add_test(tc, test_s21_atan_pos_big);
  tcase_add_test(tc, test_s21_atan_pos_one_more);
  tcase_add_test(tc, test_s21_atan_pos_one);
  tcase_add_test(tc, test_s21_atan_pos_inf);
  tcase_add_test(tc, test_s21_atan_zero);
  tcase_add_test(tc, test_s21_atan_neg_one_less);
  tcase_add_test(tc, test_s21_atan_neg_one_more);
  tcase_add_test(tc, test_s21_atan_neg_one);
  tcase_add_test(tc, test_s21_atan_neg_big);
  tcase_add_test(tc, test_s21_atan_neg_inf);
  tcase_add_test(tc, test_s21_atan_nan);
  suite_add_tcase(s, tc);

  return s;
}
