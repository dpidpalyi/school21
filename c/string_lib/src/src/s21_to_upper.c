#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  char *copy_str = S21_NULL;
  if (str) {
    copy_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
  }
  if (copy_str) {
    s21_size_t len = s21_strlen(str);
    s21_strncpy(copy_str, str, len + 1);
    for (s21_size_t i = 0; i < len; i++)
      if ('a' <= str[i] && str[i] <= 'z') copy_str[i] += ('A' - 'a');
  }
  return (void *)copy_str;
}