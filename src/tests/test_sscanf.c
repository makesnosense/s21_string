#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sscanf_int) {
  char* input_string = "77 13";
  char* format_string = "%d %i";

  int s21_res1 = 0;
  int s21_res2 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res2 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
}
END_TEST

START_TEST(test_sscanf_int_2) {
  char* input_string = "-12841 -19824127";
  char* format_string = "%d %i";

  int s21_res1 = 0;
  int s21_res2 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res2 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
}
END_TEST

START_TEST(test_sscanf_int_3) {
  char* input_string = "My date of birth is => 08-12-1994";
  char* format_string = "My date of birth is => %d-%i-%d";

  int s21_res1 = 0;
  int s21_res2 = 0;
  int s21_res3 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res2 = 0;
  int lib_res3 = 0;
  int lib_res_res = 0;

  lib_res_res =
      sscanf(input_string, format_string, &lib_res1, &lib_res2, &lib_res3);
  s21_res_res =
      s21_sscanf(input_string, format_string, &s21_res1, &s21_res2, &s21_res3);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
  ck_assert_int_eq(lib_res3, s21_res3);
}
END_TEST

START_TEST(test_sscanf_float) {
  char* input_string = "i have 0.0 money";
  char* format_string = "i have %f money";

  int s21_res1 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
}
END_TEST

START_TEST(test_sscanf_float_2) {
  char* input_string = "Pi is 3.1415926 and e is 2.7182818";
  char* format_string = "Pi is %f and e is %f";

  int s21_res1 = 0;
  int s21_res2 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res2 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
}
END_TEST

START_TEST(test_sscanf_float_3) {
  char* input_string = "Negative float 1: -0.999, negative float 2: -912.12";
  char* format_string = "Negative float 1: %f, negative float 2: %f";

  int s21_res1 = 0;
  int s21_res2 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res2 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
}
END_TEST

START_TEST(test_sscanf_char) {
  char* input_string = "Reading chars: %c-%c!%c@%c#%c$%c^";
  char* format_string = "Reading chars: Q-W!E@r#t$y^";

  char s21_res1 = 0;
  char s21_res2 = 0;
  char s21_res3 = 0;
  char s21_res4 = 0;
  char s21_res5 = 0;
  char s21_res6 = 0;
  int s21_res_res = 0;

  char lib_res1 = 0;
  char lib_res2 = 0;
  char lib_res3 = 0;
  char lib_res4 = 0;
  char lib_res5 = 0;
  char lib_res6 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2,
                       &lib_res3, &lib_res4, &lib_res5, &lib_res6);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2,
                           &s21_res3, &s21_res4, &s21_res5, &s21_res6);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
  ck_assert_int_eq(lib_res3, s21_res3);
  ck_assert_int_eq(lib_res4, s21_res4);
  ck_assert_int_eq(lib_res5, s21_res5);
  ck_assert_int_eq(lib_res6, s21_res6);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  char* input_string = "Unsigned 1: 0, unsigned 2: 123123123";
  char* format_string = "Unsigned 1: %u, unsigned 2: %u";

  unsigned s21_res1 = 0;
  unsigned s21_res2 = 0;
  int s21_res_res = 0;

  unsigned lib_res1 = 0;
  unsigned lib_res2 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
  s21_res_res = s21_sscanf(input_string, format_string, &s21_res1, &s21_res2);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
}
END_TEST

START_TEST(test_sscanf_star) {
  char* input_string =
      "int: 123, float: -123.0, char: @, unsigned: 0 %, string: cringe";
  char* format_string =
      "int: %*d, float: %*f, char: %*c, unsigned: %*u %%, string: %*s      %n";

  int s21_res1 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res_res = 0;

  lib_res_res = sscanf(input_string, format_string, &s21_res1);
  s21_res_res = s21_sscanf(input_string, format_string, &lib_res1);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
}
END_TEST

Suite* make_sscanf_suite() {
  Suite* sscanf_suite = suite_create("sscanf");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sscanf_int);
  tcase_add_test(tc_core, test_sscanf_int_2);
  tcase_add_test(tc_core, test_sscanf_int_3);
  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_float_2);
  tcase_add_test(tc_core, test_sscanf_float_3);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_unsigned);
  tcase_add_test(tc_core, test_sscanf_star);

  suite_add_tcase(sscanf_suite, tc_core);

  return sscanf_suite;
}
