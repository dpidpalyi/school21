#include "test_s21_string.h"

#define NUM 200

START_TEST(test_s21_strerror_all) {
  char *want;
  char *got;
  int k;
  for (k = -200; k < NUM; k++) {
    want = strerror(k);
    got = s21_strerror(k);
    ck_assert_msg(!strcmp(want, got),
                  "errornum = '%d', strerror returns %s, "
                  "s21_strerror returns %s",
                  k, (char *)want, (char *)got);
  }
}
END_TEST

Suite *test_s21_strerror(void) {
  Suite *s = suite_create("===== S21_STRERROR =====");
  TCase *tc = tcase_create("s21_strerror_tc");

  tcase_add_test(tc, test_s21_strerror_all);
  suite_add_tcase(s, tc);

  return s;
}
