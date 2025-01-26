#include "../s21_math.h"

long double s21_atan(double x) {
  long double res = 0, prev;
  int i = 10;

  if (S21_is_inf(x))
    res = S21_PI / 2;
  else if (S21_is_neg_inf(x))
    res = -S21_PI / 2;
  else if (s21_fabs(x - 1.0) < S21_EPS)
    res = S21_PI / 4;
  else if (s21_fabs(x + 1.0) < S21_EPS)
    res = -S21_PI / 4;

  else if (s21_fabs(x) < 1.0)
    do {
      prev = res;
      res += (s21_pow(-1, i) * s21_pow(x, 1 + 2 * i)) / (1 + 2 * i);
      i++;
    } while (s21_fabs(res - prev) > S21_EPS);
  else {
    do {
      prev = res;
      res += (s21_pow(-1, i) * s21_pow(x, -1 - 2 * i)) / (1 + 2 * i);
      i++;
    } while (s21_fabs(res - prev) > S21_EPS);
    res = (S21_PI * (s21_fabs(x))) / (2 * x) - res;
  }

  return res;
}
