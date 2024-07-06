#include "run_tests.h"

START_TEST(test_strcat_hello) {
  char str1[10] = "Hel";
  char* str2 = "lo";

  char* s21_res;

  s21_res = s21_strcat(str1, str2);

  char lib_str1[10] = "Hel";
  char* lib_str2 = "lo";
  char* lib_res;

  lib_res = strcat(lib_str1, lib_str2);

  ck_assert_str_eq(s21_res, lib_res);
  ck_assert_mem_eq(s21_res, lib_res, 10);
}
END_TEST

START_TEST(test_strcat_empty_src) {
  char str1[20] = "";
  char* str2 = "World";
  char expected[20] = "World";

  ck_assert_str_eq(s21_strcat(str1, str2), expected);
  ck_assert_mem_eq(str1, expected, strlen(str1));
}
END_TEST

START_TEST(test_strcat_empty_dest) {
  char str1[20] = "Hello";
  char* str2 = "";
  char expected[20] = "Hello";

  ck_assert_str_eq(s21_strcat(str1, str2), expected);
  ck_assert_mem_eq(str1, expected, strlen(str1));
}
END_TEST

START_TEST(test_strcat_return_value) {
  char str1[20] = "Hello";
  char* str2 = " World";

  char* result = s21_strcat(str1, str2);
  ck_assert_ptr_eq(result, str1);
}
END_TEST

Suite* make_strcat_suite() {
  Suite* cat_suite = suite_create("strcat");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strcat_hello);
  tcase_add_test(tc_core, test_strcat_empty_src);
  tcase_add_test(tc_core, test_strcat_empty_dest);
  tcase_add_test(tc_core, test_strcat_return_value);

  suite_add_tcase(cat_suite, tc_core);
  return cat_suite;
}
