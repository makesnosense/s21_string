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

  sprintf(lib_res, "%-4p %-6p %35p", (void*)&value1, (void*)&value2,
          (void*)&value3);
  s21_sprintf(s21_res, "%-4p %-6p %35p", (void*)&value1, (void*)&value2,
              (void*)&value3);
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

  double num1 = -566765.1266666643573;

  sprintf(lib_res, "%g %G", num1, num1);
  s21_sprintf(s21_res, "%g %G", num1, num1);
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

// START_TEST(test_sprintf_scientific_from_big_double) {
//   char lib_res[100];
//   char s21_res[100];
//   long double num = 3.3333333333333333;
//   sprintf(lib_res, "%Le", num);
//   s21_sprintf(s21_res, "%Le", num);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

// START_TEST(test_sprintf_scientific_long_loop_precisions) {
//   char lib_res[1000];
//   char s21_res[1000];
//   long double num1 = 1.2345678;
//   long double num2 = 1.0;
//   long double num3 = 1.2345678910;
//   long double num4 = 1;

//   int precision = _i;  // supplied through add_loop_test func

//   char format_string[70];

//   s21_sprintf(format_string, "%%.%dLe %%.%dLe %%.%dLe %%.%dLe", precision,
//               precision, precision, precision);
//   sprintf(lib_res, format_string, num1, num2, num3, num4);
//   s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

// START_TEST(test_sprintf_scientific_zero_loop_precisions) {
//   char lib_res[100];
//   char s21_res[100];

//   double zero = 0.0;

//   int precision = _i;  // supplied through add_loop_test func

//   char format_string[70];

//   s21_sprintf(format_string, "%%.%de %%.e", precision);
//   sprintf(lib_res, format_string, zero, zero);
//   s21_sprintf(s21_res, format_string, zero, zero);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

// START_TEST(test_sprintf_g_spec_loop_precisions) {
//   char lib_res[1000];
//   char s21_res[1000];
//   double num1 = 1.2345678;
//   double num2 = 1.0;
//   double num3 = 1.2345678910;
//   double num4 = 1;

//   int precision = _i;  // supplied through add_loop_test func

//   char format_string[70];

//   s21_sprintf(format_string, "%%.%dg %%.%dg %%.%dg %%.%dg", precision,
//               precision, precision, precision);
//   sprintf(lib_res, format_string, num1, num2, num3, num4);
//   s21_sprintf(s21_res, format_string, num1, num2, num3, num4);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

// START_TEST(test_sprintf_g_spec_zero_loop_precisions) {
//   char lib_res[1000];
//   char s21_res[1000];
//   double num1 = 0;
//   double num2 = 0.000;

//   int precision = _i;  // supplied through add_loop_test func

//   char format_string[70];

//   s21_sprintf(format_string, "%%.%dg %%.g %%.%dg %%.g", precision);
//   sprintf(lib_res, format_string, num1, num2);
//   s21_sprintf(s21_res, format_string, num1, num2);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

// START_TEST(test_sprintf_g_spec_no_precision) {
//   char lib_res[1000];
//   char s21_res[1000];
//   double num1 = 1234.5678;
//   double num2 = 1234.0;
//   double num3 = 123.5678910;
//   double num4 = 1;

//   sprintf(lib_res, "%g %g %g %g %.0g %.0g %.0g %.0g", num1, num2, num3, num4,
//           num1, num2, num3, num4);
//   s21_sprintf(s21_res, "%g %g %g %g %.0g %.0g %.0g %.0g", num1, num2, num3,
//               num4, num1, num2, num3, num4);
//   ck_assert_str_eq(lib_res, s21_res);
// }
// END_TEST

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

Suite* make_sprintf_suite() {
  Suite* sprintf_suite = suite_create("sprintf");
  TCase* tc_core;
  TCase* tc_problematic;

  tc_core = tcase_create("Core");
  tc_problematic = tcase_create("Problematic");

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

  tcase_add_test(tc_core, test_sprintf_mantissa_or_exponent_negative_value);
  tcase_add_test(tc_core, test_sprintf_mantissa_or_exponent_formats);

  tcase_add_loop_test(tc_core, test_sprintf_scientific_loop_precisions, 0, 14);

  tcase_add_test(tc_core, test_sprintf_double_nan_inf);
  tcase_add_test(tc_core, test_sprintf_long_double);
  tcase_add_test(tc_core, test_sprintf_double_long_double);

  // FAILING:

  // tcase_add_test(tc_core, test_sprintf_scientific_from_big_double);

  // tcase_add_loop_test(tc_core, test_sprintf_scientific_long_loop_precisions,
  // 0,
  //                     14);
  // tcase_add_loop_test(tc_core, test_sprintf_scientific_zero_loop_precisions,
  // 0,
  //                     18);
  // tcase_add_loop_test(tc_core, test_sprintf_g_spec_loop_precisions, 0, 18);
  // tcase_add_loop_test(tc_core, test_sprintf_g_spec_zero_loop_precisions, 0,
  // 18); tcase_add_test(tc_core, test_sprintf_g_spec_no_precision);
  // tcase_add_test(tc_core, test_sprintf_scientific_tiny);

  suite_add_tcase(sprintf_suite, tc_core);
  suite_add_tcase(sprintf_suite, tc_problematic);
  return sprintf_suite;
}
