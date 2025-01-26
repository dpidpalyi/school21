#include "../s21_math.h"

long double s21_exp(double x) {
  long double i = 1;  // Переменная для хранения значения i в ряду Тейлора
  long double step = 1;  // Переменная для хранения текущего шага ряда Тейлора
  long double T_series = 1;  // Переменная для хранения суммы ряда Тейлора

  if (x != x) {
    T_series = S21_NAN;
  } else if (x == 0.0) {
    T_series = 1.0;
  } else if (x == S21_INF) {
    T_series = S21_INF;
  } else if (x == S21_NEG_INF) {
    T_series = 0.0;
  } else {
    while (s21_fabs(step) > S21_EPS) {
      step *= x / i;  // Вычисляем следующий шаг ряда Тейлора
      i++;
      T_series += step;  // Добавляем шаг к сумме ряда Тейлора
      if (T_series >
          S21_MAX) {  // если достигли максимального значения, то бесконечность
        T_series = S21_INF;
        break;
      }
    }
  }

  return T_series;  // Возвращаем результат суммы ряда Тейлора
}
