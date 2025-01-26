#ifndef S21_TRANSFORMATIONS_H
#define S21_TRANSFORMATIONS_H

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "s21_model.h"

/**
 * @file s21_transformations.h
 *
 * @brief Different actions with model transformations
 *
 */

/**
 * @brief Move an object in x, y, z coordinates
 * @param A matrix
 * @param x, y, z coordinates
 */
void move_all(matrix_t *A, double x, double y, double z);

/**
 * @brief Move an object in x coordinate
 * @param A matrix
 * @param x coordinate
 */
void move_x(matrix_t *A, double x);

/**
 * @brief Move an object in y coordinate
 * @param A matrix
 * @param y coordinate
 */
void move_y(matrix_t *A, double y);

/**
 * @brief Move an object in z coordinate
 * @param A matrix
 * @param z coordinate
 */
void move_z(matrix_t *A, double z);

/**
 * @brief Rotate an object in x coordinate
 * @param A matrix
 * @param angle coordinate
 */
void rotation_x(matrix_t *A, double angle);

/**
 * @brief Rotate an object in y coordinate
 * @param A matrix
 * @param angle coordinate
 */
void rotation_y(matrix_t *A, double angle);

/**
 * @brief Rotate an object in z coordinate
 * @param A matrix
 * @param angle coordinate
 */
void rotation_z(matrix_t *A, double angle);

/**
 * @brief Scale an object in x, y, z coordinates
 * @param A matrix
 * @param x, y, z coordinates
 */
int scale_all(matrix_t *A, double x, double y, double z);

/**
 * @brief Scale an object in x coordinate
 * @param A matrix
 * @param x coordinate
 */
int scale_x(matrix_t *A, double x);

/**
 * @brief Scale an object in y coordinate
 * @param A matrix
 * @param y coordinate
 */
int scale_y(matrix_t *A, double y);

/**
 * @brief Scale an object in z coordinate
 * @param A matrix
 * @param z coordinate
 */
int scale_z(matrix_t *A, double z);

#endif
