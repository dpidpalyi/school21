#ifndef TEST_S21_DECIMAL_H
#define TEST_S21_DECIMAL_H

#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

#define EPS 1e-6

Suite *test_s21_add(void);
Suite *test_s21_sub(void);
Suite *test_s21_mul(void);
Suite *test_s21_div(void);
Suite *test_s21_is_less(void);
Suite *test_s21_is_less_or_equal(void);
Suite *test_s21_is_greater(void);
Suite *test_s21_is_greater_or_equal(void);
Suite *test_s21_is_equal(void);
Suite *test_s21_is_not_equal(void);
Suite *test_s21_from_int_to_decimal(void);
Suite *test_s21_from_float_to_decimal(void);
Suite *test_s21_from_decimal_to_int(void);
Suite *test_s21_from_decimal_to_float(void);
Suite *test_s21_floor(void);
Suite *test_s21_round(void);
Suite *test_s21_truncate(void);
Suite *test_s21_negate(void);

#endif
