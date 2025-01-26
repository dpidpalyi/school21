#include "s21_3DViewer.h"

void move_all(matrix_t *A, double x, double y, double z) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] += x;
    A->matrix[i][1] += y;
    A->matrix[i][2] += z;
  }
}

void move_x(matrix_t *A, double x) {
  for (int i = 0; i < A->rows; i++) A->matrix[i][0] += x;
}

void move_y(matrix_t *A, double y) {
  for (int i = 0; i < A->rows; i++) A->matrix[i][1] += y;
}

void move_z(matrix_t *A, double z) {
  for (int i = 0; i < A->rows; i++) A->matrix[i][2] += z;
}

void rotation_x(matrix_t *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double temp_y = A->matrix[i][1];
    double temp_z = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * temp_y + sin(angle) * temp_z;
    A->matrix[i][2] = sin(angle) * -temp_y + cos(angle) * temp_z;
  }
}

void rotation_y(matrix_t *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double temp_x = A->matrix[i][0];
    double temp_z = A->matrix[i][2];
    A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
    A->matrix[i][2] = sin(angle) * -temp_x + cos(angle) * temp_z;
  }
}

void rotation_z(matrix_t *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double temp_x = A->matrix[i][0];
    double temp_y = A->matrix[i][1];
    A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_y;
    A->matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_x;
  }
}

int scale_all(matrix_t *A, double x, double y, double z) {
  int flag = 0;
  if (x == 0 || y == 0 || z == 0) {
    flag = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      A->matrix[i][0] *= x;
      A->matrix[i][1] *= y;
      A->matrix[i][2] *= z;
    }
  }

  return flag;
}

int scale_x(matrix_t *A, double x) {
  int flag = 0;
  if (x == 0) {
    flag = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      A->matrix[i][0] *= x;
    }
  }

  return flag;
}

int scale_y(matrix_t *A, double y) {
  int flag = 0;
  if (y == 0) {
    flag = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      A->matrix[i][1] *= y;
    }
  }

  return flag;
}

int scale_z(matrix_t *A, double z) {
  int flag = 0;
  if (z == 0) {
    flag = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      A->matrix[i][2] *= z;
    }
  }

  return flag;
}
