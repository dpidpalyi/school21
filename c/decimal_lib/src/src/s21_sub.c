#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign = s21_get_bit(value_2, 127);
  if (sign)
    s21_set_bit(&value_2, 127, 0);
  else
    s21_set_bit(&value_2, 127, 1);
  int err = s21_add(value_1, value_2, result);
  return err;
}