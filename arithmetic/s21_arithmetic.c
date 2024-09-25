#include "s21_arithmetic.h"

// Функция сложения двух значений s21_decimal
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  int result_code = OK;
  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    sign_1 ? s21_negate(value_1, &value_1) : s21_negate(value_2, &value_2);
    result_code = sign_1 ? s21_sub(value_2, value_1, result)
                         : s21_sub(value_1, value_2, result);
  }

  // Если знаки разных значений различны, выполняем вычитание
  if (sign_1 == sign_2) {
    s21_big_decimal val_1 = s21_get_null_big_decimal(),
                    val_2 = s21_get_null_big_decimal(),
                    res = s21_get_null_big_decimal();

    // Преобразуем значения в формат big_decimal
    s21_to_big_decimal(value_1, &val_1);
    s21_to_big_decimal(value_2, &val_2);
    s21_to_big_decimal(s21_get_null_decimal(), &res);
    s21_normalize(&val_1, &val_2);
    s21_set_scale_big(&res, s21_get_scale_big(val_1));
    for (int i = 0, temp = 0; i < 224; i++) {
      unsigned result_bit =
          s21_get_bit_big(val_1, i) + s21_get_bit_big(val_2, i) + temp;
      temp = result_bit / 2;
      result_bit %= 2;
      s21_set_bit_big(&res, i, result_bit);
    }
    if (s21_to_decimal(res, result)) result_code = sign_1 ? 2 : 1;
    if (result_code == OK && sign_1) s21_negate(*result, result);
  }
  return result_code;
}

// Функция вычитания двух значений s21_decimal
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  int result_code = OK;
  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    s21_negate(value_2, &value_2);
    result_code = s21_add(value_1, value_2, result);
  }
  if (sign_1 == sign_2) {
    if (sign_1) {
      s21_negate(value_1, &value_1);
      s21_negate(value_2, &value_2);
      s21_swap(&value_1, &value_2);
    }
    int is_swap = s21_is_less(value_1, value_2);
    s21_big_decimal val_1 = s21_get_null_big_decimal(),
                    val_2 = s21_get_null_big_decimal(),
                    res = s21_get_null_big_decimal();
    s21_to_big_decimal(is_swap ? value_2 : value_1, &val_1);
    s21_to_big_decimal(is_swap ? value_1 : value_2, &val_2);
    s21_to_big_decimal(s21_get_null_decimal(), &res);
    s21_normalize(&val_1, &val_2);
    for (int i = 0, temp = 0; i < 224; i++) {
      int result_bit =
          s21_get_bit_big(val_1, i) - s21_get_bit_big(val_2, i) - temp;
      temp = result_bit < 0;
      if (temp) result_bit += 2;
      s21_set_bit_big(&res, i, result_bit);
    }
    s21_set_scale_big(&res, s21_get_scale_big(val_1));
    s21_to_decimal(res, result);
    if (is_swap) s21_negate(*result, result);
  }
  return result_code;
}

// Функция умножения двух значений s21_decimal
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  int result_code = OK;
  s21_big_decimal val_1, val_2, res;
  s21_to_big_decimal(value_1, &val_1);
  s21_to_big_decimal(value_2, &val_2);
  s21_to_big_decimal(s21_get_null_decimal(), &res);
  for (int i = 0; i < 224; i++) {
    if (!s21_get_bit_big(val_2, i)) continue;
    s21_big_decimal buf = s21_get_null_big_decimal();
    s21_shift_left_big(val_1, i, &buf);
    for (int j = 0, temp = 0; j < 224; j++) {
      int result_bit = s21_get_bit_big(res, j) + s21_get_bit_big(buf, j) + temp;
      temp = result_bit / 2;
      result_bit %= 2;
      s21_set_bit_big(&res, j, result_bit);
    }
  }
  s21_set_scale_big(&res, s21_get_scale_big(val_1) + s21_get_scale_big(val_2));
  if (s21_to_decimal(res, result)) result_code = sign_1 != sign_2 ? 2 : 1;
  if (sign_1 != sign_2 && !result_code) s21_negate(*result, result);
  return result_code;
}

// Функция деления двух значений s21_decimal
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_zero(value_2)) return CALCUL_ZERO_ERR;
  int result_code = OK;
  s21_big_decimal val_1 = s21_get_null_big_decimal(),
                  val_2 = s21_get_null_big_decimal();
  s21_to_big_decimal(value_1, &val_1);
  s21_to_big_decimal(value_2, &val_2);
  s21_normalize(&val_1, &val_2);
  s21_big_decimal result_int = s21_get_null_big_decimal(),
                  ost = s21_get_null_big_decimal();
  s21_stolbik(val_1, val_2, &result_int, &ost);
  s21_set_scale_big(&result_int, 0);
  s21_set_scale_big(&ost, s21_get_scale_big(val_1));
  s21_big_decimal result_frac = s21_get_null_big_decimal(),
                  result_big = s21_get_null_big_decimal();
  if (s21_compare_big(ost, s21_get_null_big_decimal())) {
    for (int i = 0; i < 28; i++) s21_multiply_by_10(ost, &ost);
    s21_stolbik(ost, val_2, &result_frac, &val_1);
    s21_set_scale_big(&result_frac, 28);
    s21_set_scale_big(&result_big, 28);
  }
  s21_normalize(&result_int, &result_frac);
  for (int i = 0, temp = 0; i < 224; i++) {
    int result_bit =
        s21_get_bit_big(result_int, i) + s21_get_bit_big(result_frac, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(&result_big, i, result_bit);
  }
  *result = s21_get_null_decimal();
  s21_set_sign_big(&result_big, s21_get_sign(value_1) ^ s21_get_sign(value_2));
  if (s21_to_decimal(result_big, result))
    result_code = s21_get_sign(*result) ? 2 : 1;
  return result_code;
}
