#include "test_s21_string.h"

#define WIDTH 10

START_TEST(test_s21_sscanf_spec_c) {
  int want = 0, got = 0;
  char width[WIDTH][3] = {"", "1", "2", "3", "5", "6", "7", "*", "12", "20"};
  char str[] = "123";
  int want_i;
  int got_i;
  for (int k = 0; k < WIDTH; k++) {
    char format[20] = "%";
    strcat(format, width[k]);
    strcat(format, "c");
    if (k == 7) {
      want_i = sscanf(str, format, &want);
      got_i = s21_sscanf(str, format, &got);
    } else {
      want_i = sscanf(str, format, &want);
      got_i = s21_sscanf(str, format, &got);
    }
    ck_assert_msg(want_i == got_i,
                  "format = \"%s\", str = \"%s\", sscanf "
                  "returns \"%d\", s21_sscanf returns \"%d\"",
                  format, str, want_i, got_i);
  }
}
END_TEST

START_TEST(test_s21_sscanf_spec_c_other) {
  char format[] = "%c";
  char format1[] = "\n%c \t%c \n%c";
  char format2[] = "%c%c%c";
  char format3[] = " %c   %c    %c ";

  char str[] = "\n\n  1 \n";
  char str1[] = "\n   \n  \ta";
  char str2[] = "\t\n\n  hel \n     \t";
  char str3[] = "\t\n\n h 2 l \t";

  char c1, c2, c3, c4, c11, c12, c13, c21, c22, c23;
  int res1, res2;
  res1 = s21_sscanf(str, format, &c1);
  res2 = sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);

  res1 = s21_sscanf(str1, format, &c3);
  res2 = sscanf(str1, format, &c4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c3, c4);

  res1 = s21_sscanf(str2, format2, &c11, &c12, &c13);
  res2 = sscanf(str2, format2, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);

  res1 = s21_sscanf(str3, format1, &c11, &c12, &c13);
  res2 = sscanf(str3, format1, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);

  res1 = s21_sscanf(str3, format3, &c11, &c12, &c13);
  res2 = sscanf(str3, format3, &c21, &c22, &c23);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c11, c21);
  ck_assert_int_eq(c12, c22);
  ck_assert_int_eq(c13, c23);
}
END_TEST

Suite *test_s21_sscanf(void) {
  Suite *s = suite_create("===== S21_SSCANF =====");
  TCase *tc = tcase_create("s21_sscanf_tc");

  tcase_add_test(tc, test_s21_sscanf_spec_c);
  tcase_add_test(tc, test_s21_sscanf_spec_c_other);
  suite_add_tcase(s, tc);
  return s;
}
