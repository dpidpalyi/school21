#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  memset(dst, 0, sizeof(float));
  for (int i = 0; i < 3; i++) *dst += src.bits[i] * pow(2, i * 32);
  unsigned scale = (src.bits[3] & SCALE) >> 16;
  *dst = *dst / pow(10, scale);
  if (s21_get_bit(src, 127)) *dst *= -1;

  return 0;
}
