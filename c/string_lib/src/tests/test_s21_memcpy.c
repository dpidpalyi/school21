#include "test_s21_string.h"

#define STR 10
#define NUM 6

START_TEST(test_s21_memcpy_all) {
  char s[STR][6] = {"",   "W",  "H",     "Wo",    "He",
                    "We", "Ho", "Hello", "Wollo", "World"};
  s21_size_t n[NUM] = {0, 1, 2, 3, 5, 6};
  void *want;
  void *got;
  char dest_copy[6];
  char s21_dest_copy[6];
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < STR; j++)
      for (int k = 0; k < NUM; k++)
        if (n[k] <= s21_strlen(s[i]) && n[k] <= s21_strlen(s[j])) {
          strcpy(dest_copy, s[i]);
          strcpy(s21_dest_copy, s[i]);
          want = memcpy(dest_copy, s[j], n[k]);
          got = s21_memcpy(s21_dest_copy, s[j], n[k]);
          ck_assert_msg(
              !s21_memcmp(want, got, n[k]),
              "dst = \"%s\", src = \"%s\" bytes = %ld, memcpy returns \"%s\", "
              "s21_memcpy returns \"%s\"",
              s[i], s[j], n[k], (char *)want, (char *)got);
        }
}
END_TEST

Suite *test_s21_memcpy(void) {
  Suite *s = suite_create("===== S21_MEMCPY =====");
  TCase *tc = tcase_create("s21_memcpy_tc");

  tcase_add_test(tc, test_s21_memcpy_all);
  suite_add_tcase(s, tc);

  return s;
}
