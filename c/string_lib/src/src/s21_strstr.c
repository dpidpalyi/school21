#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *s = S21_NULL;
  s21_size_t n = s21_strlen(needle);
  int diff = s21_strlen(haystack) - n;
  if (diff >= 0)
    for (int i = 0; i <= diff; i++, haystack++)
      if ((!s21_memcmp(haystack, needle, n))) {
        s = (char *)haystack;
        break;
      }

  return s;
}
