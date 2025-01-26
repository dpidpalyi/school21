#include "test_s21_string.h"

#define STR1 3
#define STR2 13

START_TEST(test_s21_strpbrk_all) {
  char str1[STR1][6] = {"", "H", "Hello"};
  char str2[STR2][7] = {"",      "H",     "W",     "eH",    "We",
                        "Hello", "EPRST", "PRSTH", "PReTU", "EPRSTH"};
  char *want;
  char *got;
  for (int i = 0; i < STR1; i++)
    for (int j = 0; j < STR2; j++) {
      want = strpbrk(str1[i], str2[j]);
      got = s21_strpbrk(str1[i], str2[j]);
      ck_assert_msg(want == got,
                    "str1 = \"%s\", str2 = \"%s\", strpbrk returns \"%s\", "
                    "s21_strpbrk returns \"%s\"",
                    str1[i], str2[j], want, got);
    }
}
END_TEST

Suite *test_s21_strpbrk(void) {
  Suite *s = suite_create("===== S21_STRPBRK =====");
  TCase *tc = tcase_create("s21_strpbrk_tc");

  tcase_add_test(tc, test_s21_strpbrk_all);
  suite_add_tcase(s, tc);

  return s;
}
