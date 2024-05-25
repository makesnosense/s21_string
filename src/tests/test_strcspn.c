#include "run_tests.h"

START_TEST(test_strcspn_no_match) {
  const char* str1 = "Hello, world!";
  const char* str2 = "xyz";
  s21_size_t s21_result = s21_strcspn(str1, str2);
  s21_size_t lib_result = strcspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcspn_partial_match) {
  const char* str1 = "Hello, world!";
  const char* str2 = "d!";
  s21_size_t s21_result = s21_strcspn(str1, str2);
  s21_size_t lib_result = strcspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcspn_full_match) {
  const char* str1 = "Hello, world!";
  const char* str2 = "H";
  s21_size_t s21_result = s21_strcspn(str1, str2);
  s21_size_t lib_result = strcspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcspn_empty_str1) {
  const char* str1 = "";
  const char* str2 = "Hello, world!";
  s21_size_t s21_result = s21_strcspn(str1, str2);
  s21_size_t lib_result = strcspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
  const char* str1 = "Hello, world!";
  const char* str2 = "";
  s21_size_t s21_result = s21_strcspn(str1, str2);
  s21_size_t lib_result = strcspn(str1, str2);
  ck_assert_uint_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strcspn_suite() {
  Suite* strcspn_suite = suite_create("strcspn");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strcspn_no_match);
  tcase_add_test(tc_core, test_strcspn_partial_match);
  tcase_add_test(tc_core, test_strcspn_full_match);
  tcase_add_test(tc_core, test_strcspn_empty_str1);
  tcase_add_test(tc_core, test_strcspn_empty_str2);

  suite_add_tcase(strcspn_suite, tc_core);
  return strcspn_suite;
}
