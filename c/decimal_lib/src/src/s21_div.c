#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0, temp_scale = 0;
  memset(result, 0, sizeof(s21_decimal));
  if (s21_iszero(&value_2)) {
    err = 3;
  } else if (!s21_iszero(&value_1)) {
    int sign1 = s21_get_bit(value_1, 127);
    int sign2 = s21_get_bit(value_2, 127);
    int sign_res = sign1 ^ sign2;
    s21_big big1 = s21_from_decimal_to_big(&value_1);
    s21_big big2 = s21_from_decimal_to_big(&value_2);
    s21_big *max = NULL;
    if (big1.scale > big2.scale) {
      temp_scale = big1.scale - big2.scale;
      max = &big2;
    } else {
      temp_scale = big2.scale - big1.scale;
      max = &big1;
    }
    for (int i = 0; i < temp_scale; i++) s21_mul_10(max);
    s21_big temp = {};
    s21_shift_left(&temp, &big2, 96);
    if (s21_big_less(&big1, &temp)) {
      for (int i = 95; i >= 0; i--) {
        s21_shift_left(&temp, &big2, i);
        if (s21_big_less(&temp, &big1)) {
          s21_set_bit(result, i, 1);
          s21_big_sub(&big1, &temp);
        }
      }
      s21_big zero = {};
      if (!s21_big_less(&big1, &zero)) {
        s21_big res = s21_from_decimal_to_big(result);
        s21_big temp_res = {};
        while (!s21_big_less(&big1, &zero)) {
          memset(&temp_res, 0, sizeof(s21_big));
          s21_mul_10(&big1);
          s21_mul_10(&res);
          res.scale += 1;
          for (int i = 3; i >= 0; i--) {
            s21_shift_left(&temp, &big2, i);
            if (s21_big_less(&temp, &big1)) {
              temp_res.bits[0] |= 1 << i;
              s21_big_sub(&big1, &temp);
            }
          }
          res.bits[0] += temp_res.bits[0];
          s21_clean_overflow(&res);
          if (res.bits[3] || res.scale == 29) {
            uint64_t rem = s21_del_10(&res);
            if (res.bits[0] != 0xFFFFFFFF && rem >= 5) {
              res.bits[0] += 1;
              s21_clean_overflow(&res);
            }
            res.scale -= 1;
            break;
          }
        }
        *result = s21_from_big_to_decimal(&res);
      }
      s21_set_bit(result, 127, sign_res);
    } else {
      if (sign_res)
        err = 2;
      else
        err = 1;
    }
  }

  return err;
}
