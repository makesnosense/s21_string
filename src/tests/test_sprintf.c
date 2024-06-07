#include <limits.h>
#include <locale.h>
#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sprintf_int) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+i-% d %d", -100, 0, 3333);
  s21_sprintf(s21_res, "%+i-% d %d", -100, 0, 3333);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_char) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%c %c", '\t', '@');
  s21_sprintf(s21_res, "%c %c", '\t', '@');
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_string) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%s", "JOMA");
  s21_sprintf(s21_res, "%s", "JOMA");
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_empty_string) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%s", "");
  s21_sprintf(s21_res, "%s", "");
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_problematic_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%f", 3.33);
  s21_sprintf(s21_res, "%f", 3.33);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_very_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "% .5f %+.0f %f", 33.0, 33.33, 3.33);
  s21_sprintf(s21_res, "% .5f %+.0f %f", 33.0, 33.33, 3.33);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_a_bit_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+.0f % .5f % .5f", 33.0, 33.0, 3.0);
  s21_sprintf(s21_res, "%+.0f % .5f % .5f", 33.0, 33.0, 3.0);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_float_width_precision_flag) {
  char lib_res[100];
  char s21_res[100];
  float sd = -3;
  float sd2 = 3.123456;
  float sd3 = 3.333;
  float sd4 = 3;

  sprintf(lib_res, "%-15f %+-20.1f % -10f % f", sd, sd2, sd3, sd4);
  s21_sprintf(s21_res, "%-15f %+-20.1f % -10f % f", sd, sd2, sd3, sd4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char lib_res[1000];
  char s21_res[1000];
  long int min_long_int = LONG_MIN;

  sprintf(lib_res, "%-15u %60u %u %lu %lu %lu %u %lu %hu %u", 1, 1000, UINT_MAX,
          ULONG_MAX, ULONG_MAX - 333, ULONG_MAX + 1, (UINT_MAX + 500),
          min_long_int, USHRT_MAX, UINT_MAX);
  s21_sprintf(s21_res, "%-15u %60u %u %lu %lu %lu %u %lu %hu %u", 1, 1000,
              UINT_MAX, ULONG_MAX, ULONG_MAX - 333, ULONG_MAX + 1,
              (UINT_MAX + 500), min_long_int, USHRT_MAX, UINT_MAX);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_unsigned_problematic) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res, "%hu %hu %u %lu %lu %u %u", USHRT_MAX + 5, UINT_MAX + 10,
          UINT_MAX, ULONG_MAX, ULONG_MAX + 5, -1000, -65545);
  s21_sprintf(s21_res, "%hu %hu %u %lu %lu %u %u", USHRT_MAX + 5, UINT_MAX + 10,
              UINT_MAX, ULONG_MAX, ULONG_MAX + 5, -1000, -65545);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_ints_d) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%-15d %60d %d", 1, 1000, INT_MAX);
  s21_sprintf(s21_res, "%-15d %60d %d", 1, 1000, INT_MAX);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_long_ints_d) {
  char lib_res[5000];
  char s21_res[5000];

  long int max = 2147483647;
  long int min = -2147483648;

  sprintf(lib_res, "%60ld_%ld_%-+15ld_%-+15ld", max, min, max, min);
  s21_sprintf(s21_res, "%60ld_%ld_%-+15ld_%-+15ld", max, min, max, min);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_short_ints_d) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%60hd_%hd_%-+15hd_%-+15hd", SHRT_MAX, SHRT_MIN, SHRT_MAX,
          SHRT_MIN);
  s21_sprintf(s21_res, "%60hd_%hd_%-+15hd_%-+15hd", SHRT_MAX, SHRT_MIN,
              SHRT_MAX, SHRT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_ints_i) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%-15i %60i", -1, -1000);
  s21_sprintf(s21_res, "%-15i %60i", -1, -1000);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_ints_d_min) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%d", INT_MIN);
  s21_sprintf(s21_res, "%d", INT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_long_doubles) {
  char lib_res[10000];
  char s21_res[10000];
  long double input = 9999999999.9;
  long double neg_input = -99999999.9;

  sprintf(lib_res, "%Lf %Lf", input, neg_input);
  s21_sprintf(s21_res, "%Lf %Lf", input, neg_input);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_short_overflow) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%hd %hd %hd %hd", (SHRT_MAX + 33), (SHRT_MIN - 10), INT_MAX,
          INT_MIN);
  s21_sprintf(s21_res, "%hd %hd %hd %hd", SHRT_MAX + 33, SHRT_MIN - 10, INT_MAX,
              INT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_int_overflow) {
  char lib_res[500];
  char s21_res[500];
  int very_int = INT_MAX;
  int very_min_int = INT_MIN;
  sprintf(lib_res, "%d %d", (very_int + 33), (very_min_int - 1500));
  s21_sprintf(s21_res, "%d %d", (very_int + 33), (very_min_int - 1500));

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_long_overflow) {
  char lib_res[500];
  char s21_res[500];
  long int long_int = LONG_MAX;
  long int long_min_int = LONG_MIN;
  sprintf(lib_res, "%+40.5ld %-40ld", (long_int + 33), (long_min_int - 1500));
  s21_sprintf(s21_res, "%+40.5ld %-40ld", (long_int + 33),
              (long_min_int - 1500));

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_zero_double) {
  char lib_res[100];
  char s21_res[100];
  double num = 0;
  sprintf(lib_res, "%e", num);
  s21_sprintf(s21_res, "%e", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_front_double) {
  char lib_res[100];
  char s21_res[100];
  double num = 1234.5678;
  sprintf(lib_res, "%e", num);
  s21_sprintf(s21_res, "%e", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_from_negative_double) {
  char lib_res[100];
  char s21_res[100];
  double num = -0.9;
  sprintf(lib_res, "%e", num);
  s21_sprintf(s21_res, "%e", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_from_big_double) {
  char lib_res[100];
  char s21_res[100];
  double num =
      1.7976931348623157165654643542544769789787575443755869766556454334242544676909809776765654543;
  sprintf(lib_res, "%e", num);
  s21_sprintf(s21_res, "%e", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_number_of_characters) {
  char lib_res[100];
  char s21_res[100];
  double num = 1.79769313486231571308;
  int res_or = 0;
  int res_s21 = 0;
  s21_sprintf(s21_res, "sprintf: %+E hdhgd %+d hdkjgh %n", num, 555, &res_s21);
  sprintf(lib_res, "sprintf: %+E hdhgd %+d hdkjgh %n", num, 555, &res_or);
  ck_assert_str_eq(lib_res, s21_res);
  //
}
END_TEST

START_TEST(test_sprintf_wide_character) {
  char lib_res[1000];
  char s21_res[1000];
  wchar_t wide_char = L'あ';

  s21_sprintf(s21_res, "Широкий символ: %lc\n fgtffghghgutf", wide_char);
  sprintf(lib_res, "Широкий символ: %lc\n fgtffghghgutf", wide_char);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_wide_character_string) {
  char lib_res[100];
  char s21_res[100];
  wchar_t wide_string[] = L"こんにちは";

  s21_sprintf(s21_res, "Широкий символ: %ls\n fgtffghghgutf", wide_string);
  sprintf(lib_res, "Широкий символ: %ls\n fgtffghghgutf", wide_string);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_hex_lower_with_modifiers) {
  char lib_res[1000];
  char s21_res[1000];

  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295;  // Максимум для unsigned long

  sprintf(lib_res, "%x %hx %lx ", -33, us_value, ul_value);
  s21_sprintf(s21_res, "%x %hx %lx ", -33, us_value, ul_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_hex_upper_with_modifiers) {
  char lib_res[100];
  char s21_res[100];

  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295UL + 5;  // Максимум для unsigned long

  sprintf(lib_res, "%hX %lX", us_value, ul_value);
  s21_sprintf(s21_res, "%hX %lX", us_value, ul_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_octal_with_modifiers) {
  char lib_res[500];
  char s21_res[500];

  unsigned short us_value = 0377;  // 255 в десятичной системе
  unsigned long ul_value =
      037777777777;  // Максимум для unsigned long в восьмеричной системе
  long int min_long_int = LONG_MIN;
  sprintf(lib_res, "%ho %lo %lo", us_value, ul_value, min_long_int);
  s21_sprintf(s21_res, "%ho %lo %lo", us_value, ul_value, min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_octal_problematic_two) {
  char lib_res[300];
  char s21_res[300];

  long int min_long_int = LONG_MIN;

  sprintf(lib_res, "%lo", min_long_int);
  s21_sprintf(s21_res, "%lo", min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

// START_TEST(test_sprintf_octal_problematic) {
//   char lib_res[300];
//   char s21_res[300];

//   int m = -33;

//   sprintf(lib_res, "%20o", m);
//   s21_sprintf(s21_res, "%20o", m);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

Suite* make_sprintf_suite() {
  Suite* sprintf_suite = suite_create("sprintf");
  TCase* tc_core;

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sprintf_int);
  tcase_add_test(tc_core, test_sprintf_char);
  tcase_add_test(tc_core, test_sprintf_string);
  tcase_add_test(tc_core, test_sprintf_empty_string);
  tcase_add_test(tc_core, test_sprintf_problematic_float);
  tcase_add_test(tc_core, test_sprintf_very_float);
  tcase_add_test(tc_core, test_sprintf_a_bit_float);
  tcase_add_test(tc_core, test_sprintf_float_width_precision_flag);
  tcase_add_test(tc_core, test_sprintf_unsigned);
  tcase_add_test(tc_core, test_sprintf_unsigned_problematic);
  tcase_add_test(tc_core, test_sprintf_ints_d);
  tcase_add_test(tc_core, test_sprintf_ints_i);
  tcase_add_test(tc_core, test_sprintf_ints_d_min);
  tcase_add_test(tc_core, test_sprintf_long_ints_d);
  tcase_add_test(tc_core, test_sprintf_short_ints_d);
  tcase_add_test(tc_core, test_sprintf_long_doubles);
  tcase_add_test(tc_core, test_sprintf_short_overflow);
  tcase_add_test(tc_core, test_sprintf_int_overflow);
  tcase_add_test(tc_core, test_sprintf_long_overflow);
  tcase_add_test(tc_core, test_sprintf_scientific_zero_double);
  tcase_add_test(tc_core, test_sprintf_scientific_front_double);
  tcase_add_test(tc_core, test_sprintf_scientific_from_negative_double);
  tcase_add_test(tc_core, test_sprintf_scientific_from_big_double);
  tcase_add_test(tc_core, test_sprintf_number_of_characters);
  tcase_add_test(tc_core, test_sprintf_wide_character);
  tcase_add_test(tc_core, test_sprintf_wide_character_string);
  tcase_add_test(tc_core, test_sprintf_hex_lower_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_hex_upper_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_octal_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_octal_problematic_two);
  // tcase_add_test(tc_core, test_sprintf_octal_problematic);
  suite_add_tcase(sprintf_suite, tc_core);
  return sprintf_suite;
}
