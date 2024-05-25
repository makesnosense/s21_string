#include "run_tests.h"

START_TEST(test_strchr_normal_char) {
  const char* str = "Hello, world!";
  int c = 'w';
  char* s21_result = s21_strchr(str, c);
  char* lib_result = strchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strchr_char_not_found) {
  const char* str = "Hello, world!";
  int c = 'x';
  char* s21_result = s21_strchr(str, c);
  char* lib_result = strchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strchr_null_char) {
  const char* str = "Hello, world!";
  int c = '\0';
  char* s21_result = s21_strchr(str, c);
  char* lib_result = strchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strchr_empty_string) {
  const char* str = "";
  int c = 'H';
  char* s21_result = s21_strchr(str, c);
  char* lib_result = strchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strchr_null_pointer) {
  const char* str = NULL;
  int c = 'H';
  char* s21_result = s21_strchr(str, c);
  ck_assert_ptr_eq(s21_result, NULL);
}
END_TEST

START_TEST(test_strchr_search_null_char_at_end) {
  const char* str = "Hello, world!\0";
  int c = '\0';
  char* s21_result = s21_strchr(str, c);
  char* lib_result = strchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strchr_suite() {
  Suite* strchr_suite = suite_create("strchr");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strchr_normal_char);
  tcase_add_test(tc_core, test_strchr_char_not_found);
  tcase_add_test(tc_core, test_strchr_null_char);
  tcase_add_test(tc_core, test_strchr_empty_string);
  tcase_add_test(tc_core, test_strchr_null_pointer);
  tcase_add_test(tc_core, test_strchr_search_null_char_at_end);

  suite_add_tcase(strchr_suite, tc_core);
  return strchr_suite;
}
