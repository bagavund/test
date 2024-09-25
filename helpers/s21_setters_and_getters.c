#include "s21_helpers.h"

// Устанавливает масштаб числа s21_decimal.
void s21_set_scale(s21_decimal *num, unsigned value) {
  num->bits[3] &= ~(0xFF << 16);  // Обнуляем биты масштаба (с 16 по 23 бит).
  num->bits[3] |= (value & 0xFF)
                  << 16;  // Устанавливаем новый масштаб (значение масштаба
                          // помещаем в биты с 16 по 23).
}

// Устанавливает масштаб числа s21_big_decimal.
void s21_set_scale_big(s21_big_decimal *num, unsigned value) {
  num->bits[7] &=
      ~(0xFF << 16);  // Обнуляем биты масштаба (аналогично обычному decimal).
  num->bits[7] |= (value & 0xFF) << 16;  // Устанавливаем новый масштаб.
}

// Получает масштаб числа s21_decimal (выбираем биты с 16 по 23).
int s21_get_scale(s21_decimal num) {
  return (num.bits[3] >> 16) & 0x7F;  // Извлекаем биты масштаба (7 бит).
}

// Получает масштаб числа s21_big_decimal (масштаб в том же диапазоне).
int s21_get_scale_big(s21_big_decimal num) {
  return (num.bits[7] >> 16) &
         0xFF;  // Извлекаем масштаб для big_decimal (8 бит).
}

// Получает знак числа s21_decimal (1 - отрицательный, 0 - положительный).
int s21_get_sign(s21_decimal value) {
  return (value.bits[3] & (1u << 31)) != 0;  // Извлекаем бит знака (31-й бит).
}

// Устанавливает знак числа s21_decimal: 0 - положительный, 1 - отрицательный.
void s21_set_sign(s21_decimal *num, unsigned value) {
  s21_set_bit(num, 127,
              value);  // Устанавливаем бит знака (127-й бит в массиве bits).
}

// Устанавливает знак числа s21_big_decimal: 0 - положительный, 1 -
// отрицательный.
void s21_set_sign_big(s21_big_decimal *num, unsigned value) {
  s21_set_bit_big(
      num, 255, value);  // Устанавливаем бит знака (255-й бит в массиве bits).
}

// Получает значение указанного бита в s21_big_decimal.
int s21_get_bit_big(s21_big_decimal value, int bit) {
  return (value.bits[bit / 32] >> (bit % 32)) &
         1;  // Извлекаем бит, рассчитывая его позицию в соответствующем
             // элементе массива.
}

// Получает значение указанного бита в s21_decimal.
int s21_get_bit(s21_decimal value, int bit) {
  return (value.bits[bit / 32] >> (bit % 32)) &
         1;  // Извлекаем бит аналогично для обычного decimal.
}

// Устанавливает значение указанного бита в s21_decimal.
void s21_set_bit(s21_decimal *num, int bit, int value) {
  if (value) {
    num->bits[bit / 32] |= (1 << (bit % 32));  // Устанавливаем бит в 1.
  } else {
    num->bits[bit / 32] &= ~(1 << (bit % 32));  // Устанавливаем бит в 0.
  }
}

// Устанавливает значение указанного бита в s21_big_decimal.
void s21_set_bit_big(s21_big_decimal *num, int bit, unsigned value) {
  if (value) {
    num->bits[bit / 32] |=
        (1 << (bit % 32));  // Устанавливаем бит в 1 для big_decimal.
  } else {
    num->bits[bit / 32] &=
        ~(1 << (bit % 32));  // Устанавливаем бит в 0 для big_decimal.
  }
}
