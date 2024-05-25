#include <stdio.h>

#include "run_tests.h"

START_TEST(test_strerror) {
  int err_code = _i;  // supplied through add_loop_test func
  if (!IS_EXCLUDED(err_code)) {
    char* expected = strerror(err_code);
    char* result = s21_strerror(err_code);
    ck_assert_str_eq(expected, result);
  }
}
END_TEST

// Функция для добавления всех тестов
Suite* make_strerror_suite() {
  Suite* suite = suite_create("strerror");
  TCase* tc = tcase_create("core");

  // Добавляем все тесты в один тестовый случай
  tcase_add_loop_test(tc, test_strerror, 0, ERR_COUNT);

  suite_add_tcase(suite, tc);
  return suite;
}