#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>

int main(int argc, char **argv) { return s21_cat(argc, argv); }

int s21_cat(int argc, char **argv) {
  int err = 0;
  if (argc == 1) return 1;
  int flags[6] = {0};
  if (parse_args(argc, argv, flags) || output_files(argc, argv, flags)) err = 1;

  return err;
}

int parse_args(int argc, char **argv, int flags[6]) {
  int res, err = 0;
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  while ((res = getopt_long(argc, argv, "bneEstTv", long_options, NULL)) !=
             -1 &&
         !err) {
    switch (res) {
      case 'b':
        flags[NUMBER_NONBLANK] = 1;
        flags[NUMBER] = 0;
        break;
      case 'n':
        if (!flags[NUMBER_NONBLANK]) flags[NUMBER] = 1;
        break;
      case 'e':
        flags[SHOW_ENDS] = 1;
        flags[SHOW_NONPRINTING] = 1;
        break;
      case 'v':
        flags[SHOW_NONPRINTING] = 1;
        break;
      case 'E':
        flags[SHOW_ENDS] = 1;
        break;
      case 's':
        flags[SQUEEZE_BLANK] = 1;
        break;
      case 't':
        flags[SHOW_TABS] = 1;
        flags[SHOW_NONPRINTING] = 1;
        break;
      case 'T':
        flags[SHOW_TABS] = 1;
        break;
      default:
        err = 1;
        fprintf(stderr, "Usage: s21_cat [-bneEstTv] [FILE]...\n");
        break;
    }
  }

  return err;
}

int output_files(int argc, char **argv, int flags[6]) {
  int err = 0, line = 1;
  int last = '\n', skip = 0;
  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file) {
      output_file(file, flags, &line, &last, &skip);
      fclose(file);
    } else {
      fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
      err = 1;
    }
  }

  return err;
}

void output_file(FILE *file, int flags[6], int *line, int *last, int *skip) {
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (*last == '\n') {
      if (flags[SQUEEZE_BLANK] && c == '\n') {
        if (*skip) continue;
        *skip = 1;
      } else
        *skip = 0;
      if (flags[NUMBER] || (flags[NUMBER_NONBLANK] && c != '\n'))
        fprintf(stdout, "%6d\t", (*line)++);
    }
    if (c == '\n' && flags[SHOW_ENDS]) fprintf(stdout, "$");
    if (c == '\t' && flags[SHOW_TABS])
      fprintf(stdout, "^I");
    else if (flags[SHOW_NONPRINTING] && c != '\n' && c != '\t')
      non_print(c);
    else
      fprintf(stdout, "%c", c);
    *last = c;
  }
}

void non_print(int c) {
  if (c > 127) {
    fprintf(stdout, "M-");
    c -= 128;
  }
  if (c >= 0 && c < 32)
    fprintf(stdout, "^%c", c + 64);
  else if (c == 127)
    fprintf(stdout, "^?");
  else
    fprintf(stdout, "%c", c);
}
