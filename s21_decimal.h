#ifndef S21_DECIMAL_HED
#define S21_DECIMAL_HED

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum returnValues {
  OK = 0,
  CONVERTATION_ERR = 1,
  CONVERTATION_SMALL_ERR = 2,
  CALCUL_ZERO_ERR = 3,
} returnValues;

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

#include "./arithmetic/s21_arithmetic.h"
#include "./compares/s21_compares.h"
#include "./conversion/s21_conversion.h"
#include "./helpers/s21_helpers.h"
#include "./other/s21_other.h"

#endif  // S21_DECIMAL_HED
