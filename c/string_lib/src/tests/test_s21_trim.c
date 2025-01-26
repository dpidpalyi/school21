#include "test_s21_string.h"

START_TEST(test_s21_trim_no_null) {
  char str1[] = "-!hello, world?";
  char str2[] = "HeLlOo";
  char str3[] = "1223445";

  char *new_str = s21_trim(str1, "?!-");
  ck_assert_pstr_eq(new_str, "hello, world");
  if (new_str) free(new_str);

  new_str = s21_trim(str2, "LO");
  ck_assert_pstr_eq(new_str, "HeLlOo");
  if (new_str) free(new_str);

  new_str = s21_trim(str3, "513");
  ck_assert_pstr_eq(new_str, "22344");
  if (new_str) free(new_str);

  new_str = s21_trim(str2, "Ho");
  ck_assert_pstr_eq(new_str, "eLlO");
  if (new_str) free(new_str);

  new_str = s21_trim(str2, "");
  ck_assert_pstr_eq(new_str, "HeLlOo");
  if (new_str) free(new_str);

  new_str = s21_trim("", "");
  ck_assert_pstr_eq(new_str, "");
  if (new_str) free(new_str);
}
END_TEST

START_TEST(test_s21_trim_null) {
  char str1[] = "hello, world!  ";
  char str2[] = "HeLLO";
  char *str3 = S21_NULL;

  char *new_str = s21_trim(str3, str3);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_trim(str3, str2);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_trim(str1, str3);
  ck_assert_pstr_eq(new_str, "hello, world!");
  if (new_str) free(new_str);

  new_str = s21_trim(str3, " ");
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_trim(" ", str3);
  ck_assert_pstr_eq(new_str, "");
  if (new_str) free(new_str);
}
END_TEST

Suite *test_s21_trim(void) {
  Suite *s = suite_create("===== S21_TRIM =====");
  TCase *tc = tcase_create("s21_trim_tc");

  tcase_add_test(tc, test_s21_trim_null);
  tcase_add_test(tc, test_s21_trim_no_null);
  suite_add_tcase(s, tc);

  return s;
}
