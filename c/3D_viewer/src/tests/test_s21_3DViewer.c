#include "test_s21_3DViewer.h"

int main() {
  int all_tests_failed = 0;
  Suite *test_s21_3DViewer_1[] = {test_s21_parse_file(),
                                  test_s21_transformations(), NULL};

  for (int i = 0; test_s21_3DViewer_1[i] != NULL; i++) {
    SRunner *runner = srunner_create(test_s21_3DViewer_1[i]);

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
