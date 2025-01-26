#include "test_s21_decimal.h"

static s21_decimal err_num1[] = {
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00010000}},  // 7922816251426433759354395033.5
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00020000}},  // 792281625142643375935439503.35
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80040000}},  // -7922816251426433759354395.0335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80080000}}  // -792281625142643375935.43950335
};

static s21_decimal err_num2[] = {
    {{0x00000006, 0x00000000, 0x00000000, 0x00010000}},  // 0.6
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0xFFF0BDBF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593542950335
    {{0xFFFE7906, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543850246
    {{0x00000007, 0x00000000, 0x00000000, 0x80010000}},  //-0.7
    {{0x0000000A, 0x00000000, 0x00000000, 0x80010000}},  //-1.0
    {{0xFF67697F, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593533950335
    {{0xFF642CF2, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}}  //-79228162514264337593533738226
};

static int err_result[] = {
    1, 1, 1, 1, 2, 2, 2, 2,
};

START_TEST(test_s21_add_01) {
  s21_decimal val1 = {{123, 456, 789, 0}};
  s21_decimal val2 = {{123, 456, 789, 0}};
  s21_decimal want = {{246, 912, 1578, 0}};
  ;
  s21_decimal got = {0};
  ck_assert_int_eq(s21_add(val1, val2, &got), 0);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(want.bits[i], got.bits[i]);
}
END_TEST

START_TEST(test_s21_add_02) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 123, 0}};
  s21_decimal want = {{0xFFFFFFFE, 0xFFFFFFFF, 0x0000007C, 0x00000000}};
  ;
  s21_decimal got = {0};
  ck_assert_int_eq(s21_add(val1, val2, &got), 0);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(want.bits[i], got.bits[i]);
}
END_TEST

START_TEST(test_s21_add_03) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal got = {0};
  ck_assert_int_eq(s21_add(val1, val2, &got), 2);
}
END_TEST

