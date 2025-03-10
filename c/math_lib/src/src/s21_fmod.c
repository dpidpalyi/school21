#include "../s21_math.h"

long double s21_fmod(double x, double y) {
  int signx = 0;  // Переменная для хранения знака числа x

  if (x < 0) {
    signx = 1;  // Запоминаем знак числа x (1 для отрицательного числа, 0 для
                // остальных)
  }

  if (y == 0) {
    x = S21_NAN;  // Если y равно нулю, результатом будет NaN (не число)
  } else if (x == S21_INF || x == S21_NEG_INF) {
    x = S21_NAN;  // Если x равно положительной или отрицательной бесконечности,
                  // результатом будет NaN (не число)
  } else if (y != y) {
    x = S21_NAN;  // Если y является NaN (не число), результатом будет NaN (не
                  // число)
  } else {
    x = s21_fabs(x);  // Берем абсолютное значение x
    y = s21_fabs(y);  // Берем абсолютное значение y

    while (x >= y) {
      x -= y;  // Вычитаем y из x, пока x больше или равно y
    }
  }
  if (signx == 1) {
    x = -x;  // Восстанавливаем знак числа x, если он был отрицательным
  }
  return x;  // Возвращаем результат
}
