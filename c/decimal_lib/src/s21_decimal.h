#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MINUS 0x80000000
#define SCALE 0x00FF0000
#define F8 0xFFFFFFFF

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  uint64_t bits[7];
  uint64_t scale;
} s21_big;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Common functions
int s21_get_bit(s21_decimal number, unsigned int bit_index);
void s21_set_bit(s21_decimal *number, unsigned int bit_index, unsigned int bit);

s21_big s21_from_decimal_to_big(s21_decimal *src);
s21_decimal s21_from_big_to_decimal(s21_big *src);
uint64_t s21_del_10(s21_big *big);
int s21_mul_10(s21_big *big);
int s21_clean_overflow(s21_big *big);
int s21_erase_float_part(s21_decimal value, s21_decimal *result, int flt,
                         int rnd);
void s21_normalize_big(s21_big *big);
int s21_iszero(s21_decimal *number);
int s21_check_overflow(s21_big *big);
void s21_shift_left(s21_big *result, s21_big *big, int shift);
int s21_big_less(s21_big *big1, s21_big *big2);
void s21_big_sub(s21_big *big1, s21_big *big2);

s21_big s21_reduction_to_denominator_mul(int exp, s21_big *num);
void s21_comparison_exp(s21_big *num1, s21_big *num2);
int s21_is_comparison_decimal(s21_big num1, s21_big num2, int result,
                              int comparison);
int s21_comparison_bits(s21_big num1, s21_big num2, int result_equal,
                        int comparison);
int s21_is_zero_nums(s21_decimal *num1, s21_decimal *num2, int result);
void s21_invert_big(s21_big *val);
#endif
