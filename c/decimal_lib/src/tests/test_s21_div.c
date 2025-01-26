#include "test_s21_decimal.h"

START_TEST(test_s21_div_0) {
  // 0 / 0 = 0
  s21_decimal value1 = {};
  s21_decimal value2 = {};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(3, got_int);
}
END_TEST

START_TEST(test_s21_div_1) {
  // 0 / 1 = 0
  s21_decimal value1 = {};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_2) {
  // (-1) / 0 = 0
  s21_decimal value1 = {{1, 0, 0, MINUS}};
  s21_decimal value2 = {};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(3, got_int);
}
END_TEST

START_TEST(test_s21_div_3) {
  // 1 / 1 = 1
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {{1, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_4) {
  // (-2) / 1 = -2
  s21_decimal value1 = {{2, 0, 0, MINUS}};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {{2, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_5) {
  // 1000 / 10 = 100
  s21_decimal value1 = {{1000, 0, 0, 0}};
  s21_decimal value2 = {{10, 0, 0, 0}};
  s21_decimal want = {{100, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_6) {
  // MAX / 1 = MAX
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {{F8, F8, F8, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_7) {
  // MAX / MAX = 1
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{F8, F8, F8, 0}};
  s21_decimal want = {{1, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_8) {
  // MIN / MIN = 1
  s21_decimal value1 = {{F8, F8, F8, MINUS}};
  s21_decimal value2 = {{F8, F8, F8, MINUS}};
  s21_decimal want = {{1, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_9) {
  // MAX / 0.1 = INF
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{1, 0, 0, 0x00010000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_div_10) {
  // MIN / 0.00001 = -INF
  s21_decimal value1 = {{F8, F8, F8, MINUS}};
  s21_decimal value2 = {{1, 0, 0, 0x00050000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(2, got_int);
}
END_TEST

START_TEST(test_s21_div_11) {
  // 3 / 2 = 1.5
  s21_decimal value1 = {{3, 0, 0, 0}};
  s21_decimal value2 = {{2, 0, 0, 0}};
  s21_decimal want = {{15, 0, 0, 0x00010000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_12) {
  // 2^32 / 2 = 2147483648
  s21_decimal value1 = {{0, 1, 0, 0}};
  s21_decimal value2 = {{2, 0, 0, 0}};
  s21_decimal want = {{0x80000000, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_13) {
  // -1 / 4 = 0.25
  s21_decimal value1 = {{1, 0, 0, MINUS}};
  s21_decimal value2 = {{4, 0, 0, 0}};
  s21_decimal want = {{25, 0, 0, 0x80020000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_14) {
  // 1 / 8 = 0.125
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{8, 0, 0, 0}};
  s21_decimal want = {{125, 0, 0, 0x00030000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_15) {
  // 0.6172835 / 5 = 0.1234567
  s21_decimal value1 = {{6172835, 0, 0, 0x00080000}};
  s21_decimal value2 = {{5, 0, 0, 0}};
  s21_decimal want = {{1234567, 0, 0, 0x00080000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_16) {
  // 1.23456789 / 10 = 0.123456789
  s21_decimal value1 = {{123456789, F8, F8, 0x00080000}};
  s21_decimal value2 = {{10, 0, 0, 0}};
  s21_decimal want = {{123456789, F8, F8, 0x00090000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_17) {
  // -1.666666667 / 5 = -0.3333333334
  s21_decimal value1 = {{1666666667, 0, 0, 0x80090000}};
  s21_decimal value2 = {{5, 0, 0, 0}};
  s21_decimal want = {{3333333334, 0, 0, 0x800A0000}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_div_18) {
  // 1 / 3 = 0.(3)
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{3, 0, 0, 0}};
  float got_float;
  float want_float = 1 / 3.;
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);
  s21_from_decimal_to_float(got, &got_float);

  ck_assert_int_eq(0, got_int);
  ck_assert_float_eq_tol(want_float, got_float, EPS);
}
END_TEST

START_TEST(test_s21_div_19) {
  // MAX / 2 = MAX/2
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{2, 0, 0, 0}};
  s21_decimal want = {{F8, F8, 0x7FFFFFFF, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_div_20) {
  // MIN / 4 = MIN/4
  s21_decimal value1 = {{F8, F8, F8, MINUS}};
  s21_decimal value2 = {{4, 0, 0, 0}};
  s21_decimal want = {{F8, F8, 0x3FFFFFFF, MINUS}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_div_21) {
  // 2 ^ 64 / 2 ^ 32 = 2 ^ 32
  s21_decimal value1 = {{0, 0, 1, MINUS}};
  s21_decimal value2 = {{0, 1, 0, MINUS}};
  s21_decimal want = {{0, 1, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_div(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST
Suite *test_s21_div(void) {
  Suite *s = suite_create("===== S21_DIV =====");
  TCase *tc = tcase_create("s21_div");

  tcase_add_test(tc, test_s21_div_0);
  tcase_add_test(tc, test_s21_div_1);
  tcase_add_test(tc, test_s21_div_2);
  tcase_add_test(tc, test_s21_div_3);
  tcase_add_test(tc, test_s21_div_4);
  tcase_add_test(tc, test_s21_div_5);
  tcase_add_test(tc, test_s21_div_6);
  tcase_add_test(tc, test_s21_div_7);
  tcase_add_test(tc, test_s21_div_8);
  tcase_add_test(tc, test_s21_div_9);
  tcase_add_test(tc, test_s21_div_10);
  tcase_add_test(tc, test_s21_div_11);
  tcase_add_test(tc, test_s21_div_12);
  tcase_add_test(tc, test_s21_div_13);
  tcase_add_test(tc, test_s21_div_14);
  tcase_add_test(tc, test_s21_div_15);
  tcase_add_test(tc, test_s21_div_16);
  tcase_add_test(tc, test_s21_div_17);
  tcase_add_test(tc, test_s21_div_18);
  tcase_add_test(tc, test_s21_div_19);
  tcase_add_test(tc, test_s21_div_20);
  tcase_add_test(tc, test_s21_div_21);
  suite_add_tcase(s, tc);

  return s;
}
