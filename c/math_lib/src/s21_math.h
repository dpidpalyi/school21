#ifndef S21_MATH_H
#define S21_MATH_H

#include <limits.h>
#include <stdio.h>
#define S21_EPS 1e-15
#define S21_PI 3.141592653589793115997963468544185161590576171
#define S21_EXP 2.71828182845904509079559829842764884233474731445312
#define S21_MAX 1e100

#define S21_NAN -(0.0 / 0.0L)
#define S21_is_nan(x) ((x) != (x))

#define S21_INF 1.0 / 0.0L
#define S21_NEG_INF -1.0 / 0.0L
#define S21_is_inf(x) ((x) == S21_INF)
#define S21_is_neg_inf(x) ((x) == S21_NEG_INF)

int s21_abs(int x);  //	!вычисляет абсолютное значение целого числа
long double s21_acos(double x);  //	вычисляет арккосинус
long double s21_asin(double x);  //	вычисляет арксинус
long double s21_atan(double x);  //	вычисляет арктангенс
long double s21_ceil(double x);  //	возвращает ближайшее целое число, не
                                 // меньшее заданного значения
long double s21_cos(double x);  //	вычисляет косинус
long double s21_exp(
    double x);  //	возвращает значение e, возведенное в заданную степень
long double s21_fabs(
    double x);  //	!вычисляет абсолютное значение числа с плавающей точкой
long double s21_floor(double x);  //	возвращает ближайшее целое число, не
                                  // превышающее заданное значение
long double s21_fmod(
    double x,
    double y);  //	остаток операции деления с плавающей точкой
long double s21_log(double x);  //	вычисляет натуральный логарифм
long double s21_pow(double base,
                    double exp);  //	возводит число в заданную степень
long double s21_sin(double x);  //	вычисляет синус
long double s21_sqrt(double x);  //	вычисляет квадратный корень
long double s21_tan(double x);  //	вычисляет тангенс

#endif
