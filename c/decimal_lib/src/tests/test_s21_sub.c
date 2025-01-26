#include "test_s21_decimal.h"

START_TEST(test_s21_sub_01) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_02) {
  s21_decimal dec1 = {{10, 0, 0, 0}};
  s21_decimal dec2 = {{5, 0, 0, 1 << 31}};
  s21_decimal expected = {{15, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_03) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{10, 0, 0, 1 << 31}};
  s21_decimal expected = {{15, 0, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_04) {
  s21_decimal dec1 = {{10, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{5, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_05) {
  s21_decimal dec1 = {{5, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{10, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_06) {
  s21_decimal dec1 = {{10, 0, 0, 1 << 31}};
  s21_decimal dec2 = {{5, 0, 0, 1 << 31}};
  s21_decimal expected = {{5, 0, 0, 1 << 31}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_07) {
  s21_decimal dec1 = {{0, 0b100, 0, 0}};
  s21_decimal dec2 = {{0b10, 0, 0, 0}};
  s21_decimal expected = {{0b11111111111111111111111111111110, 0b11, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_08) {
  s21_decimal dec1 = {{0b10, 0b100, 0, 0}};
  s21_decimal dec2 = {{0b10, 0, 0, 0}};
  s21_decimal expected = {{0, 0b100, 0, 0}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_09) {
  s21_decimal dec1 = {{15, 0, 0, 6 << 16}};
  s21_decimal dec2 = {{15, 0, 0, (1 << 31) + (3 << 16)}};
  s21_decimal expected = {{15015, 0, 0, 6 << 16}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_10) {
  s21_decimal dec1 = {{15, 0, 0, 3 << 16}};
  s21_decimal dec2 = {{15, 0, 0, (1 << 31) + (6 << 16)}};
  s21_decimal expected = {{15015, 0, 0, 6 << 16}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_11) {
  s21_decimal dec1 = {{15015, 0, 0, 6 << 16}};
  s21_decimal dec2 = {{15, 0, 0, 6 << 16}};
  s21_decimal expected = {{15000, 0, 0, 6 << 16}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// 123456789.1 - 0.000030000020000000123 = 123456789.09996999997999999988
START_TEST(test_s21_sub_12) {
  s21_decimal dec1 = {{1234567891, 0, 0, 65536}};
  s21_decimal dec2 = {{-145045381, 6984923, 0, 1376256}};
  s21_decimal expected = {{347007988, -1067895995, 669260594, 1310720}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// 123456789.1 - 0.00003000002000000123 = 123456789.09996999997999999877
START_TEST(test_s21_sub_13) {
  s21_decimal dec1 = {{1234567891, 0, 0, 65536}};
  s21_decimal dec2 = {{1703482491, 698492, 0, 1310720}};
  s21_decimal expected = {{347007877, -1067895995, 669260594, 1310720}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// 123456789.1 - 0.000030000020000001235 = 123456789.09996999997999999876
START_TEST(test_s21_sub_14) {
  s21_decimal dec1 = {{1234567891, 0, 0, 65536}};
  s21_decimal dec2 = {{-145044269, 6984923, 0, 1376256}};
  s21_decimal expected = {{347007876, -1067895995, 669260594, 1310720}};
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_15) {
  s21_decimal dec1 = {{0x00000019, 0x00000000, 0x00000000, 0x00010000}};  // 2.5
  s21_decimal dec2 = {{0x00000019, 0x00000000, 0x00000000, 0x00010000}};  // 2.5
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x00010000}};  // 0.0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_16) {
  s21_decimal dec1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_17) {
  s21_decimal dec1 = {{0x00000000, 0x00000000, 0x00000000, 0x80010000}};  // 0.0
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x80010000}};  // 0.0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_18) {
  s21_decimal dec1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000, 0x80010000}};  // 0.0
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x00010000}};  // 0.0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_19) {
  s21_decimal dec1 = {{0x00000000, 0x00000000, 0x00000000, 0x80010000}};  // 0.0
  s21_decimal dec2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x80010000}};  // 0.0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_20) {
  s21_decimal dec1 = {
      {0x00000001, 0x00000000, 0x00000000, 0x800E0000}};  // -0.00000000000001
  s21_decimal dec2 = {
      {0x00000006, 0x00000000, 0x00000000, 0x000F0000}};  // 0.000000000000006
  s21_decimal expected = {
      {0x00000010, 0x00000000, 0x00000000, 0x800F0000}};  // -0.000000000000016
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_21) {
  s21_decimal dec1 = {{0x00000019, 0x00000000, 0x00000000, 0x00010000}};  // 2.5
  s21_decimal dec2 = {{0x00000064, 0x00000000, 0x00000000, 0x00000000}};  // 100
  s21_decimal expected = {
      {0x000003CF, 0x00000000, 0x00000000, 0x80010000}};  // -97.5
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_22) {
  s21_decimal dec1 = {
      {0x00000183, 0x00000000, 0x00000000, 0x00020000}};  // 3.87
  s21_decimal dec2 = {
      {0x00004DA6, 0x00000000, 0x00000000, 0x00020000}};  // 198.78
  s21_decimal expected = {
      {0x00004C23, 0x00000000, 0x00000000, 0x80020000}};  // -194.91
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_23) {
  s21_decimal dec1 = {
      {0x14490831, 0x00048E23, 0x00000000, 0x00070000}};  // 128218122.2172721
  s21_decimal dec2 = {
      {0x164214B7, 0x00000028, 0x00000000, 0x00040000}};  // 17217212.1271
  s21_decimal expected = {
      {0x22281D59, 0x0003F18C, 0x00000000, 0x00070000}};  // 111000910.0901721
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_24) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};  // 1
  s21_decimal dec2 = {{0x00000019, 0x00000000, 0x00000000, 0x00010000}};  // 2.5
  s21_decimal expected = {
      {0x0000000F, 0x00000000, 0x00000000, 0x80010000}};  // -1.5
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_25) {
  s21_decimal dec1 = {
      {0x77D5E3AA, 0x0000011C, 0x00000000, 0x00060000}};  // 1221781.218218
  s21_decimal dec2 = {
      {0x00212155, 0x00000000, 0x00000000, 0x00070000}};  // 0.2171221
  s21_decimal expected = {
      {0xAE39C34F, 0x00000B1C, 0x00000000, 0x00070000}};  // 1221781.0010959
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_26) {
  s21_decimal dec1 = {{0x80000000, 0x80000000, 0x80000000,
                       0x801C0000}};  // -3.9614081266355540835774234624
  s21_decimal dec2 = {{0x80000000, 0x80000000, 0x80000000,
                       0x801C0000}};  // -3.9614081266355540835774234624
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000,
                           0x001C0000}};  // 0.0000000000000000000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_27) {
  s21_decimal dec1 = {{0x80000000, 0x80000000, 0x80000000,
                       0x000E0000}};  // 396140812663555.40835774234624
  s21_decimal dec2 = {{0x80000000, 0x80000000, 0x80000000,
                       0x000E0000}};  // 396140812663555.40835774234624
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x000E0000}};  // 0.00000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_28) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal dec2 = {{0x00000001, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000001
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000,
                           0x001C0000}};  // 0.0000000000000000000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_29) {
  s21_decimal dec1 = {{0x000F4240, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000001000000
  s21_decimal dec2 = {{0x000186A0, 0x00000000, 0x00000000,
                       0x00140000}};  // 0.00000000000000100000
  s21_decimal expected = {{0x4E635DC0, 0x00000918, 0x00000000,
                           0x801C0000}};  // -0.0000000000000009999999000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_30) {
  s21_decimal dec1 = {{0x80000000, 0x80000000, 0x80000000,
                       0x00000000}};  // 39614081266355540835774234624
  s21_decimal dec2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x000A0000}};  // 0.0000000000
  s21_decimal expected = {{0x80000000, 0x80000000, 0x80000000,
                           0x00000000}};  // 39614081266355540835774234624
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_31) {
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00010000}};  // 7922816251426433759354395033.5
  s21_decimal dec2 = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};  // 0.5
  s21_decimal expected = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00010000}};  // 7922816251426433759354395033.0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_32) {
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950335
  s21_decimal dec2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x000A0000}};  // 0.0000000000
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  // 79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_33) {
  s21_decimal dec1 = {
      {0x1422CF6C, 0x000001FC, 0x00000000, 0x80030000}};  // -2182181212.012
  s21_decimal dec2 = {
      {0xF96C01C5, 0x0007B6B6, 0x00000000, 0x800B0000}};  // -21712.21821882821
  s21_decimal expected = {{0x3D3DEA3B, 0xD45ACA59, 0x0000000B,
                           0x800B0000}};  // -2182159499.79378117179
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_34) {
  s21_decimal dec1 = {{0x2564B1EA, 0x3927F1F3, 0x041C50D7,
                       0x000B0000}};  // 12721717217217217.21821901290
  s21_decimal dec2 = {
      {0x00033F4A, 0x00000000, 0x00000000, 0x000C0000}};  // 0.000000212810
  s21_decimal expected = {{0x75EBB3DA, 0x3B8F737F, 0x291B2868,
                           0x000C0000}};  // 12721717217217217.218218800090
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_35) {
  s21_decimal dec1 = {
      {0x0001869F, 0x00000000, 0x00000000, 0x00050000}};  // 0.99999
  s21_decimal dec2 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00050000}};  // 0.00001
  s21_decimal expected = {
      {0x0001869E, 0x00000000, 0x00000000, 0x00050000}};  // 0.99998
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_36) {
  s21_decimal dec1 = {
      {0x0098967E, 0x00000000, 0x00000000, 0x80060000}};  // -9.999998
  s21_decimal dec2 = {
      {0x00000002, 0x00000000, 0x00000000, 0x80060000}};  // -0.000002
  s21_decimal expected = {
      {0x0098967C, 0x00000000, 0x00000000, 0x80060000}};  // -9.999996
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_37) {
  s21_decimal dec1 = {
      {0x000000CF, 0x00000000, 0x00000000, 0x00010000}};  // 20.7
  s21_decimal dec2 = {{0x00003F86, 0x00000000, 0x00000000,
                       0x00160000}};  // 0.0000000000000000016262
  s21_decimal expected = {{0x035FC07A, 0x7E1382FF, 0x00002BD5,
                           0x00160000}};  // 20.6999999999999999983738
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_38) {
  s21_decimal dec1 = {
      {0x0707E3C5, 0x002D8D61, 0x00000000, 0x80090000}};  // -12821821.821281221
  s21_decimal dec2 = {
      {0x058FEC8A, 0x00000000, 0x00000000, 0x00050000}};  // 933.18282
  s21_decimal expected = {
      {0x4D0FB265, 0x002D8E3A, 0x00000000, 0x80090000}};  // -12822755.004101221
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_39) {
  s21_decimal dec1 = {
      {0x846A4B4C, 0x0000012A, 0x00000000, 0x00080000}};  // 12821.21812812
  s21_decimal dec2 = {
      {0x0081787B, 0x00000000, 0x00000000, 0x80080000}};  // -0.08484987
  s21_decimal expected = {
      {0x84EBC3C7, 0x0000012A, 0x00000000, 0x00080000}};  // 12821.30297799
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_40) {
  s21_decimal dec1 = {{0x000035A3, 0x00000000, 0x00000000,
                       0x00170000}};  // 0.00000000000000000013731
  s21_decimal dec2 = {
      {0x0001F8A8, 0x00000000, 0x00000000, 0x00030000}};  // 129.192
  s21_decimal expected = {{0x827FCA5D, 0x3C3F28D0, 0x000AAFBF,
                           0x80170000}};  // -129.19199999999999999986269
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_41) {
  s21_decimal dec1 = {
      {0x79353447, 0x00000004, 0x00000000, 0x00010000}};  // 1921339911.1
  s21_decimal dec2 = {{0xD927FFFF, 0xE1003B28, 0x00000004,
                       0x00140000}};  // 0.89999999999999999999
  s21_decimal expected = {{0xDA380000, 0x5C68A936, 0x3E14F384,
                           0x00130000}};  // 1921339910.2000000000000000000
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_42) {
  s21_decimal dec1 = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  // -79228162514264337593543950333
  s21_decimal dec2 = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};  // 0.5
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_43) {
  s21_decimal dec1 = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  // -79228162514264337593543950333
  s21_decimal dec2 = {
      {0x00000033, 0x00000000, 0x00000000, 0x00020000}};  // 0.51
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_44) {
  s21_decimal dec1 = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  // -79228162514264337593543950333
  s21_decimal dec2 = {
      {0x00000031, 0x00000000, 0x00000000, 0x00020000}};  // 0.49
  s21_decimal expected = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950333
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_45) {
  s21_decimal dec1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  // -79228162514264337593543950334
  s21_decimal dec2 = {{0x00000005, 0x00000000, 0x00000000, 0x00010000}};  // 0.5
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_46) {
  s21_decimal dec1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  // -79228162514264337593543950334
  s21_decimal dec2 = {
      {0x00000033, 0x00000000, 0x00000000, 0x00020000}};  // 0.51
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_47) {
  s21_decimal dec1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  // -79228162514264337593543950334
  s21_decimal dec2 = {
      {0x00000031, 0x00000000, 0x00000000, 0x00020000}};  // 0.49
  s21_decimal expected = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950334
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_48) {
  s21_decimal dec1 = {{0x25D10992, 0xC0F1C9E2, 0x00000075,
                       0x000D0000}};  // 217217217.2121821219218
  s21_decimal dec2 = {
      {0x2B1BA438, 0x0022C51B, 0x00000000, 0x00060000}};  // 9786869686.182968
  s21_decimal expected = {{0x1B79E26E, 0xB810475F, 0x00001443,
                           0x800D0000}};  // -9569652468.9707858780782
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_49) {
  s21_decimal dec1 = {
      {0x05D6E6CB, 0x00000000, 0x00000000, 0x00000000}};  // 97969867
  s21_decimal dec2 = {
      {0x0365445B, 0x00000000, 0x00000000, 0x000C0000}};  // 0.000056968283
  s21_decimal expected = {{0x47DE6BA5, 0x4F9AE2F8, 0x00000005,
                           0x000C0000}};  // 97969866.999943031717
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_50) {
  s21_decimal dec1 = {
      {0xCC392EC8, 0x000490A0, 0x00000000, 0x00000000}};  // 1284920202309320
  s21_decimal dec2 = {{0x13F6BD6D, 0x1738423E, 0x00000000,
                       0x000D0000}};  // 167316.0095958482285
  s21_decimal expected = {{0x6E564293, 0x510205DD, 0x29849C5D,
                           0x000D0000}};  // 1284920202142003.9904041517715
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_51) {
  s21_decimal dec1 = {
      {0x10C2F579, 0x00000000, 0x00000000, 0x80050000}};  // -2812.12281
  s21_decimal dec2 = {
      {0x10C44951, 0x00000000, 0x00000000, 0x80030000}};  // -281299.281
  s21_decimal expected = {
      {0x7BE9AE2B, 0x00000006, 0x00000000, 0x00050000}};  // 278487.15819
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_52) {
  s21_decimal dec1 = {
      {0x00000190, 0x00000000, 0x00000000, 0x80000000}};  // -400
  s21_decimal dec2 = {
      {0x00000190, 0x00000000, 0x00000000, 0x80000000}};  // -400
  s21_decimal expected = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(test_s21_sub_53) {
  s21_decimal dec1 = {
      {0x00000006, 0x00000000, 0x00000000, 0x80010000}};  // -0.6
  s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 2);
}
END_TEST

