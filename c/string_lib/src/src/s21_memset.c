#include "../s21_string.h"

void *s21_memset(void *s, int c, s21_size_t n) {
  unsigned char uc = c;
  unsigned char *ptr = s;
  for (s21_size_t i = 0; i < n; i++) ptr[i] = uc;

  return (void *)ptr;
}
