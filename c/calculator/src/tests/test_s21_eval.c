#include "test_s21_calc.h"

START_TEST(test_s21_eval_0) {
  // s = ""
  char s[20] = "";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(1, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_1) {
  // s = "2"
  char s[20] = "2";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(2, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_2) {
  // s = "+1"
  char s[20] = "+1";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(1, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_3) {
  // s = "-0.333333"
  char s[20] = "-0.333333";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(-0.333333, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_4) {
  // s = "1.234567+"
  char s[20] = "1.234567+";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_5) {
  // s = "6+"
  char s[20] = "6+";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_6) {
  // s = "3^"
  char s[20] = "3^";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_7) {
  // s = "3^2"
  char s[20] = "3^2";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(9, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_8) {
  // s = "3^^"
  char s[20] = "3^^";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_9) {
  // s = "5 mod 2"
  char s[20] = "5 mod 2";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(1, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_10) {
  // s = "x * x"
  char s[20] = "x * x";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 4);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(16, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_11) {
  // s = "(x / (x - 2))"
  char s[20] = "(x / (x - 2))";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 4);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(2, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_12) {
  // s = "x * (-3 - 2)"
  char s[20] = "x * (-3 - 2)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 5);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(-25, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_13) {
  // s = "8 * 8 ^ -1"
  char s[20] = "8 * 8 ^ -1";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(1, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_14) {
  // s = "1/0"
  char s[20] = "1/0";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_infinite(got);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_15) {
  // s = "log100+2"
  char s[20] = "log100+2";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(4, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_16) {
  // s = "cos(0.5)"
  char s[20] = "cos(0.5)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(0.8775826, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_17) {
  // s = "sin(0.5)"
  char s[20] = "sin(0.5)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(0.4794255, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_18) {
  // s = "tan(0.5)"
  char s[20] = "tan(0.5)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(0.5463024, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_19) {
  // s = "acos(0.5)"
  char s[20] = "acos(0.5)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(1.0471975, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_20) {
  // s = "asin(0.5)"
  char s[20] = "asin(0.5)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(0.5235988, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_21) {
  // s = "atan(0.5)"
  char s[20] = "atan(0.5)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(0.4636476, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_22) {
  // s = "sqrt(16.0)"
  char s[20] = "sqrt(16.0)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(4, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_eval_23) {
  // s = "ln(16.0)"
  char s[20] = "ln(16.0)";
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = eval(rpn, &got, 0);
  ck_assert_int_eq(0, got_int);
  ck_assert_double_eq_tol(2.7725887, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

Suite *test_s21_eval(void) {
  Suite *s = suite_create("===== S21_EVAL =====");
  TCase *tc = tcase_create("s21_eval");

  tcase_add_test(tc, test_s21_eval_0);
  tcase_add_test(tc, test_s21_eval_1);
  tcase_add_test(tc, test_s21_eval_2);
  tcase_add_test(tc, test_s21_eval_3);
  tcase_add_test(tc, test_s21_eval_4);
  tcase_add_test(tc, test_s21_eval_5);
  tcase_add_test(tc, test_s21_eval_6);
  tcase_add_test(tc, test_s21_eval_7);
  tcase_add_test(tc, test_s21_eval_8);
  tcase_add_test(tc, test_s21_eval_9);
  tcase_add_test(tc, test_s21_eval_10);
  tcase_add_test(tc, test_s21_eval_11);
  tcase_add_test(tc, test_s21_eval_12);
  tcase_add_test(tc, test_s21_eval_13);
  tcase_add_test(tc, test_s21_eval_14);
  tcase_add_test(tc, test_s21_eval_15);
  tcase_add_test(tc, test_s21_eval_16);
  tcase_add_test(tc, test_s21_eval_17);
  tcase_add_test(tc, test_s21_eval_18);
  tcase_add_test(tc, test_s21_eval_19);
  tcase_add_test(tc, test_s21_eval_20);
  tcase_add_test(tc, test_s21_eval_21);
  tcase_add_test(tc, test_s21_eval_22);
  tcase_add_test(tc, test_s21_eval_23);
  suite_add_tcase(s, tc);

  return s;
}
