#include "test_s21_math.h"

START_TEST(pow_1) {
  ck_assert_ldouble_eq_tol(s21_pow(8, 3), powl(8, 3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(-8, 3), powl(-8, 3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(8, -3), powl(8, -3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(0, 0), powl(0, 0), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(1, -3), powl(1, -3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(0, 5), powl(0, 5), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(8.234, -3), powl(8.234, -3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(25, 0.5), powl(25, 0.5), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(5, 1.4), powl(5, 1.4), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(5, -1.4), powl(5, -1.4), TEST_EPS);
  ck_assert_ldouble_nan(s21_pow(-4, 1.4));
  ck_assert_ldouble_nan(powl(-4, 1.4));
}

START_TEST(pow_2) {
  int base = 2989839;
  double exp1 = 0.0004;
  int exp3 = 0;
  int exp5 = -2;

  ck_assert_ldouble_eq_tol(s21_pow(base, exp1), powl(base, exp1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(base, exp3), powl(base, exp3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(base, exp5), powl(base, exp5), TEST_EPS);
}

START_TEST(pow_3) {
  double base = 0.0083928293832;
  double exp1 = 0.0004;
  int exp2 = 293;
  int exp3 = 0;
  int exp4 = 66;

  ck_assert_ldouble_eq_tol(s21_pow(base, exp1), powl(base, exp1), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(base, exp2), powl(base, exp2), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(base, exp3), powl(base, exp3), TEST_EPS);
  ck_assert_ldouble_eq_tol(s21_pow(base, exp4), powl(base, exp4), TEST_EPS);
}
END_TEST

START_TEST(pow_4) {
  ck_assert_ldouble_infinite(s21_pow(0.0, -3));
  ck_assert_ldouble_infinite(powl(0.0, -3));
  ck_assert_ldouble_eq(s21_pow(0.0, 3), powl(0.0, 3));
  ck_assert_ldouble_eq(s21_pow(S21_INF, 0), powl(S21_INF, 0));
  ck_assert_ldouble_eq(s21_pow(S21_NEG_INF, 0), powl(S21_NEG_INF, 0));
  ck_assert_ldouble_eq(s21_pow(S21_NEG_INF, S21_INF),
                       powl(S21_NEG_INF, S21_INF));
  ck_assert_ldouble_nan(s21_pow(S21_NEG_INF, S21_NAN));
  ck_assert_ldouble_eq(s21_pow(S21_INF, S21_INF), powl(S21_INF, S21_INF));
  ck_assert_ldouble_nan(s21_pow(S21_INF, S21_NAN));
  ck_assert_ldouble_eq(s21_pow(0.0, 2), powl(0.0, 2));
  ck_assert_ldouble_eq(s21_pow(-1, S21_INF), powl(-1, S21_INF));
  ck_assert_ldouble_eq(s21_pow(1, S21_NAN), powl(1, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(0.0, S21_NAN));
  ck_assert_ldouble_nan(powl(0.0, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(0.0, -S21_NAN));
  ck_assert_ldouble_nan(powl(0.0, -S21_NAN));
  ck_assert_ldouble_eq(s21_pow(S21_NAN, 0), powl(S21_NAN, 0));
  ck_assert_ldouble_nan(s21_pow(-2, 1.5));
  ck_assert_ldouble_nan(s21_pow(0.0, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(0.0, -S21_NAN));
  ck_assert_ldouble_nan(powl(-2, 1.5));
  ck_assert_ldouble_eq(s21_pow(0.5, S21_NEG_INF), powl(0.5, S21_NEG_INF));
  ck_assert_ldouble_eq(s21_pow(0.0, S21_NEG_INF), powl(0.0, S21_NEG_INF));
  ck_assert_ldouble_eq(s21_pow(2, S21_NEG_INF), powl(2, S21_NEG_INF));
  ck_assert_ldouble_eq(s21_pow(0.5, S21_INF), powl(0.5, S21_INF));
  ck_assert_ldouble_eq(s21_pow(2, S21_INF), pow(2, S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_NEG_INF, -3), powl(S21_NEG_INF, -3));
  ck_assert_ldouble_eq(s21_pow(S21_NEG_INF, -2), powl(S21_NEG_INF, -2));
  ck_assert_ldouble_eq(s21_pow(S21_NEG_INF, 3), powl(S21_NEG_INF, 3));
  ck_assert_ldouble_eq(s21_pow(S21_NEG_INF, 2), powl(S21_NEG_INF, 2));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -2), powl(S21_INF, -2));
  ck_assert_ldouble_eq(s21_pow(S21_INF, 2), powl(S21_INF, 2));
}
END_TEST

Suite *test_s21_pow(void) {
  Suite *s = suite_create("--== S21_POW ==--");
  TCase *tc = tcase_create("s21_pow_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, pow_1);
  tcase_add_test(tc, pow_2);
  tcase_add_test(tc, pow_3);
  tcase_add_test(tc, pow_4);

  suite_add_tcase(s, tc);
  return s;
}
