#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sprintf_basic) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+i-% d-%+f%c%s%c", 100, -100, 9.9999, '\t', "JOMA", '@');
  s21_sprintf(s21_res, "%+i-% d-%+f%c%s%c", 100, -100, 9.9999, '\t', "JOMA",
              '@');
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

// START_TEST(second_test) {
//   s21_size_t result = s21_strlen("posh");
//   ck_assert_int_eq(result, 4);
// }
// END_TEST

Suite* make_sprintf_suite() {
  Suite* sprintf_suite = suite_create("sprintf");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sprintf_basic);
  // tcase_add_test(tc_core, second_test);

  suite_add_tcase(sprintf_suite, tc_core);
  return sprintf_suite;
}
