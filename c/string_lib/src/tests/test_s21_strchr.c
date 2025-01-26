#include "test_s21_string.h"

#define STR 5
#define CHARS 6

START_TEST(test_s21_strchr_all) {
  const char arr[STR][15] = {"World", "This is source", "", "s", "\0"};
  int c[CHARS] = {'W', 's', 'A', 200, ' ', '\0'};
  char *want;
  char *got;
  for (int i = 0; i < STR; i++)
    for (int k = 0; k < CHARS; k++) {
      want = strchr(arr[i], c[k]);
      got = s21_strchr(arr[i], c[k]);
      ck_assert_msg(want == got,
                    "Str = \"%s\", c = '%d', strchr returns %s, "
                    "s21_strchr returns %s",
                    arr[i], c[k], want, got);
    }
}
END_TEST

Suite *test_s21_strchr(void) {
  Suite *s = suite_create("===== S21_STRCHR =====");
  TCase *tc = tcase_create("s21_strchr_tc");

  tcase_add_test(tc, test_s21_strchr_all);
  suite_add_tcase(s, tc);

  return s;
}
