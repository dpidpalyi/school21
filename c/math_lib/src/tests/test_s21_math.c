#include "test_s21_math.h"

int main() {
  int all_tests_failed = 0;
  Suite *test_s21_math[] = {
      test_s21_abs(),  test_s21_sqrt(), test_s21_atan(), test_s21_acos(),
      test_s21_asin(), test_s21_cos(),  test_s21_sin(),  test_s21_tan(),
      test_s21_ceil(), test_s21_exp(),  test_s21_fabs(), test_s21_floor(),
      test_s21_fmod(), test_s21_log(),  test_s21_pow(),  NULL};

  for (int i = 0; test_s21_math[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_s21_math[i]);

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
