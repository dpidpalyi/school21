#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (rows > 0 && columns > 0) {
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = calloc(columns, sizeof(double));
    result->rows = rows;
    result->columns = columns;
  } else
    status = ERROR;

  return status;
}
