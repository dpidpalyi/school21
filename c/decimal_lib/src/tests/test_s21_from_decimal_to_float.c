#include "test_s21_decimal.h"

START_TEST(test_s21_from_decimal_to_float_0) {
  s21_decimal n = {{0, 0, 0, 0}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(0.0, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_1) {
  s21_decimal n = {{1, 0, 0, 0}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(1., got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_2) {
  s21_decimal n = {{1, 0, 0, MINUS}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(-1., got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_3) {
  s21_decimal n = {{1, 0, 0, 0x00010000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(0.1, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_4) {
  s21_decimal n = {{1, 0, 0, 0x80010000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(-0.1, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_5) {
  s21_decimal n = {{0x4F790D55, 0, 0, 0x00090000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(4 / 3., got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_6) {
  s21_decimal n = {{0x4F790D55, 0, 0, 0x80090000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(-4 / 3., got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_7) {
  s21_decimal n = {{25, 0, 0, 0x00020000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(0.25, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_8) {
  s21_decimal n = {{25, 0, 0, 0x80020000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(-0.25, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_9) {
  s21_decimal n = {{0xC6AEA155, 0, 0, 0x000A0000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(1 / 3., got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_10) {
  s21_decimal n = {{0xC6AEA155, 0, 0, 0x800A0000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  ck_assert_float_eq_tol(-1 / 3., got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_11) {
  s21_decimal n = {{F8, F8, F8, 0}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  float want_float = pow(2, 96) - 1;
  ck_assert_float_eq_tol(want_float, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_12) {
  s21_decimal n = {{F8, F8, F8, MINUS}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  float want_float = -(pow(2, 96) - 1);
  ck_assert_float_eq_tol(want_float, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_13) {
  s21_decimal n = {{F8, F8, F8, 0x00050000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  float want_float = (pow(2, 96) - 1) / pow(10, 5);
  ck_assert_float_eq_tol(want_float, got_float, EPS);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_14) {
  s21_decimal n = {{F8, F8, F8, 0x80050000}};
  float got_float;

  int got = s21_from_decimal_to_float(n, &got_float);
  ck_assert_int_eq(0, got);
  float want_float = -((pow(2, 96) - 1) / pow(10, 5));
  ck_assert_float_eq_tol(want_float, got_float, EPS);
}
END_TEST

Suite *test_s21_from_decimal_to_float(void) {
  Suite *s = suite_create("===== S21_FROM_DECIMAL_TO_FLOAT =====");
  TCase *tc = tcase_create("s21_from_decimal_to_float");

  tcase_add_test(tc, test_s21_from_decimal_to_float_0);
  tcase_add_test(tc, test_s21_from_decimal_to_float_1);
  tcase_add_test(tc, test_s21_from_decimal_to_float_2);
  tcase_add_test(tc, test_s21_from_decimal_to_float_3);
  tcase_add_test(tc, test_s21_from_decimal_to_float_4);
  tcase_add_test(tc, test_s21_from_decimal_to_float_5);
  tcase_add_test(tc, test_s21_from_decimal_to_float_6);
  tcase_add_test(tc, test_s21_from_decimal_to_float_7);
  tcase_add_test(tc, test_s21_from_decimal_to_float_8);
  tcase_add_test(tc, test_s21_from_decimal_to_float_9);
  tcase_add_test(tc, test_s21_from_decimal_to_float_10);
  tcase_add_test(tc, test_s21_from_decimal_to_float_11);
  tcase_add_test(tc, test_s21_from_decimal_to_float_12);
  tcase_add_test(tc, test_s21_from_decimal_to_float_13);
  tcase_add_test(tc, test_s21_from_decimal_to_float_14);
  suite_add_tcase(s, tc);

  return s;
}
