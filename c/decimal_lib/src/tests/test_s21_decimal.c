#include "test_s21_decimal.h"

int main() {
  int all_tests_failed = 0;
  Suite *test_s21_decimal[] = {test_s21_add(),
                               test_s21_sub(),
                               test_s21_mul(),
                               test_s21_div(),
                               test_s21_is_less(),
                               test_s21_is_less_or_equal(),
                               test_s21_is_greater(),
                               test_s21_is_greater_or_equal(),
                               test_s21_is_equal(),
                               test_s21_is_not_equal(),
                               test_s21_from_int_to_decimal(),
                               test_s21_from_float_to_decimal(),
                               test_s21_from_decimal_to_int(),
                               test_s21_from_decimal_to_float(),
                               test_s21_floor(),
                               test_s21_round(),
                               test_s21_truncate(),
                               test_s21_negate(),
                               NULL};

  for (int i = 0; test_s21_decimal[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_s21_decimal[i]);

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
