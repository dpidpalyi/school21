#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  memset(result, 0, sizeof(s21_decimal));
  if (!(s21_iszero(&value_1) || s21_iszero(&value_2))) {
    int sign1 = s21_get_bit(value_1, 127);
    int sign2 = s21_get_bit(value_2, 127);
    int sign_res = sign1 ^ sign2;
    s21_big big1 = s21_from_decimal_to_big(&value_1);
    s21_big big2 = s21_from_decimal_to_big(&value_2);
    s21_big res = s21_from_decimal_to_big(result);
    res.bits[0] = big1.bits[0] * big2.bits[0];
    res.bits[1] = big1.bits[1] * big2.bits[0] + big1.bits[0] * big2.bits[1];
    res.bits[2] = big1.bits[0] * big2.bits[2] + big1.bits[1] * big2.bits[1] +
                  big1.bits[2] * big2.bits[0];
    res.bits[3] = big1.bits[1] * big2.bits[2] + big1.bits[2] * big2.bits[1];
    res.bits[4] = big1.bits[2] * big2.bits[2];
    res.scale = big1.scale + big2.scale;
    s21_clean_overflow(&res);
    uint64_t rem = 0;
    while (s21_check_overflow(&res) && res.scale > 0) {
      rem = s21_del_10(&res);
      res.scale--;
    }
    if (rem >= 5) {
      res.bits[0] += 1;
      s21_clean_overflow(&res);
    }
    if (s21_check_overflow(&res)) {
      if (sign_res)
        err = 2;
      else
        err = 1;
    } else {
      s21_normalize_big(&res);
      *result = s21_from_big_to_decimal(&res);
      s21_set_bit(result, 127, sign_res);
    }
  }

  return err;
}
