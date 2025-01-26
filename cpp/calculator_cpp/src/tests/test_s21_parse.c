#include "test_s21_calc.h"

START_TEST(test_s21_remove_spaces_0) {
  // s = ""
  char s[1] = "";

  remove_spaces(s);
  ck_assert_str_eq(s, "");
}
END_TEST

START_TEST(test_s21_remove_spaces_1) {
  // s = "1"
  char s[2] = "1";

  remove_spaces(s);
  ck_assert_str_eq(s, "1");
}
END_TEST

START_TEST(test_s21_remove_spaces_2) {
  // s = " "
  char s[2] = " ";

  remove_spaces(s);
  ck_assert_str_eq(s, "");
}
END_TEST

START_TEST(test_s21_remove_spaces_3) {
  // s = "a "
  char s[3] = "a ";

  remove_spaces(s);
  ck_assert_str_eq(s, "a");
}
END_TEST

START_TEST(test_s21_remove_spaces_4) {
  // s = " s"
  char s[3] = " s";

  remove_spaces(s);
  ck_assert_str_eq(s, "s");
}
END_TEST

START_TEST(test_s21_remove_spaces_5) {
  // s = " 5.5 "
  char s[6] = " 5.5 ";

  remove_spaces(s);
  ck_assert_str_eq(s, "5.5");
}
END_TEST

START_TEST(test_s21_remove_spaces_6) {
  // s = "  5.5   6.6  "
  char s[20] = " 5.5  6.6  ";

  remove_spaces(s);
  ck_assert_str_eq(s, "5.56.6");
}
END_TEST

START_TEST(test_s21_remove_spaces_7) {
  // s = "5 mod 2"
  char s[20] = "5 mod 2";

  remove_spaces(s);
  ck_assert_str_eq(s, "5mod2");
}
END_TEST

START_TEST(test_s21_remove_spaces_8) {
  // s = "3.4"
  char s[10] = "3.4";

  remove_spaces(s);
  ck_assert_str_eq(s, "3.4");
}
END_TEST

START_TEST(test_s21_is_dbl_8) {
  // s = ""
  char s[1] = "";

  ck_assert_int_eq(EOF, is_dbl(s));
}
END_TEST

START_TEST(test_s21_is_dbl_9) {
  // s = "a"
  char s[2] = "a";

  ck_assert_int_eq(0, is_dbl(s));
}
END_TEST

START_TEST(test_s21_is_dbl_10) {
  // s = "1"
  char s[2] = "1";

  ck_assert_int_eq(1, is_dbl(s));
}
END_TEST

START_TEST(test_s21_is_dbl_11) {
  // s = "4.2"
  char s[4] = "4.2";

  ck_assert_int_eq(1, is_dbl(s));
}
END_TEST

START_TEST(test_s21_is_dbl_12) {
  // s = "a5.2"
  char s[5] = "a5.2";

  ck_assert_int_eq(0, is_dbl(s));
}
END_TEST

START_TEST(test_s21_is_dbl_13) {
  // s = ".2"
  char s[3] = ".2";

  ck_assert_int_eq(1, is_dbl(s));
}
END_TEST

START_TEST(test_s21_is_dbl_14) {
  // s = "5..2", n = 5.2
  char s[5] = "5..2";

  ck_assert_int_eq(1, is_dbl(s));
}
END_TEST

START_TEST(test_s21_get_token_15) {
  // s = ""
  char s[1] = "";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(0, type);
  ck_assert_double_eq_tol(0, value, EPS);
}
END_TEST

START_TEST(test_s21_get_token_16) {
  // s = "a"
  char s[2] = "a";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(0, type);
  ck_assert_double_eq_tol(0, value, EPS);
}
END_TEST

START_TEST(test_s21_get_token_17) {
  // s = "+"
  char s[2] = "+";
  enum type_t type = 0;
  char *ptr = s;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(SUM, type);
  ck_assert_double_eq_tol(0, value, EPS);
}
END_TEST

START_TEST(test_s21_get_token_18) {
  // s = "3"
  char s[2] = "3";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(3, value, EPS);
}
END_TEST

START_TEST(test_s21_get_token_19) {
  // s = "sin"
  char s[4] = "sin";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(SIN, type);
  ck_assert_double_eq_tol(0, value, EPS);
}
END_TEST

START_TEST(test_s21_get_token_20) {
  // s = "3.5+2"
  char s[6] = "3.5+2";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(3.5, value, EPS);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(SUM, type);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(2, value, EPS);
}
END_TEST

START_TEST(test_s21_get_token_21) {
  // s = "x"
  char s[2] = "x";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(VAR, type);
}
END_TEST

