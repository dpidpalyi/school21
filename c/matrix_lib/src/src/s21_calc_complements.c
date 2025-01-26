#include "../s21_matrix.h"

void calc_minor(matrix_t *A, matrix_t *M, int row, int col) {
  for (int i = 0, k = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0, l = 0; j < A->rows; j++)
        if (j != col) {
          M->matrix[k][l] = A->matrix[i][j];
          l++;
        }
      k++;
    }
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (!s21_check_matrix(A))
    status = ERROR;
  else if (A->rows != A->columns)
    status = CALC_ERROR;
  else {
    s21_create_matrix(A->rows, A->rows, result);
    if (A->rows == 1) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      matrix_t M = {};
      s21_create_matrix(A->rows - 1, A->rows - 1, &M);
      double det;

      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->rows; j++) {
          calc_minor(A, &M, i, j);
          s21_determinant(&M, &det);
          result->matrix[i][j] = ((i + j) % 2 ? -1 : 1) * det;
        }

      s21_remove_matrix(&M);
    }
  }

  return status;
}
