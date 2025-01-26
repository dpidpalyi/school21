#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // обнуляем переменную для результата
  memset(result, 0, sizeof(s21_decimal));

  // создаем переменную для результата
  s21_big res = {0};

  // получаем знаки
  int sign1 = s21_get_bit(value_1, 127);
  int sign2 = s21_get_bit(value_2, 127);
  int sign_res = 0;

  // переводим в биг децимал по модулю
  s21_big val_1 = s21_from_decimal_to_big(&value_1);
  s21_big val_2 = s21_from_decimal_to_big(&value_2);

  // приводим к одному scale
  while (val_1.scale < val_2.scale) {
    if (s21_mul_10(&val_1)) {
      printf("ошибка переполнения биг децимал в сложении");
      return 1;  // проверить какие коды должен выдавать но в целом ситуация
                 // невероятная для масштаба 28
    };
    val_1.scale++;
  }
  while (val_2.scale < val_1.scale) {
    if (s21_mul_10(&val_2)) {
      printf("ошибка переполнения биг децимал в сложении");
      return 1;  // проверить какие коды должен выдавать
    };
    val_2.scale++;
  }

  // проверка на знак и инвертирование отрицательных
  if (sign1 && sign2) sign_res = 1;  // если оба отрицательных
  if (sign1 && !sign2) {
    s21_set_bit(&value_1, 127, 0);
    if (s21_is_greater(value_1, value_2)) {
      sign_res = 1;
      s21_invert_big(&val_2);  // переводим в дополнительный код
    } else {
      s21_invert_big(&val_1);
    }
  } else if (!sign1 && sign2) {
    s21_set_bit(&value_2, 127, 0);
    if (s21_is_greater(value_2, value_1)) {
      sign_res = 1;
      s21_invert_big(&val_1);
    } else {
      s21_invert_big(&val_2);
    }
  }

  // складываем по bits с переносом разряда
  for (int i = 0; i < 7; i++) {
    res.bits[i] = val_1.bits[i] + val_2.bits[i];
  }

  // устанавливаем scale в результат
  res.scale = val_1.scale;

  s21_clean_overflow(&res);

  uint64_t rem = 0;
  int temp = 0;
  while (s21_check_overflow(&res) && res.scale > 0) {
    rem = s21_del_10(&res);
    res.scale--;
    temp++;
  }

  if (rem > 5 || (rem == 5 && temp > 1) ||
      (rem == 5 && temp <= 1 && res.bits[0] & 1)) {  // банковское округление
    res.bits[0] += 1;
    s21_clean_overflow(&res);
  }

  // проверяем на переполнение
  if (s21_check_overflow(&res)) {
    if (sign_res) return 2;
    if (!sign_res) return 1;
  }

  // переводим результат в обычный decimal
  *result = s21_from_big_to_decimal(&res);

  // устанавливаем знак
  s21_set_bit(result, 127, sign_res);
  return 0;
}
