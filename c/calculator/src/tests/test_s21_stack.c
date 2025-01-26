#include "test_s21_calc.h"

START_TEST(test_s21_init_stack_0) {
  // init
  stack *s = init();

  ck_assert_ptr_nonnull(s);
  ck_assert_ptr_null(s->top);
  free(s);
}
END_TEST

START_TEST(test_s21_destroy_stack_1) {
  // destroy
  stack *s = init();

  ck_assert_ptr_nonnull(s);
  destroy_stack(s);
  ck_assert_ptr_null(s->top);
  free(s);
}
END_TEST

START_TEST(test_s21_destroy_stack_2) {
  // push one non-double and one double values, destroy all
  stack *s = init();
  double want = 50.0;

  push(s, SUM, NULL);
  ck_assert_ptr_nonnull(s->top);
  push(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);

  destroy_stack(s);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_push_stack_3) {
  // push one double value
  stack *s = init();
  enum type_t type;
  double got, want = 100.0;

  push(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, &got);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_push_stack_4) {
  // push two double values
  stack *s = init();
  enum type_t type;
  double got, want = 100.0;

  push(s, NUM, &want);
  push(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, &got);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  want_int = pop(s, &type, &got);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_push_stack_5) {
  // push one non-double values
  stack *s = init();
  enum type_t type;

  push(s, SIN, NULL);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, NULL);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, SIN);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_push_stack_6) {
  // push two non-double values
  stack *s = init();
  enum type_t type;

  push(s, SUM, NULL);
  ck_assert_ptr_nonnull(s->top);
  push(s, COS, NULL);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, NULL);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, COS);
  want_int = pop(s, &type, NULL);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, SUM);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_push_stack_7) {
  // push one double and one non-double values
  stack *s = init();
  enum type_t type;
  double got, want = 50.0;

  push(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);
  push(s, TAN, NULL);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, NULL);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, TAN);
  want_int = pop(s, &type, &got);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_push_stack_8) {
  // push one non-double and one double values
  stack *s = init();
  enum type_t type;
  double got, want = 50.0;

  push(s, MUL, NULL);
  ck_assert_ptr_nonnull(s->top);
  push(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, &got);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  want_int = pop(s, &type, NULL);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, MUL);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_add_stack_9) {
  // add one double values
  stack *s = init();
  double want = 10.0;

  add(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);

  destroy_stack(s);
  ck_assert_ptr_null(s->top);
  free(s);
}
END_TEST

START_TEST(test_s21_add_stack_10) {
  // add one non-double and one double values
  stack *s = init();
  enum type_t type;
  double got, want = 50.0;

  add(s, MUL, NULL);
  ck_assert_ptr_nonnull(s->top);
  add(s, NUM, &want);
  ck_assert_ptr_nonnull(s->top);

  int want_int = pop(s, &type, NULL);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, MUL);
  want_int = pop(s, &type, &got);
  ck_assert_int_eq(want_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  ck_assert_ptr_null(s->top);

  free(s);
}
END_TEST

START_TEST(test_s21_copy_stack_11) {
  // copy num and sin to dst stack
  stack *s = init();
  stack *d = init();
  enum type_t type;
  double got, want = 10.0;

  add(s, NUM, &want);
  add(s, SIN, &want);
  ck_assert_ptr_nonnull(s->top);
  copy_stack(s, d);
  ck_assert_ptr_nonnull(s->top);

  int got_int = pop(d, &type, &got);
  ck_assert_int_eq(got_int, 0);
  ck_assert_int_eq(type, NUM);
  ck_assert_double_eq_tol(want, got, EPS);
  got_int = pop(d, &type, &got);
  ck_assert_int_eq(got_int, 0);
  ck_assert_int_eq(type, SIN);
  ck_assert_ptr_null(d->top);

  destroy_stack(s);
  destroy_stack(d);
  ck_assert_ptr_null(s->top);
  free(s);
  free(d);
}
END_TEST

Suite *test_s21_stack(void) {
  Suite *s = suite_create("===== S21_STACK =====");
  TCase *tc = tcase_create("s21_stack");

  tcase_add_test(tc, test_s21_init_stack_0);
  tcase_add_test(tc, test_s21_destroy_stack_1);
  tcase_add_test(tc, test_s21_destroy_stack_2);
  tcase_add_test(tc, test_s21_push_stack_3);
  tcase_add_test(tc, test_s21_push_stack_4);
  tcase_add_test(tc, test_s21_push_stack_5);
  tcase_add_test(tc, test_s21_push_stack_6);
  tcase_add_test(tc, test_s21_push_stack_7);
  tcase_add_test(tc, test_s21_push_stack_8);
  tcase_add_test(tc, test_s21_add_stack_9);
  tcase_add_test(tc, test_s21_add_stack_10);
  tcase_add_test(tc, test_s21_copy_stack_11);
  suite_add_tcase(s, tc);

  return s;
}
