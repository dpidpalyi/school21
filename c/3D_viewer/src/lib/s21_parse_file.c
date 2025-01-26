#define _POSIX_C_SOURCE 200809L

#include "s21_parse_file.h"

int s21_parse_file(char *path, Data *model) {
  setlocale(LC_ALL, "C");
  int err = 0;
  FILE *file = fopen(path, "r+");
  if (file) {
    if (s21_first_file_read(file, model)) {
      err = BAD_FORMAT;
    } else {
      if (s21_create_matrix_old(model->count_of_vertexes + 1, 3,
                                &model->matrix_3d) ||
          s21_create_polygons(model->count_of_facets + 1, &model->polygons)) {
        err = NOT_ENOUGH_MEMORY;
      } else
        err = s21_second_file_read(file, model);
      fclose(file);
    }
  } else
    err = NO_FILE;

  return err;
}

int s21_first_file_read(FILE *file, Data *model) {
  char *s = NULL;
  size_t len = 0;
  while (getline(&s, &len, file) > 0) {
    if (s[0] == 'v' && s[1] == ' ')
      model->count_of_vertexes++;
    else if (s[0] == 'f' && s[1] == ' ')
      model->count_of_facets++;
  }
  free(s);

  return (!model->count_of_vertexes || !model->count_of_facets);
}

int s21_second_file_read(FILE *file, Data *model) {
  char *p = NULL, *endptr = NULL, *s = NULL;
  size_t len = 0;
  rewind(file);
  int err = 0, v = 1, f = 1, negate = 0;
  while (getline(&s, &len, file) > 0) {
    p = s;
    if (p[0] == 'v' && p[1] == ' ') {
      if (sscanf(p, "v %lf %lf %lf", &model->matrix_3d.matrix[v][0],
                 &model->matrix_3d.matrix[v][1],
                 &model->matrix_3d.matrix[v][2]) != 3) {
        err = BAD_FORMAT;
        break;
      } else {
        s21_find_max_min(v, model);
        ++v;
      }
    } else if (p[0] == 'f' && p[1] == ' ') {
      if (s21_check_facets_string(p)) {
        err = BAD_FORMAT;
        break;
      } else {
        for (++p; *p == ' '; ++p)
          ;
        if (*p == '-')
          negate = 1;
        else
          negate = 0;
        model->polygons[f].number_of_vertexes_in_facets =
            s21_count_vertexes_in_facets(p);
        if (model->polygons[f].number_of_vertexes_in_facets > 2) {
          if (s21_create_facets(model->polygons[f].number_of_vertexes_in_facets,
                                &model->polygons[f].vertexes)) {
            err = NOT_ENOUGH_MEMORY;
            break;
          } else {
            for (int i = 0;
                 p && i < model->polygons[f].number_of_vertexes_in_facets;
                 i++) {
              model->polygons[f].vertexes[i] = strtol(p, &endptr, 10);
              p = endptr;
              p = strchr(p, ' ');
              if (p) p = strpbrk(p, "0123456789-");
              if (negate) {
                if (model->polygons[f].vertexes[i] >= 0 ||
                    (v + model->polygons[f].vertexes[i] - 1 < 0)) {
                  err = BAD_FORMAT;
                  break;
                } else {
                  model->polygons[f].vertexes[i] += v;
                }
              } else if (model->polygons[f].vertexes[i] >
                             model->count_of_vertexes ||
                         model->polygons[f].vertexes[i] < 1) {
                err = BAD_FORMAT;
                break;
              }
            }
            ++f;
          }
        } else {
          err = BAD_FORMAT;
          break;
        }
      }
    }
  }
  free(s);
  if (err) s21_remove_model(model);
  return err;
}

void s21_init_max_min(Data *model) {
  for (int i = 0; i < 3; ++i) {
    model->mx[i] = DBL_MIN;
    model->mn[i] = DBL_MAX;
  }
}

void s21_find_max_min(int v, Data *model) {
  for (int i = 0; i < 3; ++i) {
    if (model->matrix_3d.matrix[v][i] > model->mx[i])
      model->mx[i] = model->matrix_3d.matrix[v][i];
    if (model->matrix_3d.matrix[v][i] < model->mn[i])
      model->mn[i] = model->matrix_3d.matrix[v][i];
  }
}

int s21_count_vertexes_in_facets(char *s) {
  int res = 0, temp;
  char *endptr = NULL, *p = s;
  while (p) {
    if (sscanf(p, "%d", &temp) == 1) {
      ++res;
      strtol(p, &endptr, 10);
      p = endptr;
    } else {
      if ((p = (strchr(p, ' ')))) p = strpbrk(p, "0123456789");
    }
  }

  return res;
}

int s21_check_facets_string(char *s) {
  int err = 0;
  if (strspn(s, " -f0123456789/\n\r") < strlen(s)) err = 1;
  return err;
}

int s21_create_facets(int n, int **vertexes) {
  int status = 0;
  *vertexes = calloc(n, sizeof(int));
  if (*vertexes == NULL) status = 1;

  return status;
}

int s21_create_polygons(int n, polygon_t **result) {
  int status = 0;
  *result = calloc(n, sizeof(polygon_t));
  if (*result == NULL) status = 1;

  return status;
}

int s21_create_matrix_old(int rows, int columns, matrix_t *result) {
  int status = 0;
  result->matrix = calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    status = 1;
  } else {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        status = 1;
        break;
      }
    }
  }
  result->rows = rows;
  result->cols = columns;

  return status;
}

void s21_remove_matrix_old(matrix_t *A) {
  for (int j = 0; j < A->rows; j++) free(A->matrix[j]);
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->cols = 0;
}

void s21_remove_model(Data *model) {
  s21_remove_matrix_old(&model->matrix_3d);
  for (int i = 0; i < model->count_of_facets + 1; i++)
    free(model->polygons[i].vertexes);
  free(model->polygons);
}
