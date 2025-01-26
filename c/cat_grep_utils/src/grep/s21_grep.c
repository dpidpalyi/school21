#define _POSIX_C_SOURCE 200809L

#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) { return s21_grep(argc, argv); }

int s21_grep(int argc, char **argv) {
  int err = 0;
  if (argc == 1) return 1;
  FLAGS flags = {0};
  char *patterns = NULL;
  if (parse_args(argc, argv, &flags, &patterns) ||
      grep_files(argc, argv, &flags, patterns))
    err = 1;

  free(patterns);

  return err;
}

int parse_args(int argc, char **argv, FLAGS *flags, char **patterns) {
  int opt, err = 0;
  while (!err && (opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        err = add_pattern(patterns, optarg);
        break;
      case 'i':
        flags->cflags |= REG_ICASE;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;
        err = add_patterns_from_file(patterns, optarg);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        fprintf(stderr, "Usage: s21_grep [OPTION]... PATTERNS [FILE]...\n");
        err = 1;
    }
  }

  return err || check_args(argc, argv, flags, patterns);
}

int check_args(int argc, char **argv, FLAGS *flags, char **patterns) {
  int err = 0;
  if (!(flags->e || flags->f)) {
    if (optind == argc - 1)
      err = 1;
    else
      err = add_pattern(patterns, argv[optind++]);
  }
  // Need to copy the behavior of the original grep with flag -f and
  // empty patterns file.
  // When no -v flags exists, there is no output.
  // When -v exists, we need to output all lines, so we need to ignore -v.
  if (*patterns == NULL) {
    if (flags->f && !flags->v)
      err = 1;
    else {
      *patterns = malloc(1);
      (*patterns)[0] = 0;
      flags->v = 0;
    }
  }

  return err;
}

int add_pattern(char **patterns, const char *pattern) {
  int err = 0;
  size_t prev = 0;
  if (*patterns) prev = strlen(*patterns) + 3;
  size_t new_size = prev + strlen(pattern) + 1;
  char *temp = realloc(*patterns, new_size);
  if (temp == NULL) {
    fprintf(stderr, "Can't allocate enough memory.\n");
    err = 1;
  } else {
    *patterns = temp;
    if (!prev)
      (*patterns)[0] = 0;
    else
      strcat(*patterns, "\\|");
    strcat(*patterns, pattern);
  }

  return err;
}

int add_patterns_from_file(char **patterns, const char *path) {
  int err = 0;
  FILE *file = fopen(path, "r+");
  if (file == NULL) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", path);
    err = 1;
  } else {
    char *pattern = NULL;
    size_t len = 0;
    while (getline(&pattern, &len, file) > 0) {
      if (pattern[strlen(pattern) - 1] == '\n')
        pattern[strlen(pattern) - 1] = 0;
      if ((err = add_pattern(patterns, pattern))) break;
    }
    free(pattern);
    fclose(file);
  }

  return err;
}

int grep_files(int argc, char **argv, FLAGS *flags, char *patterns) {
  int err = 0;
  regex_t re;
  if (compile_regex(&re, patterns, flags->cflags))
    err = 1;
  else {
    if (argc - optind == 1) flags->h = 1;
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r+");
      if (file == NULL) {
        if (!flags->s)
          fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[i]);
      } else {
        grep_file(file, argv[i], flags, &re);
        fclose(file);
      }
    }
  }
  regfree(&re);

  return err;
}

void grep_file(FILE *file, char *path, FLAGS *flags, regex_t *re) {
  int num = 0, count = 0;
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, file) > 0) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
    num++;
    if (flags->l || flags->c) {
      if ((!regexec(re, line, 0, NULL, 0)) ^ flags->v)  // matched
        count++;
    } else if (flags->o) {
      if (!flags->v) grep_o(path, line, flags, re, num);
    } else {
      grep_simple_num(path, line, flags, re, num);
    }
  }
  grep_suppress(path, flags, count);
  free(line);
}

void grep_o(char *path, char *line, FLAGS *flags, regex_t *re, int num) {
  char *s = line;
  regmatch_t pmatch;
  while (1) {
    if (regexec(re, s, 1, &pmatch, 0)) break;
    if (!flags->h) printf("%s:", path);
    if (flags->n) printf("%d:", num);
    printf("%.*s\n", (int)(pmatch.rm_eo - pmatch.rm_so), s + pmatch.rm_so);
    s += pmatch.rm_eo;
  }
}

void grep_simple_num(char *path, char *line, FLAGS *flags, regex_t *re,
                     int num) {
  if ((!regexec(re, line, 0, NULL, 0)) ^ flags->v) {  // matched
    if (!flags->h) printf("%s:", path);
    if (flags->n) printf("%d:", num);
    printf("%s\n", line);
  }
}

void grep_suppress(char *path, FLAGS *flags, int count) {
  if (flags->l) {
    if (count > 0) printf("%s\n", path);
  } else {
    if (flags->c) {
      if (!flags->h) printf("%s:", path);
      printf("%d\n", count);
    }
  }
}

int compile_regex(regex_t *re, const char *pattern, int cflags) {
  int status = regcomp(re, pattern, cflags);
  if (status != 0) {
    char err_msg[BUF_SIZE];
    regerror(status, re, err_msg, BUF_SIZE);
    fprintf(stderr, "s21_grep: %s\n", err_msg);
  }

  return status;
}
