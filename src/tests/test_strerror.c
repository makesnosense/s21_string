#include <stdio.h>

#include "run_tests.h"

START_TEST(test_strerror) {
  int err_code = _i;  // supplied through add_loop_test func
  if (!IS_EXCLUDED(err_code)) {
    char* lib_result = strerror(err_code);
    char* s21_result = s21_strerror(err_code);
    ck_assert_str_eq(s21_result, lib_result);
  }
}
END_TEST

START_TEST(test_strerror_unknown) {
  int err_code = _i;  // supplied through add_loop_test func
  if (!IS_EXCLUDED(err_code)) {
    char* lib_result = strerror(err_code);
    char* s21_result = s21_strerror(err_code);
    ck_assert_str_eq(s21_result, lib_result);
    // free(lib_result);
  }
}
END_TEST

// Функция для добавления всех тестов
Suite* make_strerror_suite() {
  Suite* suite = suite_create("strerror");
  TCase* tc = tcase_create("core");

  tcase_add_loop_test(tc, test_strerror, 0, ERR_COUNT);
  tcase_add_loop_test(tc, test_strerror_unknown, -10, -1);

  suite_add_tcase(suite, tc);
  return suite;
}