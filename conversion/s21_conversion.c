#include "s21_conversion.h"
#include "../helpers/s21_helpers.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int OK = 0;
  int sign = src < 0 ? -1 : 1;

  dst->bits[0] = src * sign;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;

  s21_set_sign(dst, src < 0 ? 1 : 0);

  return OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int OK = 1;
  int sign = s21_get_sign(src) ? -1 : 1;

  if (src.bits[2] == 0) { // точно не влазит
    int coef = s21_get_scale(src); // это на каком разряде точка (0 - 28)
                                  // то есть ее либо нет, либо она в bits[0]
        
    // проверить, не превышает ли int

    if (src.bits[1] == 0 && src.bits[2] == 0 && 0 < src.bits[0]) {
      *dst = sign * src.bits[0];
      OK = 0;
    }
  }
  
  return OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int OK = 0;
  if (0 < src < 0, 0000000000000000000000000001) {
    OK = 1;
  }
  dst->bits[0] = src;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
  return OK;
}

int s21_from_decimal_to_float(s21_decimal src, int *dst) {
  int OK = 0;

  return OK;
}