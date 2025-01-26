#include "../s21_decimal.h"

int s21_get_bit(s21_decimal number, unsigned int bit_index) {
  return (number.bits[bit_index / 32] >> (bit_index % 32)) & 1;
}

void s21_set_bit(s21_decimal *number, unsigned int bit_index,
                 unsigned int bit) {
  if (bit)
    number->bits[bit_index / 32] |= 1 << bit_index;
  else
    number->bits[bit_index / 32] &= ~(1 << bit_index);
}

s21_big s21_from_decimal_to_big(s21_decimal *src) {
  s21_big dst = {};
  dst.scale = (src->bits[3] & SCALE) >> 16;
  for (int i = 0; i < 3; i++) dst.bits[i] = src->bits[i] & F8;
  return dst;
}

s21_decimal s21_from_big_to_decimal(s21_big *src) {
  s21_decimal dst = {};
  dst.bits[3] = src->scale << 16;
  for (int i = 0; i < 3; i++) dst.bits[i] = src->bits[i] & F8;
  return dst;
}

void s21_normalize_big(s21_big *big) {
  s21_big cpy = {};
  for (int i = 0; i < 7; i++) cpy.bits[i] = big->bits[i];
  cpy.scale = big->scale;
  uint64_t rem = 0;
  while (!rem && cpy.scale) {
    rem = s21_del_10(&cpy);
    if (!rem) {
      cpy.scale--;
      for (int i = 0; i < 7; i++) big->bits[i] = cpy.bits[i];
      big->scale = cpy.scale;
    }
  }
}

uint64_t s21_del_10(s21_big *big) {
  uint64_t rem = 0;
  for (int i = 6; i >= 0; i--) {
    big->bits[i] += rem << 32;
    rem = big->bits[i] % 10;
    big->bits[i] /= 10;
  }

  return rem;
}

int s21_mul_10(s21_big *big) {
  int err = 0;
  for (int i = 0; i <= 6; i++) {
    big->bits[i] *= 10;
  }
  err = s21_clean_overflow(big);

  return err;
}

int s21_clean_overflow(s21_big *big) {
  int err = 0;
  uint64_t overflow = 0;
  for (int i = 0; i < 7; i++) {
    big->bits[i] += overflow;
    overflow = big->bits[i] >> 32;
    big->bits[i] &= F8;
  }

  if (overflow) err = 1;

  return err;
}

int s21_check_overflow(s21_big *big) {
  return big->bits[3] || big->bits[4] || big->bits[5] || big->bits[6];
}

int s21_erase_float_part(s21_decimal value, s21_decimal *result, int flr,
                         int rnd) {
  memset(result, 0, sizeof(s21_decimal));
  s21_big big = s21_from_decimal_to_big(&value);
  uint64_t rem_cpy = 0, rem;
  for (; big.scale > 0; big.scale--) {
    rem = s21_del_10(&big);
    if (rem) rem_cpy = rem;
  }
  int sign = s21_get_bit(value, 127);
  if (rem_cpy) {
    if ((sign && flr) || (rnd && rem_cpy >= 5)) big.bits[0] += 1;
    s21_clean_overflow(&big);
  }
  *result = s21_from_big_to_decimal(&big);
  if (sign) result->bits[3] |= MINUS;

  return 0;
}

int s21_iszero(s21_decimal *number) {
  if (number->bits[0] == 0 && number->bits[1] == 0 && number->bits[2] == 0)
    return 1;
  else
    return 0;
}

s21_big s21_reduction_to_denominator_mul(int exp, s21_big *num) {
  for (int i = 1; i <= exp; i++) s21_mul_10(num);
  return (*num);
}

void s21_comparison_exp(s21_big *num1, s21_big *num2) {
  if (num1->scale > num2->scale) {
    num2->scale = num1->scale - num2->scale;
    *num2 = s21_reduction_to_denominator_mul(num2->scale, num2);
  } else if (num1->scale < num2->scale) {
    num1->scale = num2->scale - num1->scale;
    *num1 = s21_reduction_to_denominator_mul(num1->scale, num1);
  }
}

int s21_is_comparison_decimal(s21_big num1, s21_big num2, int result,
                              int comparison) {
  if (num1.scale == num2.scale) {
    result = s21_comparison_bits(num1, num2, result, comparison);
  } else {
    s21_comparison_exp(&num1, &num2);
    result = s21_comparison_bits(num1, num2, result, comparison);
  }
  return result;
}

int s21_comparison_bits(s21_big num1, s21_big num2, int result,
                        int comparison) {
  for (int i = 6; i >= 0; i--)
    if (num1.bits[i] < num2.bits[i]) {
      if (comparison == 1) {
        result = 1;
        break;
      } else if (comparison == 0 || comparison == -1) {
        result = 0;
        break;
      }
    } else if (num1.bits[i] > num2.bits[i]) {
      if (comparison == -1) {
        result = 1;
        break;
      } else if (comparison == 0 || comparison == 1) {
        result = 0;
        break;
      }
    } else if (num1.bits[i] != num2.bits[i]) {
      if (comparison == 0) {
        result = 0;
        break;
      }
    } else if (num1.bits[i] == num2.bits[i]) {
      if (comparison == 0) {
        result = 1;
      } else if (comparison == 1 || comparison == -1) {
        result = 0;
      }
    }
  return result;
}

int s21_is_zero_nums(s21_decimal *num1, s21_decimal *num2, int result) {
  if (s21_iszero(num1) && s21_iszero(num2))
    result = 1;
  else
    result = 0;
  return result;
}

void s21_invert_big(s21_big *val) {
  for (int i = 0; i < 7; i++) {
    val->bits[i] = (~val->bits[i]) & 0xFFFFFFFF;
  }
  val->bits[0] = (val->bits[0] + 1);
  s21_clean_overflow(val);
}

void s21_shift_left(s21_big *result, s21_big *big, int shift) {
  memset(result, 0, sizeof(s21_big));
  for (int i = 0; i < 7; i++) result->bits[i] = big->bits[i];
  int shift_32 = shift / 32;
  for (int i = 0; i < shift_32; i++) {
    for (int j = 6; j > i; j--) result->bits[j] = result->bits[j - 1];
    result->bits[i] = 0;
  }
  shift = shift % 32;
  if (shift) {
    for (int j = 6; j > shift_32; j--)
      result->bits[j] =
          (result->bits[j] << shift) | (result->bits[j - 1] >> (32 - shift));
    result->bits[shift_32] = (result->bits[shift_32] << shift) & F8;
  }
}

int s21_big_less(s21_big *big1, s21_big *big2) {
  int less = 1;
  for (int i = 6; i >= 0; i--)
    if (big1->bits[i] != big2->bits[i]) {
      less = big1->bits[i] < big2->bits[i];
      break;
    }
  return less;
}

void s21_big_sub(s21_big *big1, s21_big *big2) {
  for (int i = 0; i < 7; i++) big2->bits[i] = ~(big2->bits[i]) & F8;
  for (int i = 0; i < 7; i++) big1->bits[i] = big1->bits[i] + big2->bits[i];
  big1->bits[0] += 1;
  s21_clean_overflow(big1);
}
