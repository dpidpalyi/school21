#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; (i < n) && (str2[i] != '\0' || str1[i] != '\0'); i++) {
    res = str1[i] - str2[i];
    if (res) break;
  }
  return res;
}
