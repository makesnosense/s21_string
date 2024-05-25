#include "run_tests.h"

START_TEST(test_strspn_all_chars_found) {
  const char* str1 = "Hello, world!";
  const char* str2 = "Helo, wrd!";
  s21_size_t s21_result = s21_strspn(str1, str2);
  s21_size_t lib_result = strspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strspn_char_not_found) {
  const char* str1 = "Hello, world!";
  const char* str2 = "abc";
  s21_size_t s21_result = s21_strspn(str1, str2);
  s21_size_t lib_result = strspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strspn_empty_str1) {
  const char* str1 = "";
  const char* str2 = "Hello, world!";
  s21_size_t s21_result = s21_strspn(str1, str2);
  s21_size_t lib_result = strspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strspn_empty_str2) {
  const char* str1 = "Hello, world!";
  const char* str2 = "";
  s21_size_t s21_result = s21_strspn(str1, str2);
  s21_size_t lib_result = strspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strspn_both_empty) {
  const char* str1 = "";
  const char* str2 = "";
  s21_size_t s21_result = s21_strspn(str1, str2);
  s21_size_t lib_result = strspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strspn_suite() {
  Suite* strspn_suite = suite_create("strspn");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strspn_all_chars_found);
  tcase_add_test(tc_core, test_strspn_char_not_found);
  tcase_add_test(tc_core, test_strspn_empty_str1);
  tcase_add_test(tc_core, test_strspn_empty_str2);
  tcase_add_test(tc_core, test_strspn_both_empty);

  suite_add_tcase(strspn_suite, tc_core);
  return strspn_suite;
}
