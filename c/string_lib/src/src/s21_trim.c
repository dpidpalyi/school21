#include <stdlib.h>

#include "../s21_string.h"

void delete_left(char *copy_str, const char *src, const char *trim_chars) {
  s21_size_t len_src = s21_strlen(src), len_trm = s21_strlen(trim_chars);
  for (s21_size_t i = 0; i < len_src; i++) {
    int find = 1;
    for (s21_size_t j = 0; j < len_trm; j++) {
      if (src[i] == trim_chars[j]) {
        int index = 0;
        while (copy_str[index]) {
          copy_str[index] = copy_str[index + 1];
          index++;
        }
        break;
      }
      if (j == len_trm - 1) find = 0;
    }
    if (!find) break;
  }
}

void delete_right(char *copy_str, const char *trim_chars) {
  s21_size_t len_copy = s21_strlen(copy_str), len_trm = s21_strlen(trim_chars);
  for (int i = len_copy - 1; i >= 0; i--) {
    int find = 1;
    for (s21_size_t j = 0; j < len_trm; j++) {
      if (copy_str[i] == trim_chars[j]) {
        copy_str[i] = '\0';
        break;
      }
      if (j == len_trm - 1) find = 0;
    }
    if (!find) break;
  }
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *copy_str = S21_NULL;
  if (src) {
    char def_chars[7] = " \t\n\v\r\0";
    if (!trim_chars || !s21_strlen(trim_chars)) trim_chars = def_chars;
    copy_str = (char *)malloc((s21_strlen(src) + 1) * sizeof(char));
  }
  if (copy_str) {
    s21_size_t len_src = s21_strlen(src);
    s21_strncpy(copy_str, src, len_src + 1);
    delete_left(copy_str, src, trim_chars);
    delete_right(copy_str, trim_chars);
  }
  return (void *)copy_str;
}
