#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sscanf_int) {
  char* input_string = "77 13";
  char* format_string = "%d %i";

  int s21_res1 = 0;
  int s21_res2 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res2 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
}
END_TEST

Suite* make_sscanf_suite() {
  Suite* sscanf_suite = suite_create("sscanf");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sscanf_int);

  suite_add_tcase(sscanf_suite, tc_core);

  return sscanf_suite;
}