#ifndef S21_CALC_H
#define S21_CALC_H

#include <math.h>
#include <stdlib.h>

#include "parse.h"
#include "stack.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file calc.h
 *
 * @brief Calculate RPN math expression
 *
 */

#define EPS 1e-7

/**
 * @brief Evaluates RPN math expression with or without VAR value
 *
 * @param rpn stack with RPN math expression
 * @param result stores the value of calculation
 * @param var value of the X variable
 * @return error if failed to evaluate wrong expression
 */
int eval(stack *rpn, double *result, double var);

/**
 * @brief Sum function
 */
double usum(double a, double b);

/**
 * @brief Subtraction function
 */
double usub(double a, double b);

/**
 * @brief Multiplication function
 */
double umul(double a, double b);

/**
 * @brief Division function
 */
double udiv(double a, double b);

/**
 * @brief Pow function
 */
double upow(double a, double b);

/**
 * @brief Module division function
 */
double umod(double a, double b);

/**
 * @brief Unary plus function
 */
double uplus(double a);

/**
 * @brief Unary minus function
 */
double uminus(double a);

/**
 * @brief Cos function
 */
double ucos(double a);

/**
 * @brief Sin function
 */
double usin(double a);

/**
 * @brief Tan function
 */
double utan(double a);

/**
 * @brief Acos function
 */
double uacos(double a);

/**
 * @brief Asin function
 */
double uasin(double a);

/**
 * @brief Atan function
 */
double uatan(double a);

/**
 * @brief Sqrt function
 */
double usqrt(double a);

/**
 * @brief Natural log function
 */
double uln(double a);

/**
 * @brief 10-th log function
 */
double ulog(double a);

#ifdef __cplusplus
}
#endif

#endif
