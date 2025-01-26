#include "test_s21_calc.h"

int main() {
  int all_tests_failed = 0;
  Suite *test_s21_calc[] = {test_s21_stack(), test_s21_parse(), test_s21_eval(),
                            NULL};

  for (int i = 0; test_s21_calc[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_s21_calc[i]);

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
