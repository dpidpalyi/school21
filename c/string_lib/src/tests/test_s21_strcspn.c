#include "test_s21_string.h"

#define STR 9
#define MAX 15

START_TEST(test_s21_strcspn_all) {
  char arr[STR][MAX] = {"World", "is destination", "G",   "He", "This", "s",
                        "",      "12345",          "fmq5"};
  s21_size_t want;
  s21_size_t got;
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < STR; j++) {
      want = strcspn(arr[i], arr[j]);
      got = s21_strcspn(arr[i], arr[j]);
      ck_assert_msg(want == got,
                    "dest = \"%s\", src = '%s', strcspn returns %ld, "
                    "s21_strcspn returns %ld",
                    arr[i], arr[j], want, got);
    }
}
END_TEST

Suite *test_s21_strcspn(void) {
  Suite *s = suite_create("===== S21_STRCSPN =====");
  TCase *tc = tcase_create("s21_strcspn_tc");

  tcase_add_test(tc, test_s21_strcspn_all);
  suite_add_tcase(s, tc);

  return s;
}