START_TEST(test_s21_sub_54) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1
  s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00000000}};  // 79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 2);
}
END_TEST

START_TEST(test_s21_sub_55) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};  // 1
  s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  //-79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 1);
}
END_TEST

START_TEST(test_s21_sub_56) {
  s21_decimal dec1 = {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}};  // 10
  s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80000000}};  //-79228162514264337593543950335
  s21_decimal result = {0};
  ck_assert_int_eq(s21_sub(dec1, dec2, &result), 1);
}
END_TEST

Suite *test_s21_sub(void) {
  Suite *s = suite_create("===== S21_SUB =====");
  TCase *tc = tcase_create("s21_sub");

  tcase_add_test(tc, test_s21_sub_01);
  tcase_add_test(tc, test_s21_sub_02);
  tcase_add_test(tc, test_s21_sub_03);
  tcase_add_test(tc, test_s21_sub_04);
  tcase_add_test(tc, test_s21_sub_05);
  tcase_add_test(tc, test_s21_sub_06);
  tcase_add_test(tc, test_s21_sub_07);
  tcase_add_test(tc, test_s21_sub_08);
  tcase_add_test(tc, test_s21_sub_09);
  tcase_add_test(tc, test_s21_sub_10);
  tcase_add_test(tc, test_s21_sub_11);
  tcase_add_test(tc, test_s21_sub_12);
  tcase_add_test(tc, test_s21_sub_13);
  tcase_add_test(tc, test_s21_sub_14);
  tcase_add_test(tc, test_s21_sub_15);
  tcase_add_test(tc, test_s21_sub_16);
  tcase_add_test(tc, test_s21_sub_17);
  tcase_add_test(tc, test_s21_sub_18);
  tcase_add_test(tc, test_s21_sub_19);
  tcase_add_test(tc, test_s21_sub_20);
  tcase_add_test(tc, test_s21_sub_21);
  tcase_add_test(tc, test_s21_sub_22);
  tcase_add_test(tc, test_s21_sub_23);
  tcase_add_test(tc, test_s21_sub_24);
  tcase_add_test(tc, test_s21_sub_25);
  tcase_add_test(tc, test_s21_sub_26);
  tcase_add_test(tc, test_s21_sub_27);
  tcase_add_test(tc, test_s21_sub_28);
  tcase_add_test(tc, test_s21_sub_29);
  tcase_add_test(tc, test_s21_sub_30);
  tcase_add_test(tc, test_s21_sub_31);
  tcase_add_test(tc, test_s21_sub_32);
  tcase_add_test(tc, test_s21_sub_33);
  tcase_add_test(tc, test_s21_sub_34);
  tcase_add_test(tc, test_s21_sub_35);
  tcase_add_test(tc, test_s21_sub_36);
  tcase_add_test(tc, test_s21_sub_37);
  tcase_add_test(tc, test_s21_sub_38);
  tcase_add_test(tc, test_s21_sub_39);
  tcase_add_test(tc, test_s21_sub_40);
  tcase_add_test(tc, test_s21_sub_41);
  tcase_add_test(tc, test_s21_sub_42);
  tcase_add_test(tc, test_s21_sub_43);
  tcase_add_test(tc, test_s21_sub_44);
  tcase_add_test(tc, test_s21_sub_45);
  tcase_add_test(tc, test_s21_sub_46);
  tcase_add_test(tc, test_s21_sub_47);
  tcase_add_test(tc, test_s21_sub_48);
  tcase_add_test(tc, test_s21_sub_49);
  tcase_add_test(tc, test_s21_sub_50);
  tcase_add_test(tc, test_s21_sub_51);
  tcase_add_test(tc, test_s21_sub_52);
  tcase_add_test(tc, test_s21_sub_53);
  tcase_add_test(tc, test_s21_sub_54);
  tcase_add_test(tc, test_s21_sub_55);
  tcase_add_test(tc, test_s21_sub_56);
  suite_add_tcase(s, tc);

  return s;
}