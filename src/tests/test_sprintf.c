#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(__linux__)
#include <valgrind/valgrind.h>
#else
#define RUNNING_ON_VALGRIND 0
#endif

#include "run_tests.h"

START_TEST(test_sprintf_int) {
  char lib_res[100];
  char s21_res[100];

  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%+i-% d %d", -100, 0, 3333);
  s21_return = s21_sprintf(s21_res, "%+i-% d %d", -100, 0, 3333);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_int_0_padding) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%+020i-% d %020d", -100, 0, 3333);
  s21_return = s21_sprintf(s21_res, "%+020i-% d %020d", -100, 0, 3333);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_ints_d) {
  char lib_res[500];
  char s21_res[500];

  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(lib_res, "%-15d %60d %d", 1, 1000, INT_MAX);
  s21_return = s21_sprintf(s21_res, "%-15d %60d %d", 1, 1000, INT_MAX);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_ints_d_is_star) {
  char lib_res[500];
  char s21_res[500];

  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(lib_res, "%*d", 1, 10);
  s21_return = s21_sprintf(s21_res, "%*d", 1, 10);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_int_min) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;
  int min_int = INT_MIN;
  lib_return = sprintf(lib_res, "%d %hd", min_int, min_int);
  s21_return = s21_sprintf(s21_res, "%d %hd", min_int, min_int);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_long_ints_d) {
  char lib_res[5000];
  char s21_res[5000];
  int lib_return = 0;
  int s21_return = 0;

  long int max = 2147483647L;
  long int min = -2147483648L;

  lib_return =
      sprintf(lib_res, "%60ld_%ld_%-+15ld_%-+15ld", max, min, max, min);
  s21_return =
      s21_sprintf(s21_res, "%60ld_%ld_%-+15ld_%-+15ld", max, min, max, min);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_short_ints_d) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%60hd_%hd_%-+15hd_%-+15hd", SHRT_MAX, SHRT_MIN,
                       SHRT_MAX, SHRT_MIN);
  s21_return = s21_sprintf(s21_res, "%60hd_%hd_%-+15hd_%-+15hd", SHRT_MAX,
                           SHRT_MIN, SHRT_MAX, SHRT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_ints_i) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%-15i %60i", -1, -1000);
  s21_return = s21_sprintf(s21_res, "%-15i %60i", -1, -1000);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_char) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;

  lib_return =
      sprintf(lib_res, "%c %c %c %c %c %c", '\t', '@', '\n', 2, 50, 123);
  s21_return =
      s21_sprintf(s21_res, "%c %c %c %c %c %c", '\t', '@', '\n', 2, 50, 123);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_char_width) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;

  lib_return =
      sprintf(lib_res, "%20c %3c %-20c %-3c %-20c", 'A', '@', 'A', '@', 50);
  s21_return =
      s21_sprintf(s21_res, "%20c %3c %-20c %-3c %-20c", 'A', '@', 'A', '@', 50);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_char_problematic) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%20c %3c %-20c", 2, 50, 123);
  s21_return = s21_sprintf(s21_res, "%20c %3c %-20c", 2, 50, 123);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_string) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%s %40s %-40s %d %20s", "JOMA",
                       "}l{u3Hb – 3TO 6oJlb", "}l{u3Hb – 3TO 6oJlb", 42, "nan");
  s21_return =
      s21_sprintf(s21_res, "%s %40s %-40s %d %20s", "JOMA",
                  "}l{u3Hb – 3TO 6oJlb", "}l{u3Hb – 3TO 6oJlb", 42, "nan");
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_empty_string) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%s", "");
  s21_return = s21_sprintf(s21_res, "%s", "");
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_problematic_float) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%f", 3.33);
  s21_return = s21_sprintf(s21_res, "%f", 3.33);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_very_float) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;

  lib_return =
      sprintf(lib_res, "% .5f %+.0f %f %+020f", 33.0, 33.33, 3.33, 3.33);
  s21_return =
      s21_sprintf(s21_res, "% .5f %+.0f %f %+020f", 33.0, 33.33, 3.33, 3.33);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_a_bit_float) {
  char lib_res[200];
  char s21_res[200];
  int lib_return = 0;
  int s21_return = 0;

  lib_return = sprintf(lib_res, "%+.0f % .5f % .5f %f", 33.0, 33.0, 3.0, 0.0);
  s21_return =
      s21_sprintf(s21_res, "%+.0f % .5f % .5f %f", 33.0, 33.0, 3.0, 0.0);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_float_width_precision_flag) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;

  float sd = -3.0F;
  float sd2 = 3.123456F;
  float sd3 = 3.333F;
  float sd4 = 3.0F;

  lib_return = sprintf(lib_res, "%-15f %+-20.1f % -10f % f", sd, sd2, sd3, sd4);
  s21_return =
      s21_sprintf(s21_res, "%-15f %+-20.1f % -10f % f", sd, sd2, sd3, sd4);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_float_not_implemented) {
  char lib_res[100];

  float sd = -3.0F;

  int res = s21_sprintf(lib_res, "%F", sd);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;

  long unsigned luim = 4294967296UL;

  lib_return = sprintf(lib_res, "%-15u %60u %u %lu %lu %lu %u %hu %u %u", 1,
                       1000, UINT_MAX, 4294967295UL, 4294967295UL - 333, luim,
                       (UINT_MAX + 500), USHRT_MAX, UINT_MAX, 0);
  s21_return = s21_sprintf(s21_res, "%-15u %60u %u %lu %lu %lu %u %hu %u %u", 1,
                           1000, UINT_MAX, 4294967295UL, 4294967295UL - 333,
                           luim, (UINT_MAX + 500), USHRT_MAX, UINT_MAX, 0);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_unsigned_problematic) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(lib_res, "%-20hu %-30hu %-30u %lu %lu %u %u",
                       USHRT_MAX + 5, UINT_MAX + 10, UINT_MAX, 4294967295UL,
                       4294967295UL + 5, -1000, -65555);
  s21_return = s21_sprintf(s21_res, "%-20hu %-30hu %-30u %lu %lu %u %u",
                           USHRT_MAX + 5, UINT_MAX + 10, UINT_MAX, 4294967295UL,
                           4294967295UL + 5, -1000, -65555);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_long_doubles) {
  char lib_res[10000];
  char s21_res[10000];
  int lib_return = 0;
  int s21_return = 0;
  long double input = 9999999999.9L;
  long double neg_input = -99999999.9L;

  lib_return = sprintf(lib_res, "%Lf %Lf", input, neg_input);
  s21_return = s21_sprintf(s21_res, "%Lf %Lf", input, neg_input);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_short_overflow) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(lib_res, "%hd %hd %hd %hd", (SHRT_MAX + 33),
                       (SHRT_MIN - 10), INT_MAX, INT_MIN);
  s21_return = s21_sprintf(s21_res, "%hd %hd %hd %hd", SHRT_MAX + 33,
                           SHRT_MIN - 10, INT_MAX, INT_MIN);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_int_overflow) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;
  int very_int = INT_MAX;
  int very_min_int = INT_MIN;
  lib_return =
      sprintf(lib_res, "%d %d", (very_int + 33), (very_min_int - 1500));
  s21_return =
      s21_sprintf(s21_res, "%d %d", (very_int + 33), (very_min_int - 1500));

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_long_overflow) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;
  long int long_int = 2147483647L;
  long int long_min_int = -2147483648L;
  lib_return = sprintf(lib_res, "%+40.5ld %-40ld", (long_int + 33),
                       (long_min_int - 1500));
  s21_return = s21_sprintf(s21_res, "%+40.5ld %-40ld", (long_int + 33),
                           (long_min_int - 1500));

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_number_of_characters) {
  char lib_res[100] = {0};
  char s21_res[100] = {0};
  int lib_return = 0;
  int s21_return = 0;
  double num = 1.7976931348623;
  int res_or = 0;
  int res_s21 = 0;

  lib_return = sprintf(lib_res, "sprintf: %+E %% hdhgd %+d hdkjgh %n %%", num,
                       555, &res_or);
  s21_return = s21_sprintf(s21_res, "sprintf: %+E %% hdhgd %+d hdkjgh %n %%",
                           num, 555, &res_s21);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_wide_character) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  wchar_t wide_char1 = L'あ';
  wchar_t wide_char2 = L'は';
  lib_return = sprintf(lib_res, "Широкий символ: %-20lc %6lc fgtffghghgutf",
                       wide_char1, wide_char2);
  s21_return = s21_sprintf(s21_res, "Широкий символ: %-20lc %6lc fgtffghghgutf",
                           wide_char1, wide_char2);

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_wide_character_string) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  wchar_t wide_string1[] = L"こんにちは";
  wchar_t wide_string2[] = L"凛として時雨";

  lib_return = sprintf(lib_res, "Широкий символ: %-20ls %10ls fgtffghghgutf",
                       wide_string1, wide_string2);

  s21_return =
      s21_sprintf(s21_res, "Широкий символ: %-20ls %10ls fgtffghghgutf",
                  wide_string1, wide_string2);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_hex_lower_with_modifiers) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295UL;  // Максимум для unsigned long

  lib_return = sprintf(lib_res, "%x %hx %lx %20lx %-20lx %-40hx", -33, us_value,
                       ul_value, ul_value, ul_value, us_value);
  s21_return = s21_sprintf(s21_res, "%x %hx %lx %20lx %-20lx %-40hx", -33,
                           us_value, ul_value, ul_value, ul_value, us_value);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_hex_upper_with_modifiers) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295UL + 5;  // Максимум для unsigned long

  lib_return = sprintf(lib_res, "%hX %lX %-20hX %20lX", us_value, ul_value,
                       us_value, ul_value);
  s21_return = s21_sprintf(s21_res, "%hX %lX %-20hX %20lX", us_value, ul_value,
                           us_value, ul_value);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_octal_with_modifiers) {
  char lib_res[500];
  char s21_res[500];
  int lib_return = 0;
  int s21_return = 0;
  unsigned short us_value = 0377;  // 255 в десятичной системе
  unsigned long ul_value =
      037777777777UL;  // Максимум для unsigned long в восьмеричной системе
  long int min_long_int = LONG_MIN;
  lib_return =
      sprintf(lib_res, "%ho %lo %lo", us_value, ul_value, min_long_int);
  s21_return =
      s21_sprintf(s21_res, "%ho %lo %lo", us_value, ul_value, min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_octal_negative_long) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;
  long int min_long_int = LONG_MIN;

  lib_return = sprintf(lib_res, "%lo", min_long_int);
  s21_return = s21_sprintf(s21_res, "%lo", min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_octal_width) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;
  int first_test_int = -33;
  int second_test_int = INT_MAX;

  lib_return = sprintf(lib_res, "%20o %-20o", first_test_int, second_test_int);
  s21_return =
      s21_sprintf(s21_res, "%20o %-20o", first_test_int, second_test_int);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_pointer_type) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;
  long double value1 = -44366537.53746L;

  long long value2 = 4568376973LL;

  char value3 = 'f';

  lib_return = sprintf(lib_res, "%-4p %-20p %35p %p", (void*)&value1,
                       (void*)&value2, (void*)&value3, NULL);
  s21_return = s21_sprintf(s21_res, "%-4p %-20p %35p %p", (void*)&value1,
                           (void*)&value2, (void*)&value3, NULL);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_flag_sharp_oxX) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;
  int value1 = -44366537;

  lib_return = sprintf(lib_res, "%#o %#x %#X", value1, value1, value1);
  s21_return = sprintf(s21_res, "%#o %#x %#X", value1, value1, value1);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_scientific_zero_double) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  double num = 0;
  lib_return = sprintf(lib_res, "%e", num);
  s21_return = s21_sprintf(s21_res, "%e", num);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_scientific_front_double) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  double num = 1234.5678;
  lib_return = sprintf(lib_res, "%e", num);
  s21_return = s21_sprintf(s21_res, "%e", num);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_scientific_from_negative_double) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  double num = -0.9;
  lib_return = sprintf(lib_res, "%05e", num);
  s21_return = s21_sprintf(s21_res, "%05e", num);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_mantissa_or_exponent_formats) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;
  double num1 = 14376485974.123;
  double num2 = 3333.3333;

  lib_return = sprintf(lib_res, "%g %G", num1, num2);
  s21_return = s21_sprintf(s21_res, "%g %G", num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_mantissa_or_exponent_negative_value) {
  char lib_res[300];
  char s21_res[300];
  int lib_return = 0;
  int s21_return = 0;
  long double num1 = -566765.1266666L;

  lib_return = sprintf(lib_res, "%Lg %LG", num1, num1);
  s21_return = s21_sprintf(s21_res, "%Lg %LG", num1, num1);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_scientific_loop_precisions) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678910;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%de %%.%de %%.%de %%.%de", precision,
              precision, precision, precision);
  lib_return = sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_return = s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_scientific_from_big_double) {
  char lib_res[200];
  char s21_res[200];
  int lib_return = 0;
  int s21_return = 0;
  long double num = 3.33333333333333333L;
  lib_return = sprintf(lib_res, "%Le", num);
  s21_return = s21_sprintf(s21_res, "%Le", num);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_sci_long_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  long double num1 = 1.2345678L;
  long double num2 = 1.0L;
  long double num3 = 1.2345678910L;
  long double num4 = 1L;
  long double num5 = 33.2345678L;
  long double num6 = 333.0L;
  long double num7 = 33.2345678910L;
  long double num8 = 555555.1L;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string,
              "%%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe",
              precision, precision, precision, precision, precision, precision,
              precision, precision);
  lib_return = sprintf(lib_res, format_string, num1, num2, num3, num4, num5,
                       num6, num7, num8);
  s21_return = s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5,
                           num6, num7, num8);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_scientific_zero_loop_precisions) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  double zero = 0.0;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%de %%e %%.e", precision);

  lib_return = sprintf(lib_res, format_string, zero, zero, zero);

  s21_return = s21_sprintf(s21_res, format_string, zero, zero, zero);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678940;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%dg %%.%dg %%.%dg %%.%dg", precision,
              precision, precision, precision);

  lib_return = sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_return = s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.0L;
  long double num5 = 4444.7L;
  long double num6 = 4444.4L;
  long double num7 = 0.923423L;
  long double num8 = 99999999999999.92L;
  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string,
              "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg",
              precision, precision, precision, precision, precision, precision,
              precision, precision);

  lib_return = sprintf(lib_res, format_string, num1, num2, num3, num4, num5,
                       num6, num7, num8);
  s21_return = s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5,
                           num6, num7, num8);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_zero_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  double num1 = 0;
  double num2 = 0.000;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%dg %%.g %%.%dg %%.g", precision, precision);
  lib_return = sprintf(lib_res, format_string, num1, num2, num1, num2);
  s21_return = s21_sprintf(s21_res, format_string, num1, num2, num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(
      lib_res,
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
      0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  s21_return = s21_sprintf(
      s21_res,
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
      0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(
      lib_res,
      "%G %G %G %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %G %G %G",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  s21_return = s21_sprintf(
      s21_res,
      "%G %G %G %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %G %G %G",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(
      lib_res,
      "%.0G %.0G %.0G %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0G %.0G %.0G",
      0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);

  s21_return = s21_sprintf(
      s21_res,
      "%.0G %.0G %.0G %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0G %.0G %.0G",
      0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  lib_return = sprintf(
      lib_res,
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);

  s21_return = s21_sprintf(
      s21_res,
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_interesting) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  double num5 = 0.5333333333;
  double num6 = 1.5333333333;

  long double ld_value = 1.000000000000000003L;
  // Casting the same value to double to demonstrate loss of precision
  double d_value = (double)ld_value;

  lib_return =
      sprintf(lib_res, "%-5g %g %g %20Lg", num5, num6, d_value, ld_value);
  s21_return =
      s21_sprintf(s21_res, "%-5g %g %g %20Lg", num5, num6, d_value, ld_value);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_long_double) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  long double ld_value = 1.000000000000000003L;
  long double ld_value_2 = 1123123.00L;
  long double ld_value_3 = 333.000000501L;
  long double ld_value_4 = 9.00000000000501001L;

  lib_return = sprintf(lib_res, "%.18Lf %.18Lf %.18Lf %.18Lf", ld_value,
                       ld_value_2, ld_value_3, ld_value_4);
  s21_return = s21_sprintf(s21_res, "%.18Lf %.18Lf %.18Lf %.18Lf", ld_value,
                           ld_value_2, ld_value_3, ld_value_4);

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_double_long_double) {
  char lib_res[100];
  char s21_res[100];
  int lib_return = 0;
  int s21_return = 0;
  long double ld_value = 1.000000000000000003L;
  // Casting the same value to double to demonstrate loss of precision
  double d_value = (double)ld_value;

  lib_return = sprintf(lib_res, "%.18Lf %.18f", ld_value, d_value);
  s21_return = s21_sprintf(s21_res, "%.18Lf %.18f", ld_value, d_value);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  int pr = _i;  // supplied through add_loop_test func
  char format_string[500];
  s21_sprintf(
      format_string,
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr);

  lib_return = sprintf(
      lib_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.23456,
      0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234,
      1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0,
      12.2, 12.23, 12.234, 12.2345, 12.23456, 12.234567, 12.2345678,
      12.23456789, 12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345,
      123.23456, 123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_return = s21_sprintf(
      s21_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.23456,
      0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234,
      1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0,
      12.2, 12.23, 12.234, 12.2345, 12.23456, 12.234567, 12.2345678,
      12.23456789, 12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345,
      123.23456, 123.234567, 123.2345678, 123.23456789, 123.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  lib_return = sprintf(
      lib_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
      1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
      12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
      12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910, 123456.0,
      123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
      123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0, 1234567.2,
      1234567.23, 1234567.234, 1234567.2345, 1234567.23456, 1234567.234567,
      1234567.2345678, 1234567.23456789, 1234567.2345678910);

  s21_return = s21_sprintf(
      s21_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
      1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
      12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
      12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910, 123456.0,
      123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
      123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0, 1234567.2,
      1234567.23, 1234567.234, 1234567.2345, 1234567.23456, 1234567.234567,
      1234567.2345678, 1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p3) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  lib_return = sprintf(
      lib_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93446, 0.934567,
      0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49, 9.500, 9.5001,
      9.93456, 9.934567, 9.9945678, 9.93456789, 9.9345678910, 99.9, 99.9, 99.93,
      99.934, 99.2934, 99.29345, 99.934567, 99.9345678, 99.93456789,
      99.9345678910, 993.0, 923.2, 923.23, 923.234, 923.2345, 923.23456,
      923.234567, 923.2345678, 923.23456789, 923.2345678910);
  s21_return = s21_sprintf(
      s21_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93446, 0.934567,
      0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49, 9.500, 9.5001,
      9.93456, 9.934567, 9.9945678, 9.93456789, 9.9345678910, 99.9, 99.9, 99.93,
      99.934, 99.2934, 99.29345, 99.934567, 99.9345678, 99.93456789,
      99.9345678910, 993.0, 923.2, 923.23, 923.234, 923.2345, 923.23456,
      923.234567, 923.2345678, 923.23456789, 923.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p4) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
      "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  lib_return = sprintf(
      lib_res, format_string, 9934.9, 9934.9, 9934.93, 9934.934, 9934.9345,
      9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
      99999.0, 99999.9, 99999.93, 99999.934, 99999.9345, 99999.93456,
      99999.934567, 99999.9345678, 99999.93456789, 99999.9345678910, 999999.0,
      999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456, 999999.234567,
      999999.2345678, 999999.23456789, 999999.2345678910, 9999999.0, 9999999.9,
      9999999.93, 9999999.934, 9999999.9345, 9999999.93456, 9999999.934567,
      9999999.9345678, 9999999.93456789, 9999999.9345678910);

  s21_return = s21_sprintf(
      s21_res, format_string, 9934.9, 9934.9, 9934.93, 9934.934, 9934.9345,
      9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
      99999.0, 99999.9, 99999.93, 99999.934, 99999.9345, 99999.93456,
      99999.934567, 99999.9345678, 99999.93456789, 99999.9345678910, 999999.0,
      999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456, 999999.234567,
      999999.2345678, 999999.23456789, 999999.2345678910, 9999999.0, 9999999.9,
      9999999.93, 9999999.934, 9999999.9345, 9999999.93456, 9999999.934567,
      9999999.9345678, 9999999.93456789, 9999999.9345678910);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_dbl_set_precision_p1) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
              "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
              "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
              "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
              "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  lib_return = sprintf(
      lib_res, format_string, 9234.0L, 9234.9L, 9234.93L, 9234.934L, 9234.9345L,
      9234.93456L, 9234.934567L, 9234.9345678L, 9234.93456789L,
      9234.9345678910L, 99999.0L, 99999.9L, 99999.93L, 99999.934L, 99999.9345L,
      99999.93456L, 99999.934567L, 99999.9345678L, 99999.93456789L,
      99999.9345678910L, 999999.0L, 999999.2L, 999999.23L, 999999.234L,
      999999.2345L, 999999.23456L, 999999.234567L, 999999.2345678L,
      999999.23456789L, 999999.2345678910L, 9999999.0L, 9999999.9L, 9999999.93L,
      9999999.934L, 9999999.9345L, 9999999.93456L, 9999999.934567L,
      9999999.9345678L, 9999999.93456789L, 9999999.9345678910L);

  s21_return = s21_sprintf(
      s21_res, format_string, 9234.0L, 9234.9L, 9234.93L, 9234.934L, 9234.9345L,
      9234.93456L, 9234.934567L, 9234.9345678L, 9234.93456789L,
      9234.9345678910L, 99999.0L, 99999.9L, 99999.93L, 99999.934L, 99999.9345L,
      99999.93456L, 99999.934567L, 99999.9345678L, 99999.93456789L,
      99999.9345678910L, 999999.0L, 999999.2L, 999999.23L, 999999.234L,
      999999.2345L, 999999.23456L, 999999.234567L, 999999.2345678L,
      999999.23456789L, 999999.2345678910L, 9999999.0L, 9999999.9L, 9999999.93L,
      9999999.934L, 9999999.9345L, 9999999.93456L, 9999999.934567L,
      9999999.9345678L, 9999999.93456789L, 9999999.9345678910L);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_dbl_set_precision_p2) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  long double num7_1 = 1234567.0L;
  long double num7_2 = 1234567.2L;
  long double num7_3 = 1234567.23L;
  long double num7_4 = 1234567.234L;
  long double num7_5 = 1234567.2345L;
  long double num7_6 = 1234567.23456L;
  long double num7_7 = 1234567.234567L;
  long double num7_8 = 1234567.2345678L;
  long double num7_9 = 1234567.23456789L;
  long double num7_10 = 1234567.2345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  lib_return = sprintf(lib_res, format_string, num7_1, num7_2, num7_3, num7_4,
                       num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_return =
      s21_sprintf(s21_res, format_string, num7_1, num7_2, num7_3, num7_4,
                  num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

START_TEST(test_sprintf_loop_star) {
  char lib_res[1000];
  char s21_res[1000];
  int lib_return = 0;
  int s21_return = 0;
  long double long_double_num = 9234.93456L;
  long long_num = 9234L;
  unsigned unsinged_num = 1234567U;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string, "%%*.*Lf %%*.*ld %%*.*u");

  lib_return = sprintf(lib_res, format_string, pr, pr, long_double_num, pr, pr,
                       long_num, pr, pr, unsinged_num);

  s21_return = sprintf(s21_res, format_string, pr, pr, long_double_num, pr, pr,
                       long_num, pr, pr, unsinged_num);

  ck_assert_str_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_return, s21_return);
}
END_TEST

///////////////////

START_TEST(test_sprintf_sharp_g_spec_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678940;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%#.%dg %%#.%dg %%#.%dg %%#.%dg", precision,
              precision, precision, precision);

  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_long_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.0L;
  long double num5 = 4444.7L;
  long double num6 = 4444.4L;
  long double num7 = 0.923423L;
  long double num8 = 99999999999998.8L;
  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(
      format_string,
      "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg",
      precision, precision, precision, precision, precision, precision,
      precision, precision);

  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_zero_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 0;
  double num2 = 0.000;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%#.%dg %%#.g %%#.%dg %%#.g", precision,
              precision);

  sprintf(lib_res, format_string, num1, num2, num1, num2);
  s21_sprintf(s21_res, format_string, num1, num2, num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g %#g",
          0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678,
          0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456,
          1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
          12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
          12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
          123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(
      s21_res,
      "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
      "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
      "%#g %#g %#g %#g %#g %#g",
      0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g %#g",
          1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
          1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2,
          12345.23, 12345.234, 12345.2345, 12345.23456, 12345.234567,
          12345.2345678, 12345.23456789, 12345.2345678910, 123456.0, 123456.2,
          123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
          123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0,
          1234567.2, 1234567.23, 1234567.234, 1234567.2345, 1234567.23456,
          1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);
  s21_sprintf(s21_res,
              "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
              "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
              "%#g %#g %#g %#g %#g %#g %#g %#g",
              1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456,
              1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
              12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
              12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910,
              123456.0, 123456.2, 123456.23, 123456.234, 123456.2345,
              123456.23456, 123456.234567, 123456.2345678, 123456.23456789,
              123456.2345678910, 1234567.0, 1234567.2, 1234567.23, 1234567.234,
              1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
              1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_p1) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
          0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678,
          0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456,
          1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
          12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
          12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
          123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(s21_res,
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
              0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678,
              0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456,
              1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
              12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
              12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
              123.234567, 123.2345678, 123.23456789, 123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_p2) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
          "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
          1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
          1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2,
          12345.23, 12345.234, 12345.2345, 12345.23456, 12345.234567,
          12345.2345678, 12345.23456789, 12345.2345678910, 123456.0, 123456.2,
          123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
          123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0,
          1234567.2, 1234567.23, 1234567.234, 1234567.2345, 1234567.23456,
          1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);
  s21_sprintf(s21_res,
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
              "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
              1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456,
              1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
              12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
              12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910,
              123456.0, 123456.2, 123456.23, 123456.234, 123456.2345,
              123456.23456, 123456.234567, 123456.2345678, 123456.23456789,
              123456.2345678910, 1234567.0, 1234567.2, 1234567.23, 1234567.234,
              1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
              1234567.23456789, 1234567.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_interesting) {
  char lib_res[1000];
  char s21_res[1000];
  double num5 = 0.5333333333;
  double num6 = 1.5333333333;

  long double ld_value = 1.000000000000000003L;
  // Casting the same value to double to demonstrate loss of precision
  double d_value = (double)ld_value;

  sprintf(lib_res, "%-#5g %#g %#g %#20Lg", num5, num6, d_value, ld_value);
  s21_sprintf(s21_res, "%-#5g %#g %#g %#20Lg", num5, num6, d_value, ld_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_double_nan_inf) {
  char lib_res[50];
  char s21_res[50];

  long double ld_value = 1.0e+4932L;
  double inf_value = (double)ld_value;
  double nan_value = sqrt(-1.0);

  sprintf(lib_res, "%-4f %f", nan_value, inf_value);
  s21_sprintf(s21_res, "%-4f %f", nan_value, inf_value);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_double_NaN_INF) {
  char lib_res[50];
  char s21_res[50];

  long double ld_value = 1.0e+4932L;
  double inf_value = (double)ld_value;
  double nan_value = sqrt(-1.0);

  sprintf(lib_res, "%-4G %G", nan_value, inf_value);
  s21_sprintf(s21_res, "%-4G %G", nan_value, inf_value);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_double_nan_inf) {
  char lib_res[50];
  char s21_res[50];

  long double ld_value = 1.0e+4932L;
  double inf_value = (double)ld_value;
  double nan_value = sqrt(-1.0);

  sprintf(lib_res, "%-#4f %#f", nan_value, inf_value);
  s21_sprintf(s21_res, "%-#4f %#f", nan_value, inf_value);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_long_double) {
  char lib_res[100];
  char s21_res[100];

  long double ld_value = 1.000000000000000003L;
  long double ld_value_2 = 1123123.00L;
  long double ld_value_3 = 333.000000501L;
  long double ld_value_4 = 9.00000000000501001L;

  sprintf(lib_res, "%#.18Lf %#.18Lf %#.18Lf %#.18Lf", ld_value, ld_value_2,
          ld_value_3, ld_value_4);
  s21_sprintf(s21_res, "%#.18Lf %#.18Lf %#.18Lf %#.18Lf", ld_value, ld_value_2,
              ld_value_3, ld_value_4);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_double_long_double) {
  char lib_res[100];
  char s21_res[100];

  long double ld_value = 1.000000000000000003L;
  // Casting the same value to double to demonstrate loss of precision
  double d_value = (double)ld_value;

  sprintf(lib_res, "%#.18Lf %#.18f", ld_value, d_value);
  s21_sprintf(s21_res, "%#.18Lf %#.18f", ld_value, d_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_p1) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456,
          0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234,
          1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0,
          12.2, 12.23, 12.234, 12.2345, 12.23456, 12.234567, 12.2345678,
          12.23456789, 12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345,
          123.23456, 123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(s21_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456,
              0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23,
              1.234, 1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789,
              1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
              12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2,
              123.23, 123.234, 123.2345, 123.23456, 123.234567, 123.2345678,
              123.23456789, 123.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_p2) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
              "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
          1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
          12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
          12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910,
          123456.0, 123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456,
          123456.234567, 123456.2345678, 123456.23456789, 123456.2345678910,
          1234567.0, 1234567.2, 1234567.23, 1234567.234, 1234567.2345,
          1234567.23456, 1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);

  s21_sprintf(
      s21_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
      1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
      12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
      12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910, 123456.0,
      123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
      123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0, 1234567.2,
      1234567.23, 1234567.234, 1234567.2345, 1234567.23456, 1234567.234567,
      1234567.2345678, 1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_p3) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93456,
          0.934567, 0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49, 9.500,
          9.5001, 9.93456, 9.934567, 9.9945678, 9.93456789, 9.9345678910, 95.9,
          95.9, 95.93, 95.934, 95.2934, 95.29345, 95.934567, 95.9345678,
          95.93456789, 95.9345678910, 993.0, 923.2, 923.23, 923.234, 923.2345,
          923.23456, 923.234567, 923.2345678, 923.23456789, 923.2345678910);
  s21_sprintf(s21_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93456,
              0.934567, 0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49,
              9.500, 9.5001, 9.93456, 9.934567, 9.9945678, 9.93456789,
              9.9345678910, 95.9, 95.9, 95.93, 95.934, 95.2934, 95.29345,
              95.934567, 95.9345678, 95.93456789, 95.9345678910, 993.0, 923.2,
              923.23, 923.234, 923.2345, 923.23456, 923.234567, 923.2345678,
              923.23456789, 923.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_p4) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 9939.9, 9934.9, 9934.93, 9934.934, 9934.9345,
          9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
          99999.0, 99998.9, 99998.93, 99998.934, 99998.9345, 99998.93456,
          99998.934567, 99998.9345678, 99998.93456789, 99998.9345678910,
          999999.0, 999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456,
          999999.234567, 999999.2345678, 999999.23456789, 999999.2345678910,
          9999999.0, 9999998.9, 9999998.93, 9999998.934, 9999998.9345,
          9999998.93456, 9999998.934567, 9999998.9345678, 9999998.93456789,
          9999998.9345678910);

  s21_sprintf(
      s21_res, format_string, 9939.9, 9934.9, 9934.93, 9934.934, 9934.9345,
      9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
      99999.0, 99998.9, 99998.93, 99998.934, 99998.9345, 99998.93456,
      99998.934567, 99998.9345678, 99998.93456789, 99998.9345678910, 999999.0,
      999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456, 999999.234567,
      999999.2345678, 999999.23456789, 999999.2345678910, 9999999.0, 9999998.9,
      9999998.93, 9999998.934, 9999998.9345, 9999998.93456, 9999998.934567,
      9999998.9345678, 9999998.93456789, 9999998.9345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_ldbl_set_precision_p1) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
      "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
      "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
      "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
      "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 9230.9L, 9234.9L, 9234.93L, 9234.934L,
          9234.9345L, 9234.93456L, 9234.934567L, 9234.9345678L, 9234.93456789L,
          9234.9345678910L, 99999.0L, 99998.9L, 99998.93L, 99998.934L,
          99998.9345L, 99998.93456L, 99998.934567L, 99998.9345678L,
          99998.93456789L, 99998.9345678910L, 999999.0L, 999999.2L, 999999.23L,
          999999.234L, 999999.2345L, 999999.23456L, 999999.234567L,
          999999.2345678L, 999999.23456789L, 999999.2345678910L, 9999999.0L,
          9999998.9L, 9999998.93L, 9999998.934L, 9999998.9345L, 9999998.93456L,
          9999998.934567L, 9999998.9345678L, 9999998.93456789L,
          9999998.9345678910L);
  s21_sprintf(s21_res, format_string, 9230.9L, 9234.9L, 9234.93L, 9234.934L,
              9234.9345L, 9234.93456L, 9234.934567L, 9234.9345678L,
              9234.93456789L, 9234.9345678910L, 99999.0L, 99998.9L, 99998.93L,
              99998.934L, 99998.9345L, 99998.93456L, 99998.934567L,
              99998.9345678L, 99998.93456789L, 99998.9345678910L, 999999.0L,
              999999.2L, 999999.23L, 999999.234L, 999999.2345L, 999999.23456L,
              999999.234567L, 999999.2345678L, 999999.23456789L,
              999999.2345678910L, 9999999.0L, 9999998.9L, 9999998.93L,
              9999998.934L, 9999998.9345L, 9999998.93456L, 9999998.934567L,
              9999998.9345678L, 9999998.93456789L, 9999998.9345678910L);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_ldbl_set_precision_p2) {
  char lib_res[1000];
  char s21_res[1000];

  double num7 = 1234567;
  double num7_1 = 1234567.0;
  double num7_2 = 1234567.2;
  double num7_3 = 1234567.23;
  double num7_4 = 1234567.234;
  double num7_5 = 1234567.2345;
  double num7_6 = 1234567.23456;
  double num7_7 = 1234567.234567;
  double num7_8 = 1234567.2345678;
  double num7_9 = 1234567.23456789;
  double num7_10 = 1234567.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num7, num7_1, num7_2, num7_3, num7_4, num7_5,
          num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num7, num7_1, num7_2, num7_3, num7_4,
              num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_loop_star) {
  char lib_res[1000];
  char s21_res[1000];

  long double long_double_num = 9234.93456L;
  long long_num = 9234L;
  unsigned unsinged_num = 1234567U;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string, "%%#*.*Lf %%#*.*ld %%#*.*u");

  sprintf(lib_res, format_string, pr, pr, long_double_num, pr, pr, long_num, pr,
          pr, unsinged_num);

  sprintf(s21_res, format_string, pr, pr, long_double_num, pr, pr, long_num, pr,
          pr, unsinged_num);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

