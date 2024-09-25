#ifndef OTHERS_H
#define OTHERS_H

#include "../s21_decimal.h"

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
// 2,6-> 2, −2,6 -> −3
int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа.
// 11,9 -> 12; −0,9 -> −1; −1,1 -> −1; 2,5 -> 3
// Возвращает 1 в случае overflow
int s21_round(s21_decimal value, s21_decimal *result);

// Записывает в result целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули. Возвращает 1 в случае overflow
int s21_truncate(s21_decimal value, s21_decimal *result);

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

#endif