#include "run_tests.h"

START_TEST(test_strcmp_equal_strings) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, World";

  int s21_result = s21_strcmp(str1, str2);
  int lib_result = strcmp(str1, str2);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcmp_first_string_longer) {
  char* str1 = "Hello, World!";
  char* str2 = "Hello, World";

  int s21_result = s21_strcmp(str1, str2);
  int lib_result = strcmp(str1, str2);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcmp_second_string_longer) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, World!";

  int s21_result = s21_strcmp(str1, str2);
  int lib_result = strcmp(str1, str2);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcmp_strings_different) {
  char* str1 = "Hello, World";
  char* str2 = "Hello, there";

  int s21_result = s21_strcmp(str1, str2);
  int lib_result = strcmp(str1, str2);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcmp_empty_strings) {
  char* str1 = "";
  char* str2 = "";

  int s21_result = s21_strcmp(str1, str2);
  int lib_result = strcmp(str1, str2);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strcmp_suite() {
  Suite* strcmp_suite = suite_create("strcmp");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strcmp_equal_strings);
  tcase_add_test(tc_core, test_strcmp_first_string_longer);
  tcase_add_test(tc_core, test_strcmp_second_string_longer);
  tcase_add_test(tc_core, test_strcmp_strings_different);
  tcase_add_test(tc_core, test_strcmp_empty_strings);

  suite_add_tcase(strcmp_suite, tc_core);
  return strcmp_suite;
}
