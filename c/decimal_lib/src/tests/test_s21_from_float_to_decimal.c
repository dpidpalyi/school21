#include "test_s21_decimal.h"

START_TEST(test_s21_from_float_to_decimal_0) {
  s21_decimal got = {};
  s21_decimal want = {{0, 0, 0, 0}};
  float n = 0.;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_1) {
  s21_decimal got = {};
  s21_decimal want = {{1, 0, 0, 0}};
  float n = 1.;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_2) {
  s21_decimal got = {};
  s21_decimal want = {{1, 0, 0, MINUS}};
  float n = -1.;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_3) {
  s21_decimal got = {};
  float n = pow(2, 96);

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_4) {
  s21_decimal got = {};
  float n = -pow(2, 96);

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_5) {
  s21_decimal got = {};
  s21_decimal want = {{0, 0, 0, 0}};
  float n = 1e-29;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_6) {
  s21_decimal got = {};
  s21_decimal want = {{0, 0, 0, 0}};
  float n = -1e-29;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_7) {
  s21_decimal got = {};
  s21_decimal want = {{1, 0, 0, 0x001C0000}};
  float n = 1e-28;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_8) {
  s21_decimal got = {};
  s21_decimal want = {{1, 0, 0, 0x801C0000}};
  float n = -1e-28;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_9) {
  s21_decimal got = {};
  s21_decimal want = {{0x31600000, 0x085B549B, 0x204FCE28, 0}};
  float n = 9.99999944e+27;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_10) {
  s21_decimal got = {};
  s21_decimal want = {{0x31600000, 0x085B549B, 0x204FCE28, MINUS}};
  float n = -9.99999944e+27;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_11) {
  s21_decimal got = {};
  s21_decimal want = {{2, 0, 0, 0x001C0000}};
  float n = 1.69293838e-28;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_12) {
  s21_decimal got = {};
  s21_decimal want = {{1, 0, 0, 0x801C0000}};
  float n = -1.444444e-28;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_13) {
  s21_decimal got = {};
  float n = INFINITY;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_14) {
  s21_decimal got = {};
  float n = -INFINITY;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_15) {
  s21_decimal got = {};
  float n = NAN;

  int got_int = s21_from_float_to_decimal(n, &got);
  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_16) {
  float want_float = 5.458129;
  float got_float;
  s21_decimal got_dec = {};
  float got_dec_err = s21_from_float_to_decimal(want_float, &got_dec);
  float got_float_err = s21_from_decimal_to_float(got_dec, &got_float);

  ck_assert_float_eq(0, got_dec_err);
  ck_assert_float_eq(0, got_float_err);
  ck_assert_float_eq(want_float, got_float);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_17) {
  float want_float = -4.899999;
  float got_float;
  s21_decimal got_dec = {};
  float got_dec_err = s21_from_float_to_decimal(want_float, &got_dec);
  float got_float_err = s21_from_decimal_to_float(got_dec, &got_float);

  ck_assert_float_eq(0, got_dec_err);
  ck_assert_float_eq(0, got_float_err);
  ck_assert_float_eq(want_float, got_float);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_18) {
  float want_float = 0.000215;
  float got_float;
  s21_decimal got_dec = {};
  float got_dec_err = s21_from_float_to_decimal(want_float, &got_dec);
  float got_float_err = s21_from_decimal_to_float(got_dec, &got_float);

  ck_assert_float_eq(0, got_dec_err);
  ck_assert_float_eq(0, got_float_err);
  ck_assert_float_eq(want_float, got_float);
}
END_TEST

Suite *test_s21_from_float_to_decimal(void) {
  Suite *s = suite_create("===== S21_FROM_FLOAT_TO_DECIMAL =====");
  TCase *tc = tcase_create("s21_from_float_to_decimal");

  tcase_add_test(tc, test_s21_from_float_to_decimal_0);
  tcase_add_test(tc, test_s21_from_float_to_decimal_1);
  tcase_add_test(tc, test_s21_from_float_to_decimal_2);
  tcase_add_test(tc, test_s21_from_float_to_decimal_3);
  tcase_add_test(tc, test_s21_from_float_to_decimal_4);
  tcase_add_test(tc, test_s21_from_float_to_decimal_5);
  tcase_add_test(tc, test_s21_from_float_to_decimal_6);
  tcase_add_test(tc, test_s21_from_float_to_decimal_7);
  tcase_add_test(tc, test_s21_from_float_to_decimal_8);
  tcase_add_test(tc, test_s21_from_float_to_decimal_9);
  tcase_add_test(tc, test_s21_from_float_to_decimal_10);
  tcase_add_test(tc, test_s21_from_float_to_decimal_11);
  tcase_add_test(tc, test_s21_from_float_to_decimal_12);
  tcase_add_test(tc, test_s21_from_float_to_decimal_13);
  tcase_add_test(tc, test_s21_from_float_to_decimal_14);
  tcase_add_test(tc, test_s21_from_float_to_decimal_15);
  tcase_add_test(tc, test_s21_from_float_to_decimal_16);
  tcase_add_test(tc, test_s21_from_float_to_decimal_17);
  tcase_add_test(tc, test_s21_from_float_to_decimal_18);
  suite_add_tcase(s, tc);

  return s;
}
