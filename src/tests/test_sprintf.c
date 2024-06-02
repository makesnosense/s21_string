#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sprintf_int) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+i-% d", -100, 0);
  s21_sprintf(s21_res, "%+i-% d", -100, 0);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_char) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%c %c", '\t', '@');
  s21_sprintf(s21_res, "%c %c", '\t', '@');
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_string) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%s", "JOMA");
  s21_sprintf(s21_res, "%s", "JOMA");
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_very_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "% .5f %+.0f %f", 33.0, 33.33, 3.33);
  s21_sprintf(s21_res, "% .5f %+.0f %f", 33.0, 33.33, 3.33);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_a_bit_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+.0f % .5f % .5f", 33.0, 33.0, 3.0);
  s21_sprintf(s21_res, "%+.0f % .5f % .5f", 33.0, 33.0, 3.0);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_float_width_precision_flag) {
  char lib_res[100];
  char s21_res[100];
  float sd = -3;
  float sd2 = 3.123456;
  float sd3 = 3.333;

  sprintf(lib_res, "%-15f %+-20.1f % -10f", sd, sd2, sd3);
  s21_sprintf(s21_res, "%-15f %+-20.1f % -10f", sd, sd2, sd3);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%u", 33);
  s21_sprintf(s21_res, "%u", 33);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

Suite* make_sprintf_suite() {
  Suite* sprintf_suite = suite_create("sprintf");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sprintf_int);
  tcase_add_test(tc_core, test_sprintf_char);
  tcase_add_test(tc_core, test_sprintf_string);
  tcase_add_test(tc_core, test_sprintf_very_float);
  tcase_add_test(tc_core, test_sprintf_a_bit_float);
  tcase_add_test(tc_core, test_sprintf_float_width_precision_flag);
  tcase_add_test(tc_core, test_sprintf_unsigned);

  suite_add_tcase(sprintf_suite, tc_core);
  return sprintf_suite;
}
