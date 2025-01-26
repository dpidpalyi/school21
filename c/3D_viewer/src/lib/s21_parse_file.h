#ifndef S21_PARSE_FILE_H
#define S21_PARSE_FILE_H
#define NO_FILE 1
#define BAD_FORMAT 2
#define NOT_ENOUGH_MEMORY 3

#include <float.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file s21_parse_file.h
 *
 * @brief Main task is to parse obj file and translate it to model.
 *
 */

/**
 * @brief Main function to parse obj file
 *
 * @param path to obj file wich need to parse
 * @param Data model to store vertexes and facets
 * @return error if bad input file
 */
int s21_parse_file(char *path, Data *model);

/**
 * @brief Checks obj file and counts vertexes and facets in it
 *
 * @param obj file to check
 * @param model to store data
 * @return error if no vertexes of facets exist
 */
int s21_first_file_read(FILE *file, Data *model);

/**
 * @brief Checks obj file for correct format for vertexes and facets
 *
 * @param obj file to check
 * @param model to store data
 * @return error if bad format file found
 */
int s21_second_file_read(FILE *file, Data *model);

/**
 * @brief Init max and min with DBL_MIN and DBL_MAX
 *
 * @param model to init max and min vertexes
 */
void s21_init_max_min(Data *model);
/**
 * @brief Finds max and min coordinates for future scale
 *
 * @param v for current index to search
 * @param model to search max and min vertexes
 */
void s21_find_max_min(int v, Data *model);

/**
 * @brief Counts vertexes in each facets to allocate memory
 *
 * @param line with vertexes in format 'f 1 2 3'
 * @return number of vertexes in facet
 */
int s21_count_vertexes_in_facets(char *s);

/** @brief Checks that facets line consist only with correct symbols
 *
 * @param line with vertexes in format 'f 1 2 3'
 * @return error if bad format of facets found
 */
int s21_check_facets_string(char *s);

/** @brief Creates array of vertexes in facet
 *
 * @param n for numbers of vertexes
 * @param array to store vertexes
 * @return error if can't allocate memory
 */
int s21_create_facets(int n, int **vertexes);

/** @brief Creates array of polygons
 *
 * @param n for numbers of facets
 * @param array to store facets
 * @return error if can't allocate memory
 */
int s21_create_polygons(int n, polygon_t **result);

/** @brief Creates matrix to store vertexes coordinates
 *
 * @param rows for vertexes
 * @param columns for x, y, z coordinates
 * @matrix to store matrix_t type
 * @return error if can't allocate memory
 */
int s21_create_matrix_old(int rows, int columns, matrix_t *result);

/** @brief Free memory for matrix
 *
 * @param matrix to free
 */
void s21_remove_matrix_old(matrix_t *A);

/** @brief Free memory for model
 *
 * @param model to free
 */
void s21_remove_model(Data *model);

#ifdef __cplusplus
}
#endif

#endif
