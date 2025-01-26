#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  char *copy_str = S21_NULL;
  if (str) {
    copy_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
  }
  if (copy_str) {
    s21_size_t len = s21_strlen(str);
    s21_strncpy(copy_str, str, len + 1);
    for (s21_size_t i = 0; i < len; i++)
      if ('A' <= str[i] && str[i] <= 'Z') copy_str[i] += ('a' - 'A');
  }
  return (void *)copy_str;
}