#include "test_s21_string.h"

#define STR 7
#define NUM 9
#define MAX 10

START_TEST(test_s21_strncpy_all) {
  char arr[STR][MAX] = {"World",   "123456789", "",  "Hello",
                        "abcdefg", "L",         "aB"};
  s21_size_t n[NUM] = {0, 1, 2, 3, 5, 6, 7, 9, 10};
  char *want;
  char *got;
  char dest_copy[MAX] = "";
  char s21_dest_copy[MAX] = "";
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < STR; j++)
      for (int k = 0; k < NUM; k++)
        if (n[k] <= s21_strlen(arr[i])) {
          want = strncpy(dest_copy, arr[j], n[k]);
          got = s21_strncpy(s21_dest_copy, arr[j], n[k]);
          ck_assert_msg(
              !strcmp(want, got),
              "dst = \"%s\", src = '%s', bytes = %ld, strncpy returns %s, "
              "s21_strncpy returns %s",
              arr[i], arr[j], n[k], want, got);
        }
}
END_TEST

Suite *test_s21_strncpy(void) {
  Suite *s = suite_create("===== S21_STRNCPY =====");
  TCase *tc = tcase_create("s21_strncpy_tc");

  tcase_add_test(tc, test_s21_strncpy_all);
  suite_add_tcase(s, tc);

  return s;
}
