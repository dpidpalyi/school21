#include "../s21_math.h"

long double s21_asin(double x) {
  if (s21_fabs(x) - 1.0 > S21_EPS) return S21_NAN;

  return s21_atan(x / s21_sqrt(1 - x * x));
}
