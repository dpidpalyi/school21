#include "../s21_decimal.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int sign1, sign2, result_equal = -1, comparison = 0;
  sign1 = s21_get_bit(num1, 127);
  sign2 = s21_get_bit(num2, 127);
  if ((sign1 != 0 && sign2 == 0) || (sign1 == 0 && sign2 != 0)) {
    result_equal = s21_is_zero_nums(&num1, &num2, result_equal);
  } else {
    for (int i = 3; i >= 0; i--)
      if (num1.bits[i] != num2.bits[i]) {
        s21_big val1 = s21_from_decimal_to_big(&num1);
        s21_big val2 = s21_from_decimal_to_big(&num2);
        result_equal =
            s21_is_comparison_decimal(val1, val2, result_equal, comparison);
        break;
      } else
        result_equal = 1;
  }
  return result_equal;
}
