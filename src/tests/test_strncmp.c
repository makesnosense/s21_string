#include "run_tests.h"

START_TEST(test_strncmp_equal_strings) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, World";
  s21_size_t n = sizeof(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_different_strings) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, world";  // lowercase 'w'
  s21_size_t n = sizeof(str1);

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_partial_compare) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, World!!!";
  s21_size_t n = 12;  // Only compare up to the 'd'

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_one_string_shorter) {
  char* str1 = "Hello";
  char* str2 = "Hello, world!";
  s21_size_t n = 20;  // n bigger than both

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_another_string_shorter) {
  char* str1 = "Hello, world!";
  char* str2 = "Hello";
  s21_size_t n = 20;  // n bigger than both

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_no_chars) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, World";
  s21_size_t n = 0;  // Compare zero characters

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_n_greater_than_length) {
  char* str1 = "Short";
  char* str2 = "Shorter";
  s21_size_t n = 20;  // n is greater than the length of both strings

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_strings_equal_but_one_longer) {
  char* str1 = "Hello";
  char* str2 = "Hello\0extra";
  s21_size_t n = 15;

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncmp_substring) {
  char* str1 = "Hello";
  char* str2 = "Hello, world!";
  s21_size_t n = 10;  // n больше длины str1, но меньше str2

  int s21_result = s21_strncmp(str1, str2, n);
  int lib_result = strncmp(str1, str2, n);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strncmp_suite() {
  Suite* strncmp_suite = suite_create("strncmp");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strncmp_equal_strings);
  tcase_add_test(tc_core, test_strncmp_different_strings);
  tcase_add_test(tc_core, test_strncmp_partial_compare);
  tcase_add_test(tc_core, test_strncmp_no_chars);
  tcase_add_test(tc_core, test_strncmp_n_greater_than_length);
  tcase_add_test(tc_core, test_strncmp_one_string_shorter);
  tcase_add_test(tc_core, test_strncmp_strings_equal_but_one_longer);
  tcase_add_test(tc_core, test_strncmp_another_string_shorter);
  tcase_add_test(tc_core, test_strncmp_substring);

  suite_add_tcase(strncmp_suite, tc_core);
  return strncmp_suite;
}
