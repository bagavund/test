#include <limits.h>

#include "check.h"
#include "s21_decimal.h"

#pragma region math_tests

START_TEST(test_s21_add) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{579, 0, 0, 0}},
              res;

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_add_minus_a) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{333, 0, 0, 0}},
              res;
  s21_set_sign(&a, 1);

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_add_minus_b) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{333, 0, 0, 0}},
              res;
  s21_set_sign(&b, 1);
  s21_set_sign(&c, 1);

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_add_minus_ab) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{579, 0, 0, 0}},
              res;
  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  s21_set_sign(&c, 1);

  ck_assert_int_eq(s21_add(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_sub) {
  s21_decimal a = {{579, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{123, 0, 0, 0}},
              res;

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_sub_minus_a) {
  s21_decimal a = {{579, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{1035, 0, 0, 0}},
              res;

  s21_set_sign(&a, 1);
  s21_set_sign(&c, 1);

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_sub_minus_b) {
  s21_decimal a = {{579, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{1035, 0, 0, 0}},
              res;

  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_sub_minus_ab) {
  s21_decimal a = {{579, 0, 0, 0}}, b = {{456, 0, 0, 0}}, c = {{123, 0, 0, 0}},
              res;

  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);
  s21_set_sign(&c, 1);

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_sub_bank) {
  s21_decimal a = {{INT_MAX, INT_MAX, INT_MAX, 0}}, 
    b = {{6, 0, 0, 0}}, 
    c = {{INT_MAX - 1, INT_MAX, INT_MAX, 0}},
    res;

  s21_set_scale(&b, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_mul) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}},
              c = {{56088, 0, 0, 0}}, res;

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_mul_minus_a) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}},
              c = {{56088, 0, 0, 0}}, res;

  s21_set_sign(&a, 1);
  s21_set_sign(&c, 1);

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_mul_minus_b) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}},
              c = {{56088, 0, 0, 0}}, res;

  s21_set_sign(&b, 1);
  s21_set_sign(&c, 1);

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_mul_minus_ab) {
  s21_decimal a = {{123, 0, 0, 0}}, b = {{456, 0, 0, 0}},
              c = {{56088, 0, 0, 0}}, res;

  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_mul(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_mul_overflow) {
  s21_decimal a = {{INT_MAX, INT_MAX, INT_MAX, 0}}, b = {{2, 0, 0, 0}},
              c = {{INT_MAX, INT_MAX, INT_MAX, 0}}, res;

  ck_assert_int_eq(s21_mul(a, b, &res), 1);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

START_TEST(test_s21_div) {
  s21_decimal a = {{56088, 0, 0, 0}}, b = {{456, 0, 0, 0}},
              c = {{123, 0, 0, 0}}, res;

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_div_bank) {
  s21_decimal a = {{INT_MAX, INT_MAX, INT_MAX, 0}}, 
    b = {{15, 0, 0, 0}}, 
    c = {{INT_MAX, INT_MAX, INT_MAX, 0}},
    res;

  s21_set_scale(&b, 3);

  ck_assert_int_eq(s21_sub(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

START_TEST(test_s21_div_zero) {
  s21_decimal a = {{56088, 0, 0, 0}}, b = {{0, 0, 0, 0}}, res;

  ck_assert_int_eq(s21_div(a, b, &res), 3);
}

START_TEST(test_s21_div_b) {
  s21_decimal a = {{1, 0, 0, 0}}, b = {{2, 0, 0, 0}}, c = {{5, 0, 0, 0}}, res;

  s21_set_scale(&c, 1);

  ck_assert_int_eq(s21_div(a, b, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, c), 1);
}

END_TEST

#pragma endregion

#pragma region compares_tests

START_TEST(test_s21_compare) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};
  s21_decimal a4 = {{ 0, 0, 0, 0}}, b4 = {{ 0, 0, 0, 0 }};
  s21_decimal a5 = {{ 0, 1, 0, 0}}, b5 = {{ 0, 0, 0, 0 }};
  s21_decimal a6 = {{ 0, 1, 0, 0}}, b6 = {{ 0, 1, 0, 0 }};

  s21_set_sign(&a3, 1);
  s21_set_sign(&b3, 1);
  s21_set_sign(&a5, 1);
  s21_set_sign(&b6, 1);

  ck_assert_int_eq(s21_compare(a1, b1), -1);
  ck_assert_int_eq(s21_compare(a2, b2), 1);
  ck_assert_int_eq(s21_compare(a3, b3), 0);
  ck_assert_int_eq(s21_compare(a4, b4), 0);
  ck_assert_int_eq(s21_compare(a5, b5), -1);
  ck_assert_int_eq(s21_compare(a6, b6), 1);
}

START_TEST(test_s21_is_zero) {
  s21_decimal value1 = {{ 123, 0, 0, 0}}, value2 = {{ 0, 456, 0, 0}},
    value3 = {{ 0, 0, 789, 0}};
  s21_decimal zero_value = {{ 0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_zero(value1), 0);
  ck_assert_int_eq(s21_is_zero(value2), 0);
  ck_assert_int_eq(s21_is_zero(value3), 0);
  ck_assert_int_eq(s21_is_zero(zero_value), 1);
}

END_TEST

START_TEST(test_s21_is_less) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};

  ck_assert_int_eq(s21_is_less(a1, b1), 1);
  ck_assert_int_eq(s21_is_less(a2, b2), 0);
  ck_assert_int_eq(s21_is_less(a3, b3), 0);
}

END_TEST

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};

  ck_assert_int_eq(s21_is_less_or_equal(a1, b1), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a2, b2), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a3, b3), 1);
}

