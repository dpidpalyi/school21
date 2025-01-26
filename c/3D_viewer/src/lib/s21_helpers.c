#include "s21_3DViewer.h"

void getCube(Data *data) {
  data->count_of_vertexes = 8;
  data->count_of_facets = 12;

  double temp_matrix[] = {1.0, -1.0, -1.0, 1.0,  -1.0, 1.0,  -1.0, -1.0,
                          1.0, -1.0, -1.0, -1.0, 1.0,  1.0,  -1.0, 1.0,
                          1.0, 1.0,  -1.0, 1.0,  1.0,  -1.0, 1.0,  -1.0};

  int temp_polygons[] = {2, 3, 4, 8, 7, 6, 5, 6, 2, 6, 7, 3, 3, 7, 8, 1, 4, 8,
                         1, 2, 4, 5, 8, 6, 1, 5, 2, 2, 6, 3, 4, 3, 8, 5, 1, 8};

  s21_create_matrix(data->count_of_vertexes + 1, 3, &data->matrix_3d);

  int count = 0;
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] = temp_matrix[count++];
    data->matrix_3d.matrix[i][1] = temp_matrix[count++];
    data->matrix_3d.matrix[i][2] = temp_matrix[count++];
  }

  count = 0;
  data->polygons = calloc(data->count_of_facets + 1, sizeof(polygon_t));
  for (int i = 1; i < data->count_of_facets + 1; i++) {
    data->polygons[i].vertexes = calloc(3, sizeof(int));
    data->polygons[i].number_of_vertexes_in_facets = 3;
    data->polygons[i].vertexes[0] = temp_polygons[count++];
    data->polygons[i].vertexes[1] = temp_polygons[count++];
    data->polygons[i].vertexes[2] = temp_polygons[count++];
  }
}

// void CreateAndPrintData(Data *data) {
//   for (int i = 1; i < 9; i++) {
//     printf("v: %.1lf %.1lf %.1lf\n", data->matrix_3d.matrix[i][0],
//            data->matrix_3d.matrix[i][1], data->matrix_3d.matrix[i][2]);
//   }
//   printf("\n");
//   for (int j = 1; j < 13; j++) {
//     printf("f: %d %d %d\n", data->polygons[j].vertexes[0],
//            data->polygons[j].vertexes[1], data->polygons[j].vertexes[2]);
//   }
// }

// void DataFree(Data *data) {
//   s21_remove_matrix(&data->matrix_3d);

//   for (int i = 0; i < data->count_of_facets + 1; i++)
//     free(data->polygons[i].vertexes);

//   free(data->polygons);
// }

int s21_create_matrix(int rows, int cols, matrix_t *result) {
  int flag = 0;

  if (rows <= 0 || cols <= 0) flag = 1;

  if (flag == 0) {
    result->matrix = (double **)calloc(rows, sizeof(double *));

    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(cols, sizeof(double));
    }

    result->cols = cols;
    result->rows = rows;
  }

  return flag;
}

// void s21_remove_matrix(matrix_t *A) {
//   for (int i = 0; i < A->rows; i++) {
//     free(A->matrix[i]);
//   }
//   free(A->matrix);
//   A->matrix = NULL;

//   A->rows = 0;
//   A->cols = 0;
// }

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 1, rows = A->rows, cols = A->cols;

  if (check_matrix(rows, cols, A) || check_matrix(rows, cols, B)) {
    flag = 0;
  }

  if (flag == 1) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.000001) {
          flag = 0;
          break;
        }
      }
      if (flag == 0) break;
    }
  }

  return flag;
}

int check_matrix(int rows, int cols, matrix_t *A) {
  int flag = 0;

  if (A->matrix == NULL) {
    flag = 2;
  } else if (A->rows != rows || A->cols != cols) {
    flag = 1;
  }

  return flag;
}

// Эта часть нужна для компиляции на Windows, т.к. на mingw нет этой библиотеки
// Компиляции на Linux вроде бы никак не мешает
// ssize_t getline(char **restrict buffer, size_t *restrict size,
//                 FILE *restrict fp) {
//   register int c;
//   register char *cs = NULL;

//   if (cs == NULL) {
//     register int length = 0;
//     while ((c = getc(fp)) != EOF) {
//       cs = (char *)realloc(cs, ++length+1);
//       if ((*(cs + length - 1) = c) == '\n') {
//         *(cs + length) = '\0';
//         *buffer = cs;
//         break;
//       }
//     }
//     return (ssize_t)(*size = length);
//   } else {
//     while (--(*size) > 0 && (c = getc(fp)) != EOF) {
//       if ((*cs++ = c) == '\n')
//         break;
//     }
//     *cs = '\0';
//   }
//   return (ssize_t)(*size=strlen(*buffer));
// }
