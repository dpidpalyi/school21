#ifndef TEST_S21_STRING_H
#define TEST_S21_STRING_H
#define _GNU_SOURCE

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *test_s21_memchr(void);
Suite *test_s21_memcmp(void);
Suite *test_s21_memcpy(void);
Suite *test_s21_memset(void);
Suite *test_s21_strncat(void);
Suite *test_s21_strchr(void);
Suite *test_s21_strncmp(void);
Suite *test_s21_strncpy(void);
Suite *test_s21_strcspn(void);
Suite *test_s21_strerror(void);
Suite *test_s21_strlen(void);
Suite *test_s21_strpbrk(void);
Suite *test_s21_strrchr(void);
Suite *test_s21_strstr(void);
Suite *test_s21_strtok(void);
Suite *test_s21_sscanf(void);
Suite *test_s21_sprintf(void);
Suite *test_s21_to_upper(void);
Suite *test_s21_to_lower(void);
Suite *test_s21_insert(void);
Suite *test_s21_trim(void);

#endif
