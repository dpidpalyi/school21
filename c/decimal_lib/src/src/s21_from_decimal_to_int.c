#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  memset(dst, 0, sizeof(int));
  s21_big big = s21_from_decimal_to_big(&src);
  for (; big.scale > 0; big.scale--) {
    s21_del_10(&big);
  }
  int sign = s21_get_bit(src, 127);
  if (big.bits[2] || big.bits[1] || big.bits[0] > MINUS ||
      (big.bits[0] == MINUS && !sign)) {
    err = 1;
  } else {
    *dst = big.bits[0];
    if (sign) *dst *= -1;
  }

  return err;
}
