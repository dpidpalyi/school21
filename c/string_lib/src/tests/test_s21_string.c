#include "test_s21_string.h"

int main() {
  int all_tests_failed = 0;
  Suite *test_s21_string[] = {test_s21_memchr(),   test_s21_memcmp(),
                              test_s21_memcpy(),   test_s21_memset(),
                              test_s21_strncat(),  test_s21_strchr(),
                              test_s21_strncmp(),  test_s21_strncpy(),
                              test_s21_strcspn(),  test_s21_strerror(),
                              test_s21_strlen(),   test_s21_strpbrk(),
                              test_s21_strrchr(),  test_s21_strstr(),
                              test_s21_strtok(),   test_s21_sscanf(),
                              test_s21_sprintf(),  test_s21_to_upper(),
                              test_s21_to_lower(), test_s21_insert(),
                              test_s21_trim(),     NULL};

  for (int i = 0; test_s21_string[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_s21_string[i]);

    srunner_run_all(runner, CK_NORMAL);
    int failed = srunner_ntests_failed(runner);
    all_tests_failed += failed;
    printf("-----------------------------------------\n");
    srunner_free(runner);
  }

  if (all_tests_failed)
    printf("======= NUMBER OF FAILED TESTS: %d =======\n", all_tests_failed);
  else
    printf("======= SUCCESS =======\n");

  return all_tests_failed;
}
