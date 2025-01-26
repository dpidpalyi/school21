#ifndef S21_PARSE_H
#define S21_PARSE_H

#include <stdio.h>

#include "stack.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file parse.h
 *
 * @brief Main task is to parse string math expression to RPN.
 *
 */

/**
 * @brief Main function to parse math expression
 *
 * @param str string with math expression
 * @param rpn stack to store math expression in RPN
 * @return error if bad input math expression
 */
int parse(char *str, stack *rpn);

/**
 * @brief Checks if lexem is function (sin, cos, etc..)
 *
 * @param type lexem's type
 * @return if lexem is function
 */
int is_func(enum type_t type);

/**
 * @brief Checks if lexem is operator (+, -, mod, etc..)
 *
 * @param type lexem's type
 * @return if lexem is operator
 */
int is_operator(enum type_t type);

/**
 * @brief Dijsktra Shunting yard algorithm for operators order
 *
 * @param rpn stack to store final RPN expression
 * @param temp stack to store temp lexems with bigger priority
 * @param type current lexem's type
 * @param unary can be current lexem unary
 */
void evaluate_operators(stack *rpn, stack *temp, enum type_t type, int unary);

/**
 * @brief Dijkstra Shunting yard alorithm for brackets
 *
 * @param rpn stack to store final RPN expression
 * @param temp stack to store temp lexems
 * @return error with wrong brackets order
 */
int evaluate_brackets(stack *rpn, stack *temp);

/**
 * @brief Out all operators to RPN from temp stack
 *
 * @param rpn stack to store final RPN expression
 * @param temp stack with operators
 * @return error if unnecessary lexems finds in stack
 */
int clean_stack(stack *rpn, stack *temp);

/**
 * @brief Finds lexem at the start of the string
 *
 * @param **ptr move string pointer when find lexem
 * @param type store finded lexem in type
 * @param value store finded value if lexem is NUM
 * @return error if can't find valid lexems
 */
int get_token(char **ptr, enum type_t *type, double *value);

/**
 * @brief Remove unnecessary spaces in math expression
 *
 * @param str input math expression
 */
void remove_spaces(char *str);

/**
 * @brief Checks if at the start of the string there is number
 *
 * @param str input string to check
 * @return if string is number
 */
int is_dbl(char *str);
// void print_rpn(stack *rpn);

#ifdef __cplusplus
}
#endif

#endif
