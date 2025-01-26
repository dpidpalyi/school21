#ifndef S21_CAT_H
#define S21_CAT_H
#include <stdio.h>

typedef enum {
  NUMBER_NONBLANK,
  NUMBER,
  SHOW_NONPRINTING,
  SHOW_ENDS,
  SQUEEZE_BLANK,
  SHOW_TABS
} FLAGS;

int s21_cat(int argc, char **argv);
int parse_args(int argc, char **argv, int flags[6]);
int output_files(int argc, char **argv, int flags[6]);
void output_file(FILE *file, int flags[6], int *line, int *last, int *skip);
void non_print(int c);

#endif
