#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  return s21_erase_float_part(value, result, 0, 0);
}
