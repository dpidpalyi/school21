#include "../s21_math.h"

long double s21_floor(double x) {
  long double res;
  if (x != x) {
    res = S21_NAN;
  } else if (x == S21_INF) {
    res = S21_INF;
  } else if (x == S21_NEG_INF) {
    res = S21_NEG_INF;
  } else if (x == +0.0) {
    res = +0.0;
  } else {
    res = (long long int)x;  // Целая часть числа

    // Проверка на случай отрицательных чисел
    if (x < 0 && x != res) {
      res -= 1;
    }
  }
  return res;
}
