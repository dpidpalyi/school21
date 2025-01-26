#include "test_s21_decimal.h"

START_TEST(test_s21_mul_0) {
  // 0 * 0 = 0
  s21_decimal value1 = {};
  s21_decimal value2 = {};
  s21_decimal want = {};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_1) {
  // 0 * 1 = 0
  s21_decimal value1 = {};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_2) {
  // (-1) * 0 = 0
  s21_decimal value1 = {{1, 0, 0, MINUS}};
  s21_decimal value2 = {};
  s21_decimal want = {};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_3) {
  // 1 * 1 = 1
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {{1, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_4) {
  // (-1) * 2 = -2
  s21_decimal value1 = {{1, 0, 0, MINUS}};
  s21_decimal value2 = {{2, 0, 0, 0}};
  s21_decimal want = {{2, 0, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_5) {
  // (-2) * (-2) = 4
  s21_decimal value1 = {{2, 0, 0, MINUS}};
  s21_decimal value2 = {{2, 0, 0, MINUS}};
  s21_decimal want = {{4, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_6) {
  // MAX * 1 = MAX
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal want = {{F8, F8, F8, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_7) {
  // 1 * MIN = MIN
  s21_decimal value1 = {{1, 0, 0, 0}};
  s21_decimal value2 = {{F8, F8, F8, MINUS}};
  s21_decimal want = {{F8, F8, F8, MINUS}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_8) {
  // (-2) * MAX = -INF
  s21_decimal value1 = {{2, 0, 0, MINUS}};
  s21_decimal value2 = {{F8, F8, F8, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(2, got_int);
}
END_TEST

START_TEST(test_s21_mul_9) {
  // MAX * 3 = INF
  s21_decimal value2 = {{F8, F8, F8, 0}};
  s21_decimal value1 = {{3, 0, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_mul_10) {
  // 10^7 * 10^7 = 10^14
  s21_decimal value1 = {{0x00989680, 0, 0, 0}};
  s21_decimal value2 = {{0x00989680, 0, 0, 0}};
  s21_decimal want = {{0x107A4000, 0x00005AF3, 0, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_11) {
  // 10^7 * (-10^7) = 10^14
  s21_decimal value1 = {{0x00989680, 0, 0, 0}};
  s21_decimal value2 = {{0x00989680, 0, 0, MINUS}};
  s21_decimal want = {{0x107A4000, 0x00005AF3, 0, MINUS}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_12) {
  // 7.922816 * 10^28 * (10^-28) = 7.922816 * 10^-28
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{1, 0, 0, 0x001C0000}};
  s21_decimal want = {{F8, F8, F8, 0x001C0000}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_13) {
  // 10^10 * 10^10 = 10^20
  s21_decimal value1 = {{0x540BE400, 0x00000002, 0, 0}};
  s21_decimal value2 = {{0x540BE400, 0x00000002, 0, 0}};
  s21_decimal want = {{0x63100000, 0x6BC75E2D, 0x00000005, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_14) {
  // 10^10 * 10^20 = 10^30(ERR)
  s21_decimal value1 = {{0x540BE400, 0x00000002, 0, 0}};
  s21_decimal value2 = {{0x63100000, 0x6BC75E2D, 0x00000005, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(1, got_int);
}
END_TEST

START_TEST(test_s21_mul_15) {
  // 10^20/10^10 * 10^20/10^10 = 10^20
  s21_decimal value1 = {{0x63100000, 0x6BC75E2D, 0x00000005, 0x000A0000}};
  s21_decimal value2 = {{0x63100000, 0x6BC75E2D, 0x00000005, 0x000A0000}};
  s21_decimal want = {{0x63100000, 0x6BC75E2D, 0x00000005, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_mul_16) {
  // MAX * 0.5 = MAX >> 1
  s21_decimal value1 = {{F8, F8, F8, 0}};
  s21_decimal value2 = {{0x00000005, 0, 0, 0x00010000}};
  s21_decimal want = {{0, 0, 0x80000000, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_17) {
  // -11 * 0.5 = -5.5
  s21_decimal value1 = {{11, 0, 0, MINUS}};
  s21_decimal value2 = {{0x00000005, 0, 0, 0x00010000}};
  s21_decimal want = {{55, 0, 0, 0x80010000}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_18) {
  // 2 * 10^-28 * 0.5 = 1 * 10^-28
  s21_decimal value1 = {{2, 0, 0, 0x001C0000}};
  s21_decimal value2 = {{0x00000005, 0, 0, 0x00010000}};
  s21_decimal want = {{1, 0, 0, 0x001C0000}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_19) {
  // 2 * 10^-14 * 2 * 10^-14 = -4 * 10^-28
  s21_decimal value1 = {{2, 0, 0, 0x000E0000}};
  s21_decimal value2 = {{2, 0, 0, 0x000E0000}};
  s21_decimal want = {{4, 0, 0, 0x001C0000}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_20) {
  // 2 ^ 32 * 2 ^ 32 = 2 ^ 64
  s21_decimal value1 = {{0, 1, 0, 0}};
  s21_decimal value2 = {{0, 1, 0, 0}};
  s21_decimal want = {{0, 0, 1, 0}};
  s21_decimal got = {};
  int got_int = s21_mul(value1, value2, &got);

  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(want.bits[0], got.bits[0]);
  ck_assert_int_eq(want.bits[1], got.bits[1]);
  ck_assert_int_eq(want.bits[2], got.bits[2]);
  ck_assert_int_eq(want.bits[3], got.bits[3]);
}
END_TEST

START_TEST(test_s21_mul_21) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 6521;
  // src2 = 74121;
  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00011100110011110011101011000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(test_s21_mul_22) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 4;
  // src2 = 97623323;
  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00010111010001100111010001101100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(test_s21_mul_23) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 65658654;
  // src2 = 5;
  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b00010011100100010101101110010110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(test_s21_mul_24) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = -9878798789;
  // src2 = -3;
  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11100110011101111000010101001111;
  origin.bits[1] = 0b00000000000000000000000000000110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(test_s21_mul_25) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;
  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b01011111001100010111011110111010;
  origin.bits[1] = 0b01000100111111001101101110110001;
  origin.bits[2] = 0b00000001101011100011011100011110;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

START_TEST(test_s21_mul_26) {
  s21_decimal src1, src2, origin, result;
  int value_type_result, value_type_origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  value_type_result = s21_mul(src1, src2, &result);
  value_type_origin = 0;
  origin.bits[0] = 0b11000100010110100111001000111001;
  origin.bits[1] = 0b01100100100011011110110011010011;
  origin.bits[2] = 0b00000000000001001101011111010011;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(value_type_result, value_type_origin);
}
END_TEST

Suite *test_s21_mul(void) {
  Suite *s = suite_create("===== S21_MUL =====");
  TCase *tc = tcase_create("s21_mul");

  tcase_add_test(tc, test_s21_mul_0);
  tcase_add_test(tc, test_s21_mul_1);
  tcase_add_test(tc, test_s21_mul_2);
  tcase_add_test(tc, test_s21_mul_3);
  tcase_add_test(tc, test_s21_mul_4);
  tcase_add_test(tc, test_s21_mul_5);
  tcase_add_test(tc, test_s21_mul_6);
  tcase_add_test(tc, test_s21_mul_7);
  tcase_add_test(tc, test_s21_mul_8);
  tcase_add_test(tc, test_s21_mul_9);
  tcase_add_test(tc, test_s21_mul_10);
  tcase_add_test(tc, test_s21_mul_11);
  tcase_add_test(tc, test_s21_mul_12);
  tcase_add_test(tc, test_s21_mul_13);
  tcase_add_test(tc, test_s21_mul_14);
  tcase_add_test(tc, test_s21_mul_15);
  tcase_add_test(tc, test_s21_mul_16);
  tcase_add_test(tc, test_s21_mul_17);
  tcase_add_test(tc, test_s21_mul_18);
  tcase_add_test(tc, test_s21_mul_19);
  tcase_add_test(tc, test_s21_mul_20);
  tcase_add_test(tc, test_s21_mul_21);
  tcase_add_test(tc, test_s21_mul_22);
  tcase_add_test(tc, test_s21_mul_23);
  tcase_add_test(tc, test_s21_mul_24);
  tcase_add_test(tc, test_s21_mul_25);
  tcase_add_test(tc, test_s21_mul_26);
  suite_add_tcase(s, tc);

  return s;
}
