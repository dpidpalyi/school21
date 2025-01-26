#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "s21_model.h"

/**
 * @brief Create struct Data from example cube.obj file
 */
void CreateAndPrintData(Data *data);
void getCube(Data *data);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
void DataFree(Data *data);

// Стандартные функции из матриц
int s21_create_matrix(int rows, int cols, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int check_matrix(int rows, int cols, matrix_t *A);

#endif
