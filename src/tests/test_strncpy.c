#include "run_tests.h"

START_TEST(test_strncpy_exact_length) {
  char* src = "Hello, World";
  char s21_dest[50] = {0};
  char lib_dest[50] = {0};
  s21_size_t n = sizeof(src);

  char* s21_result = s21_strncpy(s21_dest, src, n);
  char* lib_result = strncpy(lib_dest, src, n);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncpy_shorter_n) {
  char* src = "Hello, World";
  char s21_dest[50] = {0};
  char lib_dest[50] = {0};
  s21_size_t n = 5;

  char* s21_result = s21_strncpy(s21_dest, src, n);
  char* lib_result = strncpy(lib_dest, src, n);

  ck_assert_str_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_strncpy_longer_n) {
  char* src = "Hello";
  char s21_dest[50] = {0};
  char lib_dest[50] = {0};
  s21_size_t n = sizeof(src) + 20;

  char* s21_result = strncpy(s21_dest, src, n);
  char* lib_result = strncpy(lib_dest, src, n);

  ck_assert_str_eq(s21_result, lib_result);
  ck_assert_mem_eq(s21_result, lib_result, 50);
}
END_TEST

START_TEST(test_strncpy_empty_src) {
  char* src = "";
  char s21_dest[50] = "Previous content";
  char lib_dest[50] = "Previous content";
  s21_size_t n = 10;

  char* s21_result = s21_strncpy(s21_dest, src, n);
  char* lib_result = strncpy(lib_dest, src, n);

  ck_assert_str_eq(s21_result, lib_result);
  ck_assert_mem_eq(s21_result, lib_result, 50);
}
END_TEST

START_TEST(test_strncpy_zero_n) {
  char* src = "Hello, World";
  char s21_dest[50] = "Previous content";
  char lib_dest[50] = "Previous content";
  s21_size_t n = 0;

  char* s21_result = s21_strncpy(s21_dest, src, n);
  char* lib_result = strncpy(lib_dest, src, n);

  ck_assert_str_eq(s21_result, lib_result);
  ck_assert_mem_eq(s21_result, lib_result, 50);
}
END_TEST

Suite* make_strncpy_suite() {
  Suite* strncpy_suite = suite_create("strncpy");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strncpy_exact_length);
  tcase_add_test(tc_core, test_strncpy_shorter_n);
  tcase_add_test(tc_core, test_strncpy_longer_n);
  tcase_add_test(tc_core, test_strncpy_empty_src);
  tcase_add_test(tc_core, test_strncpy_zero_n);

  suite_add_tcase(strncpy_suite, tc_core);
  return strncpy_suite;
}