/////////

START_TEST(test_sprintf_sharp_very_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "% #.5f %+#.0f %#f %+#020f", 33.0, 33.33, 3.33, 3.33);
  s21_sprintf(s21_res, "% #.5f %+#.0f %#f %+#020f", 33.0, 33.33, 3.33, 3.33);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_a_bit_float) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+#.0f % #.5f % #.5f", 33.0, 33.0, 3.0);
  s21_sprintf(s21_res, "%+#.0f % #.5f % #.5f", 33.0, 33.0, 3.0);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_float_width_precision_flag) {
  char lib_res[100];
  char s21_res[100];
  float sd = -3.0F;
  float sd2 = 3.123456F;
  float sd3 = 3.333F;
  float sd4 = 3.3F;

  sprintf(lib_res, "%-#15f %+-#20.1f % -#10f % #f", sd, sd2, sd3, sd4);
  s21_sprintf(s21_res, "%-#15f %+-#20.1f % -#10f % #f", sd, sd2, sd3, sd4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

//////

START_TEST(test_sprintf_sharp_hex_lower_with_modifiers) {
  char lib_res[1000];
  char s21_res[1000];

  unsigned short us_value = 255U;
  unsigned long ul_value = 4294967295UL;  // Максимум для unsigned long

  sprintf(lib_res, "%#x %#hx %#lx %#20lx %-#20lx %-#40hx", -33, us_value,
          ul_value, ul_value, ul_value, us_value);
  s21_sprintf(s21_res, "%#x %#hx %#lx %#20lx %-#20lx %-#40hx", -33, us_value,
              ul_value, ul_value, ul_value, us_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_hex_upper_with_modifiers) {
  char lib_res[100];
  char s21_res[100];

  unsigned short us_value = 255U;
  unsigned long ul_value = 4294967295UL + 5;  // Максимум для unsigned long

  sprintf(lib_res, "%#hX %#lX %-#20hX %#20lX", us_value, ul_value, us_value,
          ul_value);
  s21_sprintf(s21_res, "%#hX %#lX %-#20hX %#20lX", us_value, ul_value, us_value,
              ul_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_octal_with_modifiers) {
  char lib_res[500];
  char s21_res[500];

  unsigned short us_value = 0377U;  // 255 в десятичной системе
  unsigned long ul_value =
      037777777777UL;  // Максимум для unsigned long в восьмеричной системе
  long int min_long_int = LONG_MIN;
  sprintf(lib_res, "%#20ho %#-20lo %#lo", us_value, ul_value, min_long_int);
  s21_sprintf(s21_res, "%#20ho %#-20lo %#lo", us_value, ul_value, min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_octal_negative_long) {
  char lib_res[300];
  char s21_res[300];

  long int min_long_int = LONG_MIN;

  sprintf(lib_res, "%#lo", min_long_int);
  s21_sprintf(s21_res, "%#lo", min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_octal_width) {
  char lib_res[300];
  char s21_res[300];

  int first_test_int = -33;
  int second_test_int = INT_MAX;

  sprintf(lib_res, "%#20o %-#20o", first_test_int, second_test_int);
  s21_sprintf(s21_res, "%#20o %-#20o", first_test_int, second_test_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

//////////////////// scientific sharp below

START_TEST(test_sprintf_sharp_scientific_zero_double) {
  char lib_res[100];
  char s21_res[100];
  double num = 0;
  sprintf(lib_res, "%#020e", num);
  s21_sprintf(s21_res, "%#020e", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_scientific_front_double) {
  char lib_res[100];
  char s21_res[100];
  double num = 1234.5678;
  sprintf(lib_res, "%-#20e", num);
  s21_sprintf(s21_res, "%-#20e", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_scientific_from_negative_double) {
  char lib_res[100];
  char s21_res[100];
  double num = -0.9;
  sprintf(lib_res, "%-#20E", num);
  s21_sprintf(s21_res, "%-#20E", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_mantissa_or_exponent_formats) {
  char lib_res[300];
  char s21_res[300];

  double num1 = 14376485974.123;
  double num2 = 3333.3333;

  sprintf(lib_res, "%#g %#G", num1, num2);
  s21_sprintf(s21_res, "%#g %#G", num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_mantissa_or_exponent_negative_value) {
  char lib_res[300];
  char s21_res[300];

  long double num1 = -566765.1266666L;

  sprintf(lib_res, "%#Lg %#LG", num1, num1);
  s21_sprintf(s21_res, "%#Lg %#LG", num1, num1);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_sci_loop_precisions) {
  char lib_res[100];
  char s21_res[100];
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678910;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%de %%.%de %%.%de %%.%de", precision,
              precision, precision, precision);
  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_scientific_from_big_double) {
  char lib_res[200];
  char s21_res[200];
  long double num = 3.33333333333333333L;
  sprintf(lib_res, "%#Le", num);
  s21_sprintf(s21_res, "%#Le", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_sci_long_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 1.2345678L;
  long double num2 = 1.0L;
  long double num3 = 1.2345678910L;
  long double num4 = 1L;
  long double num5 = 33.2345678L;
  long double num6 = 333.0L;
  long double num7 = 33.2345678910L;
  long double num8 = 555555.1L;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string,
              "%%#.%dLe %%#.%dLe %%#.%dLe %%#4.%dLe %%#.%dLE %%#10.%dLe "
              "%%#.%dLE %%#.%dLe",
              precision, precision, precision, precision, precision, precision,
              precision, precision);
  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_sci_zero_loop_precisions) {
  char lib_res[100];
  char s21_res[100];

  double zero = 0.0;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%#.%de %%#e %%#.e", precision);

  sprintf(lib_res, format_string, zero, zero, zero);

  s21_sprintf(s21_res, format_string, zero, zero, zero);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

/*
 /\_/\
( o.o )
 > ^ <
*/
/////////various width with G-spec, GO!

START_TEST(test_sprintf_g_spec_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678940;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%4.%dg %%4.%dg %%4.%dg %%4.%dg", precision,
              precision, precision, precision);

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_long_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.0L;
  long double num5 = 4444.7L;
  long double num6 = 4444.4L;
  long double num7 = 0.923423L;
  long double num8 = 99999999999999.92L;
  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(
      format_string,
      "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg",
      precision, precision, precision, precision, precision, precision,
      precision, precision);

  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_zero_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 0;
  double num2 = 0.000;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%4.%dg %%4.g %%4.%dg %%4.g", precision,
              precision);
  sprintf(lib_res, format_string, num1, num2, num1, num2);
  s21_sprintf(s21_res, format_string, num1, num2, num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g",
          0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678,
          0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456,
          1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
          12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
          12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
          123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(s21_res,
              "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
              "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
              "%4g %4g %4g %4g %4g %4g %4g %4g",
              0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678,
              0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456,
              1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
              12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
              12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
              123.234567, 123.2345678, 123.23456789, 123.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g",
          1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
          1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2,
          12345.23, 12345.234, 12345.2345, 12345.23456, 12345.234567,
          12345.2345678, 12345.23456789, 12345.2345678910, 123456.0, 123456.2,
          123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
          123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0,
          1234567.2, 1234567.23, 1234567.234, 1234567.2345, 1234567.23456,
          1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);
  s21_sprintf(
      s21_res,
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
      "%4g %4g %4g %4g %4g %4g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
          0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678,
          0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456,
          1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
          12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
          12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
          123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(s21_res,
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
              0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678,
              0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456,
              1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0, 12.2, 12.23,
              12.234, 12.2345, 12.23456, 12.234567, 12.2345678, 12.23456789,
              12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345, 123.23456,
              123.234567, 123.2345678, 123.23456789, 123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res,
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
          1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
          1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2,
          12345.23, 12345.234, 12345.2345, 12345.23456, 12345.234567,
          12345.2345678, 12345.23456789, 12345.2345678910, 123456.0, 123456.2,
          123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
          123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0,
          1234567.2, 1234567.23, 1234567.234, 1234567.2345, 1234567.23456,
          1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);
  s21_sprintf(s21_res,
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
              "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
              1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456,
              1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
              12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
              12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910,
              123456.0, 123456.2, 123456.23, 123456.234, 123456.2345,
              123456.23456, 123456.234567, 123456.2345678, 123456.23456789,
              123456.2345678910, 1234567.0, 1234567.2, 1234567.23, 1234567.234,
              1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
              1234567.23456789, 1234567.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

//////hm
START_TEST(test_sprintf_g_spec_set_precision_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456,
          0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234,
          1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0,
          12.2, 12.23, 12.234, 12.2345, 12.23456, 12.234567, 12.2345678,
          12.23456789, 12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345,
          123.23456, 123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(s21_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456,
              0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23,
              1.234, 1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789,
              1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
              12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2,
              123.23, 123.234, 123.2345, 123.23456, 123.234567, 123.2345678,
              123.23456789, 123.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
          1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
          12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
          12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910,
          123456.0, 123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456,
          123456.234567, 123456.2345678, 123456.23456789, 123456.2345678910,
          1234567.0, 1234567.2, 1234567.23, 1234567.234, 1234567.2345,
          1234567.23456, 1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);
  s21_sprintf(
      s21_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
      1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
      12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
      12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910, 123456.0,
      123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
      123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0, 1234567.2,
      1234567.23, 1234567.234, 1234567.2345, 1234567.23456, 1234567.234567,
      1234567.2345678, 1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_width_4_p3) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93456,
          0.934567, 0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49, 9.500,
          9.5001, 9.93456, 9.934567, 9.9945678, 9.93456789, 9.9345678910, 99.9,
          99.9, 99.93, 99.934, 99.2934, 99.29345, 99.934567, 99.9345678,
          99.93456789, 99.9345678910, 993.0, 923.2, 923.23, 923.234, 923.2345,
          923.23456, 923.234567, 923.2345678, 923.23456789, 923.2345678910);
  s21_sprintf(s21_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93456,
              0.934567, 0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49,
              9.500, 9.5001, 9.93456, 9.934567, 9.9945678, 9.93456789,
              9.9345678910, 99.9, 99.9, 99.93, 99.934, 99.2934, 99.29345,
              99.934567, 99.9345678, 99.93456789, 99.9345678910, 993.0, 923.2,
              923.23, 923.234, 923.2345, 923.23456, 923.234567, 923.2345678,
              923.23456789, 923.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_width_4_p4) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
              "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 9939.9, 9934.9, 9934.93, 9934.934, 9934.9345,
          9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
          99999.0, 99999.9, 99999.93, 99999.934, 99999.9345, 99999.93456,
          99999.934567, 99999.9345678, 99999.93456789, 99999.9345678910,
          999999.0, 999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456,
          999999.234567, 999999.2345678, 999999.23456789, 999999.2345678910,
          9999999.0, 9999999.9, 9999999.93, 9999999.934, 9999999.9345,
          9999999.93456, 9999999.934567, 9999999.9345678, 9999999.93456789,
          9999999.9345678910);
  s21_sprintf(
      s21_res, format_string, 9939.9, 9934.9, 9934.93, 9934.934, 9934.9345,
      9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
      99999.0, 99999.9, 99999.93, 99999.934, 99999.9345, 99999.93456,
      99999.934567, 99999.9345678, 99999.93456789, 99999.9345678910, 999999.0,
      999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456, 999999.234567,
      999999.2345678, 999999.23456789, 999999.2345678910, 9999999.0, 9999999.9,
      9999999.93, 9999999.934, 9999999.9345, 9999999.93456, 9999999.934567,
      9999999.9345678, 9999999.93456789, 9999999.9345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_ldbl_set_precision_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
      "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
      "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
      "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
      "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 9239.9L, 9234.9L, 9234.93L, 9234.934L,
          9234.9345L, 9234.93456L, 9234.934567L, 9234.9345678L, 9234.93456789L,
          9234.9345678910L, 99999.0L, 99999.9L, 99999.93L, 99999.934L,
          99999.9345L, 99999.93456L, 99999.934567L, 99999.9345678L,
          99999.93456789L, 99999.9345678910L, 999999.0L, 999999.2L, 999999.23L,
          999999.234L, 999999.2345L, 999999.23456L, 999999.234567L,
          999999.2345678L, 999999.23456789L, 999999.2345678910L, 9999999.0L,
          9999999.9L, 9999999.93L, 9999999.934L, 9999999.9345L, 9999999.93456L,
          9999999.934567L, 9999999.9345678L, 9999999.93456789L,
          9999999.9345678910L);
  s21_sprintf(s21_res, format_string, 9239.9L, 9234.9L, 9234.93L, 9234.934L,
              9234.9345L, 9234.93456L, 9234.934567L, 9234.9345678L,
              9234.93456789L, 9234.9345678910L, 99999.0L, 99999.9L, 99999.93L,
              99999.934L, 99999.9345L, 99999.93456L, 99999.934567L,
              99999.9345678L, 99999.93456789L, 99999.9345678910L, 999999.0L,
              999999.2L, 999999.23L, 999999.234L, 999999.2345L, 999999.23456L,
              999999.234567L, 999999.2345678L, 999999.23456789L,
              999999.2345678910L, 9999999.0L, 9999999.9L, 9999999.93L,
              9999999.934L, 9999999.9345L, 9999999.93456L, 9999999.934567L,
              9999999.9345678L, 9999999.93456789L, 9999999.9345678910L);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_ldbl_set_precision_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  long double num7_1 = 1234567.0L;
  long double num7_2 = 1234567.2L;
  long double num7_3 = 1234567.23L;
  long double num7_4 = 1234567.234L;
  long double num7_5 = 1234567.2345L;
  long double num7_6 = 1234567.23456L;
  long double num7_7 = 1234567.234567L;
  long double num7_8 = 1234567.2345678L;
  long double num7_9 = 1234567.23456789L;
  long double num7_10 = 1234567.2345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg %%4.%dLg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num7_1, num7_2, num7_3, num7_4, num7_5,
          num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num7_1, num7_2, num7_3, num7_4, num7_5,
              num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678940;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg", precision,
              precision, precision, precision);

  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_long_loop_precs_wd_4) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.0L;
  long double num5 = 4444.7L;
  long double num6 = 4444.4L;
  long double num7 = 0.923423L;
  long double num8 = 99999999999998.92L;
  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(
      format_string,
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg",
      precision, precision, precision, precision, precision, precision,
      precision, precision);

  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_0_loop_precisions_wd_4) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 0;
  double num2 = 0.000;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%#4.%dg %%#4.g %%#4.%dg %%#4.g", precision,
              precision);

  sprintf(lib_res, format_string, num1, num2, num1, num2);
  s21_sprintf(s21_res, format_string, num1, num2, num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(
      lib_res,
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g",
      0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  s21_sprintf(
      s21_res,
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g",
      0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 1.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(
      lib_res,
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  s21_sprintf(
      s21_res,
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(
      lib_res,
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
      0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  s21_sprintf(
      s21_res,
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
      0.0, 0.2, 0.23, 0.234, 5.2345, 0.23456, 0.234567, 0.2345678, 0.23456789,
      0.2345678910, 1.0, 1.2, 1.23, 1.234, 5.2345, 1.23456, 1.234567, 1.2345678,
      1.23456789, 1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
      12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2, 123.23,
      123.234, 123.2345, 123.23456, 123.234567, 123.2345678, 123.23456789,
      123.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(
      lib_res,
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  s21_sprintf(
      s21_res,
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
      "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
      1234.0, 1234.2, 1234.23, 1234.234, 1234.2345, 1234.23456, 1234.234567,
      1234.2345678, 1234.23456789, 1234.2345678910, 12345.0, 12345.2, 12345.23,
      12345.234, 12345.2345, 12345.23456, 12345.234567, 12345.2345678,
      12345.23456789, 12345.2345678910, 123456.0, 123456.2, 123456.23,
      123456.234, 123456.2345, 123456.23456, 123456.234567, 123456.2345678,
      123456.23456789, 123456.2345678910, 1234567.0, 1234567.2, 1234567.23,
      1234567.234, 1234567.2345, 1234567.23456, 1234567.234567, 1234567.2345678,
      1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_set_precision_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456,
          0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23, 1.234,
          1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789, 1.2345678910, 12.0,
          12.2, 12.23, 12.234, 12.2345, 12.23456, 12.234567, 12.2345678,
          12.23456789, 12.2345678910, 123.0, 123.2, 123.23, 123.234, 123.2345,
          123.23456, 123.234567, 123.2345678, 123.23456789, 123.2345678910);
  s21_sprintf(s21_res, format_string, 0.0, 0.2, 0.23, 0.234, 0.2345, 0.23456,
              0.234567, 0.2345678, 0.23456789, 0.2345678910, 1.0, 1.2, 1.23,
              1.234, 1.2345, 1.23456, 1.234567, 1.2345678, 1.23456789,
              1.2345678910, 12.0, 12.2, 12.23, 12.234, 12.2345, 12.23456,
              12.234567, 12.2345678, 12.23456789, 12.2345678910, 123.0, 123.2,
              123.23, 123.234, 123.2345, 123.23456, 123.234567, 123.2345678,
              123.23456789, 123.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_set_precision_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
          1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
          12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
          12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910,
          123456.0, 123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456,
          123456.234567, 123456.2345678, 123456.23456789, 123456.2345678910,
          1234567.0, 1234567.2, 1234567.23, 1234567.234, 1234567.2345,
          1234567.23456, 1234567.234567, 1234567.2345678, 1234567.23456789,
          1234567.2345678910);

  s21_sprintf(
      s21_res, format_string, 1234.0, 1234.2, 1234.23, 1234.234, 1234.2345,
      1234.23456, 1234.234567, 1234.2345678, 1234.23456789, 1234.2345678910,
      12345.0, 12345.2, 12345.23, 12345.234, 12345.2345, 12345.23456,
      12345.234567, 12345.2345678, 12345.23456789, 12345.2345678910, 123456.0,
      123456.2, 123456.23, 123456.234, 123456.2345, 123456.23456, 123456.234567,
      123456.2345678, 123456.23456789, 123456.2345678910, 1234567.0, 1234567.2,
      1234567.23, 1234567.234, 1234567.2345, 1234567.23456, 1234567.234567,
      1234567.2345678, 1234567.23456789, 1234567.2345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_set_precision_width_4_p3) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93456,
          0.934567, 0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49, 9.500,
          9.5001, 9.93456, 9.934567, 9.9945678, 9.93456789, 9.9345678910, 98.9,
          98.9, 98.83, 98.834, 98.2934, 98.29345, 98.934567, 98.9345678,
          98.93456789, 98.9345678910, 993.0, 923.2, 923.23, 923.234, 923.2345,
          923.23456, 923.234567, 923.2345678, 923.23456789, 923.2345678910);
  s21_sprintf(s21_res, format_string, 0.1, 0.9, 0.93, 0.934, 0.9349, 0.93456,
              0.934567, 0.9345678, 0.93456789, 0.9345678910, 9.0, 9.9, 9.49,
              9.500, 9.5001, 9.93456, 9.934567, 9.9945678, 9.93456789,
              9.9345678910, 98.9, 98.9, 98.83, 98.834, 98.2934, 98.29345,
              98.934567, 98.9345678, 98.93456789, 98.9345678910, 993.0, 923.2,
              923.23, 923.234, 923.2345, 923.23456, 923.234567, 923.2345678,
              923.23456789, 923.2345678910);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_set_precision_width_4_p4) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%#4.%dg %%#04.%dg %%#04.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, 9930.9, 9934.9, 9934.93, 9934.934, 9934.9345,
          9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
          99999.0, 99998.9, 99998.93, 99998.934, 99998.9345, 99998.93456,
          99998.934567, 99998.9345678, 99998.93456789, 99998.9345678910,
          999999.0, 999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456,
          999999.234567, 999999.2345678, 999999.23456789, 999999.2345678910,
          9999999.0, 9999998.9, 9999998.93, 9999998.934, 9999998.9345,
          9999998.93456, 9999998.934567, 9999998.9345678, 9999998.93456789,
          9999998.9345678910);

  s21_sprintf(
      s21_res, format_string, 9930.9, 9934.9, 9934.93, 9934.934, 9934.9345,
      9934.93456, 9934.934567, 9934.9345678, 9934.93456789, 9234.9345678910,
      99999.0, 99998.9, 99998.93, 99998.934, 99998.9345, 99998.93456,
      99998.934567, 99998.9345678, 99998.93456789, 99998.9345678910, 999999.0,
      999999.2, 999999.23, 999999.234, 999999.2345, 999999.23456, 999999.234567,
      999999.2345678, 999999.23456789, 999999.2345678910, 9999999.0, 9999998.9,
      9999998.93, 9999998.934, 9999998.9345, 9999998.93456, 9999998.934567,
      9999998.9345678, 9999998.93456789, 9999998.9345678910);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_ldbl_set_prec_wd_4_p1) {
  char lib_res[1000];
  char s21_res[1000];

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr);

  sprintf(lib_res, format_string, 9229.9L, 9234.9L, 9234.93L, 9234.934L,
          9234.9345L, 9234.93456L, 9234.934567L, 9234.9345678L, 9234.93456789L,
          9234.9345678910L, 99999.0L, 99998.9L, 99998.93L, 99998.934L,
          99998.9345L, 99998.93456L, 99998.934567L, 99998.9345678L,
          99998.93456789L, 99998.9345678910L, 999999.0L, 999999.2L, 999999.23L,
          999999.234L, 999999.2345L, 999999.23456L, 999999.234567L,
          999999.2345678L, 999999.23456789L, 999999.2345678910L, 9999999.0L,
          9999998.9L, 9999998.93L, 9999998.934L, 9999998.9345L, 9999998.93456L,
          9999998.934567L, 9999998.9345678L, 9999998.93456789L,
          9999998.9345678910L);

  s21_sprintf(s21_res, format_string, 9229.9L, 9234.9L, 9234.93L, 9234.934L,
              9234.9345L, 9234.93456L, 9234.934567L, 9234.9345678L,
              9234.93456789L, 9234.9345678910L, 99999.0L, 99998.9L, 99998.93L,
              99998.934L, 99998.9345L, 99998.93456L, 99998.934567L,
              99998.9345678L, 99998.93456789L, 99998.9345678910L, 999999.0L,
              999999.2L, 999999.23L, 999999.234L, 999999.2345L, 999999.23456L,
              999999.234567L, 999999.2345678L, 999999.23456789L,
              999999.2345678910L, 9999999.0L, 9999998.9L, 9999998.93L,
              9999998.934L, 9999998.9345L, 9999998.93456L, 9999998.934567L,
              9999998.9345678L, 9999998.93456789L, 9999998.9345678910L);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_ldbl_set_prec_wd_4_p2) {
  char lib_res[1000];
  char s21_res[1000];

  long double num7_1 = 1234567.0L;
  long double num7_2 = 1234567.2L;
  long double num7_3 = 1234567.23L;
  long double num7_4 = 1234567.234L;
  long double num7_5 = 1234567.2345L;
  long double num7_6 = 1234567.23456L;
  long double num7_7 = 1234567.234567L;
  long double num7_8 = 1234567.2345678L;
  long double num7_9 = 1234567.23456789L;
  long double num7_10 = 1234567.2345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num7_1, num7_2, num7_3, num7_4, num7_5,
          num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num7_1, num7_2, num7_3, num7_4, num7_5,
              num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

void add_basic_tests(TCase* tc) {
  tcase_add_test(tc, test_sprintf_int);
  tcase_add_test(tc, test_sprintf_int_0_padding);
  tcase_add_test(tc, test_sprintf_ints_d);
  tcase_add_test(tc, test_sprintf_ints_d_is_star);
  tcase_add_test(tc, test_sprintf_ints_i);
  tcase_add_test(tc, test_sprintf_int_min);
  tcase_add_test(tc, test_sprintf_long_ints_d);
  tcase_add_test(tc, test_sprintf_short_ints_d);
  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_char_width);
  tcase_add_test(tc, test_sprintf_string);
  tcase_add_test(tc, test_sprintf_empty_string);
  tcase_add_test(tc, test_sprintf_problematic_float);
  tcase_add_test(tc, test_sprintf_very_float);
  tcase_add_test(tc, test_sprintf_a_bit_float);
  tcase_add_test(tc, test_sprintf_float_width_precision_flag);
  tcase_add_test(tc, test_sprintf_float_not_implemented);
  tcase_add_test(tc, test_sprintf_unsigned);
  tcase_add_test(tc, test_sprintf_unsigned_problematic);
  tcase_add_test(tc, test_sprintf_long_doubles);
  tcase_add_test(tc, test_sprintf_short_overflow);
  tcase_add_test(tc, test_sprintf_int_overflow);
  tcase_add_test(tc, test_sprintf_long_overflow);
  tcase_add_test(tc, test_sprintf_number_of_characters);
  tcase_add_test(tc, test_sprintf_wide_character);
  tcase_add_test(tc, test_sprintf_wide_character_string);
  tcase_add_test(tc, test_sprintf_hex_lower_with_modifiers);
  tcase_add_test(tc, test_sprintf_hex_upper_with_modifiers);
  tcase_add_test(tc, test_sprintf_octal_with_modifiers);
  tcase_add_test(tc, test_sprintf_octal_negative_long);
  tcase_add_test(tc, test_sprintf_octal_width);
  tcase_add_test(tc, test_sprintf_char_problematic);
  tcase_add_test(tc, test_sprintf_pointer_type);
  tcase_add_test(tc, test_sprintf_flag_sharp_oxX);
  tcase_add_loop_test(tc, test_sprintf_loop_star, 0, 14);
  tcase_add_test(tc, test_sprintf_long_double);
  tcase_add_test(tc, test_sprintf_double_long_double);
  tcase_add_test(tc, test_sprintf_sharp_long_double);
  tcase_add_test(tc, test_sprintf_sharp_double_long_double);
  if (RUNNING_ON_VALGRIND == false) {
    tcase_add_test(tc, test_sprintf_double_nan_inf);
    tcase_add_test(tc, test_sprintf_double_NaN_INF);
    tcase_add_test(tc, test_sprintf_sharp_double_nan_inf);
  };
}

void add_basic_sharp_tests(TCase* tc) {
  tcase_add_loop_test(tc, test_sprintf_sharp_loop_star, 0, 14);
  tcase_add_test(tc, test_sprintf_sharp_very_float);
  tcase_add_test(tc, test_sprintf_sharp_a_bit_float);
  tcase_add_test(tc, test_sprintf_sharp_float_width_precision_flag);
  tcase_add_test(tc, test_sprintf_sharp_hex_lower_with_modifiers);
  tcase_add_test(tc, test_sprintf_sharp_hex_upper_with_modifiers);
  tcase_add_test(tc, test_sprintf_sharp_octal_with_modifiers);
  tcase_add_test(tc, test_sprintf_sharp_octal_negative_long);
  tcase_add_test(tc, test_sprintf_sharp_octal_width);
}

void add_scientific_tests(TCase* tc) {
  tcase_add_test(tc, test_sprintf_scientific_zero_double);
  tcase_add_test(tc, test_sprintf_scientific_front_double);
  tcase_add_test(tc, test_sprintf_scientific_from_negative_double);
  tcase_add_loop_test(tc, test_sprintf_scientific_loop_precisions, 0, 14);
  tcase_add_test(tc, test_sprintf_scientific_from_big_double);
  tcase_add_loop_test(tc, test_sprintf_scientific_zero_loop_precisions, 0, 18);
  tcase_add_test(tc, test_sprintf_sharp_scientific_zero_double);
  tcase_add_test(tc, test_sprintf_sharp_scientific_front_double);
  tcase_add_test(tc, test_sprintf_sharp_scientific_from_negative_double);
  tcase_add_loop_test(tc, test_sprintf_sharp_sci_loop_precisions, 0, 14);
  tcase_add_test(tc, test_sprintf_sharp_scientific_from_big_double);
  tcase_add_loop_test(tc, test_sprintf_sharp_sci_zero_loop_precisions, 0, 18);
  if (RUNNING_ON_VALGRIND) {
    tcase_add_loop_test(tc, test_sprintf_sci_long_loop_precisions, 0, 14);
    tcase_add_loop_test(tc, test_sprintf_sharp_sci_long_loop_precisions, 0, 14);
  } else {
    tcase_add_loop_test(tc, test_sprintf_sci_long_loop_precisions, 0, 18);
    tcase_add_loop_test(tc, test_sprintf_sharp_sci_long_loop_precisions, 0, 18);
  }
}

void add_g_spec_tests(TCase* tc) {
  tcase_add_test(tc, test_sprintf_mantissa_or_exponent_negative_value);
  tcase_add_test(tc, test_sprintf_mantissa_or_exponent_formats);
  tcase_add_loop_test(tc, test_sprintf_g_spec_loop_precisions, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_zero_loop_precisions, 0, 14);
  tcase_add_test(tc, test_sprintf_g_spec_no_precision_many_p1);
  tcase_add_test(tc, test_sprintf_g_spec_no_precision_many_p2);
  tcase_add_test(tc, test_sprintf_g_spec_precision_0_many_p1);
  tcase_add_test(tc, test_sprintf_g_spec_precision_0_many_p2);
  tcase_add_test(tc, test_sprintf_g_spec_no_precision_interesting);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_many_p1, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_many_p2, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_many_p3, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_many_p4, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_long_dbl_set_precision_p1, 0, 18);
  tcase_add_loop_test(tc, test_sprintf_g_spec_long_dbl_set_precision_p2, 0, 18);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_spec_loop_precisions, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_zero_loop_precisions, 0, 14);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_no_precision_many_p1);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_no_precision_many_p2);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_precision_0_many_p1);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_precision_0_many_p2);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_no_precision_interesting);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_spec_set_precision_p1, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_spec_set_precision_p2, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_spec_set_precision_p3, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_spec_set_precision_p4, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_ldbl_set_precision_p1, 0, 18);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_ldbl_set_precision_p2, 0, 18);
  tcase_add_test(tc, test_sprintf_sharp_mantissa_or_exponent_formats);
  tcase_add_test(tc, test_sprintf_sharp_mantissa_or_exponent_negative_value);
  if (RUNNING_ON_VALGRIND) {
    tcase_add_loop_test(tc, test_sprintf_g_spec_long_loop_precisions, 0, 14);
    tcase_add_loop_test(tc, test_sprintf_sharp_g_long_loop_precisions, 0, 14);
  } else {
    tcase_add_loop_test(tc, test_sprintf_g_spec_long_loop_precisions, 0, 17);
    tcase_add_loop_test(tc, test_sprintf_sharp_g_long_loop_precisions, 0, 17);
  }
}

void add_g_spec_width_4_tests(TCase* tc) {
  tcase_add_loop_test(tc, test_sprintf_g_spec_loop_precisions_width_4, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_zero_loop_precisions_width_4, 0, 14);
  tcase_add_test(tc, test_sprintf_g_spec_no_precision_many_width_4_p1);
  tcase_add_test(tc, test_sprintf_g_spec_no_precision_many_width_4_p2);
  tcase_add_test(tc, test_sprintf_g_spec_precision_0_many_width_4_p1);
  tcase_add_test(tc, test_sprintf_g_spec_precision_0_many_width_4_p2);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_width_4_p1, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_width_4_p2, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_width_4_p3, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_spec_set_precision_width_4_p4, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_g_ldbl_set_precision_width_4_p1, 0, 18);
  tcase_add_loop_test(tc, test_sprintf_g_ldbl_set_precision_width_4_p2, 0, 18);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_loop_precisions_width_4, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_0_loop_precisions_wd_4, 0, 14);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_no_precision_many_width_4_p1);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_no_precision_many_width_4_p2);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_precision_0_many_width_4_p1);
  tcase_add_test(tc, test_sprintf_sharp_g_spec_precision_0_many_width_4_p2);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_set_precision_width_4_p1, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_set_precision_width_4_p2, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_set_precision_width_4_p3, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_set_precision_width_4_p4, 0, 14);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_ldbl_set_prec_wd_4_p1, 0, 18);
  tcase_add_loop_test(tc, test_sprintf_sharp_g_ldbl_set_prec_wd_4_p2, 0, 18);
  if (RUNNING_ON_VALGRIND) {
    tcase_add_loop_test(tc, test_sprintf_g_long_loop_precisions_width_4, 0, 14);
    tcase_add_loop_test(tc, test_sprintf_sharp_g_long_loop_precs_wd_4, 0, 14);
  } else {
    tcase_add_loop_test(tc, test_sprintf_g_long_loop_precisions_width_4, 0, 17);
    tcase_add_loop_test(tc, test_sprintf_sharp_g_long_loop_precs_wd_4, 0, 17);
  }
}

Suite* make_sprintf_suite() {
  Suite* sprintf_suite = suite_create("sprintf");
  TCase* tc_core;
  TCase* tc_problematic;

  tc_core = tcase_create("Core");
  tc_problematic = tcase_create("Problematic");

  add_basic_tests(tc_core);
  add_basic_sharp_tests(tc_core);
  add_scientific_tests(tc_core);
  add_g_spec_tests(tc_core);
  add_g_spec_width_4_tests(tc_core);

  suite_add_tcase(sprintf_suite, tc_core);
  suite_add_tcase(sprintf_suite, tc_problematic);
  return sprintf_suite;
}