#include "../s21_matrix.h"

void swap_rows(double **matr, int k, int l) {
  double *temp;
  temp = matr[k];
  matr[k] = matr[l];
  matr[l] = temp;
}

double det(double **matr, int m) {
  double dt = 1.;
  for (int i = 0; i < m; i++) {
    int k = i;
    for (int j = i + 1; j < m; j++)
      if (fabs(matr[j][i]) > fabs(matr[k][i])) k = j;
    if (fabs(matr[k][i]) < EPS) return 0.;
    swap_rows(matr, i, k);
    if (i != k) dt = -dt;
    dt *= matr[i][i];
    for (int j = i + 1; j < m; j++) matr[i][j] /= matr[i][i];
    for (int j = 0; j < m; j++)
      if (j != i && fabs(matr[j][i]) > EPS)
        for (int l = i + 1; l < m; l++) matr[j][l] -= matr[i][l] * matr[j][i];
  }
  return dt;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  if (!s21_check_matrix(A))
    status = ERROR;
  else if (A->rows != A->columns)
    status = CALC_ERROR;
  else {
    matrix_t T = {};
    s21_create_matrix(A->rows, A->rows, &T);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->rows; j++) T.matrix[i][j] = A->matrix[i][j];
    *result = det(T.matrix, T.rows);
    s21_remove_matrix(&T);
  }

  return status;
}
