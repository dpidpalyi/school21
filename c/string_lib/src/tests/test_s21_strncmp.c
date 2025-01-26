#include "test_s21_string.h"

#define STR 12
#define NUM 6

START_TEST(test_s21_strncmp_all) {
  char s[STR][6] = {"",   "W",     "H",     "Wo",    "He",    "We",
                    "Ho", "Hello", "Wollo", "World", "abc\0", "\0"};
  s21_size_t n[NUM] = {0, 1, 2, 3, 5, 6};
  int want;
  int got;
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < STR; j++)
      for (int k = 0; k < NUM; k++) {
        want = strncmp(s[i], s[j], n[k]);
        got = s21_strncmp(s[i], s[j], n[k]);
        if ((want < 0 && got > 0) || (want > 0 && got < 0) ||
            (want != got && got == 0))
          ck_abort_msg(
              "str1 = \"%s\", str2 = \"%s\" bytes = %ld, strncmp returns %d, "
              "s21_strncmp returns %d",
              s[i], s[j], n[k], want, got);
      }
}
END_TEST

START_TEST(test_s21_strncmp_null) {
  void *s1 = S21_NULL;
  void *s2 = S21_NULL;
  char *s = "Hello";
  ck_assert_int_eq(strncmp(s1, s2, 0), s21_strncmp(s1, s2, 0));
  ck_assert_int_eq(strncmp(s1, s, 0), s21_strncmp(s1, s, 0));
  ck_assert_int_eq(strncmp(s, s1, 0), s21_strncmp(s, s1, 0));
}
END_TEST

Suite *test_s21_strncmp(void) {
  Suite *s = suite_create("===== S21_STRNCMP =====");
  TCase *tc = tcase_create("s21_strncmp_tc");

  tcase_add_test(tc, test_s21_strncmp_all);
  tcase_add_test(tc, test_s21_strncmp_null);
  suite_add_tcase(s, tc);

  return s;
}