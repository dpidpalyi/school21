#include "test_s21_string.h"

#define STR 10
#define NUM 6

START_TEST(test_s21_memcmp_all) {
  char s[STR][6] = {"",   "W",  "H",     "Wo",    "He",
                    "We", "Ho", "Hello", "Wollo", "World"};
  s21_size_t n[NUM] = {0, 1, 2, 3, 5, 6};
  int want;
  int got;
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < STR; j++)
      for (int k = 0; k < NUM; k++)
        if (n[k] <= s21_strlen(s[i]) && n[k] <= s21_strlen(s[j])) {
          want = memcmp(s[i], s[j], n[k]);
          got = s21_memcmp(s[i], s[j], n[k]);
          if ((want < 0 && got > 0) || (want > 0 && got < 0) ||
              (want != got && got == 0))
            ck_abort_msg(
                "str1 = \"%s\", str2 = \"%s\" bytes = %ld, memcmp returns %d, "
                "s21_memcmp returns %d",
                s[i], s[j], n[k], want, got);
        }
}
END_TEST

START_TEST(test_s21_memcmp_null) {
  void *s1 = S21_NULL;
  void *s2 = S21_NULL;
  char *s = "Hello";
  ck_assert_int_eq(memcmp(s1, s2, 0), s21_memcmp(s1, s2, 0));
  ck_assert_int_eq(memcmp(s1, s, 0), s21_memcmp(s1, s, 0));
  ck_assert_int_eq(memcmp(s, s1, 0), s21_memcmp(s, s1, 0));
}
END_TEST

Suite *test_s21_memcmp(void) {
  Suite *s = suite_create("===== S21_MEMCMP =====");
  TCase *tc = tcase_create("s21_memcmp_tc");

  tcase_add_test(tc, test_s21_memcmp_all);
  tcase_add_test(tc, test_s21_memcmp_null);
  suite_add_tcase(s, tc);

  return s;
}
