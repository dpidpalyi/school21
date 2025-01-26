#include "test_s21_string.h"

#define STR 19
#define DELIM 5
#define LENGTH 20

START_TEST(test_s21_strtok_all) {
  char s[STR][LENGTH] = {"",
                         "W",
                         ",",
                         ",. ",
                         "H,",
                         ".S",
                         "Hello",
                         ".World",
                         "Hello,",
                         ".Hello,",
                         ",.World",
                         "Hello,.",
                         "Hello World",
                         ",Hello World",
                         "Hello World.",
                         ".,Hello World",
                         "Hello World.,",
                         "Hello,.,World",
                         ",.,Hello,. World,."};
  char delim[DELIM][DELIM] = {"", ".", ",. ", " ,.", ",,,"};
  char *want_token;
  char *got_token;
  char s_copy[LENGTH];
  char s21_s_copy[LENGTH];
  for (int i = 0; i < STR; i++)
    for (int j = 0; j < DELIM; j++) {
      strcpy(s_copy, s[i]);
      strcpy(s21_s_copy, s[i]);
      want_token = strtok(s_copy, delim[j]);
      got_token = s21_strtok(s21_s_copy, delim[j]);
      if (want_token == S21_NULL) {
        ck_assert_ptr_null(got_token);
      } else {
        ck_assert_msg(
            !(strcmp(want_token, got_token) || strcmp(s_copy, s21_s_copy)),
            "str = \"%s\", delim = \"%s\",\nstrtok returns \"%s\", s_copy = "
            "\"%s\", "
            "\ns21_strtok returns \"%s\", s21_s_copy = \"%s\"",
            s[i], delim[j], want_token, s_copy, got_token, s21_s_copy);
        while ((want_token = strtok(S21_NULL, delim[j])) != S21_NULL) {
          got_token = s21_strtok(S21_NULL, delim[j]);
          ck_assert_msg(!strcmp(want_token, got_token),
                        "str = \"%s\", delim = \"%s\",\nstrtok returns \"%s\", "
                        "s21_strtok returns \"%s\"",
                        s[i], delim[j], want_token, got_token);
        }
        got_token = s21_strtok(S21_NULL, delim[j]);
        ck_assert_ptr_null(want_token);
        ck_assert_ptr_null(got_token);
      }
    }
}
END_TEST

Suite *test_s21_strtok(void) {
  Suite *s = suite_create("===== S21_STRTOK =====");
  TCase *tc = tcase_create("s21_strtok_tc");

  tcase_add_test(tc, test_s21_strtok_all);
  suite_add_tcase(s, tc);

  return s;
}
