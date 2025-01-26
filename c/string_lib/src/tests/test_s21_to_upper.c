#include "test_s21_string.h"

START_TEST(test_s21_to_upper_all) {
  char str1[] = "hello, world!";
  char str2[] = "HeLlOo";
  char str3[] = "";
  char str4[] = "WORLD HELLO";
  char *str5 = S21_NULL;

  char *new_str = s21_to_upper(str1);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "HELLO, WORLD!");
    free(new_str);
  }

  new_str = s21_to_upper(str2);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "HELLOO");
    free(new_str);
  }

  new_str = s21_to_upper(str3);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "");
    free(new_str);
  }

  new_str = s21_to_upper(str4);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "WORLD HELLO");
    free(new_str);
  }

  new_str = s21_to_upper(str5);
  char *s6 = S21_NULL;
  ck_assert_pstr_eq(s6, new_str);
  if (new_str) free(new_str);
}
END_TEST

Suite *test_s21_to_upper(void) {
  Suite *s = suite_create("===== S21_TO_UPPER =====");
  TCase *tc = tcase_create("s21_to_upper_tc");

  tcase_add_test(tc, test_s21_to_upper_all);
  suite_add_tcase(s, tc);

  return s;
}
