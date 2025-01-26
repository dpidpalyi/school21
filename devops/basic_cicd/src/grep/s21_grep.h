#ifndef S21_GREP_H
#define S21_GREP_H

#define BUF_SIZE 256
#include <regex.h>
#include <stdio.h>

typedef struct {
  int cflags;
  int e;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} FLAGS;

int s21_grep(int argc, char **argv);
int parse_args(int argc, char **argv, FLAGS *flags, char **patterns);
int check_args(int argc, char **argv, FLAGS *flags, char **patterns);
int add_pattern(char **patterns, const char *pattern);
int add_patterns_from_file(char **patterns, const char *path);
int grep_files(int argc, char **argv, FLAGS *flags, char *patterns);
void grep_file(FILE *file, char *path, FLAGS *flags, regex_t *re);
void grep_o(char *path, char *line, FLAGS *flags, regex_t *re, int num);
void grep_simple_num(char *path, char *line, FLAGS *flags, regex_t *re,
                     int num);
void grep_suppress(char *path, FLAGS *flags, int count);
int compile_regex(regex_t *re, const char *pattern, int cflags);

#endif
