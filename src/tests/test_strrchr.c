#include "run_tests.h"

START_TEST(test_strrchr_normal_char) {
  const char* str = "Hello, world!";
  int c = 'o';
  char* s21_result = s21_strrchr(str, c);
  char* lib_result = strrchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strrchr_char_not_found) {
  const char* str = "Hello, world!";
  int c = 'x';
  char* s21_result = s21_strrchr(str, c);
  char* lib_result = strrchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strrchr_null_char) {
  const char* str = "Hello, world!";
  int c = '\0';
  char* s21_result = s21_strrchr(str, c);
  char* lib_result = strrchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strrchr_empty_string) {
  const char* str = "";
  int c = 'H';
  char* s21_result = s21_strrchr(str, c);
  char* lib_result = strrchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strrchr_null_pointer) {
  const char* str = NULL;
  int c = 'H';
  char* s21_result = s21_strrchr(str, c);
  ck_assert_ptr_eq(s21_result, NULL);
}
END_TEST

START_TEST(test_strrchr_search_null_char_at_end) {
  const char* str = "Hello, world!\0";
  int c = '\0';
  char* s21_result = s21_strrchr(str, c);
  char* lib_result = strrchr(str, c);
  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

Suite* make_strrchr_suite() {
  Suite* strrchr_suite = suite_create("strrchr");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strrchr_normal_char);
  tcase_add_test(tc_core, test_strrchr_char_not_found);
  tcase_add_test(tc_core, test_strrchr_null_char);
  tcase_add_test(tc_core, test_strrchr_empty_string);
  tcase_add_test(tc_core, test_strrchr_null_pointer);
  tcase_add_test(tc_core, test_strrchr_search_null_char_at_end);

  suite_add_tcase(strrchr_suite, tc_core);
  return strrchr_suite;
}
