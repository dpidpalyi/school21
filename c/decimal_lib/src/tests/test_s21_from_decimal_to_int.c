#include "test_s21_decimal.h"

START_TEST(test_s21_from_decimal_to_int_0) {
  s21_decimal n = {{0, 0, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_1) {
  s21_decimal n = {{1, 0, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_2) {
  s21_decimal n = {{1, 0, 0, MINUS}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(-1, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_3) {
  s21_decimal n = {{256, 0, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(256, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_4) {
  s21_decimal n = {{256, 0, 0, MINUS}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(-256, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_5) {
  s21_decimal n = {{INT_MIN, 0, 0, MINUS}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(INT_MIN, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_6) {
  s21_decimal n = {{INT_MIN, 0, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(1, got);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_7) {
  s21_decimal n = {{0, 1, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(1, got);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_8) {
  s21_decimal n = {{1, 1, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(1, got);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_9) {
  s21_decimal n = {{1, 1, 0, MINUS}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(1, got);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_10) {
  s21_decimal n = {{0, 0, 1, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(1, got);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_11) {
  s21_decimal n = {{F8, 0, 0, 0x00010000}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(UINT_MAX / 10, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_12) {
  s21_decimal n = {{F8, 0, 0, 0}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(1, got);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_13) {
  s21_decimal n = {{0, 1, 0, 0x00010000}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(UINT_MAX / 10, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_14) {
  s21_decimal n = {{0x00000009, 0, 0, 0x00010000}};
  int got_int;

  int got = s21_from_decimal_to_int(n, &got_int);
  ck_assert_int_eq(0, got);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_15) {
  int want_int = INT_MIN;
  int got_int;
  s21_decimal got_dec = {};
  int got_dec_err = s21_from_int_to_decimal(want_int, &got_dec);
  ck_assert_int_eq(0, got_dec_err);
  int got_int_err = s21_from_decimal_to_int(got_dec, &got_int);
  ck_assert_int_eq(0, got_int_err);

  ck_assert_int_eq(want_int, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_16) {
  int want_int = INT_MAX;
  int got_int;
  s21_decimal got_dec = {};
  int got_dec_err = s21_from_int_to_decimal(want_int, &got_dec);
  ck_assert_int_eq(0, got_dec_err);
  int got_int_err = s21_from_decimal_to_int(got_dec, &got_int);
  ck_assert_int_eq(0, got_int_err);

  ck_assert_int_eq(want_int, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_17) {
  int want_int = 1234567890;
  int got_int;
  s21_decimal got_dec = {};
  int got_dec_err = s21_from_int_to_decimal(want_int, &got_dec);
  int got_int_err = s21_from_decimal_to_int(got_dec, &got_int);

  ck_assert_int_eq(0, got_dec_err);
  ck_assert_int_eq(0, got_int_err);
  ck_assert_int_eq(want_int, got_int);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_18) {
  int want_int = -1234567890;
  int got_int;
  s21_decimal got_dec = {};
  int got_dec_err = s21_from_int_to_decimal(want_int, &got_dec);
  int got_int_err = s21_from_decimal_to_int(got_dec, &got_int);

  ck_assert_int_eq(0, got_dec_err);
  ck_assert_int_eq(0, got_int_err);
  ck_assert_int_eq(want_int, got_int);
}
END_TEST

Suite *test_s21_from_decimal_to_int(void) {
  Suite *s = suite_create("===== S21_FROM_DECIMAL_TO_INT =====");
  TCase *tc = tcase_create("s21_from_decimal_to_int");

  tcase_add_test(tc, test_s21_from_decimal_to_int_0);
  tcase_add_test(tc, test_s21_from_decimal_to_int_1);
  tcase_add_test(tc, test_s21_from_decimal_to_int_2);
  tcase_add_test(tc, test_s21_from_decimal_to_int_3);
  tcase_add_test(tc, test_s21_from_decimal_to_int_4);
  tcase_add_test(tc, test_s21_from_decimal_to_int_5);
  tcase_add_test(tc, test_s21_from_decimal_to_int_6);
  tcase_add_test(tc, test_s21_from_decimal_to_int_7);
  tcase_add_test(tc, test_s21_from_decimal_to_int_8);
  tcase_add_test(tc, test_s21_from_decimal_to_int_9);
  tcase_add_test(tc, test_s21_from_decimal_to_int_10);
  tcase_add_test(tc, test_s21_from_decimal_to_int_11);
  tcase_add_test(tc, test_s21_from_decimal_to_int_12);
  tcase_add_test(tc, test_s21_from_decimal_to_int_13);
  tcase_add_test(tc, test_s21_from_decimal_to_int_14);
  tcase_add_test(tc, test_s21_from_decimal_to_int_15);
  tcase_add_test(tc, test_s21_from_decimal_to_int_16);
  tcase_add_test(tc, test_s21_from_decimal_to_int_17);
  tcase_add_test(tc, test_s21_from_decimal_to_int_18);
  suite_add_tcase(s, tc);

  return s;
}
