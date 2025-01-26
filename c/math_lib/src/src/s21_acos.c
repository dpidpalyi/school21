#include "../s21_math.h"

long double s21_acos(double x) {
  if (s21_fabs(x) > 1.0) return S21_NAN;

  long double res = s21_atan(s21_sqrt(1 - x * x) / x);
  if (-1.0 <= x && x < 0.0) res += S21_PI;

  return res;
}
