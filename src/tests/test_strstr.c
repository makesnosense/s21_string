#include "run_tests.h"

START_TEST(test_strstr_normal_use) {
  const char* haystack = "Hello, world!";
  const char* needle = "world";
  char* s21_result = s21_strstr(haystack, needle);
  char* lib_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strstr_no_match) {
  const char* haystack = "Hello, world!";
  const char* needle = "xyz";
  char* s21_result = s21_strstr(haystack, needle);
  char* lib_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char* haystack = "Hello, world!";
  const char* needle = "";
  char* s21_result = s21_strstr(haystack, needle);
  char* lib_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  const char* haystack = "";
  const char* needle = "Hello";
  char* s21_result = s21_strstr(haystack, needle);
  char* lib_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strstr_immediate) {
  const char* haystack = "HelloHello";
  const char* needle = "Hello";
  char* s21_result = s21_strstr(haystack, needle);
  char* lib_result = strstr(haystack, needle);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strstr_suite() {
  Suite* strstr_suite = suite_create("strstr");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strstr_normal_use);
  tcase_add_test(tc_core, test_strstr_no_match);
  tcase_add_test(tc_core, test_strstr_empty_needle);
  tcase_add_test(tc_core, test_strstr_empty_haystack);
  tcase_add_test(tc_core, test_strstr_immediate);

  suite_add_tcase(strstr_suite, tc_core);
  return strstr_suite;
}
