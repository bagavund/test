#include "s21_other.h"

/* Функция округления вниз (floor) для числа типа s21_decimal.
 * Обрабатывает числа с разными масштабами и знаками.
 * Использует вспомогательные функции для получения масштаба и знака числа, а
 * также для деления числа на 10. Если число отрицательное, добавляет 1 к
 * результату после отбрасывания дробной части.
 */

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return CONVERTATION_ERR;
  int sign = s21_get_sign(value);
  int flag = OK;
  int scale = s21_get_scale(value);
  if (scale < 0 || scale > 28) flag = CONVERTATION_ERR;
  if (flag == OK) {
    s21_decimal unsigned_value = s21_get_null_decimal();
    s21_copy_decimal(value, &unsigned_value);
    s21_set_sign(&unsigned_value, 0);
    s21_decimal truncated_unsigned_value = s21_get_null_decimal();
    s21_copy_decimal(unsigned_value, &truncated_unsigned_value);
    s21_truncate(truncated_unsigned_value, &truncated_unsigned_value);

    s21_decimal fractal = s21_get_null_decimal(),
                zero_decimal = s21_get_null_decimal();
    flag = s21_sub(unsigned_value, truncated_unsigned_value, &fractal);
    if (flag == OK && s21_is_greater(fractal, zero_decimal) && sign == 1) {
      s21_decimal one = {{1, 0, 0, 0}};
      flag = s21_add(truncated_unsigned_value, one, &truncated_unsigned_value);
    }
    s21_set_sign(&truncated_unsigned_value, sign);
    s21_copy_decimal(truncated_unsigned_value, result);
  }
  return flag;
}

/* Функция изменения знака (negate) для числа типа s21_decimal.
 * Обрабатывает числа с разными знаками.
 * Использует вспомогательные функции для получения и установки знака числа.
 * Изменяет знак числа на противоположный.
 */

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return CONVERTATION_ERR;
  int flag = OK;
  int scale = s21_get_scale(value);
  if (scale < 0 || scale > 28) flag = CONVERTATION_ERR;
  if (flag == OK) {
    *result = value;
    s21_set_bit(result, 127, !s21_get_bit(*result, 127));
  }
  return flag;
}

/* Функция округления (round) для числа типа s21_decimal.
 * Обрабатывает числа с разными масштабами и знаками.
 * Использует вспомогательные функции для получения масштаба и знака числа, а
 * также для деления и взятия остатка от деления. Округляет число по правилам
 * математического округления.
 */

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) return CONVERTATION_ERR;
  int code = OK;
  unsigned int sign = s21_get_sign(value);
  if (sign) s21_set_sign(&value, 0);

  s21_decimal fract = s21_get_null_decimal(), half_of_one = {{5, 0, 0, 0}},
              one = {{1, 0, 0, 0}};
  s21_set_scale(&half_of_one, 1);
  if (s21_truncate(value, result) || s21_sub(value, *result, &fract)) {
    code = 1;
  }
  if (!code && s21_is_greater_or_equal(fract, half_of_one)) {
    s21_add(*result, one, result);
  }
  s21_set_sign(result, sign);
  return code;
}

/* Функция усечения (truncate) для числа типа s21_decimal.
 * Обрабатывает числа с разными масштабами и знаками.
 * Использует вспомогательные функции для получения масштаба и знака числа, а
 * также для деления числа на 10. Отбрасывает дробную часть числа.
 */

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  int code = OK;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  s21_big_decimal temp = s21_get_null_big_decimal();
  s21_to_big_decimal(value, &temp);
  int scale = s21_get_scale_big(temp);
  if (scale < 0 || scale > 28) code = CONVERTATION_ERR;
  if (code == OK && scale > 0) {
    for (int i = 0; i < scale; ++i) {
      int ost;
      s21_div_10(&temp, &ost);
    }
    s21_set_scale_big(&temp, 0);
    code = s21_to_decimal(temp, result);
  }
  return code;
}