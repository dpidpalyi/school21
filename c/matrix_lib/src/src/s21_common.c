#include "../s21_matrix.h"

int s21_check_matrix(matrix_t *A) { return (A->rows > 0 && A->columns > 0); }

int s21_same_size(matrix_t *A, matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns);
}
