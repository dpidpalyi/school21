#ifndef TEST_S21_3DVIEWER_H
#define TEST_S21_3DVIEWER_H

#include <check.h>
#include <stdio.h>

#include "../lib/s21_3DViewer.h"

#define EPS 1e-6

Suite *test_s21_parse_file(void);
Suite *test_s21_transformations(void);

#endif