// 1844674407800451891.3 + 1844674407800451891.3 = 3689348815600903782.6
START_TEST(test_s21_add_04) {
  s21_decimal dec1 = {{1, 1, 1, 65536}};
  s21_decimal dec2 = {{1, 1, 1, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 2, 2, 65536}};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// 1844674407.8004518913 + 1844674407.8004518913 = 3689348815.6009037826
START_TEST(test_s21_add_05) {
  s21_decimal dec1 = {{1, 1, 1, 655360}};
  s21_decimal dec2 = {{1, 1, 1, 655360}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 2, 2, 655360}};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// -1844674407800451893.6 + 1844674413.8134061057 =
// -1844674405955777479.7865938943
START_TEST(test_s21_add_06) {
  s21_decimal dec1 = {{24, 1, 1, -2147418112}};
  s21_decimal dec2 = {{1, 15, 1, 655360}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1769803777, 999999990, 999999999, -2146828288}};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// 1844674407.8004518913 + -1844674407800451891.3 =
// -1844674405955777483.4995481087
START_TEST(test_s21_add_07) {
  s21_decimal dec1 = {{1, 1, 1, 655360}};
  s21_decimal dec2 = {{1, 1, 1, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{999999999, 999999999, 999999999, -2146828288}};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_08) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_09) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_10) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{5, 0, 0, 1 << 31}};
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_11) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 1 << 31}};
  s21_decimal expected = {{5, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_12) {
  s21_decimal dec1 = {{10, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_13) {
  s21_decimal dec1 = {{5, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_14) {
  s21_decimal dec1 = {{10, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{5, 0, 0, 1 << 31}};
  s21_decimal expected = {{15, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_15) {
  s21_decimal dec1 = {{5, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{10, 0, 0, 1 << 31}};
  s21_decimal expected = {{15, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_16) {
  s21_decimal dec1 = {{0b1, 0b1, 0, 0}};
  s21_decimal dec2 = {{0b100, 0, 0, 0}};
  s21_decimal expected = {{0b101, 0b1, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_17) {
  s21_decimal dec1 = {{0b100, 0b1, 0, 0}};
  s21_decimal dec2 = {{0b100, 0b1, 0, 1 << 31}};
  s21_decimal expected = {0};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_18) {
  s21_decimal dec1 = {{0b10010101000000101111100100000000, 0, 0, 0}};
  s21_decimal dec2 = {{0b10010101000000101111100100000000, 0, 0, 0}};
  s21_decimal expected = {{0b00101010000001011111001000000000, 0b1, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_19) {
  s21_decimal dec1 = {{0b100, 0b1, 0, 1 << 31}};
  s21_decimal dec2 = {{0b1000, 0, 0, 1 << 31}};
  s21_decimal expected = {{0b1100, 0b1, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_20) {
  s21_decimal dec1 = {{-1, -1, -1, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal expected = {0};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 1);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_21) {
  s21_decimal dec1 = {{-1, -1, -1, 0}};
  s21_decimal dec2 = {0};
  s21_decimal expected = dec1;
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_22) {
  s21_decimal dec1 = {{15, 0, 0, 6 << 16}};
  s21_decimal dec2 = {{15, 0, 0, 3 << 16}};
  s21_decimal expected = {{15015, 0, 0, 6 << 16}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_23) {
  s21_decimal dec1 = {{15, 0, 0, 3 << 16}};
  s21_decimal dec2 = {{15, 0, 0, 6 << 16}};
  s21_decimal expected = {{15015, 0, 0, 6 << 16}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// 12345678910111213 + 0.12345678910111213 =
START_TEST(test_s21_add_24) {
  s21_decimal dec1 = {{1576189421, 2874452, 0, 0}};
  s21_decimal dec2 = {{1576189421, 2874452, 0, 1114112}};
  s21_decimal expected = {{-1741100435, -1041303680, 669260594, 786432}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_25) {
  s21_decimal dec1 = {{119992852, 301347381, 277743149, 0}};
  s21_decimal dec2 = {{119992852, 301347381, 277743149, 0}};
  s21_decimal expected = {{239985704, 602694762, 555486298, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_26) {
  for (size_t i = 0; i < sizeof(err_num1) / sizeof(s21_decimal); ++i) {
    s21_decimal tmp;
    int ret = s21_add(err_num1[i], err_num2[i], &tmp);
    if (tmp.bits[0] == 0) {
      tmp.bits[0] = 1;
    }
    ck_assert_int_eq(ret, err_result[i]);
  }
}
END_TEST
START_TEST(test_s21_add_27) {
  s21_decimal dec1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal result = {0};
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_28) {
  s21_decimal dec1 = {{0x00000000, 0x00000000, 0x00000000, 0x80010000}};  // 0.0
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal result = {0};
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x00010000}};  // 0.0
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_29) {
  s21_decimal dec1 = {
      {0x00000001, 0x00000000, 0x00000000, 0x800E0000}};  // -0.00000000000001
  s21_decimal dec2 = {
      {0x00000006, 0x00000000, 0x00000000, 0x000F0000}};  // 0.000000000000006
  s21_decimal expected = {
      {0x00000004, 0x00000000, 0x00000000, 0x800F0000}};  //-0.000000000000004
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_30) {
  s21_decimal dec1 = {{0x00000019, 0x00000000, 0x00000000, 0x00010000}};  // 2.5
  s21_decimal dec2 = {{0x00000064, 0x00000000, 0x00000000, 0x00000000}};  // 100
  s21_decimal expected = {
      {0x00000401, 0x00000000, 0x00000000, 0x00010000}};  // 102.5
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_31) {
  s21_decimal dec1 = {
      {0x00000183, 0x00000000, 0x00000000, 0x00020000}};  // 3.87
  s21_decimal dec2 = {
      {0x00004DA6, 0x00000000, 0x00000000, 0x00020000}};  // 198.78
  s21_decimal expected = {
      {0x00004F29, 0x00000000, 0x00000000, 0x00020000}};  // 202.65
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_32) {
  s21_decimal dec1 = {
      {0x14490831, 0x00048E23, 0x00000000, 0x00070000}};  // 128218122.2172721
  s21_decimal dec2 = {
      {0x164214B7, 0x00000028, 0x00000000, 0x00040000}};  // 17217212.1271
  s21_decimal expected = {
      {0x0669F309, 0x00052ABA, 0x00000000, 0x00070000}};  // 145435334.3443721
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_33) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};  // 1
  s21_decimal dec2 = {{0x00000019, 0x00000000, 0x00000000, 0x00010000}};  // 2.5
  s21_decimal expected = {
      {0x00000023, 0x00000000, 0x00000000, 0x00010000}};  // 3.5
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_34) {
  s21_decimal dec1 = {
      {0x77D5E3AA, 0x0000011C, 0x00000000, 0x00060000}};  // 1221781.218218
  s21_decimal dec2 = {
      {0x00212155, 0x00000000, 0x00000000, 0x00070000}};  // 0.2171221
  s21_decimal expected = {
      {0xAE7C05F9, 0x00000B1C, 0x00000000, 0x00070000}};  // 1221781.4353401
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_35) {
  s21_decimal dec1 = {{0x80000000, 0x80000000, 0x80000000,
                       0x801C0000}};  // -3.9614081266355540835774234624
  s21_decimal dec2 = {{0x80000000, 0x80000000, 0x80000000,
                       0x801C0000}};  //-3.9614081266355540835774234624
  s21_decimal expected = {{0x4CCCCCCD, 0xB3333333, 0x19999999,
                           0x801B0000}};  //-7.922816253271108167154846925
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_36) {
  s21_decimal dec1 = {{0x80000000, 0x80000000, 0x80000000,
                       0x000E0000}};  // 396140812663555.40835774234624
  s21_decimal dec2 = {{0x80000000, 0x80000000, 0x80000000,
                       0x000E0000}};  // 396140812663555.40835774234624
  s21_decimal expected = {{0x4CCCCCCD, 0xB3333333, 0x19999999,
                           0x000D0000}};  // 792281625327110.8167154846925
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_37) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal dec2 = {{0x00000001, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal expected = {{0x00000002, 0x00000000, 0x00000000,
                           0x001C0000}};  // 0.0000000000000000000000000002
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_38) {
  s21_decimal dec1 = {{0x000F4240, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000001000000
  s21_decimal dec2 = {{0x000186A0, 0x00000000, 0x00000000,
                       0x00140000}};  // 0.00000000000000100000
  s21_decimal expected = {{0x4E81E240, 0x00000918, 0x00000000,
                           0x001C0000}};  // 0.0000000000000010000001000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_39) {
  s21_decimal dec1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x000E0000}};  // 0.00000000000000
  s21_decimal dec2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x000A0000}};  // 0.0000000000
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x000E0000}};  // 0.00000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_40) {
  s21_decimal dec1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x000E0000}};  // 0.00000000000000
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000000
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000,
                           0x001C0000}};  // 0.0000000000000000000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_41) {
  s21_decimal dec1 = {{0x80000000, 0x80000000, 0x80000000,
                       0x00000000}};  // 39614081266355540835774234624
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000000
  s21_decimal expected = {{0x80000000, 0x80000000, 0x80000000,
                           0x00000000}};  // 39614081266355540835774234624
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_42) {
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00010000}};  // 7922816251426433759354395033.5
  s21_decimal dec2 = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};  // 0.5
  s21_decimal expected = {{0x9999999A, 0x99999999, 0x19999999,
                           0x00000000}};  // 7922816251426433759354395034
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_43) {
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950335
  s21_decimal dec2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x000A0000}};  // 0.0000000000
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_44) {
  s21_decimal dec1 = {
      {0x1422CF6C, 0x000001FC, 0x00000000, 0x80030000}};  // -2182181212.012
  s21_decimal dec2 = {
      {0xF96C01C5, 0x0007B6B6, 0x00000000, 0x800B0000}};  //-21712.21821882821
  s21_decimal expected = {{0x3015EDC5, 0xD46A37C7, 0x0000000B,
                           0x800B0000}};  //-2182202924.23021882821
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_45) {
  s21_decimal dec1 = {{0x2564B1EA, 0x3927F1F3, 0x041C50D7,
                       0x000B0000}};  // 12721717217217217.21821901290
  s21_decimal dec2 = {
      {0x00033F4A, 0x00000000, 0x00000000, 0x000C0000}};  // 0.000000212810
  s21_decimal expected = {{0x75F2326E, 0x3B8F737F, 0x291B2868,
                           0x000C0000}};  // 12721717217217217.218219225710
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_46) {
  s21_decimal dec1 = {
      {0x0001869F, 0x00000000, 0x00000000, 0x00050000}};  // 0.99999
  s21_decimal dec2 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00050000}};  // 0.00001
  s21_decimal expected = {
      {0x000186A0, 0x00000000, 0x00000000, 0x00050000}};  // 1.00000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_47) {
  s21_decimal dec1 = {
      {0x0098967E, 0x00000000, 0x00000000, 0x80060000}};  // -9.999998
  s21_decimal dec2 = {
      {0x00000002, 0x00000000, 0x00000000, 0x80060000}};  //-0.000002
  s21_decimal expected = {
      {0x00989680, 0x00000000, 0x00000000, 0x80060000}};  //-10.000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_48) {
  s21_decimal dec1 = {
      {0x000000CF, 0x00000000, 0x00000000, 0x00010000}};  // 20.7
  s21_decimal dec2 = {{0x00003F86, 0x00000000, 0x00000000,
                       0x00160000}};  // 0.0000000000000000016262
  s21_decimal expected = {{0x03603F86, 0x7E1382FF, 0x00002BD5,
                           0x00160000}};  // 20.7000000000000000016262
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_49) {
  s21_decimal dec1 = {
      {0x0707E3C5, 0x002D8D61, 0x00000000, 0x80090000}};  // -12821821.821281221
  s21_decimal dec2 = {
      {0x058FEC8A, 0x00000000, 0x00000000, 0x00050000}};  // 933.18282
  s21_decimal expected = {
      {0xC1001525, 0x002D8C87, 0x00000000, 0x80090000}};  //-12820888.638461221
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_50) {
  s21_decimal dec1 = {
      {0x846A4B4C, 0x0000012A, 0x00000000, 0x00080000}};  // 12821.21812812
  s21_decimal dec2 = {
      {0x0081787B, 0x00000000, 0x00000000, 0x80080000}};  //-0.08484987
  s21_decimal expected = {
      {0x83E8D2D1, 0x0000012A, 0x00000000, 0x00080000}};  // 12821.13327825
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_51) {
  s21_decimal dec1 = {{0x000035A3, 0x00000000, 0x00000000,
                       0x00170000}};  // 0.00000000000000000013731
  s21_decimal dec2 = {
      {0x0001F8A8, 0x00000000, 0x00000000, 0x00030000}};  // 129.192
  s21_decimal expected = {{0x828035A3, 0x3C3F28D0, 0x000AAFBF,
                           0x00170000}};  // 129.19200000000000000013731
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_52) {
  s21_decimal dec1 = {
      {0x79353447, 0x00000004, 0x00000000, 0x00010000}};  // 1921339911.1
  s21_decimal dec2 = {{0xD927FFFF, 0xE1003B28, 0x00000004,
                       0x00140000}};  // 0.89999999999999999999
  s21_decimal expected = {{0x9F400000, 0x563581D8, 0x3E14F385,
                           0x00130000}};  // 1921339912.0000000000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_53) {
  s21_decimal dec1 = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950333 12323
  s21_decimal dec2 = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};  // 0.5
  s21_decimal expected = {
      {0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
       0x00000000}};  // 79228162514264337593543950334 121212
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_54) {
  s21_decimal dec1 = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950333
  s21_decimal dec2 = {
      {0x00000033, 0x00000000, 0x00000000, 0x00020000}};  // 0.51
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_55) {
  s21_decimal dec1 = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950333
  s21_decimal dec2 = {
      {0x00000031, 0x00000000, 0x00000000, 0x00020000}};  // 0.49
  s21_decimal expected = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950333
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_56) {
  s21_decimal dec1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950334
  s21_decimal dec2 = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};  // 0.5
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_57) {
  s21_decimal dec1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950334
  s21_decimal dec2 = {
      {0x00000033, 0x00000000, 0x00000000, 0x00020000}};  // 0.51
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_add_58) {
  s21_decimal dec1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950334
  s21_decimal dec2 = {
      {0x00000031, 0x00000000, 0x00000000, 0x00020000}};  // 0.49
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_add(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

Suite *test_s21_add(void) {
  Suite *s = suite_create("===== S21_ADD =====");
  TCase *tc = tcase_create("s21_add");

  tcase_add_test(tc, test_s21_add_01);
  tcase_add_test(tc, test_s21_add_02);
  tcase_add_test(tc, test_s21_add_03);
  tcase_add_test(tc, test_s21_add_04);
  tcase_add_test(tc, test_s21_add_05);
  tcase_add_test(tc, test_s21_add_06);
  tcase_add_test(tc, test_s21_add_07);
  tcase_add_test(tc, test_s21_add_08);
  tcase_add_test(tc, test_s21_add_09);
  tcase_add_test(tc, test_s21_add_10);
  tcase_add_test(tc, test_s21_add_11);
  tcase_add_test(tc, test_s21_add_12);
  tcase_add_test(tc, test_s21_add_13);
  tcase_add_test(tc, test_s21_add_14);
  tcase_add_test(tc, test_s21_add_15);
  tcase_add_test(tc, test_s21_add_16);
  tcase_add_test(tc, test_s21_add_17);
  tcase_add_test(tc, test_s21_add_18);
  tcase_add_test(tc, test_s21_add_19);
  tcase_add_test(tc, test_s21_add_20);
  tcase_add_test(tc, test_s21_add_21);
  tcase_add_test(tc, test_s21_add_22);
  tcase_add_test(tc, test_s21_add_23);
  tcase_add_test(tc, test_s21_add_24);
  tcase_add_test(tc, test_s21_add_25);
  tcase_add_test(tc, test_s21_add_26);
  tcase_add_test(tc, test_s21_add_27);
  tcase_add_test(tc, test_s21_add_28);
  tcase_add_test(tc, test_s21_add_29);
  tcase_add_test(tc, test_s21_add_30);
  tcase_add_test(tc, test_s21_add_31);
  tcase_add_test(tc, test_s21_add_32);
  tcase_add_test(tc, test_s21_add_33);
  tcase_add_test(tc, test_s21_add_34);
  tcase_add_test(tc, test_s21_add_35);
  tcase_add_test(tc, test_s21_add_36);
  tcase_add_test(tc, test_s21_add_37);
  tcase_add_test(tc, test_s21_add_38);
  tcase_add_test(tc, test_s21_add_39);
  tcase_add_test(tc, test_s21_add_40);
  tcase_add_test(tc, test_s21_add_41);
  tcase_add_test(tc, test_s21_add_42);
  tcase_add_test(tc, test_s21_add_43);
  tcase_add_test(tc, test_s21_add_44);
  tcase_add_test(tc, test_s21_add_45);
  tcase_add_test(tc, test_s21_add_46);
  tcase_add_test(tc, test_s21_add_47);
  tcase_add_test(tc, test_s21_add_48);
  tcase_add_test(tc, test_s21_add_49);
  tcase_add_test(tc, test_s21_add_50);
  tcase_add_test(tc, test_s21_add_51);
  tcase_add_test(tc, test_s21_add_52);
  tcase_add_test(tc, test_s21_add_53);
  tcase_add_test(tc, test_s21_add_54);
  tcase_add_test(tc, test_s21_add_55);
  tcase_add_test(tc, test_s21_add_56);
  tcase_add_test(tc, test_s21_add_57);
  tcase_add_test(tc, test_s21_add_58);
  suite_add_tcase(s, tc);

  return s;
}
