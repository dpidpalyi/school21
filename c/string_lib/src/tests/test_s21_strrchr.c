#include "test_s21_string.h"

#define STR 3
#define NUM 5

START_TEST(test_s21_strrchr_all) {
  const char s[3][6] = {"", "W", "World"};
  int c[] = {'d', 'W', 'r', 200, 0};
  char *want;
  char *got;
  for (int i = 0; i < STR; i++)
    for (int k = 0; k < NUM; k++) {
      want = strrchr(s[i], c[k]);
      got = s21_strrchr(s[i], c[k]);
      ck_assert_msg(want == got,
                    "Str = \"%s\", c = '%d', strchr returns %s, "
                    "s21_strchr returns %s",
                    s[i], c[k], want, got);
    }
}
END_TEST

Suite *test_s21_strrchr(void) {
  Suite *s = suite_create("===== S21_STRRCHR =====");
  TCase *tc = tcase_create("s21_strrchr_tc");

  tcase_add_test(tc, test_s21_strrchr_all);
  suite_add_tcase(s, tc);

  return s;
}
