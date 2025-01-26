#include "../s21_decimal.h"

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int sign1 = s21_get_bit(num1, 127), sign2 = s21_get_bit(num2, 127),
      result_greater = -1, comparison = -1;
  s21_big val1 = s21_from_decimal_to_big(&num1),
          val2 = s21_from_decimal_to_big(&num2);
  if (sign1 && !sign2) {
    result_greater = 0;
  } else if (!sign1 && sign2) {
    result_greater = !s21_is_zero_nums(&num1, &num2, result_greater);
  } else if (sign1 && sign2) {
    for (int i = 3; i >= 0; i--)
      if (num1.bits[i] != num2.bits[i]) {
        comparison = 1;
        result_greater =
            s21_is_comparison_decimal(val1, val2, result_greater, comparison);
        break;
      } else
        result_greater = 0;
  } else
    result_greater =
        s21_is_comparison_decimal(val1, val2, result_greater, comparison);
  return result_greater;
}
