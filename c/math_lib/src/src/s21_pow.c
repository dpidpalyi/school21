#include "../s21_math.h"

#define OK 1000.0;  // Константа, указывающая на успешное выполнение

int isInt(double d) {  // Проверяем, является ли число целым
  return d == (long long int)d;
};

double helper(double base, double stepen) {  // проверяем все дебильные условия
  double res = OK;

  if (base == 0.0) {
    if /*(stepen == S21_NAN) {
      res = S21_NAN;
    } else if (stepen == -S21_NAN) {
      res = -S21_NAN;
    } else if*/
        (stepen == S21_NEG_INF) {
      res = S21_INF;
    } else if (stepen == 0.0) {
      res = 1.0;
    } else if (stepen < 0) {
      res = S21_INF;
    }
  } else if (base == 1.0) {
    res = 1.0;
  } else if (base == -1.0) {
    if (stepen == S21_INF || stepen == S21_NEG_INF) {
      res = 1.0;
    }
  } else if (!isInt(base) && !(base == S21_INF) && !(base == S21_NEG_INF)) {
    // База не является целым числом, плюс бесконечностью или минус
    // бесконечностью
    if (stepen == S21_INF) {
      res = 0.0;
    } else if (stepen == S21_NEG_INF) {
      res = S21_INF;
    }
  } else if (isInt(base)) {  // База является целым числом
    if (stepen == S21_INF) {
      res = S21_INF;
    } else if (stepen == S21_NEG_INF) {
      res = 0;
    }
  } else if (base == S21_INF) {
    // База является положительной бесконечностью
    if (stepen == 0.0) {
      res = 1.0;
    } else if (stepen > 0 && isInt(stepen)) {
      res = S21_INF;
    } else if (stepen == S21_INF) {
      res = S21_INF;
    } else if (stepen != stepen) {
      res = S21_NAN;
    }
  } else if (base == S21_NEG_INF) {
    // База является отрицательной бесконечностью
    if (stepen == 0.0) {
      res = 1.0;
    } else if (stepen > 0 && isInt(stepen) && (int)stepen % 2 == 0) {
      res = S21_INF;
    } else if (stepen > 0 && isInt(stepen) && (int)stepen % 2 != 0) {
      res = -S21_INF;
    } else if (stepen == S21_INF) {
      res = S21_INF;
    } else if (stepen != stepen) {
      res = S21_NAN;
    }
  }

  return res;
}

long double fast_pow(double base, long long int stepen) {
  long double res = 1.0;  // Инициализируем ответ единицей
  long long copy =
      s21_fabs(stepen);  // Берем абсолютное значение показателя степени

  // Вычисление быстрого возведения в степень
  while (copy) {
    res *= base;  // Умножаем на базу
    copy--;       // Уменьшаем показатель степени
  }

  return (stepen < 0) ? 1.0 / res
                      : res;  // Если показатель степени отрицателен, возвращаем
                              // обратное значение ответа, иначе - ответ
}

long double s21_pow(double base, double stepen) {
  long double res;

  if (helper(base, stepen) == 1000.0) {
    if (isInt(stepen)) {
      res = fast_pow(base,
                     stepen);  // Если показатель степени является целым числом,
                               // вычисляем результат с помощью функции fast_pow
    } else {  // stepen не является целым числом
      if (base < 0) {
        res = S21_NAN;  // Если база отрицательная, результатом будет NaN (не
                        // число)
      } else {
        res = s21_exp(stepen * s21_log(base));  // Вычисляем результат с помощью
                                                // функций s21_exp и s21_log
      }
    }
  } else {
    res = helper(base,
                 stepen);  // Если база и показатель степени соответствуют
                           // определенным случаям, возвращаем соответствующий
                           // результат из функции helper
  }

  return res;  // Возвращаем ответ
}
