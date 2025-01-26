#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int eq = SUCCESS;
  if (s21_check_matrix(A) && s21_check_matrix(B) && s21_same_size(A, B)) {
    for (int i = 0; i < A->rows && eq; i++)
      for (int j = 0; j < A->columns && eq; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) eq = FAILURE;
  } else
    eq = FAILURE;

  return eq;
}
