#include "test_s21_string.h"

#define STR 3
#define NDL 13

START_TEST(test_s21_strstr_all) {
  char hst[STR][6] = {"", "H", "Hello"};
  char ndl[NDL][7] = {"",   "H",   "W",     "He",    "We",     "llo",   "klo",
                      "ll", "elk", "Hello", "World", "Hello1", "World1"};
  char *want;
  char *got;
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < NDL; j++) {
      want = strstr(hst[i], ndl[j]);
      got = s21_strstr(hst[i], ndl[j]);
      ck_assert_msg(
          want == got,
          "haystack = \"%s\", needle = \"%s\", strstr returns \"%s\", "
          "s21_strstr returns \"%s\"",
          hst[i], ndl[j], want, got);
    }
}
END_TEST

Suite *test_s21_strstr(void) {
  Suite *s = suite_create("===== S21_STRSTR =====");
  TCase *tc = tcase_create("s21_strstr_tc");

  tcase_add_test(tc, test_s21_strstr_all);
  suite_add_tcase(s, tc);

  return s;
}
