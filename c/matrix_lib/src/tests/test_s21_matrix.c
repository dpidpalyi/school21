#include "test_s21_matrix.h"

int main() {
  int all_tests_failed = 0;
  Suite *test_s21_matrix[] = {
      test_s21_create_matrix(),    test_s21_remove_matrix(),
      test_s21_eq_matrix(),        test_s21_sum_matrix(),
      test_s21_sub_matrix(),       test_s21_mult_number(),
      test_s21_mult_matrix(),      test_s21_transpose(),
      test_s21_calc_complements(), test_s21_determinant(),
      test_s21_inverse_matrix(),   NULL};

  for (int i = 0; test_s21_matrix[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_s21_matrix[i]);

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
