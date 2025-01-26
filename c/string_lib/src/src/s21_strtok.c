#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  char *token = S21_NULL;
  static char *s;
  if (str) s = str;
  for (; *s && s21_strchr(delim, *s); s++)
    ;
  if (*s) {
    token = s;
    for (; *s && !s21_strchr(delim, *s); s++)
      ;
    if (*s) {
      *s = 0;
      s++;
    }
  }

  return token;
}
