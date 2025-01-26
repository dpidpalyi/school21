#include "../s21_math.h"

long double s21_cos(double x) {
  if (S21_is_nan(x) || S21_is_inf(x) || S21_is_neg_inf(x)) return S21_NAN;

  long double res = 1;
  if (x < -S21_EPS) x = -x;
  while (x - S21_PI * 2 > S21_EPS) x -= S21_PI * 2;

  if (s21_fabs(x) < S21_EPS)
    res = 1;
  else if (s21_fabs(x - S21_PI) < S21_EPS)
    res = -1;
  else if (s21_fabs(x - S21_PI / 2) < S21_EPS)
    res = 6.123233995736766035868820147e-17;
  else {
    long double term = 1;
    for (int i = 1; i < 21; i++) {
      term *= s21_pow(-1, 2 * i - 1) * x * x / (2 * i * (2 * i - 1));
      res += term;
    }
  }

  return res;
}
