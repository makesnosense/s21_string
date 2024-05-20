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

Suite* make_strlen_suite() {
  Suite* sui = suite_create("strlen");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, first_test);
  tcase_add_test(tc_core, second_test);

  suite_add_tcase(sui, tc_core);
  return sui;
}
