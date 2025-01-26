#ifndef S21_STACK_H
#define S21_STACK_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file stack.h
 *
 * @brief Custom stack implementation to store lexems and values.
 *
 */

/**
 * @enum type_t
 * @brief Enumerate for different lexems(tokens) in math expression.
 */
enum type_t {
  NUM,
  VAR,
  OPEN,
  CLOSE,
  SUM,
  SUB,
  MUL,
  DIV,
  POW,
  MOD,
  UPLUS,
  UMINUS,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
};

/**
 * @struct element
 * @brief Structure of the stack element
 */
typedef struct element {
  /**
   * @brief Type of the stack element (NUM, VAR, COS etc.)
   */
  enum type_t type;
  /**
   * @brief Value of the element (if NUM, there will be double);
   */
  void *value;
  /**
   * @brief Pointer to the next element;
   */
  struct element *next;
} element;

/**
 * @struct stack
 * @brief Pointer to the top(head) of the stack for simplicity work with it.
 */
typedef struct stack {
  element *top;
} stack;

/**
 * @brief Creates a new stack
 *
 * @return pointer to created stack
 */
stack *init();

/**
 * @brief Add element to the end of the stack
 *
 * @param s top pointer
 * @param type lexem's type
 * @param value value to store in the element
 */
void add(stack *s, enum type_t type, void *value);

/**
 * @brief Push element to the top of the stack
 *
 * @param s top pointer
 * @param type lexem's type
 * @param value to store value in the element
 */
void push(stack *s, enum type_t type, void *value);

/**
 * @brief Pop element from the top of the stack
 *
 * @param s top pointer
 * @param type lexem's type where to write it
 * @param value where to write element's value
 * @return error if stack is empty
 */
int pop(stack *s, enum type_t *type, void *value);

/**
 * @brief Destroy all elements from stack
 *
 * @param s top pointer
 */
void destroy_stack(stack *s);

/**
 * @brief Copy all elements from one to another stack
 *
 * @param src copy from
 * @param dst copy to
 */
void copy_stack(stack *src, stack *dst);

#ifdef __cplusplus
}
#endif

#endif
