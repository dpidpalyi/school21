#include "test_s21_string.h"

START_TEST(test_s21_to_lower_all) {
  char str1[] = "HELLO, WORLD!";
  char str2[] = "HeLlOo";
  char str3[] = "";
  char str4[] = "world hello";
  char *str5 = S21_NULL;

  char *new_str = s21_to_lower(str1);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "hello, world!");
    free(new_str);
  }

  new_str = s21_to_lower(str2);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "helloo");
    free(new_str);
  }

  new_str = s21_to_lower(str3);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "");
    free(new_str);
  }

  new_str = s21_to_lower(str4);
  if (new_str) {
    ck_assert_pstr_eq(new_str, "world hello");
    free(new_str);
  }

  new_str = s21_to_lower(str5);
  char *s6 = S21_NULL;
  ck_assert_pstr_eq(s6, new_str);
  if (new_str) free(new_str);
}
END_TEST

Suite *test_s21_to_lower(void) {
  Suite *s = suite_create("===== S21_TO_LOWER =====");
  TCase *tc = tcase_create("s21_to_lower_tc");

  tcase_add_test(tc, test_s21_to_lower_all);
  suite_add_tcase(s, tc);

  return s;
}
