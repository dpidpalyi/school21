#include "test_s21_string.h"

#define STR 3
#define CHARS 5
#define NUM 5

START_TEST(test_s21_memset_all) {
  char s[][6] = {"", "W", "World"};
  int c[] = {'W', 'd', 'A', 0, 200};
  s21_size_t n[] = {0, 1, 2, 5, 6};
  void *want;
  void *got;
  char s_copy[6];
  char s21_s_copy[6];
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < CHARS; j++)
      for (int k = 0; k < NUM; k++)
        if (n[k] <= s21_strlen(s[i])) {
          strcpy(s_copy, s[i]);
          strcpy(s21_s_copy, s[i]);
          want = memset(s_copy, c[j], n[k]);
          got = s21_memset(s21_s_copy, c[j], n[k]);
          ck_assert_msg(
              !s21_memcmp(want, got, n[k]),
              "Str = \"%s\", c = '%d', bytes = %ld, memset returns %s, "
              "s21_memset returns %s",
              s[i], c[j], n[k], (char *)want, (char *)got);
        }
}
END_TEST

Suite *test_s21_memset(void) {
  Suite *s = suite_create("===== S21_MEMSET =====");
  TCase *tc = tcase_create("s21_memset_tc");

  tcase_add_test(tc, test_s21_memset_all);
  suite_add_tcase(s, tc);

  return s;
}
