#include "run_tests.h"

START_TEST(test_strcpy_empty) {
  char src[] = "";
  char dest[10];  // Больше, чем достаточно для пустой строки

  char* result = s21_strcpy(dest, src);
  ck_assert_str_eq(dest, src);
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_strcpy_content) {
  char src[] = "Hello, world!";
  char dest[20];

  char* result = s21_strcpy(dest, src);
  ck_assert_str_eq(dest, src);
  ck_assert_ptr_eq(result, dest);
}
END_TEST

Suite* make_strcpy_suite() {
  Suite* strcpy_suite = suite_create("strcpy");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strcpy_empty);
  tcase_add_test(tc_core, test_strcpy_content);

  suite_add_tcase(strcpy_suite, tc_core);
  return strcpy_suite;
}
