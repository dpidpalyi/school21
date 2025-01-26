#include "test_s21_string.h"

#define STR 4

START_TEST(test_s21_strlen_all) {
  char s[][20] = {"", "W", "World", "Hello world!"};
  size_t want;
  s21_size_t got;
  for (int i = 0; i < STR; i++) {
    want = strlen(s[i]);
    got = s21_strlen(s[i]);
    ck_assert_msg(want == got,
                  "str = \"%s\", strlen returns %ld, "
                  "s21_strlen returns %ld",
                  s[i], want, got);
  }
}
END_TEST

Suite *test_s21_strlen(void) {
  Suite *s = suite_create("===== S21_STRLEN =====");
  TCase *tc = tcase_create("s21_strlen_tc");

  tcase_add_test(tc, test_s21_strlen_all);
  suite_add_tcase(s, tc);

  return s;
}
