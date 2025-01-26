#include "../s21_math.h"

long double s21_sqrt(double x) {
  if (x < -S21_EPS || S21_is_nan(x)) return S21_NAN;

  // Newton's method
  long double res = x / 2;
  long double div = 1;
  if (x < 1.0) div = x;
  while (s21_fabs(x - res * res) / div > S21_EPS) {
    res = (res + x / res) / 2;
  }

  return res;
}
