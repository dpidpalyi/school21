#include "test_s21_decimal.h"

START_TEST(test_s21_truncate_0) {
  // 0 => 0
  s21_decimal value = {};
  s21_decimal want = {};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_1) {
  // 1 => 1
  s21_decimal value = {{1, 0, 0, 0}};
  s21_decimal want = {{1, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  // -1 => -1
  s21_decimal value = {{1, 0, 0, MINUS}};
  s21_decimal want = {{1, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  // 0.1 => 0
  s21_decimal value = {{1, 0, 0, 0x00010000}};
  s21_decimal want = {{0, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_4) {
  // -0.1 => -0
  s21_decimal value = {{1, 0, 0, 0x80010000}};
  s21_decimal want = {{0, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_5) {
  // -0.9 => -0
  s21_decimal value = {{9, 0, 0, 0x80010000}};
  s21_decimal want = {{0, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_6) {
  // -4294967295.0 => -4294967295
  s21_decimal value = {{0xFFFFFFF6, 0x00000009, 0, 0x80010000}};
  s21_decimal want = {{0xFFFFFFFF, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_7) {
  // -4294967295.1 => -4294967295
  s21_decimal value = {{0xFFFFFFF7, 0x00000009, 0, 0x80010000}};
  s21_decimal want = {{0xFFFFFFFF, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_8) {
  // 4294967295.1 => 4294967295
  s21_decimal value = {{0xFFFFFFF7, 0x00000009, 0, 0x00010000}};
  s21_decimal want = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_truncate_9) {
  // 100 => 100
  s21_decimal value = {{0x000186A0, 0, 0, 0x00030000}};
  s21_decimal want = {{0x00000064, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

START_TEST(test_s21_truncate_10) {
  // 100.1 => 100
  s21_decimal value = {{0x000186A1, 0, 0, 0x00030000}};
  s21_decimal want = {{0x00000064, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

START_TEST(test_s21_truncate_11) {
  // -100.1 => -100
  s21_decimal value = {{0x000186A1, 0, 0, 0x80030000}};
  s21_decimal want = {{0x00000064, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

START_TEST(test_s21_truncate_12) {
  // 100.9 => 100
  s21_decimal value = {{0x000186A9, 0, 0, 0x00030000}};
  s21_decimal want = {{0x00000064, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

START_TEST(test_s21_truncate_13) {
  // -100.9 => -100
  s21_decimal value = {{0x000186A9, 0, 0, 0x80030000}};
  s21_decimal want = {{0x00000064, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

START_TEST(test_s21_truncate_14) {
  // MAX => MAX
  s21_decimal value = {{F8, F8, F8, 0}};
  s21_decimal want = {{F8, F8, F8, 0}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

START_TEST(test_s21_truncate_15) {
  // MIN => MIN
  s21_decimal value = {{F8, F8, F8, MINUS}};
  s21_decimal want = {{F8, F8, F8, MINUS}};
  s21_decimal got = {};
  int got_int = s21_truncate(value, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}

END_TEST
Suite *test_s21_truncate(void) {
  Suite *s = suite_create("===== S21_TRUNCATE =====");
  TCase *tc = tcase_create("s21_truncate");

  tcase_add_test(tc, test_s21_truncate_0);
  tcase_add_test(tc, test_s21_truncate_1);
  tcase_add_test(tc, test_s21_truncate_2);
  tcase_add_test(tc, test_s21_truncate_3);
  tcase_add_test(tc, test_s21_truncate_4);
  tcase_add_test(tc, test_s21_truncate_5);
  tcase_add_test(tc, test_s21_truncate_6);
  tcase_add_test(tc, test_s21_truncate_7);
  tcase_add_test(tc, test_s21_truncate_8);
  tcase_add_test(tc, test_s21_truncate_9);
  tcase_add_test(tc, test_s21_truncate_10);
  tcase_add_test(tc, test_s21_truncate_11);
  tcase_add_test(tc, test_s21_truncate_12);
  tcase_add_test(tc, test_s21_truncate_13);
  tcase_add_test(tc, test_s21_truncate_14);
  tcase_add_test(tc, test_s21_truncate_15);
  suite_add_tcase(s, tc);

  return s;
}
