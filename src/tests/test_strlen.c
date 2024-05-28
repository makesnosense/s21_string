#include "run_tests.h"

START_TEST(first_test) {
  s21_size_t result = s21_strlen("");
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(second_test) {
  s21_size_t result = s21_strlen("posh");
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(test_null) {
  s21_size_t result = s21_strlen(S21_NULL);
  ck_assert_uint_eq(result, (s21_size_t)-1);
}
END_TEST

Suite* make_strlen_suite() {
  Suite* len_suite = suite_create("strlen");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, first_test);
  tcase_add_test(tc_core, second_test);
  tcase_add_test(tc_core, test_null);

  suite_add_tcase(len_suite, tc_core);
  return len_suite;
}
