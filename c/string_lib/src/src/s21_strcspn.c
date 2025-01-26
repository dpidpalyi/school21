#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len1 = s21_strlen(str1), len2 = s21_strlen(str2), i, j;
  int find = 0;
  for (i = 0; i < len1; i++) {
    for (j = 0; j < len2; j++)
      if (str1[i] == str2[j]) find = 1;
    if (find) break;
  }
  return i;
}
