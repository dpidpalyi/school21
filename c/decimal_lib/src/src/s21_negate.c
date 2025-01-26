#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  s21_set_bit(result, 127, !s21_get_bit(value, 127));

  return 0;
}
