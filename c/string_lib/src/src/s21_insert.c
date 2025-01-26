#include <stdlib.h>

#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (str && src && start_index <= (s21_strlen(src) + s21_strlen(str))) {
    result =
        (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
  }
  if (result) {
    s21_size_t len_src = s21_strlen(src), len_str = s21_strlen(str), i, j,
               res_index = start_index;
    s21_strncpy(result, src, len_src);
    for (i = 0; i < len_str; i++, res_index++) {
      for (j = len_src; j > res_index; j--)
        result[j + len_str - 1] = src[j - 1];
      result[res_index] = str[i];
    }
    result[(len_src + len_str)] = '\0';
  }
  return (void *)result;
}