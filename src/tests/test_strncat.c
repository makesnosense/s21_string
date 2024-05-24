#include "run_tests.h"

START_TEST(test_strncat_hello_first) {
  char str1[15] = "Hel";
  char* str2 = "lo1234";

  char* s21_res;

  s21_res = s21_strncat(str1, str2, 2);

  char lib_str1[15] = "Hel";
  char* lib_res;

  lib_res = strncat(lib_str1, str2, 2);

  ck_assert_str_eq(s21_res, lib_res);
  ck_assert_mem_eq(s21_res, lib_res, 10);
}
END_TEST

START_TEST(test_strncat_hello_full) {
  char str1[15] = "Hel";
  char* str2 = "lo1234";

  char* s21_res;

  s21_res = s21_strncat(str1, str2, 6);

  char lib_str1[15] = "Hel";
  char* lib_res;

  lib_res = strncat(lib_str1, str2, 6);

  ck_assert_str_eq(s21_res, lib_res);
  ck_assert_mem_eq(s21_res, lib_res, 15);
}
END_TEST

START_TEST(test_strncat_zero_length) {
  char str1[15] = "Hello";
  char* str2 = "World";

  char* s21_res = s21_strncat(str1, str2, 0);

  char lib_str1[15] = "Hello";

  char* lib_res = strncat(lib_str1, str2, 0);

  ck_assert_str_eq(s21_res, lib_res);
}
END_TEST

START_TEST(test_strncat_empty_destination) {
  char str1[15] = "";
  char* str2 = "World";

  char* s21_res = s21_strncat(str1, str2, 5);
  char lib_str1[15] = "";
  char* lib_res = strncat(lib_str1, str2, 5);

  ck_assert_str_eq(s21_res, lib_res);
}
END_TEST

START_TEST(test_strncat_n_larger_than_source) {
  char str1[15] = "Hello";
  char* str2 = "Wo";

  char* s21_res = s21_strncat(str1, str2, 10);
  char lib_str1[15] = "Hello";
  char* lib_res = strncat(lib_str1, str2, 10);

  ck_assert_str_eq(s21_res, lib_res);
}
END_TEST

START_TEST(test_strncat_boundary_condition) {
  char str1[11] = "Hello";
  char* str2 = "56789";

  char* s21_res = s21_strncat(str1, str2, 5);
  char lib_str1[11] = "Hello";
  char* lib_res = strncat(lib_str1, str2, 5);

  ck_assert_str_eq(s21_res, lib_res);
  ck_assert_int_eq(strlen(s21_res), 10);
}
END_TEST

Suite* make_strncat_suite() {
  Suite* catn_suite = suite_create("strncat");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strncat_hello_first);
  tcase_add_test(tc_core, test_strncat_hello_full);
  tcase_add_test(tc_core, test_strncat_zero_length);
  tcase_add_test(tc_core, test_strncat_empty_destination);
  tcase_add_test(tc_core, test_strncat_n_larger_than_source);
  tcase_add_test(tc_core, test_strncat_boundary_condition);

  suite_add_tcase(catn_suite, tc_core);
  return catn_suite;
}