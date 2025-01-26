#include "test_s21_decimal.h"

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {  // первое число отрицательное
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(
    s21_is_less_or_equal_4) {  // отрицательные числа (отличаются 2 разряды)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000000000000011;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000000011;
  src2.bits[2] = 0b00000000000000000000000000010101;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000010101111111;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000011111;
  src2.bits[2] = 0b00000000000000000000000000000001;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {  // положительные числа (оличаются 0
                                      // разряды)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000010111;
  src1.bits[2] = 0b00000000000000000000000000010101;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000010111;
  src2.bits[2] = 0b00000000000000000000000000010101;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000000000011111;
  src1.bits[2] = 0b00000000000000000000000111100001;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000000000011111;
  src2.bits[2] = 0b00000000000000000000000000000001;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {  // положительные числа (равны)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000010111;
  src1.bits[2] = 0b00000000000000000000000000010101;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000010111;
  src2.bits[2] = 0b00000000000000000000000000010101;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000011111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000011111111111;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}

START_TEST(s21_is_less_or_equal_10) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b10000000000000000000000000001110;
  src1.bits[1] = 0b00000000000000000000011111010101;
  src1.bits[2] = 0b00000000000000000000011111010101;
  src1.bits[3] = 0b10000000000000110000000000000000;
  src2.bits[0] = 0b10000000000000000000000000001110;
  src2.bits[1] = 0b00000000000000000000011111010101;
  src2.bits[2] = 0b00000000000000000000011111010101;
  src2.bits[3] = 0b10000000000000110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}

START_TEST(
    s21_is_less_or_equal_11) {  // отрицательные числа (отличаются 3 разряды)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000010111;
  src1.bits[1] = 0b00000000000000000000000000000011;
  src1.bits[2] = 0b00000000000000000000000000001111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000010111;
  src2.bits[1] = 0b00000000000000000000000000000011;
  src2.bits[2] = 0b00000000000000000000000000001111;
  src2.bits[3] = 0b10000000000000110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(
    s21_is_less_or_equal_12) {  // отрицательные числа (отличаются 1 разряды)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000011;
  src1.bits[2] = 0b00000000000000000000000000010101;
  src1.bits[3] = 0b10000000000000000000000000000001;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000001111111;
  src2.bits[2] = 0b00000000000000000000000000010101;
  src2.bits[3] = 0b10000000000000000000000000000001;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(
    s21_is_less_or_equal_13) {  // отрицательные числа (отличаются 3 разряды)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000101110;
  src1.bits[1] = 0b00000000000000000000000000000011;
  src1.bits[2] = 0b00000000000000000000000001111111;
  src1.bits[3] = 0b10000000000000110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000101110;
  src2.bits[1] = 0b00000000000000000000000000000011;
  src2.bits[2] = 0b00000000000000000000000001111111;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_14) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000001010111100;  // **700 / 10^2**
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000111;  // **7 / 10^0**
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_15) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000001010111100;  // **700 / 10^2**
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000111;  // **7 / 10^0**
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_16) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000001111101000;  // **-1000 / 10^1**
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00000000000000000000000001100100;  // **-100 / 10^0**
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_17) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000000000;  //**00000..**
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;  //**-00000..**
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_18) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000000000;  //**-00000..**
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;  //**00000..**
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_19) {  // отрицательные отличаются 3
  ////разряды, большая степень)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000111000000000000000000;  // exp = 28
  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b00000000000000110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_20) {  // отрицательные числа (отличаются 3
  ////разряды, большая степень)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b00000000000000000000000000101110;
  src1.bits[1] = 0b00000000000000000000000000001100;
  src1.bits[2] = 0b00000000000000000000000001111111;
  src1.bits[3] = 0b10000000000111000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000101110;
  src2.bits[1] = 0b00000000000000000000000000001100;
  src2.bits[2] = 0b00000000000000000000000001111111;
  src2.bits[3] = 0b10000000000000110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_21) {  // отрицательные отличаются 3
  ////разряды, большая степень)
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000011111111111111111111111111;
  src1.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b00000011111111111111111111111111;
  src2.bits[3] = 0b00000000000111000000000000000000;  // exp = 28
  int result = s21_is_less_or_equal(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_is_less_or_equal_22) {
  s21_decimal src1, src2;
  int origin;
  src1.bits[0] = 0b01111111111111111111111111111111;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000001111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b01111111111111111111111111111111;
  src2.bits[1] = 0b00000000000000000000000000000010;
  src2.bits[2] = 0b00000000000000000000000001111111;
  src2.bits[3] = 0b10000000000000110000000000000000;
  int result = s21_is_less_or_equal(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

Suite *test_s21_is_less_or_equal(void) {
  Suite *s = suite_create("===== S21_IS_LESS_OR_EQUAL =====");
  TCase *tc = tcase_create("s21_is_less_or_equal_tc");

  tcase_add_test(tc, s21_is_less_or_equal_1);
  tcase_add_test(tc, s21_is_less_or_equal_2);
  tcase_add_test(tc, s21_is_less_or_equal_3);
  tcase_add_test(tc, s21_is_less_or_equal_4);
  tcase_add_test(tc, s21_is_less_or_equal_5);
  tcase_add_test(tc, s21_is_less_or_equal_6);
  tcase_add_test(tc, s21_is_less_or_equal_7);
  tcase_add_test(tc, s21_is_less_or_equal_8);
  tcase_add_test(tc, s21_is_less_or_equal_9);
  tcase_add_test(tc, s21_is_less_or_equal_10);
  tcase_add_test(tc, s21_is_less_or_equal_11);
  tcase_add_test(tc, s21_is_less_or_equal_12);
  tcase_add_test(tc, s21_is_less_or_equal_13);
  tcase_add_test(tc, s21_is_less_or_equal_14);
  tcase_add_test(tc, s21_is_less_or_equal_15);
  tcase_add_test(tc, s21_is_less_or_equal_16);
  tcase_add_test(tc, s21_is_less_or_equal_17);
  tcase_add_test(tc, s21_is_less_or_equal_18);
  tcase_add_test(tc, s21_is_less_or_equal_19);
  tcase_add_test(tc, s21_is_less_or_equal_20);
  tcase_add_test(tc, s21_is_less_or_equal_21);
  tcase_add_test(tc, s21_is_less_or_equal_22);
  suite_add_tcase(s, tc);

  return s;
}
