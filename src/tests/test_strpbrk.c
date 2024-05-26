#include "run_tests.h"

START_TEST(test_strpbrk_normal_use) {
  const char* str1 = "Hello, world!";
  const char* str2 = "world";
  char* s21_result = s21_strpbrk(str1, str2);
  char* lib_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strpbrk_no_match) {
  const char* str1 = "Hello, world!";
  const char* str2 = "xyz";
  char* s21_result = s21_strpbrk(str1, str2);
  char* lib_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strpbrk_empty_first_string) {
  const char* str1 = "";
  const char* str2 = "world";
  char* s21_result = s21_strpbrk(str1, str2);
  char* lib_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strpbrk_empty_second_string) {
  const char* str1 = "Hello, world!";
  const char* str2 = "";
  char* s21_result = s21_strpbrk(str1, str2);
  char* lib_result = strpbrk(str1, str2);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strpbrk_suite() {
  Suite* strpbrk_suite = suite_create("strpbrk");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strpbrk_normal_use);
  tcase_add_test(tc_core, test_strpbrk_no_match);
  tcase_add_test(tc_core, test_strpbrk_empty_first_string);
  tcase_add_test(tc_core, test_strpbrk_empty_second_string);

  suite_add_tcase(strpbrk_suite, tc_core);
  return strpbrk_suite;
}
