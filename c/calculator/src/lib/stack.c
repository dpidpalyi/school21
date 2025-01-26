#include "stack.h"

#include <stdio.h>

stack *init() {
  stack *s = malloc(sizeof(stack));
  s->top = NULL;

  return s;
}

void add(stack *s, enum type_t type, void *value) {
  element *e = malloc(sizeof(element));
  e->type = type;
  if (value) {
    e->value = malloc(sizeof(double));
    memcpy(e->value, value, sizeof(double));
  } else
    e->value = NULL;
  if (!s->top) {
    e->next = s->top;
    s->top = e;
  } else {
    element *temp = s->top;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = e;
    e->next = NULL;
  }
}

void push(stack *s, enum type_t type, void *value) {
  element *e = malloc(sizeof(element));
  e->type = type;
  if (value) {
    e->value = malloc(sizeof(double));
    memcpy(e->value, value, sizeof(double));
  } else
    e->value = NULL;
  e->next = s->top;
  s->top = e;
}

int pop(stack *s, enum type_t *type, void *value) {
  int err = 0;
  if (s->top) {
    element *e = s->top;
    if (value && e->value) memcpy(value, e->value, sizeof(double));
    *type = e->type;
    free(e->value);
    s->top = e->next;
    free(e);
  } else
    err = 1;

  return err;
}

void destroy_stack(stack *s) {
  enum type_t type;
  double n = 0;
  while (s->top) pop(s, &type, &n);
}

void copy_stack(stack *src, stack *dst) {
  element *e = src->top;
  while (e) {
    add(dst, e->type, e->value);
    e = e->next;
  }
}
