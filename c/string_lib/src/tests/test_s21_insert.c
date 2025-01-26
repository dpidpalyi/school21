#include "test_s21_string.h"

START_TEST(test_s21_insert_no_null) {
  char str1[] = "hello, world!";
  char str2[] = "HeLLO";
  char str3[] = " ";
  char str4[] = "world hello";
  char str6[] = "abcdefghij";

  char *new_str;
  new_str = s21_insert(str2, "FP", 3);
  ck_assert_pstr_eq(new_str, "HeLFPLO");
  if (new_str) free(new_str);

  new_str = s21_insert(str3, " ", 0);
  ck_assert_pstr_eq(new_str, "  ");
  if (new_str) free(new_str);

  new_str = s21_insert(" ", "HELL", 1);
  ck_assert_pstr_eq(new_str, " HELL");
  if (new_str) free(new_str);

  new_str = s21_insert(str4, " ", 2);
  ck_assert_pstr_eq(new_str, "wo rld hello");
  if (new_str) free(new_str);

  new_str = s21_insert(str1, "hELLO, WORLD!", 7);
  ck_assert_pstr_eq(new_str, "hello, hELLO, WORLD!world!");
  if (new_str) free(new_str);

  new_str = s21_insert(str6, "\'I WAS HERE\'", 3);
  ck_assert_pstr_eq(new_str, "abc\'I WAS HERE\'defghij");
  if (new_str) free(new_str);
}
END_TEST

START_TEST(test_s21_insert_null) {
  char str1[] = "hello, world!";
  char str2[] = "HeLLO";
  char *str3 = S21_NULL;

  char *new_str = s21_insert(str3, str3, 7);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_insert(str3, str2, 3);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_insert(str1, str3, 4);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_insert(str3, " ", 0);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);

  new_str = s21_insert(" ", str3, 2);
  ck_assert_pstr_eq(new_str, str3);
  if (new_str) free(new_str);
}
END_TEST

Suite *test_s21_insert(void) {
  Suite *s = suite_create("===== S21_INSERT =====");
  TCase *tc = tcase_create("s21_insert_tc");

  tcase_add_test(tc, test_s21_insert_no_null);
  tcase_add_test(tc, test_s21_insert_null);
  suite_add_tcase(s, tc);

  return s;
}
