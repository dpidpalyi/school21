#ifndef TEST_S21_MATH_H
#define TEST_S21_MATH_H

#define TEST_EPS 1e-6

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_math.h"

Suite *test_s21_abs(void);
Suite *test_s21_acos(void);
Suite *test_s21_asin(void);
Suite *test_s21_atan(void);
Suite *test_s21_ceil(void);
Suite *test_s21_cos(void);
Suite *test_s21_exp(void);
Suite *test_s21_fabs(void);
Suite *test_s21_floor(void);
Suite *test_s21_fmod(void);
Suite *test_s21_log(void);
Suite *test_s21_pow(void);
Suite *test_s21_sin(void);
Suite *test_s21_sqrt(void);
Suite *test_s21_tan(void);

#endif
