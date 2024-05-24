#include "run_tests.h"

START_TEST(test_memset_zeros) {
  char dest[33] = "1.2.3.4.5.6.7.8.9.10.11.12.13.14";
  char* expected_result = "00000000000000000000000000000000";
  void* s21_result = s21_memset(dest, 48, strlen(dest));

  ck_assert_mem_eq(dest, expected_result, strlen(dest));
  ck_assert_ptr_eq(s21_result, dest);
}
END_TEST

START_TEST(test_memset_zero_length) {
  char dest[33] = "Initial string";
  char expected_result[33];
  strcpy(expected_result, dest);  // Copy original to expected

  void* s21_result = s21_memset(dest, 'Z', 0);  // Zero length

  ck_assert_mem_eq(dest, expected_result, strlen(dest));
  ck_assert_ptr_eq(s21_result, dest);
}
END_TEST

START_TEST(test_memset_money) {
  char dest[33] = "1.2.3.4.5.6.7.8.9.10.11.12.13.14";
  char* expected_result = "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
  void* s21_result = s21_memset(dest, '$', strlen(dest));

  ck_assert_mem_eq(dest, expected_result, strlen(dest));
  ck_assert_ptr_eq(s21_result, dest);
}
END_TEST

Suite* make_memset_suite() {
  Suite* memset_suite = suite_create("memset");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memset_zeros);
  tcase_add_test(tc_core, test_memset_zero_length);
  tcase_add_test(tc_core, test_memset_money);

  suite_add_tcase(memset_suite, tc_core);

  return memset_suite;
}
