#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ptr = S21_NULL;
  for (long i = s21_strlen(str); i >= 0; i--)
    if (str[i] == c) {
      ptr = (char *)(str + i);
      break;
    }

  return ptr;
}
