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
  int err_code = -3;
  if (!IS_EXCLUDED(err_code)) {
    char* lib_result = strerror(err_code);
    char* s21_result = s21_strerror(err_code);
    ck_assert_str_eq(s21_result, lib_result);
    free(lib_result);
  }
}
END_TEST

START_TEST(test_strerror_unknown_above) {
  int err_code = 333;
  if (!IS_EXCLUDED(err_code)) {
#if defined(__linux__)
    char* lib_result = "Unknown error 333";
#elif defined(__APPLE__)
    char* lib_result = "Unknown error: 333";
#endif
    // char* lib_result = strerror(err_code);

    char* s21_result = s21_strerror(err_code);
    ck_assert_str_eq(s21_result, lib_result);

    // #if defined(__linux__)
    //     free(lib_result);
    // #endif
  }
}
END_TEST

Suite* make_strerror_suite() {
  Suite* suite = suite_create("strerror");
  TCase* tc = tcase_create("Core");

  tcase_add_loop_test(tc, test_strerror, 0, ERR_COUNT);
  tcase_add_test(tc, test_strerror_unknown);
  tcase_add_test(tc, test_strerror_unknown_above);

  suite_add_tcase(suite, tc);
  return suite;
}
