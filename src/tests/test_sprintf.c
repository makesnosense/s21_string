#include <limits.h>
#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sprintf_int) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+i-% d %d", -100, 0, 3333);
  s21_sprintf(s21_res, "%+i-% d %d", -100, 0, 3333);
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

START_TEST(test_sprintf_empty_string) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%s", "");
  s21_sprintf(s21_res, "%s", "");
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_problematic_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%f", 3.33);
  s21_sprintf(s21_res, "%f", 3.33);
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
  float sd4 = 3;

  sprintf(lib_res, "%-15f %+-20.1f % -10f % f", sd, sd2, sd3, sd4);
  s21_sprintf(s21_res, "%-15f %+-20.1f % -10f % f", sd, sd2, sd3, sd4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char lib_res[1000];
  char s21_res[1000];
  sprintf(lib_res, "%-15u %60u %u %lu %lu", 1, 1000, UINT_MAX, ULONG_MAX,
          ULONG_MAX - 333);
  s21_sprintf(s21_res, "%-15u %60u %u %lu %lu", 1, 1000, UINT_MAX, ULONG_MAX,
              ULONG_MAX - 333);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_ints_d) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%-15d %60d %d", 1, 1000, INT_MAX);
  s21_sprintf(s21_res, "%-15d %60d %d", 1, 1000, INT_MAX);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_long_ints_d) {
  char lib_res[5000];
  char s21_res[5000];

  // long int min = -9223372036854775808;

  sprintf(lib_res, "%60ld_%ld_%-+15ld_%-+15ld", LONG_MAX, LONG_MIN, LONG_MAX,
          LONG_MIN);
  s21_sprintf(s21_res, "%60ld_%ld_%-+15ld_%-+15ld", LONG_MAX, LONG_MIN,
              LONG_MAX, LONG_MIN);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_short_ints_d) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%60hd_%hd_%-+15hd_%-+15hd", SHRT_MAX, SHRT_MIN, SHRT_MAX,
          SHRT_MIN);
  s21_sprintf(s21_res, "%60hd_%hd_%-+15hd_%-+15hd", SHRT_MAX, SHRT_MIN,
              SHRT_MAX, SHRT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_ints_i) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%-15i %60i", -1, -1000);
  s21_sprintf(s21_res, "%-15i %60i", -1, -1000);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_ints_d_min) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%d", INT_MIN);
  s21_sprintf(s21_res, "%d", INT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_long_doubles) {
  char lib_res[10000];
  char s21_res[10000];
  long double input = 9999999999.9;
  long double neg_input = -99999999.9;

  sprintf(lib_res, "%Lf %Lf", input, neg_input);
  s21_sprintf(s21_res, "%Lf %Lf", input, neg_input);
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
  tcase_add_test(tc_core, test_sprintf_empty_string);
  tcase_add_test(tc_core, test_sprintf_problematic_float);
  tcase_add_test(tc_core, test_sprintf_very_float);
  tcase_add_test(tc_core, test_sprintf_a_bit_float);
  tcase_add_test(tc_core, test_sprintf_float_width_precision_flag);
  tcase_add_test(tc_core, test_sprintf_unsigned);
  tcase_add_test(tc_core, test_sprintf_ints_d);
  tcase_add_test(tc_core, test_sprintf_ints_i);
  tcase_add_test(tc_core, test_sprintf_ints_d_min);
  tcase_add_test(tc_core, test_sprintf_long_ints_d);
  tcase_add_test(tc_core, test_sprintf_short_ints_d);
  tcase_add_test(tc_core, test_sprintf_long_doubles);
  suite_add_tcase(sprintf_suite, tc_core);
  return sprintf_suite;
}
