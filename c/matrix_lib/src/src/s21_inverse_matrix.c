#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (!s21_check_matrix(A))
    status = ERROR;
  else if (A->rows != A->columns)
    status = CALC_ERROR;
  else {
    double det;
    s21_determinant(A, &det);
    if (fabs(det) < EPS)
      status = CALC_ERROR;
    else {
      matrix_t M = {};
      matrix_t T = {};
      s21_calc_complements(A, &M);
      s21_transpose(&M, &T);
      s21_mult_number(&T, 1 / det, result);
      s21_remove_matrix(&M);
      s21_remove_matrix(&T);
    }
  }

  return status;
}
