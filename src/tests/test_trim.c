#include "run_tests.h"

START_TEST(test_trim_basic) {
  const char* src = "  Hello, world!  ";
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_trim_multiple_chars) {
  const char* src = "\t\n Hello, world! \n\t";
  const char* trim_chars = " \t\n";
  char* result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_trim_no_trim_chars) {
  const char* src = "Hello, world!";
  const char* trim_chars = NULL;
  char* result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, world!");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_string) {
  const char* src = "";
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_all_trimmed) {
  const char* src = "     ";
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_null_src) {
  const char* src = NULL;
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite* make_trim_suite() {
  Suite* trim_suite = suite_create("trim");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_trim_basic);
  tcase_add_test(tc_core, test_trim_multiple_chars);
  tcase_add_test(tc_core, test_trim_no_trim_chars);
  tcase_add_test(tc_core, test_trim_empty_string);
  tcase_add_test(tc_core, test_trim_all_trimmed);
  tcase_add_test(tc_core, test_trim_null_src);

  suite_add_tcase(trim_suite, tc_core);
  return trim_suite;
}
