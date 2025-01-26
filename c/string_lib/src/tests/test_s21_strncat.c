#include "test_s21_string.h"

#define STR 7
#define NUM 8
#define MAX 15

START_TEST(test_s21_strncat_all) {
  char arr[STR][MAX] = {"World", "is destination", "T", "He", "This", "s", ""};
  s21_size_t n[NUM] = {0, 1, 2, 3, 5, 6, 14, 15};
  char *want;
  char *got;
  char dest_copy[MAX];
  char s21_dest_copy[MAX];
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < STR; j++)
      for (int k = 0; k < NUM; k++)
        if (n[k] <= (MAX - s21_strlen(arr[i]) - 1)) {
          strcpy(dest_copy, arr[i]);
          strcpy(s21_dest_copy, arr[i]);
          want = strncat(dest_copy, arr[j], n[k]);
          got = s21_strncat(s21_dest_copy, arr[j], n[k]);
          ck_assert_msg(
              !strcmp(want, got),
              "dest = \"%s\", src = '%s', bytes = %ld, strncat returns %s, "
              "s21_strncat returns %s",
              arr[i], arr[j], n[k], want, got);
        }
}
END_TEST

Suite *test_s21_strncat(void) {
  Suite *s = suite_create("===== S21_STRNCAT =====");
  TCase *tc = tcase_create("s21_strncat_tc");

  tcase_add_test(tc, test_s21_strncat_all);
  suite_add_tcase(s, tc);

  return s;
}
