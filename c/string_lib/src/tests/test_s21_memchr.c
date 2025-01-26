#include "test_s21_string.h"

#define STR 3
#define CHARS 6
#define NUM 5

START_TEST(test_s21_memchr_all) {
  char s[STR][6] = {"", "W", "World"};
  int c[CHARS] = {'W', 'r', 'd', 'A', 0, 200};
  s21_size_t n[NUM] = {0, 1, 2, 5, 6};
  void *want;
  void *got;
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < CHARS; j++)
      for (int k = 0; k < NUM; k++)
        if (n[k] <= s21_strlen(s[i])) {
          want = memchr(s[i], c[j], n[k]);
          got = s21_memchr(s[i], c[j], n[k]);
          ck_assert_msg(
              want == got,
              "Str = \"%s\", c = '%d', bytes = %ld, memchr returns %p, "
              "s21_memchr returns %p",
              s[i], c[j], n[k], want, got);
        }
}
END_TEST

START_TEST(test_s21_memchr_null) {
  void *s = S21_NULL;
  int c = 'A';
  ck_assert_ptr_eq(memchr(s, c, 0), s21_memchr(s, c, 0));
}
END_TEST

Suite *test_s21_memchr(void) {
  Suite *s = suite_create("===== S21_MEMCHR =====");
  TCase *tc = tcase_create("s21_memchr_tc");

  tcase_add_test(tc, test_s21_memchr_all);
  tcase_add_test(tc, test_s21_memchr_null);
  suite_add_tcase(s, tc);

  return s;
}
