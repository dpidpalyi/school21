#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *ptr = S21_NULL;
  const unsigned char *s = str;
  unsigned char uc = c;
  while (n--) {
    if (*s == uc) {
      ptr = (void *)s;
      break;
    }
    s++;
  }

  return ptr;
}
