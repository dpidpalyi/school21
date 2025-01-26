#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  memset(dst, 0, sizeof(s21_decimal));
  if ((fabs(src) > 0 && fabs(src) < 1e-28) || fabs(src) >= pow(2, 96) ||
      isnan(src) || isinf(src)) {
    err = 1;
  } else if (src != 0.0) {
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src *= -1;
    }
    char s[256] = "";
    sprintf(s, "%.6e", src);
    unsigned int_part, float_part = 0;
    int scale;
    sscanf(s, "%u.%ue%d", &int_part, &float_part, &scale);
    scale = -scale + 6;
    dst->bits[0] = int_part * 1000000 + float_part;
    s21_big big = s21_from_decimal_to_big(dst);
    if (scale < 0) {
      for (; scale < 0; scale++) s21_mul_10(&big);
    } else if (scale > 28) {
      uint64_t rem = 0;
      for (; scale > 28; scale--) rem = s21_del_10(&big);
      if (rem >= 5) big.bits[0] += 1;
    }
    big.scale = scale;
    s21_normalize_big(&big);
    *dst = s21_from_big_to_decimal(&big);
    s21_set_bit(dst, 127, sign);
  }

  return err;
}