START_TEST(test_s21_get_token_22) {
  // s = "sin(x+2)"
  char s[9] = "sin(x+2)";
  char *ptr = s;
  enum type_t type = 0;
  double value = 0;

  int got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(SIN, type);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(OPEN, type);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(VAR, type);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(SUM, type);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(2, value, EPS);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(1, got_int);
  ck_assert_int_eq(CLOSE, type);

  got_int = get_token(&ptr, &type, &value);
  ck_assert_int_eq(0, got_int);
}
END_TEST

START_TEST(test_s21_parse_23) {
  // s = ""
  char s[20] = "";
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_24) {
  // s = "b"
  char s[20] = "b";
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_25) {
  // s = "1"
  char s[20] = "1";
  enum type_t type;
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(1, got, EPS);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_26) {
  // s = "tanx"
  char s[20] = "tanx";
  enum type_t type;
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(VAR, type);
  got_int = pop(rpn, &type, NULL);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(TAN, type);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_27) {
  // s = "sin."
  char s[20] = "sin.";
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_28) {
  // s = "sin.5"
  char s[20] = "sin.5";
  enum type_t type;
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(0.5, got, EPS);
  got_int = pop(rpn, &type, NULL);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(SIN, type);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_29) {
  // s = "10^2+atan3.5"
  char s[20] = "10^2+atan3.5";
  enum type_t type;
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(10, got, EPS);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(2, got, EPS);
  got_int = pop(rpn, &type, NULL);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(POW, type);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(3.5, got, EPS);
  got_int = pop(rpn, &type, NULL);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(ATAN, type);
  got_int = pop(rpn, &type, NULL);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(SUM, type);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_30) {
  // s = "-1"
  char s[20] = "-1";
  enum type_t type;
  double got = 0;
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(0, got_int);
  got_int = pop(rpn, &type, &got);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(NUM, type);
  ck_assert_double_eq_tol(got, 1, EPS);
  got_int = pop(rpn, &type, NULL);
  ck_assert_int_eq(0, got_int);
  ck_assert_int_eq(UMINUS, type);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

START_TEST(test_s21_parse_31) {
  // s = "((())"
  char s[20] = "((())";
  stack *rpn = init();
  int got_int = parse(s, rpn);

  ck_assert_int_eq(1, got_int);

  destroy_stack(rpn);
  free(rpn);
}
END_TEST

Suite *test_s21_parse(void) {
  Suite *s = suite_create("===== S21_PARSE =====");
  TCase *tc = tcase_create("s21_parse");

  tcase_add_test(tc, test_s21_remove_spaces_0);
  tcase_add_test(tc, test_s21_remove_spaces_1);
  tcase_add_test(tc, test_s21_remove_spaces_2);
  tcase_add_test(tc, test_s21_remove_spaces_3);
  tcase_add_test(tc, test_s21_remove_spaces_4);
  tcase_add_test(tc, test_s21_remove_spaces_5);
  tcase_add_test(tc, test_s21_remove_spaces_6);
  tcase_add_test(tc, test_s21_remove_spaces_7);
  tcase_add_test(tc, test_s21_remove_spaces_8);
  tcase_add_test(tc, test_s21_is_dbl_8);
  tcase_add_test(tc, test_s21_is_dbl_9);
  tcase_add_test(tc, test_s21_is_dbl_10);
  tcase_add_test(tc, test_s21_is_dbl_11);
  tcase_add_test(tc, test_s21_is_dbl_12);
  tcase_add_test(tc, test_s21_is_dbl_13);
  tcase_add_test(tc, test_s21_is_dbl_14);
  tcase_add_test(tc, test_s21_get_token_15);
  tcase_add_test(tc, test_s21_get_token_16);
  tcase_add_test(tc, test_s21_get_token_17);
  tcase_add_test(tc, test_s21_get_token_18);
  tcase_add_test(tc, test_s21_get_token_19);
  tcase_add_test(tc, test_s21_get_token_20);
  tcase_add_test(tc, test_s21_get_token_21);
  tcase_add_test(tc, test_s21_get_token_22);
  tcase_add_test(tc, test_s21_parse_23);
  tcase_add_test(tc, test_s21_parse_24);
  tcase_add_test(tc, test_s21_parse_25);
  tcase_add_test(tc, test_s21_parse_26);
  tcase_add_test(tc, test_s21_parse_27);
  tcase_add_test(tc, test_s21_parse_28);
  tcase_add_test(tc, test_s21_parse_29);
  tcase_add_test(tc, test_s21_parse_30);
  tcase_add_test(tc, test_s21_parse_31);
  suite_add_tcase(s, tc);

  return s;
}
