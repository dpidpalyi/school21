#ifndef S21_MODEL_H
#define S21_MODEL_H

/**
 * @file s21_model.h
 *
 * @brief Custom implementation to store models data
 *
 */

/**
 * @struct matrix
 * @brief Structure to store matrix of vertexes
 */
typedef struct matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

/**
 * @struct polygon
 * @brief Structure to store facets of model
 */
typedef struct polygon {
  int *vertexes;
  int number_of_vertexes_in_facets;
} polygon_t;

/**
 * @struct data
 * @brief Structure to store model's data
 */
typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
  double mx[3];
  double mn[3];
} Data;

#endif
