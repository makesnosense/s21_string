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

START_TEST(test_sprintf_int_0_padding) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%+020i-% d %020d", -100, 0, 3333);
  s21_sprintf(s21_res, "%+020i-% d %020d", -100, 0, 3333);
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

START_TEST(test_sprintf_int_min) {
  char lib_res[500];
  char s21_res[500];
  int min_int = INT_MIN;
  sprintf(lib_res, "%d %hd", min_int, min_int);
  s21_sprintf(s21_res, "%d %hd", min_int, min_int);
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

START_TEST(test_sprintf_char) {
  char lib_res[100];
  char s21_res[100];
  sprintf(lib_res, "%c %c %c %c %c %c", '\t', '@', '\n', 2, 50, 123);
  s21_sprintf(s21_res, "%c %c %c %c %c %c", '\t', '@', '\n', 2, 50, 123);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_char_width) {
  char lib_res[300];
  char s21_res[300];
  sprintf(lib_res, "%20c %3c %-20c %-3c %-20c", 'A', '@', 'A', '@', 50);
  s21_sprintf(s21_res, "%20c %3c %-20c %-3c %-20c", 'A', '@', 'A', '@', 50);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_char_problematic) {
  char lib_res[300];
  char s21_res[300];
  sprintf(lib_res, "%20c %3c %-20c", 2, 50, 123);
  s21_sprintf(s21_res, "%20c %3c %-20c", 2, 50, 123);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_string) {
  char lib_res[500];
  char s21_res[500];
  sprintf(lib_res, "%s %40s %-40s %d %20s", "JOMA", "}l{u3Hb – 3TO 6oJlb",
          "}l{u3Hb – 3TO 6oJlb", 42, "nan");
  s21_sprintf(s21_res, "%s %40s %-40s %d %20s", "JOMA", "}l{u3Hb – 3TO 6oJlb",
              "}l{u3Hb – 3TO 6oJlb", 42, "nan");
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
  sprintf(lib_res, "% .5f %+.0f %f %+020f", 33.0, 33.33, 3.33, 3.33);
  s21_sprintf(s21_res, "% .5f %+.0f %f %+020f", 33.0, 33.33, 3.33, 3.33);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_a_bit_float) {
  char lib_res[200];
  char s21_res[200];
  sprintf(lib_res, "%+.0f % .5f % .5f %f", 33.0, 33.0, 3.0, 0.0);
  s21_sprintf(s21_res, "%+.0f % .5f % .5f %f", 33.0, 33.0, 3.0, 0.0);
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

  sprintf(lib_res, "%-15u %60u %u %lu %lu %lu %u %lu %hu %u %u", 1, 1000,
          UINT_MAX, ULONG_MAX, ULONG_MAX - 333, ULONG_MAX + 1, (UINT_MAX + 500),
          min_long_int, USHRT_MAX, UINT_MAX, 0);
  s21_sprintf(s21_res, "%-15u %60u %u %lu %lu %lu %u %lu %hu %u %u", 1, 1000,
              UINT_MAX, ULONG_MAX, ULONG_MAX - 333, ULONG_MAX + 1,
              (UINT_MAX + 500), min_long_int, USHRT_MAX, UINT_MAX, 0);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_unsigned_problematic) {
  char lib_res[1000];
  char s21_res[1000];

  sprintf(lib_res, "%-20hu %-30hu %-30u %lu %lu %u %u", USHRT_MAX + 5,
          UINT_MAX + 10, UINT_MAX, ULONG_MAX, ULONG_MAX + 5, -1000, -65555);
  s21_sprintf(s21_res, "%-20hu %-30hu %-30u %lu %lu %u %u", USHRT_MAX + 5,
              UINT_MAX + 10, UINT_MAX, ULONG_MAX, ULONG_MAX + 5, -1000, -65555);
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

START_TEST(test_sprintf_number_of_characters) {
  char lib_res[100];
  char s21_res[100];
  double num = 1.79769313486231571308;
  int res_or = 0;
  int res_s21 = 0;
  s21_sprintf(s21_res, "sprintf: %+E %% hdhgd %+d hdkjgh %n %%", num, 555,
              &res_s21);
  sprintf(lib_res, "sprintf: %+E %% hdhgd %+d hdkjgh %n %%", num, 555, &res_or);
  ck_assert_str_eq(lib_res, s21_res);
  //
}
END_TEST

START_TEST(test_sprintf_wide_character) {
  char lib_res[1000];
  char s21_res[1000];
  wchar_t wide_char1 = L'あ';
  wchar_t wide_char2 = L'は';

  s21_sprintf(s21_res, "Широкий символ: %-20lc %6lc fgtffghghgutf", wide_char1,
              wide_char2);
  sprintf(lib_res, "Широкий символ: %-20lc %6lc fgtffghghgutf", wide_char1,
          wide_char2);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_wide_character_string) {
  char lib_res[1000];
  char s21_res[1000];
  wchar_t wide_string1[] = L"こんにちは";
  wchar_t wide_string2[] = L"凛として時雨";

  s21_sprintf(s21_res, "Широкий символ: %-20ls %10ls fgtffghghgutf",
              wide_string1, wide_string2);
  sprintf(lib_res, "Широкий символ: %-20ls %10ls fgtffghghgutf", wide_string1,
          wide_string2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_hex_lower_with_modifiers) {
  char lib_res[1000];
  char s21_res[1000];

  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295;  // Максимум для unsigned long

  sprintf(lib_res, "%x %hx %lx %20lx %-20lx %-40hx", -33, us_value, ul_value,
          ul_value, ul_value, us_value);
  s21_sprintf(s21_res, "%x %hx %lx %20lx %-20lx %-40hx", -33, us_value,
              ul_value, ul_value, ul_value, us_value);
  // sprintf(lib_res, "%20hx", us_value);
  // s21_sprintf(s21_res, "%20hx", us_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_hex_upper_with_modifiers) {
  char lib_res[100];
  char s21_res[100];

  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295UL + 5;  // Максимум для unsigned long

  sprintf(lib_res, "%hX %lX %-20hX %20lX", us_value, ul_value, us_value,
          ul_value);
  s21_sprintf(s21_res, "%hX %lX %-20hX %20lX", us_value, ul_value, us_value,
              ul_value);
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

START_TEST(test_sprintf_octal_negative_long) {
  char lib_res[300];
  char s21_res[300];

  long int min_long_int = LONG_MIN;

  sprintf(lib_res, "%lo", min_long_int);
  s21_sprintf(s21_res, "%lo", min_long_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_octal_width) {
  char lib_res[300];
  char s21_res[300];

  int first_test_int = -33;
  int second_test_int = INT_MAX;

  sprintf(lib_res, "%20o %-20o", first_test_int, second_test_int);
  s21_sprintf(s21_res, "%20o %-20o", first_test_int, second_test_int);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_pointer_type) {
  char lib_res[300];
  char s21_res[300];

  long double value1 = -44366537.53746;

  long long value2 = 4568376973;

  char value3 = 'f';

  sprintf(lib_res, "%-4p %-20p %35p %p", (void*)&value1, (void*)&value2,
          (void*)&value3, NULL);
  s21_sprintf(s21_res, "%-4p %-20p %35p %p", (void*)&value1, (void*)&value2,
              (void*)&value3, NULL);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_flag_sharp_oxX) {
  char lib_res[300];
  char s21_res[300];

  int value1 = -44366537;

  sprintf(lib_res, "%#o %#x %#X", value1, value1, value1);
  sprintf(s21_res, "%#o %#x %#X", value1, value1, value1);
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

START_TEST(test_sprintf_mantissa_or_exponent_formats) {
  char lib_res[300];
  char s21_res[300];

  double num1 = 14376485974.123;
  double num2 = 3333.3333;

  sprintf(lib_res, "%g %G", num1, num2);
  s21_sprintf(s21_res, "%g %G", num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_mantissa_or_exponent_negative_value) {
  char lib_res[300];
  char s21_res[300];

  long double num1 = -566765.1266666;

  sprintf(lib_res, "%Lg %LG", num1, num1);
  s21_sprintf(s21_res, "%Lg %LG", num1, num1);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_loop_precisions) {
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

START_TEST(test_sprintf_scientific_from_big_double) {
  char lib_res[200];
  char s21_res[200];
  long double num = 3.33333333333333333L;
  sprintf(lib_res, "%Le", num);
  s21_sprintf(s21_res, "%Le", num);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_long_loop_precisions) {
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
              "%%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe %%.%dLe",
              precision, precision, precision, precision, precision, precision,
              precision, precision);
  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_scientific_zero_loop_precisions) {
  char lib_res[100];
  char s21_res[100];

  double zero = 0.0;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%de %%e %%.e", precision);

  sprintf(lib_res, format_string, zero, zero, zero);

  s21_sprintf(s21_res, format_string, zero, zero, zero);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 1.2345678;
  double num2 = 1.0;
  double num3 = 1.2345678940;
  double num4 = 1;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%dg %%.%dg %%.%dg %%.%dg", precision,
              precision, precision, precision);

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.1L;
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

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_zero_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 0;
  double num2 = 0.000;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%.%dg %%.g %%.%dg %%.g", precision, precision);
  // printf("\n\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num1, num2);
  s21_sprintf(s21_res, format_string, num1, num2, num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
          "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
          "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(
      s21_res,
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g "
      "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 5.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 5.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
          "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(
      s21_res,
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g "
      "%.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g %.0g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_interesting) {
  char lib_res[1000];
  char s21_res[1000];
  double num5 = 0.5333333333;
  double num6 = 1.5333333333;

  long double ld_value = 1.000000000000000003L;
  // Casting the same value to double to demonstrate loss of precision
  double d_value = (double)ld_value;

  sprintf(lib_res, "%-5g %g %g %20Lg", num5, num6, d_value, ld_value);
  s21_sprintf(s21_res, "%-5g %g %g %20Lg", num5, num6, d_value, ld_value);
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

START_TEST(test_sprintf_long_double) {
  char lib_res[100];
  char s21_res[100];

  long double ld_value = 1.000000000000000003L;
  long double ld_value_2 = 1123123.04L;
  long double ld_value_3 = 333.000000501L;
  long double ld_value_4 = 9.00000000000501001L;

  sprintf(lib_res, "%.18Lf %.18Lf %.18Lf %.18Lf", ld_value, ld_value_2,
          ld_value_3, ld_value_4);
  s21_sprintf(s21_res, "%.18Lf %.18Lf %.18Lf %.18Lf", ld_value, ld_value_2,
              ld_value_3, ld_value_4);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_double_long_double) {
  char lib_res[100];
  char s21_res[100];

  long double ld_value = 1.000000000000000003L;
  // Casting the same value to double to demonstrate loss of precision
  double d_value = (double)ld_value;

  sprintf(lib_res, "%.18Lf %.18f", ld_value, d_value);
  s21_sprintf(s21_res, "%.18Lf %.18f", ld_value, d_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  s21_sprintf(format_string,
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p3) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.1;
  double num0_2 = 0.9;
  double num0_3 = 0.93;
  double num0_4 = 0.934;
  double num0_5 = 0.9345;
  double num0_6 = 0.93456;
  double num0_7 = 0.934567;
  double num0_8 = 0.9345678;
  double num0_9 = 0.93456789;
  double num0_10 = 0.9345678910;

  double num1 = 9;
  double num1_1 = 9.0;
  double num1_2 = 9.9;
  double num1_3 = 9.49;
  double num1_4 = 9.500;
  double num1_5 = 9.5001;
  double num1_6 = 9.93456;
  double num1_7 = 9.934567;
  double num1_8 = 9.9945678;
  double num1_9 = 9.93456789;
  double num1_10 = 9.9345678910;

  double num2 = 92;
  double num2_1 = 99.9;
  double num2_2 = 99.9;
  double num2_3 = 99.93;
  double num2_4 = 99.934;
  double num2_5 = 99.2934;
  double num2_6 = 99.29345;
  double num2_7 = 99.934567;
  double num2_8 = 99.9345678;
  double num2_9 = 99.93456789;
  double num2_10 = 99.9345678910;

  double num3 = 999;
  double num3_1 = 993.0;
  double num3_2 = 923.2;
  double num3_3 = 923.23;
  double num3_4 = 923.234;
  double num3_5 = 923.2345;
  double num3_6 = 923.23456;
  double num3_7 = 923.234567;
  double num3_8 = 923.2345678;
  double num3_9 = 923.23456789;
  double num3_10 = 923.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_p4) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 9994;
  double num4_1 = 9934.9;
  double num4_2 = 9934.9;
  double num4_3 = 9934.93;
  double num4_4 = 9934.934;
  double num4_5 = 9934.9345;
  double num4_6 = 9934.93456;
  double num4_7 = 9934.934567;
  double num4_8 = 9934.9345678;
  double num4_9 = 9934.93456789;
  double num4_10 = 9234.9345678910;

  double num5 = 92345;
  double num5_1 = 99999.0;
  double num5_2 = 99999.9;
  double num5_3 = 99999.93;
  double num5_4 = 99999.934;
  double num5_5 = 99999.9345;
  double num5_6 = 99999.93456;
  double num5_7 = 99999.934567;
  double num5_8 = 99999.9345678;
  double num5_9 = 99999.93456789;
  double num5_10 = 99999.9345678910;

  double num6 = 999999;
  double num6_1 = 999999.0;
  double num6_2 = 999999.2;
  double num6_3 = 999999.23;
  double num6_4 = 999999.234;
  double num6_5 = 999999.2345;
  double num6_6 = 999999.23456;
  double num6_7 = 999999.234567;
  double num6_8 = 999999.2345678;
  double num6_9 = 999999.23456789;
  double num6_10 = 999999.2345678910;

  double num7 = 9999999;
  double num7_1 = 9999999.0;
  double num7_2 = 9999999.9;
  double num7_3 = 9999999.93;
  double num7_4 = 9999999.934;
  double num7_5 = 9999999.9345;
  double num7_6 = 9999999.93456;
  double num7_7 = 9999999.934567;
  double num7_8 = 9999999.9345678;
  double num7_9 = 9999999.93456789;
  double num7_10 = 9999999.9345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_double_set_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  long double num4 = 9994.0L;
  long double num4_1 = 9234.9L;
  long double num4_2 = 9234.9L;
  long double num4_3 = 9234.93L;
  long double num4_4 = 9234.934L;
  long double num4_5 = 9234.9345L;
  long double num4_6 = 9234.93456L;
  long double num4_7 = 9234.934567L;
  long double num4_8 = 9234.9345678L;
  long double num4_9 = 9234.93456789L;
  long double num4_10 = 9234.9345678910L;

  long double num5 = 92345L;
  long double num5_1 = 99999.0L;
  long double num5_2 = 99999.9L;
  long double num5_3 = 99999.93L;
  long double num5_4 = 99999.934L;
  long double num5_5 = 99999.9345L;
  long double num5_6 = 99999.93456L;
  long double num5_7 = 99999.934567L;
  long double num5_8 = 99999.9345678L;
  long double num5_9 = 99999.93456789L;
  long double num5_10 = 99999.9345678910L;

  long double num6 = 999999L;
  long double num6_1 = 999999.0L;
  long double num6_2 = 999999.2L;
  long double num6_3 = 999999.23L;
  long double num6_4 = 999999.234L;
  long double num6_5 = 999999.2345L;
  long double num6_6 = 999999.23456L;
  long double num6_7 = 999999.234567L;
  long double num6_8 = 999999.2345678L;
  long double num6_9 = 999999.23456789L;
  long double num6_10 = 999999.2345678910L;

  long double num7 = 9999999L;
  long double num7_1 = 9999999.0L;
  long double num7_2 = 9999999.9L;
  long double num7_3 = 9999999.93L;
  long double num7_4 = 9999999.934L;
  long double num7_5 = 9999999.9345L;
  long double num7_6 = 9999999.93456L;
  long double num7_7 = 9999999.934567L;
  long double num7_8 = 9999999.9345678L;
  long double num7_9 = 9999999.93456789L;
  long double num7_10 = 9999999.9345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
      "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
      "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
      "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg "
      "%%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg %%.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_double_set_precision_many_p2) {
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

  s21_sprintf(format_string,
              "%%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg %%.%dg "
              "%%.%dg %%.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num7, num7_1, num7_2, num7_3, num7_4, num7_5,
          num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num7, num7_1, num7_2, num7_3, num7_4,
              num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_loop_star) {
  char lib_res[1000];
  char s21_res[1000];

  long double long_double_num = 9234.93456L;
  long long_num = 9234;
  unsigned unsinged_num = 1234567;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string, "%%*.*Lf %%*.*ld %%*.*u");

  sprintf(lib_res, format_string, pr, pr, long_double_num, pr, pr, long_num, pr,
          pr, unsinged_num);

  sprintf(s21_res, format_string, pr, pr, long_double_num, pr, pr, long_num, pr,
          pr, unsinged_num);

  ck_assert_str_eq(lib_res, s21_res);
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

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_long_loop_precisions) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.1L;
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

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_zero_loop_precisions) {
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
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
      "%#g %#g %#g %#g %#g "
      "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
      "%#g %#g %#g %#g %#g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
          "%#g %#g %#g %#g %#g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(s21_res,
              "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
              "%#g %#g %#g %#g %#g %#g "
              "%#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g %#g "
              "%#g %#g %#g %#g %#g %#g",
              num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7,
              num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4,
              num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
              num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
              num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6,
              num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 5.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 5.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(
      lib_res,
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(
      lib_res,
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(
      s21_res,
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g "
      "%#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g %#.0g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
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
  long double ld_value_2 = 1123123.04L;
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

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_p3) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.1;
  double num0_2 = 0.9;
  double num0_3 = 0.93;
  double num0_4 = 0.934;
  double num0_5 = 0.9345;
  double num0_6 = 0.93456;
  double num0_7 = 0.934567;
  double num0_8 = 0.9345678;
  double num0_9 = 0.93456789;
  double num0_10 = 0.9345678910;

  double num1 = 9;
  double num1_1 = 9.0;
  double num1_2 = 9.9;
  double num1_3 = 9.49;
  double num1_4 = 9.500;
  double num1_5 = 9.5001;
  double num1_6 = 9.93456;
  double num1_7 = 9.934567;
  double num1_8 = 9.9945678;
  double num1_9 = 9.93456789;
  double num1_10 = 9.9345678910;

  double num2 = 92;
  double num2_1 = 95.9;
  double num2_2 = 95.9;
  double num2_3 = 95.93;
  double num2_4 = 95.934;
  double num2_5 = 95.2934;
  double num2_6 = 95.29345;
  double num2_7 = 95.934567;
  double num2_8 = 95.9345678;
  double num2_9 = 95.93456789;
  double num2_10 = 95.9345678910;

  double num3 = 999;
  double num3_1 = 993.0;
  double num3_2 = 923.2;
  double num3_3 = 923.23;
  double num3_4 = 923.234;
  double num3_5 = 923.2345;
  double num3_6 = 923.23456;
  double num3_7 = 923.234567;
  double num3_8 = 923.2345678;
  double num3_9 = 923.23456789;
  double num3_10 = 923.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_p4) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 9994;
  double num4_1 = 9934.9;
  double num4_2 = 9934.9;
  double num4_3 = 9934.93;
  double num4_4 = 9934.934;
  double num4_5 = 9934.9345;
  double num4_6 = 9934.93456;
  double num4_7 = 9934.934567;
  double num4_8 = 9934.9345678;
  double num4_9 = 9934.93456789;
  double num4_10 = 9234.9345678910;

  double num5 = 92345;
  double num5_1 = 99999.0;
  double num5_2 = 99998.9;
  double num5_3 = 99998.93;
  double num5_4 = 99998.934;
  double num5_5 = 99998.9345;
  double num5_6 = 99998.93456;
  double num5_7 = 99998.934567;
  double num5_8 = 99998.9345678;
  double num5_9 = 99998.93456789;
  double num5_10 = 99998.9345678910;

  double num6 = 999999;
  double num6_1 = 999999.0;
  double num6_2 = 999999.2;
  double num6_3 = 999999.23;
  double num6_4 = 999999.234;
  double num6_5 = 999999.2345;
  double num6_6 = 999999.23456;
  double num6_7 = 999999.234567;
  double num6_8 = 999999.2345678;
  double num6_9 = 999999.23456789;
  double num6_10 = 999999.2345678910;

  double num7 = 9999999;
  double num7_1 = 9999999.0;
  double num7_2 = 9999998.9;
  double num7_3 = 9999998.93;
  double num7_4 = 9999998.934;
  double num7_5 = 9999998.9345;
  double num7_6 = 9999998.93456;
  double num7_7 = 9999998.934567;
  double num7_8 = 9999998.9345678;
  double num7_9 = 9999998.93456789;
  double num7_10 = 9999998.9345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg "
      "%%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg %%#.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_long_double_set_precision_many_p1) {
  char lib_res[1000];
  char s21_res[1000];
  long double num4 = 9994.0L;
  long double num4_1 = 9234.9L;
  long double num4_2 = 9234.9L;
  long double num4_3 = 9234.93L;
  long double num4_4 = 9234.934L;
  long double num4_5 = 9234.9345L;
  long double num4_6 = 9234.93456L;
  long double num4_7 = 9234.934567L;
  long double num4_8 = 9234.9345678L;
  long double num4_9 = 9234.93456789L;
  long double num4_10 = 9234.9345678910L;

  long double num5 = 92345L;
  long double num5_1 = 99999.0L;
  long double num5_2 = 99998.9L;
  long double num5_3 = 99998.93L;
  long double num5_4 = 99998.934L;
  long double num5_5 = 99998.9345L;
  long double num5_6 = 99998.93456L;
  long double num5_7 = 99998.934567L;
  long double num5_8 = 99998.9345678L;
  long double num5_9 = 99998.93456789L;
  long double num5_10 = 99998.9345678910L;

  long double num6 = 999999L;
  long double num6_1 = 999999.0L;
  long double num6_2 = 999999.2L;
  long double num6_3 = 999999.23L;
  long double num6_4 = 999999.234L;
  long double num6_5 = 999999.2345L;
  long double num6_6 = 999999.23456L;
  long double num6_7 = 999999.234567L;
  long double num6_8 = 999999.2345678L;
  long double num6_9 = 999999.23456789L;
  long double num6_10 = 999999.2345678910L;

  long double num7 = 9999999L;
  long double num7_1 = 9999999.0L;
  long double num7_2 = 9999998.9L;
  long double num7_3 = 9999998.93L;
  long double num7_4 = 9999998.934L;
  long double num7_5 = 9999998.9345L;
  long double num7_6 = 9999998.93456L;
  long double num7_7 = 9999998.934567L;
  long double num7_8 = 9999998.9345678L;
  long double num7_9 = 9999998.93456789L;
  long double num7_10 = 9999998.9345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg "
              "%%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg %%#.%dLg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_long_double_set_precision_many_p2) {
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
  long long_num = 9234;
  unsigned unsinged_num = 1234567;

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
  float sd = -3;
  float sd2 = 3.123456;
  float sd3 = 3.333;
  float sd4 = 3;

  sprintf(lib_res, "%-#15f %+-#20.1f % -#10f % #f", sd, sd2, sd3, sd4);
  s21_sprintf(s21_res, "%-#15f %+-#20.1f % -#10f % #f", sd, sd2, sd3, sd4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

//////

START_TEST(test_sprintf_sharp_hex_lower_with_modifiers) {
  char lib_res[1000];
  char s21_res[1000];

  unsigned short us_value = 255;
  unsigned long ul_value = 4294967295;  // Максимум для unsigned long

  sprintf(lib_res, "%#x %#hx %#lx %#20lx %-#20lx %-#40hx", -33, us_value,
          ul_value, ul_value, ul_value, us_value);
  s21_sprintf(s21_res, "%#x %#hx %#lx %#20lx %-#20lx %-#40hx", -33, us_value,
              ul_value, ul_value, ul_value, us_value);
  // sprintf(lib_res, "%20hx", us_value);
  // s21_sprintf(s21_res, "%20hx", us_value);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_hex_upper_with_modifiers) {
  char lib_res[100];
  char s21_res[100];

  unsigned short us_value = 255;
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

  unsigned short us_value = 0377;  // 255 в десятичной системе
  unsigned long ul_value =
      037777777777;  // Максимум для unsigned long в восьмеричной системе
  long int min_long_int = LONG_MIN;
  sprintf(lib_res, "%#ho %#lo %#lo", us_value, ul_value, min_long_int);
  s21_sprintf(s21_res, "%#ho %#lo %#lo", us_value, ul_value, min_long_int);
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
  sprintf(lib_res, "%#20e", num);
  s21_sprintf(s21_res, "%#20e", num);
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

  long double num1 = -566765.1266666;

  sprintf(lib_res, "%#Lg %#LG", num1, num1);
  s21_sprintf(s21_res, "%#Lg %#LG", num1, num1);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_scientific_loop_precisions) {
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

START_TEST(test_sprintf_sharp_scientific_long_loop_precisions) {
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

START_TEST(test_sprintf_sharp_scientific_zero_loop_precisions) {
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

START_TEST(test_sprintf_g_spec_long_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.1L;
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

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_zero_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  double num1 = 0;
  double num2 = 0.000;

  int precision = _i;  // supplied through add_loop_test func

  char format_string[70];

  s21_sprintf(format_string, "%%4.%dg %%4.g %%4.%dg %%4.g", precision,
              precision);
  // printf("\n\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num1, num2);
  s21_sprintf(s21_res, format_string, num1, num2, num1, num2);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_no_precision_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
          "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(
      s21_res,
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g %4g "
      "%4g %4g %4g %4g %4g %4g %4g %4g %4g %4g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 5.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 5.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_precision_0_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
          "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(
      s21_res,
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g "
      "%4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g %4.0g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

//////hm
START_TEST(test_sprintf_g_spec_set_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_width_4_p3) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.1;
  double num0_2 = 0.9;
  double num0_3 = 0.93;
  double num0_4 = 0.934;
  double num0_5 = 0.9345;
  double num0_6 = 0.93456;
  double num0_7 = 0.934567;
  double num0_8 = 0.9345678;
  double num0_9 = 0.93456789;
  double num0_10 = 0.9345678910;

  double num1 = 9;
  double num1_1 = 9.0;
  double num1_2 = 9.9;
  double num1_3 = 9.49;
  double num1_4 = 9.500;
  double num1_5 = 9.5001;
  double num1_6 = 9.93456;
  double num1_7 = 9.934567;
  double num1_8 = 9.9945678;
  double num1_9 = 9.93456789;
  double num1_10 = 9.9345678910;

  double num2 = 92;
  double num2_1 = 99.9;
  double num2_2 = 99.9;
  double num2_3 = 99.93;
  double num2_4 = 99.934;
  double num2_5 = 99.2934;
  double num2_6 = 99.29345;
  double num2_7 = 99.934567;
  double num2_8 = 99.9345678;
  double num2_9 = 99.93456789;
  double num2_10 = 99.9345678910;

  double num3 = 999;
  double num3_1 = 993.0;
  double num3_2 = 923.2;
  double num3_3 = 923.23;
  double num3_4 = 923.234;
  double num3_5 = 923.2345;
  double num3_6 = 923.23456;
  double num3_7 = 923.234567;
  double num3_8 = 923.2345678;
  double num3_9 = 923.23456789;
  double num3_10 = 923.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_set_precision_many_width_4_p4) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 9994;
  double num4_1 = 9934.9;
  double num4_2 = 9934.9;
  double num4_3 = 9934.93;
  double num4_4 = 9934.934;
  double num4_5 = 9934.9345;
  double num4_6 = 9934.93456;
  double num4_7 = 9934.934567;
  double num4_8 = 9934.9345678;
  double num4_9 = 9934.93456789;
  double num4_10 = 9234.9345678910;

  double num5 = 92345;
  double num5_1 = 99999.0;
  double num5_2 = 99999.9;
  double num5_3 = 99999.93;
  double num5_4 = 99999.934;
  double num5_5 = 99999.9345;
  double num5_6 = 99999.93456;
  double num5_7 = 99999.934567;
  double num5_8 = 99999.9345678;
  double num5_9 = 99999.93456789;
  double num5_10 = 99999.9345678910;

  double num6 = 999999;
  double num6_1 = 999999.0;
  double num6_2 = 999999.2;
  double num6_3 = 999999.23;
  double num6_4 = 999999.234;
  double num6_5 = 999999.2345;
  double num6_6 = 999999.23456;
  double num6_7 = 999999.234567;
  double num6_8 = 999999.2345678;
  double num6_9 = 999999.23456789;
  double num6_10 = 999999.2345678910;

  double num7 = 9999999;
  double num7_1 = 9999999.0;
  double num7_2 = 9999999.9;
  double num7_3 = 9999999.93;
  double num7_4 = 9999999.934;
  double num7_5 = 9999999.9345;
  double num7_6 = 9999999.93456;
  double num7_7 = 9999999.934567;
  double num7_8 = 9999999.9345678;
  double num7_9 = 9999999.93456789;
  double num7_10 = 9999999.9345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_double_set_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  long double num4 = 9994.0L;
  long double num4_1 = 9234.9L;
  long double num4_2 = 9234.9L;
  long double num4_3 = 9234.93L;
  long double num4_4 = 9234.934L;
  long double num4_5 = 9234.9345L;
  long double num4_6 = 9234.93456L;
  long double num4_7 = 9234.934567L;
  long double num4_8 = 9234.9345678L;
  long double num4_9 = 9234.93456789L;
  long double num4_10 = 9234.9345678910L;

  long double num5 = 92345L;
  long double num5_1 = 99999.0L;
  long double num5_2 = 99999.9L;
  long double num5_3 = 99999.93L;
  long double num5_4 = 99999.934L;
  long double num5_5 = 99999.9345L;
  long double num5_6 = 99999.93456L;
  long double num5_7 = 99999.934567L;
  long double num5_8 = 99999.9345678L;
  long double num5_9 = 99999.93456789L;
  long double num5_10 = 99999.9345678910L;

  long double num6 = 999999L;
  long double num6_1 = 999999.0L;
  long double num6_2 = 999999.2L;
  long double num6_3 = 999999.23L;
  long double num6_4 = 999999.234L;
  long double num6_5 = 999999.2345L;
  long double num6_6 = 999999.23456L;
  long double num6_7 = 999999.234567L;
  long double num6_8 = 999999.2345678L;
  long double num6_9 = 999999.23456789L;
  long double num6_10 = 999999.2345678910L;

  long double num7 = 9999999L;
  long double num7_1 = 9999999.0L;
  long double num7_2 = 9999999.9L;
  long double num7_3 = 9999999.93L;
  long double num7_4 = 9999999.934L;
  long double num7_5 = 9999999.9345L;
  long double num7_6 = 9999999.93456L;
  long double num7_7 = 9999999.934567L;
  long double num7_8 = 9999999.9345678L;
  long double num7_9 = 9999999.93456789L;
  long double num7_10 = 9999999.9345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(format_string,
              "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg "
              "%%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg %%4.%dLg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_g_spec_long_double_set_precision_many_width_4_p2) {
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
      "%%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg %%4.%dg "
      "%%4.%dg %%4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num7, num7_1, num7_2, num7_3, num7_4, num7_5,
          num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num7, num7_1, num7_2, num7_3, num7_4,
              num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_loop_precisions_width_4) {
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

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_long_loop_precisions_width_4) {
  char lib_res[1000];
  char s21_res[1000];
  long double num1 = 0.234567891011L;
  long double num2 = 333.0L;
  long double num3 = 33.2345678910L;
  long double num4 = 555555.1L;
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

  // printf("\n%s\n", format_string);
  sprintf(lib_res, format_string, num1, num2, num3, num4, num5, num6, num7,
          num8);
  s21_sprintf(s21_res, format_string, num1, num2, num3, num4, num5, num6, num7,
              num8);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_zero_loop_precisions_width_4) {
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
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
          "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
          "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
          "%#4g %#4g %#4g %#4g %#4g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(
      s21_res,
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g",
      num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
      num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
      num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
      num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
      num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_no_precision_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
          "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
          "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
          "%#4g %#4g %#4g %#4g %#4g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(
      s21_res,
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g %#4g "
      "%#4g %#4g %#4g %#4g %#4g",
      num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
      num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
      num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
      num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
      num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 5.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 5.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  sprintf(lib_res,
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
          num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7, num0_8,
          num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4, num1_5, num1_6,
          num1_7, num1_8, num1_9, num1_10, num2, num2_1, num2_2, num2_3, num2_4,
          num2_5, num2_6, num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2,
          num3_3, num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);
  s21_sprintf(s21_res,
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
              num0, num0_1, num0_2, num0_3, num0_4, num0_5, num0_6, num0_7,
              num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3, num1_4,
              num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
              num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
              num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6,
              num3_7, num3_8, num3_9, num3_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_precision_0_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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

  sprintf(lib_res,
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
          "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
          num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7, num4_8,
          num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4, num5_5, num5_6,
          num5_7, num5_8, num5_9, num5_10, num6, num6_1, num6_2, num6_3, num6_4,
          num6_5, num6_6, num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2,
          num7_3, num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  s21_sprintf(s21_res,
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g "
              "%#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g %#4.0g",
              num4, num4_1, num4_2, num4_3, num4_4, num4_5, num4_6, num4_7,
              num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3, num5_4,
              num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
              num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
              num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6,
              num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  double num0 = 0;
  double num0_1 = 0.0;
  double num0_2 = 0.2;
  double num0_3 = 0.23;
  double num0_4 = 0.234;
  double num0_5 = 0.2345;
  double num0_6 = 0.23456;
  double num0_7 = 0.234567;
  double num0_8 = 0.2345678;
  double num0_9 = 0.23456789;
  double num0_10 = 0.2345678910;

  double num1 = 1;
  double num1_1 = 1.0;
  double num1_2 = 1.2;
  double num1_3 = 1.23;
  double num1_4 = 1.234;
  double num1_5 = 1.2345;
  double num1_6 = 1.23456;
  double num1_7 = 1.234567;
  double num1_8 = 1.2345678;
  double num1_9 = 1.23456789;
  double num1_10 = 1.2345678910;

  double num2 = 12;
  double num2_1 = 12.0;
  double num2_2 = 12.2;
  double num2_3 = 12.23;
  double num2_4 = 12.234;
  double num2_5 = 12.2345;
  double num2_6 = 12.23456;
  double num2_7 = 12.234567;
  double num2_8 = 12.2345678;
  double num2_9 = 12.23456789;
  double num2_10 = 12.2345678910;

  double num3 = 123;
  double num3_1 = 123.0;
  double num3_2 = 123.2;
  double num3_3 = 123.23;
  double num3_4 = 123.234;
  double num3_5 = 123.2345;
  double num3_6 = 123.23456;
  double num3_7 = 123.234567;
  double num3_8 = 123.2345678;
  double num3_9 = 123.23456789;
  double num3_10 = 123.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_width_4_p2) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 1234;
  double num4_1 = 1234.0;
  double num4_2 = 1234.2;
  double num4_3 = 1234.23;
  double num4_4 = 1234.234;
  double num4_5 = 1234.2345;
  double num4_6 = 1234.23456;
  double num4_7 = 1234.234567;
  double num4_8 = 1234.2345678;
  double num4_9 = 1234.23456789;
  double num4_10 = 1234.2345678910;

  double num5 = 12345;
  double num5_1 = 12345.0;
  double num5_2 = 12345.2;
  double num5_3 = 12345.23;
  double num5_4 = 12345.234;
  double num5_5 = 12345.2345;
  double num5_6 = 12345.23456;
  double num5_7 = 12345.234567;
  double num5_8 = 12345.2345678;
  double num5_9 = 12345.23456789;
  double num5_10 = 12345.2345678910;

  double num6 = 123456;
  double num6_1 = 123456.0;
  double num6_2 = 123456.2;
  double num6_3 = 123456.23;
  double num6_4 = 123456.234;
  double num6_5 = 123456.2345;
  double num6_6 = 123456.23456;
  double num6_7 = 123456.234567;
  double num6_8 = 123456.2345678;
  double num6_9 = 123456.23456789;
  double num6_10 = 123456.2345678910;

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
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_width_4_p3) {
  char lib_res[1000];
  char s21_res[1000];

  double num0 = 0;
  double num0_1 = 0.1;
  double num0_2 = 0.9;
  double num0_3 = 0.93;
  double num0_4 = 0.934;
  double num0_5 = 0.9345;
  double num0_6 = 0.93456;
  double num0_7 = 0.934567;
  double num0_8 = 0.9345678;
  double num0_9 = 0.93456789;
  double num0_10 = 0.9345678910;

  double num1 = 9;
  double num1_1 = 9.0;
  double num1_2 = 9.9;
  double num1_3 = 9.49;
  double num1_4 = 9.500;
  double num1_5 = 9.5001;
  double num1_6 = 9.93456;
  double num1_7 = 9.934567;
  double num1_8 = 9.9945678;
  double num1_9 = 9.93456789;
  double num1_10 = 9.9345678910;

  double num2 = 92;
  double num2_1 = 98.9;
  double num2_2 = 98.9;
  double num2_3 = 98.83;
  double num2_4 = 98.834;
  double num2_5 = 98.2934;
  double num2_6 = 98.29345;
  double num2_7 = 98.934567;
  double num2_8 = 98.9345678;
  double num2_9 = 98.93456789;
  double num2_10 = 98.9345678910;

  double num3 = 999;
  double num3_1 = 993.0;
  double num3_2 = 923.2;
  double num3_3 = 923.23;
  double num3_4 = 923.234;
  double num3_5 = 923.2345;
  double num3_6 = 923.23456;
  double num3_7 = 923.234567;
  double num3_8 = 923.2345678;
  double num3_9 = 923.23456789;
  double num3_10 = 923.2345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num0, num0_1, num0_2, num0_3, num0_4, num0_5,
          num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1, num1_2, num1_3,
          num1_4, num1_5, num1_6, num1_7, num1_8, num1_9, num1_10, num2, num2_1,
          num2_2, num2_3, num2_4, num2_5, num2_6, num2_7, num2_8, num2_9,
          num2_10, num3, num3_1, num3_2, num3_3, num3_4, num3_5, num3_6, num3_7,
          num3_8, num3_9, num3_10);
  s21_sprintf(s21_res, format_string, num0, num0_1, num0_2, num0_3, num0_4,
              num0_5, num0_6, num0_7, num0_8, num0_9, num0_10, num1, num1_1,
              num1_2, num1_3, num1_4, num1_5, num1_6, num1_7, num1_8, num1_9,
              num1_10, num2, num2_1, num2_2, num2_3, num2_4, num2_5, num2_6,
              num2_7, num2_8, num2_9, num2_10, num3, num3_1, num3_2, num3_3,
              num3_4, num3_5, num3_6, num3_7, num3_8, num3_9, num3_10);

  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(test_sprintf_sharp_g_spec_set_precision_many_width_4_p4) {
  char lib_res[1000];
  char s21_res[1000];
  double num4 = 9994;
  double num4_1 = 9934.9;
  double num4_2 = 9934.9;
  double num4_3 = 9934.93;
  double num4_4 = 9934.934;
  double num4_5 = 9934.9345;
  double num4_6 = 9934.93456;
  double num4_7 = 9934.934567;
  double num4_8 = 9934.9345678;
  double num4_9 = 9934.93456789;
  double num4_10 = 9234.9345678910;

  double num5 = 92345;
  double num5_1 = 99999.0;
  double num5_2 = 99998.9;
  double num5_3 = 99998.93;
  double num5_4 = 99998.934;
  double num5_5 = 99998.9345;
  double num5_6 = 99998.93456;
  double num5_7 = 99998.934567;
  double num5_8 = 99998.9345678;
  double num5_9 = 99998.93456789;
  double num5_10 = 99998.9345678910;

  double num6 = 999999;
  double num6_1 = 999999.0;
  double num6_2 = 999999.2;
  double num6_3 = 999999.23;
  double num6_4 = 999999.234;
  double num6_5 = 999999.2345;
  double num6_6 = 999999.23456;
  double num6_7 = 999999.234567;
  double num6_8 = 999999.2345678;
  double num6_9 = 999999.23456789;
  double num6_10 = 999999.2345678910;

  double num7 = 9999999;
  double num7_1 = 9999999.0;
  double num7_2 = 9999998.9;
  double num7_3 = 9999998.93;
  double num7_4 = 9999998.934;
  double num7_5 = 9999998.9345;
  double num7_6 = 9999998.93456;
  double num7_7 = 9999998.934567;
  double num7_8 = 9999998.9345678;
  double num7_9 = 9999998.93456789;
  double num7_10 = 9999998.9345678910;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
      "%%#4.%dg %%#4.%dg %%#4.%dg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(
    test_sprintf_sharp_g_spec_long_double_set_precision_many_width_4_p1) {
  char lib_res[1000];
  char s21_res[1000];
  long double num4 = 9994.0L;
  long double num4_1 = 9234.9L;
  long double num4_2 = 9234.9L;
  long double num4_3 = 9234.93L;
  long double num4_4 = 9234.934L;
  long double num4_5 = 9234.9345L;
  long double num4_6 = 9234.93456L;
  long double num4_7 = 9234.934567L;
  long double num4_8 = 9234.9345678L;
  long double num4_9 = 9234.93456789L;
  long double num4_10 = 9234.9345678910L;

  long double num5 = 92345L;
  long double num5_1 = 99999.0L;
  long double num5_2 = 99998.9L;
  long double num5_3 = 99998.93L;
  long double num5_4 = 99998.934L;
  long double num5_5 = 99998.9345L;
  long double num5_6 = 99998.93456L;
  long double num5_7 = 99998.934567L;
  long double num5_8 = 99998.9345678L;
  long double num5_9 = 99998.93456789L;
  long double num5_10 = 99998.9345678910L;

  long double num6 = 999999L;
  long double num6_1 = 999999.0L;
  long double num6_2 = 999999.2L;
  long double num6_3 = 999999.23L;
  long double num6_4 = 999999.234L;
  long double num6_5 = 999999.2345L;
  long double num6_6 = 999999.23456L;
  long double num6_7 = 999999.234567L;
  long double num6_8 = 999999.2345678L;
  long double num6_9 = 999999.23456789L;
  long double num6_10 = 999999.2345678910L;

  long double num7 = 9999999L;
  long double num7_1 = 9999999.0L;
  long double num7_2 = 9999998.9L;
  long double num7_3 = 9999998.93L;
  long double num7_4 = 9999998.934L;
  long double num7_5 = 9999998.9345L;
  long double num7_6 = 9999998.93456L;
  long double num7_7 = 9999998.934567L;
  long double num7_8 = 9999998.9345678L;
  long double num7_9 = 9999998.93456789L;
  long double num7_10 = 9999998.9345678910L;

  int pr = _i;  // supplied through add_loop_test func

  char format_string[500];

  s21_sprintf(
      format_string,
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg %%#4.%dLg "
      "%%#4.%dLg",
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr,
      pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num4, num4_1, num4_2, num4_3, num4_4, num4_5,
          num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1, num5_2, num5_3,
          num5_4, num5_5, num5_6, num5_7, num5_8, num5_9, num5_10, num6, num6_1,
          num6_2, num6_3, num6_4, num6_5, num6_6, num6_7, num6_8, num6_9,
          num6_10, num7, num7_1, num7_2, num7_3, num7_4, num7_5, num7_6, num7_7,
          num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num4, num4_1, num4_2, num4_3, num4_4,
              num4_5, num4_6, num4_7, num4_8, num4_9, num4_10, num5, num5_1,
              num5_2, num5_3, num5_4, num5_5, num5_6, num5_7, num5_8, num5_9,
              num5_10, num6, num6_1, num6_2, num6_3, num6_4, num6_5, num6_6,
              num6_7, num6_8, num6_9, num6_10, num7, num7_1, num7_2, num7_3,
              num7_4, num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

START_TEST(
    test_sprintf_sharp_g_spec_long_double_set_precision_many_width_4_p2) {
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

  s21_sprintf(format_string,
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg "
              "%%#4.%dg %%#4.%dg %%#4.%dg %%#4.%dg",
              pr, pr, pr, pr, pr, pr, pr, pr, pr, pr, pr);

  sprintf(lib_res, format_string, num7, num7_1, num7_2, num7_3, num7_4, num7_5,
          num7_6, num7_7, num7_8, num7_9, num7_10);

  s21_sprintf(s21_res, format_string, num7, num7_1, num7_2, num7_3, num7_4,
              num7_5, num7_6, num7_7, num7_8, num7_9, num7_10);
  ck_assert_str_eq(lib_res, s21_res);
}
END_TEST

Suite* make_sprintf_suite() {
  Suite* sprintf_suite = suite_create("sprintf");
  TCase* tc_core;
  TCase* tc_problematic;
  // TCase* tc_another;

  tc_core = tcase_create("Core");
  tc_problematic = tcase_create("Problematic");
  // tc_another = tcase_create("Another");

  tcase_add_test(tc_core, test_sprintf_int);
  tcase_add_test(tc_core, test_sprintf_int_0_padding);
  tcase_add_test(tc_core, test_sprintf_ints_d);
  tcase_add_test(tc_core, test_sprintf_ints_i);
  tcase_add_test(tc_core, test_sprintf_int_min);
  tcase_add_test(tc_core, test_sprintf_long_ints_d);
  tcase_add_test(tc_core, test_sprintf_short_ints_d);
  tcase_add_test(tc_core, test_sprintf_char);
  tcase_add_test(tc_core, test_sprintf_char_width);
  tcase_add_test(tc_core, test_sprintf_string);
  tcase_add_test(tc_core, test_sprintf_empty_string);
  tcase_add_test(tc_core, test_sprintf_problematic_float);
  tcase_add_test(tc_core, test_sprintf_very_float);
  tcase_add_test(tc_core, test_sprintf_a_bit_float);
  tcase_add_test(tc_core, test_sprintf_float_width_precision_flag);
  tcase_add_test(tc_core, test_sprintf_unsigned);
  tcase_add_test(tc_core, test_sprintf_unsigned_problematic);

  tcase_add_test(tc_core, test_sprintf_long_doubles);
  tcase_add_test(tc_core, test_sprintf_short_overflow);
  tcase_add_test(tc_core, test_sprintf_int_overflow);
  tcase_add_test(tc_core, test_sprintf_long_overflow);
  tcase_add_test(tc_core, test_sprintf_number_of_characters);
  tcase_add_test(tc_core, test_sprintf_wide_character);
  tcase_add_test(tc_core, test_sprintf_wide_character_string);
  tcase_add_test(tc_core, test_sprintf_hex_lower_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_hex_upper_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_octal_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_octal_negative_long);
  tcase_add_test(tc_core, test_sprintf_octal_width);
  tcase_add_test(tc_core, test_sprintf_char_problematic);
  tcase_add_test(tc_core, test_sprintf_pointer_type);
  tcase_add_test(tc_core, test_sprintf_flag_sharp_oxX);

  tcase_add_test(tc_core, test_sprintf_scientific_zero_double);
  tcase_add_test(tc_core, test_sprintf_scientific_front_double);
  tcase_add_test(tc_core, test_sprintf_scientific_from_negative_double);

  tcase_add_test(tc_problematic,
                 test_sprintf_mantissa_or_exponent_negative_value);
  tcase_add_test(tc_core, test_sprintf_mantissa_or_exponent_formats);

  tcase_add_loop_test(tc_core, test_sprintf_scientific_loop_precisions, 0, 14);

  tcase_add_test(tc_core, test_sprintf_scientific_from_big_double);

  tcase_add_loop_test(tc_core, test_sprintf_scientific_long_loop_precisions, 0,
                      18);
  tcase_add_loop_test(tc_core, test_sprintf_scientific_zero_loop_precisions, 0,
                      18);

  tcase_add_loop_test(tc_core, test_sprintf_g_spec_loop_precisions, 0, 14);
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_long_loop_precisions, 0, 17);
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_zero_loop_precisions, 0, 14);
  tcase_add_test(tc_core, test_sprintf_g_spec_no_precision_many_p1);
  tcase_add_test(tc_core, test_sprintf_g_spec_no_precision_many_p2);
  tcase_add_test(tc_core, test_sprintf_g_spec_precision_0_many_p1);
  tcase_add_test(tc_core, test_sprintf_g_spec_precision_0_many_p2);

  tcase_add_test(tc_problematic, test_sprintf_g_spec_no_precision_interesting);

  tcase_add_test(tc_core, test_sprintf_double_nan_inf);
  tcase_add_test(tc_core, test_sprintf_long_double);
  tcase_add_test(tc_core, test_sprintf_double_long_double);

  tcase_add_loop_test(tc_core, test_sprintf_g_spec_set_precision_many_p1, 0,
                      14);
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_set_precision_many_p2, 0,
                      14);
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_set_precision_many_p3, 0,
                      14);
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_set_precision_many_p4, 0,
                      14);

  tcase_add_loop_test(
      tc_core, test_sprintf_g_spec_long_double_set_precision_many_p1, 0, 18);

  tcase_add_loop_test(
      tc_core, test_sprintf_g_spec_long_double_set_precision_many_p2, 0, 18);

  tcase_add_loop_test(tc_core, test_sprintf_loop_star, 0, 14);

  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_loop_precisions, 0,
                      14);
  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_long_loop_precisions,
                      0, 17);
  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_zero_loop_precisions,
                      0, 14);
  tcase_add_test(tc_core, test_sprintf_sharp_g_spec_no_precision_many_p1);
  tcase_add_test(tc_core, test_sprintf_sharp_g_spec_no_precision_many_p2);
  tcase_add_test(tc_core, test_sprintf_sharp_g_spec_precision_0_many_p1);
  tcase_add_test(tc_core, test_sprintf_sharp_g_spec_precision_0_many_p2);

  tcase_add_test(tc_problematic,
                 test_sprintf_sharp_g_spec_no_precision_interesting);

  tcase_add_test(tc_core, test_sprintf_sharp_double_nan_inf);
  tcase_add_test(tc_core, test_sprintf_sharp_long_double);
  tcase_add_test(tc_core, test_sprintf_sharp_double_long_double);

  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_set_precision_many_p1,
                      0, 14);
  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_set_precision_many_p2,
                      0, 14);
  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_set_precision_many_p3,
                      0, 14);
  tcase_add_loop_test(tc_core, test_sprintf_sharp_g_spec_set_precision_many_p4,
                      0, 14);

  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_long_double_set_precision_many_p1, 0,
      18);

  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_long_double_set_precision_many_p2, 0,
      18);

  tcase_add_loop_test(tc_core, test_sprintf_sharp_loop_star, 0, 14);

  tcase_add_test(tc_core, test_sprintf_sharp_very_float);
  tcase_add_test(tc_core, test_sprintf_sharp_a_bit_float);
  tcase_add_test(tc_core, test_sprintf_sharp_float_width_precision_flag);

  tcase_add_test(tc_core, test_sprintf_sharp_hex_lower_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_sharp_hex_upper_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_sharp_octal_with_modifiers);
  tcase_add_test(tc_core, test_sprintf_sharp_octal_negative_long);
  tcase_add_test(tc_core, test_sprintf_sharp_octal_width);

  tcase_add_test(tc_core, test_sprintf_sharp_scientific_zero_double);
  tcase_add_test(tc_core, test_sprintf_sharp_scientific_front_double);
  tcase_add_test(tc_core, test_sprintf_sharp_scientific_from_negative_double);

  tcase_add_test(tc_core, test_sprintf_sharp_mantissa_or_exponent_formats);
  tcase_add_test(tc_problematic,
                 test_sprintf_sharp_mantissa_or_exponent_negative_value);

  tcase_add_loop_test(tc_core, test_sprintf_sharp_scientific_loop_precisions, 0,
                      14);

  tcase_add_test(tc_core, test_sprintf_sharp_scientific_from_big_double);

  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_scientific_long_loop_precisions, 0, 18);
  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_scientific_zero_loop_precisions, 0, 18);

  //////new
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_loop_precisions_width_4, 0,
                      14);
  tcase_add_loop_test(tc_core, test_sprintf_g_spec_long_loop_precisions_width_4,
                      0, 17);

  tcase_add_loop_test(tc_core, test_sprintf_g_spec_zero_loop_precisions_width_4,
                      0, 14);
  tcase_add_test(tc_core, test_sprintf_g_spec_no_precision_many_width_4_p1);
  tcase_add_test(tc_core, test_sprintf_g_spec_no_precision_many_width_4_p2);
  tcase_add_test(tc_core, test_sprintf_g_spec_precision_0_many_width_4_p1);
  tcase_add_test(tc_core, test_sprintf_g_spec_precision_0_many_width_4_p2);

  tcase_add_loop_test(tc_core,
                      test_sprintf_g_spec_set_precision_many_width_4_p1, 0, 14);
  tcase_add_loop_test(tc_core,
                      test_sprintf_g_spec_set_precision_many_width_4_p2, 0, 14);
  tcase_add_loop_test(tc_core,
                      test_sprintf_g_spec_set_precision_many_width_4_p3, 0, 14);
  tcase_add_loop_test(tc_core,
                      test_sprintf_g_spec_set_precision_many_width_4_p4, 0, 14);

  tcase_add_loop_test(
      tc_core, test_sprintf_g_spec_long_double_set_precision_many_width_4_p1, 0,
      18);
  tcase_add_loop_test(
      tc_core, test_sprintf_g_spec_long_double_set_precision_many_width_4_p2, 0,
      18);
  tcase_add_loop_test(tc_core,
                      test_sprintf_sharp_g_spec_loop_precisions_width_4, 0, 14);
  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_long_loop_precisions_width_4, 0, 17);
  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_zero_loop_precisions_width_4, 0, 14);
  tcase_add_test(tc_core,
                 test_sprintf_sharp_g_spec_no_precision_many_width_4_p1);
  tcase_add_test(tc_core,
                 test_sprintf_sharp_g_spec_no_precision_many_width_4_p2);
  tcase_add_test(tc_core,
                 test_sprintf_sharp_g_spec_precision_0_many_width_4_p1);
  tcase_add_test(tc_core,
                 test_sprintf_sharp_g_spec_precision_0_many_width_4_p2);

  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_set_precision_many_width_4_p1, 0, 14);
  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_set_precision_many_width_4_p2, 0, 14);
  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_set_precision_many_width_4_p3, 0, 14);
  tcase_add_loop_test(
      tc_core, test_sprintf_sharp_g_spec_set_precision_many_width_4_p4, 0, 14);

  tcase_add_loop_test(
      tc_core,
      test_sprintf_sharp_g_spec_long_double_set_precision_many_width_4_p1, 0,
      18);

  tcase_add_loop_test(
      tc_core,
      test_sprintf_sharp_g_spec_long_double_set_precision_many_width_4_p2, 0,
      18);

  suite_add_tcase(sprintf_suite, tc_core);
  suite_add_tcase(sprintf_suite, tc_problematic);
  // suite_add_tcase(sprintf_suite, tc_another);
  return sprintf_suite;
}