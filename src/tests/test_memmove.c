#include <stdio.h>

#include "run_tests.h"
START_TEST(test_memmove_empty) {
  char src[1] = {0};
  char dest[1];

  void* result = s21_memmove(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_memmove_content) {
  char src[] = "Hello, world!";
  char dest[20];

  void* result = s21_memmove(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_memmove_overlap_forward) {
  char dest[33] = "1.2.3.4.5.6.7.8.9.10.11.12.13.14";
  char* src = dest;

  char* lib_expected_result = "1.2.31.2.3.4.5.6.7.8.9.10.11.12.";

  void* s21_result = s21_memmove(dest + 5, src, 27);

  ck_assert_mem_eq(dest, lib_expected_result, strlen(lib_expected_result));
  ck_assert_ptr_eq(s21_result - 5, dest);
}
END_TEST

START_TEST(test_memmove_overlap_backward) {
  char dest[] = "123456789.10.11.12.13.14";
  char* src = dest;

  char* lib_expected_result = "6789.10.11.12.13.14";

  void* s21_result = s21_memmove(dest, src + 5, 25);

  ck_assert_mem_eq(dest, lib_expected_result, strlen(dest));
  ck_assert_ptr_eq(s21_result, dest);
}
END_TEST

Suite* make_memmove_suite() {
  Suite* memmove_suite = suite_create("memmove");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memmove_empty);
  tcase_add_test(tc_core, test_memmove_content);
  tcase_add_test(tc_core, test_memmove_overlap_forward);
  tcase_add_test(tc_core, test_memmove_overlap_backward);

  suite_add_tcase(memmove_suite, tc_core);
  return memmove_suite;
}
