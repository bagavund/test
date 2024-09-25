#include "s21_helpers.h"

// Возвращает пустой s21_big_decimal с нулевыми битами.
s21_big_decimal s21_get_null_big_decimal() {
  s21_big_decimal result = {{0}};
  for (size_t i = 0; i < 8; i++) result.bits[i] = 0;  // Обнуляем все биты.
  return result;
}

// Проверяет переполнение, возвращает ненулевое значение, если есть
// переполнение.
int s21_overflow_check(s21_big_decimal* value) {
  return value->bits[3] || value->bits[4] || value->bits[5] ||
         value->bits[6];  // Проверяем биты, которые могут вызвать переполнение.
}

// Деление big_decimal на 10, возвращает остаток.
void s21_div_10(s21_big_decimal* value, int* ost) {
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; --i) {
    unsigned long long current = (remainder << 32) | value->bits[i];
    value->bits[i] = current / 10;
    remainder = current % 10;
  }
  *ost = (int)remainder;

  if (s21_get_scale_big(*value) > 0)
    s21_set_scale_big(value, s21_get_scale_big(*value) - 1);
}

// Округление банковским методом. Возвращает ошибку при переполнении.
int s21_bank(s21_big_decimal* value) {
  int err = OK;
  int ost = 0;

  // Пока есть переполнение или масштаб превышает 28, делим на 10.
  while ((s21_overflow_check(value) && s21_get_scale_big(*value) > 0) ||
         s21_get_scale_big(*value) > 28) {
    s21_div_10(value, &ost);
  }

  if (s21_overflow_check(value)) err = 1;

  // Если округление необходимо (остаток больше 5 или равно 5 с нечётным битом).
  if (!err && (ost > 5 || (ost == 5 && s21_get_bit_big(*value, 0)))) {
    for (int i = 0, temp = 1; i < 224; i++) {
      int result_bit = s21_get_bit_big(*value, i) + temp;
      temp = result_bit / 2;
      result_bit %= 2;
      s21_set_bit_big(value, i, result_bit);
    }
  }

  if (s21_overflow_check(value)) err = 1;
  return err;
}

// Сравнение двух s21_big_decimal значений. Возвращает разницу битов.
int s21_compare_big(s21_big_decimal val1, s21_big_decimal val2) {
  int result_code = 0;
  for (int i = 223; i >= 0 && !result_code; i--) {
    result_code = s21_get_bit_big(val1, i) - s21_get_bit_big(val2, i);
  }
  return result_code;
}

// Возвращает длину числа в битах.
int s21_get_length_big(s21_big_decimal value) {
  int result = 0;
  for (int i = 223; i >= 0 && !result; i--) {
    if (s21_get_bit_big(value, i)) result = i + 1;
  }
  return result;
}

// Добавление одного бита в конец числа (сдвиг и добавление).
void s21_add_bit(s21_big_decimal* value, int bit) {
  s21_shift_left_big(*value, 1, value);
  for (int i = 0, temp = 1; i < 224 && bit; i++) {
    int result_bit = s21_get_bit_big(*value, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(value, i, result_bit);
  }
}

// Столбиковое деление двух s21_big_decimal.
void s21_stolbik(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal* result, s21_big_decimal* ost) {
  if (s21_compare_big(value_1, value_2) == -1) {
    *result = s21_get_null_big_decimal();
    *ost = value_1;
    return;
  }

  int length = s21_get_length_big(value_1);
  int count = 0;
  int flag = 0;
  *ost = s21_get_null_big_decimal();

  // Основной цикл для деления.
  while (count < length) {
    int iterations = 0;
    for (int i = length - 1 - count;
         i >= 0 && s21_compare_big(*ost, value_2) == -1; i--) {
      s21_add_bit(ost, s21_get_bit_big(value_1, i));
      iterations++;
      if (flag && iterations > 1) s21_add_bit(result, 0);
    }
    count += iterations;

    // Вычитание делителя из текущего остатка.
    int buf2 = s21_compare_big(*ost, value_2);
    for (int i = 0, temp = 0; i < 224 && buf2 != -1; i++) {
      int result_bit =
          s21_get_bit_big(*ost, i) - s21_get_bit_big(value_2, i) - temp;
      temp = result_bit < 0;
      if (temp) result_bit += 2;
      s21_set_bit_big(ost, i, result_bit);
    }
    s21_add_bit(result, buf2 != -1);
    flag = 1;
  }
}

// Сдвиг big_decimal влево на num бит.
int s21_shift_left_big(s21_big_decimal value, int num,
                       s21_big_decimal* result) {
  *result = s21_get_null_big_decimal();
  for (int i = 0; i < 224 - num; i++) {
    s21_set_bit_big(result, i + num, s21_get_bit_big(value, i));
  }
  return OK;
}

// Обмен значениями двух s21_decimal.
void s21_swap(s21_decimal* value_1, s21_decimal* value_2) {
  s21_decimal buf = *value_1;
  *value_1 = *value_2;
  *value_2 = buf;
}

// Копирует значение src в dst.
void s21_copy_decimal(s21_decimal src, s21_decimal* dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
}

// Возвращает пустое значение s21_decimal.
s21_decimal s21_get_null_decimal() {
  s21_decimal result = {{0, 0, 0, 0}};
  return result;
}