END_TEST

START_TEST(test_s21_is_greater) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};

  ck_assert_int_eq(s21_is_greater(a1, b1), 0);
  ck_assert_int_eq(s21_is_greater(a2, b2), 1);
  ck_assert_int_eq(s21_is_greater(a3, b3), 0);
}

END_TEST

START_TEST(test_s21_is_greater_or_equal) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};

  ck_assert_int_eq(s21_is_greater_or_equal(a1, b1), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a2, b2), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a3, b3), 1);
}

END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};

  ck_assert_int_eq(s21_is_equal(a1, b1), 0);
  ck_assert_int_eq(s21_is_equal(a2, b2), 0);
  ck_assert_int_eq(s21_is_equal(a3, b3), 1);
}

END_TEST

START_TEST(test_s21_is_not_equal) {
  s21_decimal a1 = {{ 123, 0, 0, 0}}, b1 = {{ 345, 0, 0, 0 }};
  s21_decimal a2 = {{ 345, 0, 0, 0}}, b2 = {{ 123, 0, 0, 0 }};
  s21_decimal a3 = {{ 1, 0, 0, 0}}, b3 = {{ 1, 0, 0, 0 }};

  ck_assert_int_eq(s21_is_not_equal(a1, b1), 1);
  ck_assert_int_eq(s21_is_not_equal(a2, b2), 1);
  ck_assert_int_eq(s21_is_not_equal(a3, b3), 0);
}

END_TEST

#pragma endregion

#pragma region other_tests

START_TEST(test_s21_floor) {
  s21_decimal value = {{ 22, 0, 0, 0 }}, result = {{ 0, 0, 0, 0}},
    answer = {{ 2, 0, 0, 0}};

  s21_set_scale(&value, 1);

  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_int_eq(s21_is_equal(answer, result), 1);
}

END_TEST

START_TEST(test_s21_round) {
  s21_decimal a1 = {{ 20, 0, 0, 0 }}, b1 = {{ 2, 0, 0, 0}},
    a2 = {{ 23, 0, 0, 0 }}, b2 = {{ 3, 0, 0, 0}},
    result;

  s21_set_scale(&a1, 1);
  s21_set_scale(&a2, 1);

  ck_assert_int_eq(s21_round(a1, &result), 0);
  ck_assert_int_eq(s21_is_equal(b1, result), 1);

  ck_assert_int_eq(s21_round(a2, &result), 0);
  ck_assert_int_eq(s21_is_equal(b2, result), 1);
}

END_TEST

#pragma endregion

Suite *s21_suite_create() {
  Suite *s21_suite = suite_create("s21_decimal_tests");
  
#pragma region math
  TCase *tc_math = tcase_create("math");
  suite_add_tcase(s21_suite, tc_math);

  tcase_add_test(tc_math, test_s21_add);
  tcase_add_test(tc_math, test_s21_add_minus_a);
  tcase_add_test(tc_math, test_s21_add_minus_b);
  tcase_add_test(tc_math, test_s21_add_minus_ab);

  tcase_add_test(tc_math, test_s21_sub);
  tcase_add_test(tc_math, test_s21_sub_minus_a);
  tcase_add_test(tc_math, test_s21_sub_minus_b);
  tcase_add_test(tc_math, test_s21_sub_minus_ab);
  tcase_add_test(tc_math, test_s21_sub_bank);

  tcase_add_test(tc_math, test_s21_mul);
  tcase_add_test(tc_math, test_s21_mul_minus_a);
  tcase_add_test(tc_math, test_s21_mul_minus_b);
  tcase_add_test(tc_math, test_s21_mul_minus_ab);

  tcase_add_test(tc_math, test_s21_mul_overflow);

  tcase_add_test(tc_math, test_s21_div);
  tcase_add_test(tc_math, test_s21_div_zero);
  tcase_add_test(tc_math, test_s21_div_b);
  tcase_add_test(tc_math, test_s21_div_bank);

#pragma endregion

#pragma region compares

  TCase *tc_compares = tcase_create("compares");
  suite_add_tcase(s21_suite, tc_compares);

  tcase_add_test(tc_compares, test_s21_compare);
  tcase_add_test(tc_compares, test_s21_is_zero);
  tcase_add_test(tc_compares, test_s21_is_less);
  tcase_add_test(tc_compares, test_s21_is_less_or_equal);
  tcase_add_test(tc_compares, test_s21_is_greater);
  tcase_add_test(tc_compares, test_s21_is_greater_or_equal);
  tcase_add_test(tc_compares, test_s21_is_equal);
  tcase_add_test(tc_compares, test_s21_is_not_equal);

#pragma endregion

#pragma region other_tests

  TCase* tc_other = tcase_create("other");
  suite_add_tcase(s21_suite, tc_other);

  tcase_add_test(tc_other, test_s21_floor);
  tcase_add_test(tc_other, test_s21_round);

#pragma endregion

  return s21_suite;
}

int main() {
  Suite *suite = s21_suite_create();
  SRunner *sr = srunner_create(suite);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);

  return 0;
}
