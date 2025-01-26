#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  memset(dst, 0, sizeof(s21_decimal));
  if (src < 0) {
    s21_set_bit(dst, 127, 1);
    src = -src;
  }
  dst->bits[0] = src;

  return 0;
}
