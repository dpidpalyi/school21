#include "parse.h"

static const char *tokens[] = {
    "",      // NUM
    "x",     // VAR
    "(",     // OPEN
    ")",     // CLOSE
    "+",     // SUM
    "-",     // SUB
    "*",     // MUL
    "/",     // DIV
    "^",     // POW
    "mod",   // MOD
    "+",     // UPLUS
    "-",     // UMINUS
    "cos",   // COS
    "sin",   // SIN
    "tan",   // TAN
    "acos",  // ACOS
    "asin",  // ASIN
    "atan",  // ATAN
    "sqrt",  // SQRT
    "ln",    // LN
    "log"    // LOG
};

static const int priority[] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 1, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0,
};

int get_token(char **ptr, enum type_t *type, double *value) {
  int find = 0;
  for (size_t i = 1; !find && i < sizeof(tokens) / sizeof(char *); i++) {
    if (!strncmp(*ptr, tokens[i], strlen(tokens[i]))) {
      *ptr += strlen(tokens[i]);
      *type = i;
      find = 1;
    }
  }
  if (!find && is_dbl(*ptr) > 0) {
    char *endptr = NULL;
    *value = strtod(*ptr, &endptr);
    find = 1;
    *type = NUM;
    *ptr = endptr;
  }

  return find;
}

int parse(char *str, stack *rpn) {
  int err = 0, find = 0;
  remove_spaces(str);
  char *ptr = str;
  double value;
  enum type_t type;
  stack *temp = init();
  int unary = 1;
  while (*ptr && !err && (find = get_token(&ptr, &type, &value))) {
    if (type == NUM || type == VAR) {
      add(rpn, type, &value);
      unary = 0;
    }
    if (is_func(type) || type == OPEN) {
      push(temp, type, NULL);
      unary = 1;
    }
    if (is_operator(type)) {
      evaluate_operators(rpn, temp, type, unary);
      unary = 1;
    }
    if (type == CLOSE) {
      err = evaluate_brackets(rpn, temp);
      unary = 0;
    }
  }
  if (!find || is_func(type)) {
    err = 1;
  } else {
    err = clean_stack(rpn, temp);
  }

  destroy_stack(temp);
  free(temp);

  return err;
}

int is_func(enum type_t type) { return type > 11; }

int is_operator(enum type_t type) { return type > 3 && type < 12; }

void evaluate_operators(stack *rpn, stack *temp, enum type_t type, int unary) {
  enum type_t temp_type;
  if (unary && (type == SUM || type == SUB)) type += 6;  // UPLUS or UMINUS
  while (temp->top &&
         (priority[temp->top->type] > priority[type] ||
          ((priority[temp->top->type] == priority[type]) && !unary))) {
    pop(temp, &temp_type, NULL);
    add(rpn, temp_type, NULL);
  }
  push(temp, type, NULL);
}

int evaluate_brackets(stack *rpn, stack *temp) {
  enum type_t temp_type;
  int err = 0;
  while (temp->top && temp->top->type != OPEN) {
    pop(temp, &temp_type, NULL);
    add(rpn, temp_type, NULL);
  }
  if (!temp->top || temp->top->type != OPEN)
    err = 1;
  else {
    pop(temp, &temp_type, NULL);
    if (temp->top && is_func(temp->top->type)) {
      pop(temp, &temp_type, NULL);
      add(rpn, temp_type, NULL);
    }
  }

  return err;
}

int clean_stack(stack *rpn, stack *temp) {
  int err = 0;
  enum type_t temp_type;
  while (!err && temp->top) {
    if (temp->top->type == OPEN || temp->top->type == CLOSE)
      err = 1;
    else {
      pop(temp, &temp_type, NULL);
      add(rpn, temp_type, NULL);
    }
  }

  return err;
}

void remove_spaces(char *str) {
  if (*str) {
    char *dst = str;

    do {
      while (*dst == ' ') ++dst;
    } while ((*str++ = *dst++));
  }
}

int is_dbl(char *str) {
  double n;
  return sscanf(str, "%lf", &n);
}

// void print_rpn(stack *rpn) {
//  element *temp = rpn->top;
//  while (temp) {
//    if (temp->type == NUM)
//      printf("%.6lf ", *(double *)temp->value);
//    else if (temp->type == VAR)
//      printf("x ");
//    else
//      printf("%s%d ", tokens[temp->type], temp->type);
//    temp = temp->next;
//  }
//  printf("\n");
//}
