#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *ptr = S21_NULL;
  while (*str != '\0') {
    if (*str == c) {
      ptr = (char *)str;
      break;
    }
    str++;
  }
  if (c == '\0') ptr = (char *)str;
  return ptr;
}
