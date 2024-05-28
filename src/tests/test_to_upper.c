#include "run_tests.h"

START_TEST(test_to_upper_basic) {
  const char* str = "Hello, World!";
  char* s21_result = s21_to_upper(str);
  char* expected_result = "HELLO, WORLD!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_to_upper_all_lowercase) {
  const char* str = "hello, world!";
  char* s21_result = s21_to_upper(str);
  char* expected_result = "HELLO, WORLD!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_to_upper_all_uppercase) {
  const char* str = "HELLO, WORLD!";
  char* s21_result = s21_to_upper(str);
  char* expected_result = "HELLO, WORLD!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_to_upper_numbers_and_symbols) {
  const char* str = "1234!@#$";
  char* s21_result = s21_to_upper(str);
  char* expected_result = "1234!@#$";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_to_upper_empty_string) {
  const char* str = "";
  char* s21_result = s21_to_upper(str);
  char* expected_result = "";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_to_upper_null_pointer) {
  const char* str = S21_NULL;
  char* s21_result = s21_to_upper(str);
  ck_assert_ptr_eq(s21_result, S21_NULL);
}
END_TEST

START_TEST(test_to_upper_numbers_and_symbols2) {
  const char* str = "||";
  char* s21_result = s21_to_upper(str);
  char* expected_result = "||";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

Suite* make_to_upper_suite() {
  Suite* to_upper_suite = suite_create("to_upper");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper_basic);
  tcase_add_test(tc_core, test_to_upper_all_lowercase);
  tcase_add_test(tc_core, test_to_upper_all_uppercase);
  tcase_add_test(tc_core, test_to_upper_numbers_and_symbols);
  tcase_add_test(tc_core, test_to_upper_empty_string);
  tcase_add_test(tc_core, test_to_upper_null_pointer);
  tcase_add_test(tc_core, test_to_upper_numbers_and_symbols2);

  suite_add_tcase(to_upper_suite, tc_core);
  return to_upper_suite;
}
