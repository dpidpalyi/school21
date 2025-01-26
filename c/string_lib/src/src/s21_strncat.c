#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i, j = s21_strlen(dest);
  for (i = 0; i < n && src[i] != '\0'; i++) dest[j + i] = src[i];
  dest[j + i] = '\0';
  return dest;
}
