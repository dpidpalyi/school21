#include "test_s21_decimal.h"

START_TEST(test_s21_from_int_to_decimal_0) {
  int n = 0;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(0, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(0, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_1) {
  int n = 1;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(1, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(0, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_2) {
  int n = -1;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(1, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(MINUS, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_3) {
  int n = 255;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(0x000000FF, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(0, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_4) {
  int n = -255;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(0x000000FF, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(MINUS, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_5) {
  int n = 0x00FFFFFF;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(0x00FFFFFF, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(0, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_6) {
  int n = 0x80FFFFFF;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(0x7F000001, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(MINUS, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_7) {
  int n = INT_MAX;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(INT_MAX, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(0, got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_8) {
  int n = INT_MIN + 1;
  s21_decimal got;

  s21_from_int_to_decimal(n, &got);
  ck_assert_int_eq(INT_MAX, got.bits[0]);
  ck_assert_int_eq(0, got.bits[1]);
  ck_assert_int_eq(0, got.bits[2]);
  ck_assert_int_eq(MINUS, got.bits[3]);
}
END_TEST

Suite *test_s21_from_int_to_decimal(void) {
  Suite *s = suite_create("===== S21_FROM_INT_TO_DECIMAL =====");
  TCase *tc = tcase_create("s21_from_int_to_decimal");

  tcase_add_test(tc, test_s21_from_int_to_decimal_0);
  tcase_add_test(tc, test_s21_from_int_to_decimal_1);
  tcase_add_test(tc, test_s21_from_int_to_decimal_2);
  tcase_add_test(tc, test_s21_from_int_to_decimal_3);
  tcase_add_test(tc, test_s21_from_int_to_decimal_4);
  tcase_add_test(tc, test_s21_from_int_to_decimal_5);
  tcase_add_test(tc, test_s21_from_int_to_decimal_6);
  tcase_add_test(tc, test_s21_from_int_to_decimal_7);
  tcase_add_test(tc, test_s21_from_int_to_decimal_8);
  suite_add_tcase(s, tc);

  return s;
}
