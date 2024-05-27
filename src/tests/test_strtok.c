#include <stdio.h>

#include "../s21_string.h"
#include "run_tests.h"

START_TEST(test_strtok_single_delim) {
  char str[] = "Hello, world!";
  const char* delim = ",";
  char* s21_result = s21_strtok(str, delim);
  char* lib_result = strtok(str, delim);
  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strtok_no_delim_found) {
  char str[] = "Hello";
  const char* delim = ",";
  char* s21_result = s21_strtok(str, delim);
  char* lib_result = strtok(str, delim);
  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
  char s21_str[] = "Hello, world! This is a test.";
  const char* delim = ", .!";
  char* s21_result = s21_strtok(s21_str, delim);
  s21_result = s21_strtok(S21_NULL, delim);

  char lib_str[] = "Hello, world! This is a test.";

  char* lib_result = strtok(lib_str, delim);
  lib_result = strtok(S21_NULL, delim);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strtok_till_end) {
  char s21_str[] = "Hello, world! This is a test.";
  const char* delim = ", .!";
  char* s21_result = s21_strtok(s21_str, delim);
  for (int i = 0; i < 6; i++) {
    s21_result = s21_strtok(S21_NULL, delim);
  }

  char lib_str[] = "Hello, world! This is a test.";

  char* lib_result = strtok(lib_str, delim);
  for (int i = 0; i < 6; i++) {
    lib_result = strtok(S21_NULL, delim);
  }

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char str[] = "";
  const char* delim = ",";
  char* s21_result = s21_strtok(str, delim);
  char* lib_result = strtok(str, delim);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strtok_null_str) {
  const char* delim = ",";
  char* s21_result = s21_strtok(S21_NULL, delim);
  char* lib_result = strtok(S21_NULL, delim);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strtok_suite() {
  Suite* strtok_suite = suite_create("strtok");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strtok_single_delim);
  tcase_add_test(tc_core, test_strtok_multiple_delims);
  tcase_add_test(tc_core, test_strtok_no_delim_found);

  tcase_add_test(tc_core, test_strtok_empty_string);
  tcase_add_test(tc_core, test_strtok_till_end);
  tcase_add_test(tc_core, test_strtok_null_str);

  suite_add_tcase(strtok_suite, tc_core);
  return strtok_suite;
}
