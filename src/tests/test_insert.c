#include "run_tests.h"

START_TEST(test_insert_normal) {
  const char* src = "Hello, world!";
  const char* str = "beautiful ";
  s21_size_t start_index = 7;
  char* s21_result = s21_insert(src, str, start_index);
  char* expected_result = "Hello, beautiful world!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_insert_empty_str) {
  const char* src = "Hello, world!";
  const char* str = "";
  s21_size_t start_index = 5;
  char* s21_result = s21_insert(src, str, start_index);
  char* expected_result = "Hello, world!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_insert_empty_src) {
  const char* src = "";
  const char* str = "Hello";
  s21_size_t start_index = 0;
  char* s21_result = s21_insert(src, str, start_index);
  char* expected_result = "Hello";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_insert_start_index_zero) {
  const char* src = "world!";
  const char* str = "Hello, ";
  s21_size_t start_index = 0;
  char* s21_result = s21_insert(src, str, start_index);
  char* expected_result = "Hello, world!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_insert_start_index_end) {
  const char* src = "Hello, ";
  const char* str = "world!";
  s21_size_t start_index = 7;
  char* s21_result = s21_insert(src, str, start_index);
  char* expected_result = "Hello, world!";
  ck_assert_str_eq(s21_result, expected_result);
  free(s21_result);
}
END_TEST

START_TEST(test_insert_start_index_out_of_range) {
  const char* src = "Hello, world!";
  const char* str = "beautiful ";
  s21_size_t start_index = 20;
  char* s21_result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(s21_result, S21_NULL);
}
END_TEST

START_TEST(test_insert_start_index_out_of_range_below) {
  const char* src = "Hello, world!";
  const char* str = "beautiful ";
  s21_size_t start_index = -33;
  char* s21_result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(s21_result, S21_NULL);
}
END_TEST

Suite* make_insert_suite() {
  Suite* insert_suite = suite_create("insert");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_insert_normal);
  tcase_add_test(tc_core, test_insert_empty_str);
  tcase_add_test(tc_core, test_insert_empty_src);
  tcase_add_test(tc_core, test_insert_start_index_zero);
  tcase_add_test(tc_core, test_insert_start_index_end);
  tcase_add_test(tc_core, test_insert_start_index_out_of_range);
  tcase_add_test(tc_core, test_insert_start_index_out_of_range_below);

  suite_add_tcase(insert_suite, tc_core);
  return insert_suite;
}
