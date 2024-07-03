#include <stdio.h>

#include "run_tests.h"

START_TEST(test_sscanf_simple_char) {
  char* input_string = "\t\tab \t \n \f";
  char* format_string = " %c %c %n";

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

  printf("первый чар %c второй чар %c n: %d\n", lib_res1, lib_res2, lib_res3);
  printf("первый чар %c второй чар %c n: %d\n", s21_res1, s21_res2, s21_res3);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
  ck_assert_int_eq(lib_res2, s21_res2);
  ck_assert_int_eq(lib_res3, s21_res3);
}
END_TEST

START_TEST(test_sscanf_char) {
  char* format_string = "Reading chars: %c-%c!%c@%c#%c$%c^";
  char* input_string = "Reading chars: Q-W!E@r#t$y^";

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

START_TEST(test_sscanf_possible_minus_one_p1) {
  char* input_string = "\t\t\t\n\f";
  char* format_string = " %c %c %n";

  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_res = 0;

  lib_res = sscanf(input_string, format_string, &lib_a, &lib_b, &lib_c);
  s21_res = s21_sscanf(input_string, format_string, &s21_a, &s21_b, &s21_c);

  printf("первый чар %c второй чар %c n: %d res: %d\n", lib_a, lib_b, lib_c,
         lib_res);
  printf("первый чар  %c второй чар %c n: %d res: %d\n", s21_a, s21_b, s21_c,
         s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
  ck_assert_int_eq(lib_c, s21_c);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p2) {
  int s21_a = 0;
  int s21_b = 0;
  char s21_c = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  char lib_c = 0;
  int lib_res = 0;

  s21_res = s21_sscanf(" ", " %n%n%c", &s21_a, &s21_b, &s21_c);
  lib_res = sscanf(" ", " %n%n%c", &lib_a, &lib_b, &lib_c);

  printf("наша %d %d %c res: %d\n", s21_a, s21_b, s21_c, s21_res);
  printf("__их %d %d %c res: %d\n", lib_a, lib_b, lib_c, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
  ck_assert_int_eq(lib_c, s21_c);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p3) {
  int s21_a = 0;
  int s21_b = 0;
  char s21_c = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  char lib_c = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("     \t\n", " %n %n %c", &s21_a, &s21_b, &s21_c);
  lib_res = sscanf("     \t\n", " %n %n %c", &lib_a, &lib_b, &lib_c);

  printf("наша %d %d %c res: %d\n", s21_a, s21_b, s21_c, s21_res);
  printf("__их %d %d %c res: %d\n", lib_a, lib_b, lib_c, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
  ck_assert_int_eq(lib_c, s21_c);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p4) {
  int s21_a = 0;
  int s21_b = 0;
  char s21_c = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  char lib_c = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("     \t\n", "%n %n %c", &s21_a, &s21_b, &s21_c);
  lib_res = sscanf("     \t\n", "%n %n %c", &lib_a, &lib_b, &lib_c);

  printf("наша %d %d %c res: %d\n", s21_a, s21_b, s21_c, s21_res);
  printf("__их %d %d %c res: %d\n", lib_a, lib_b, lib_c, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
  ck_assert_int_eq(lib_c, s21_c);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p5) {
  int s21_a = 0;
  int s21_b = 0;
  char s21_c = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  char lib_c = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("     \t\n", "%n%n%c", &s21_a, &s21_b, &s21_c);
  lib_res = sscanf("     \t\n", "%n%n%c", &lib_a, &lib_b, &lib_c);

  printf("наша %d %d %c res: %d\n", s21_a, s21_b, s21_c, s21_res);
  printf("__их %d %d %c res: %d\n", lib_a, lib_b, lib_c, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
  ck_assert_int_eq(lib_c, s21_c);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p6) {
  char s21_a = 0;
  char s21_b = 0;
  int s21_c = 0;
  int s21_res = 0;

  char lib_a = 0;
  char lib_b = 0;
  int lib_c = 0;
  int lib_res = 0;

  lib_res = sscanf("\t\t\t\n\fz", " %c %c %n", &lib_a, &lib_b, &lib_c);
  s21_res = s21_sscanf("\t\t\t\n\fz", " %c %c %n", &s21_a, &s21_b, &s21_c);

  printf("lin первый чар %c второй чар %c n: %d res: %d\n", lib_a, lib_b, lib_c,
         lib_res);
  printf("s21 первый чар %c второй чар %c n: %d res: %d\n", s21_a, s21_b, s21_c,
         s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
  ck_assert_int_eq(lib_c, s21_c);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p7) {
  int s21_a = 0;
  char s21_b = 0;

  int s21_res = 0;

  int lib_a = 0;
  char lib_b = 0;

  int lib_res = 0;

  lib_res = sscanf(" ", "%n%c ", &lib_a, &lib_b);
  s21_res = s21_sscanf(" ", "%n%c ", &s21_a, &s21_b);

  printf("первый чар %c второй чар %c res: %d\n", lib_a, lib_b, lib_res);
  printf("первый чар  %c второй чар %c res: %d\n", s21_a, s21_b, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_possible_minus_one_p8) {
  int s21_a = 0;
  int s21_b = 0;

  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;

  int lib_res = 0;

  lib_res = sscanf(" ", "%n%d ", &lib_a, &lib_b);
  s21_res = s21_sscanf(" ", "%n%d ", &s21_a, &s21_b);

  printf("первый чар %c второй чар %c res: %d\n", lib_a, lib_b, lib_res);
  printf("первый чар  %c второй чар %c res: %d\n", s21_a, s21_b, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_i_p1) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("0123 0123 123", "%i %i %i %n", &s21_a, &s21_b, &s21_c,
                       &s21_n);
  lib_res =
      sscanf("0123 0123 123", "%i %i %i %n", &lib_a, &lib_b, &lib_c, &lib_n);

  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a, lib_b,
         lib_c, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a, s21_b,
         s21_c, s21_n, s21_res);

  ck_assert_int_eq(s21_n, lib_n);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
}
END_TEST

START_TEST(test_sscanf_i_p2) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("0x123 0123 123", "%i %i %i %n", &s21_a, &s21_b, &s21_c,
                       &s21_n);
  lib_res =
      sscanf("0x123 0123 123", "%i %i %i %n", &lib_a, &lib_b, &lib_c, &lib_n);

  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a, lib_b,
         lib_c, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a, s21_b,
         s21_c, s21_n, s21_res);

  ck_assert_int_eq(s21_n, lib_n);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
}
END_TEST

START_TEST(test_sscanf_i_p3) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res =
      s21_sscanf("0 0 123", "%i %d %i %n", &s21_a, &s21_b, &s21_c, &s21_n);
  lib_res = sscanf("0 0 123", "%i %d %i %n", &lib_a, &lib_b, &lib_c, &lib_n);

  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a, lib_b,
         lib_c, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a, s21_b,
         s21_c, s21_n, s21_res);

  ck_assert_int_eq(s21_n, lib_n);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
}
END_TEST

START_TEST(test_sscanf_i_p4) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 06789 123", "%d %i %i %n", &s21_a, &s21_b, &s21_c,
                       &s21_n);
  lib_res =
      sscanf("23254 06789 123", "%d %i %i %n", &lib_a, &lib_b, &lib_c, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a,
         lib_b, lib_c, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a,
         s21_b, s21_c, s21_n, s21_res);

  ck_assert_int_eq(s21_n, lib_n);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
}
END_TEST

START_TEST(test_sscanf_i_p5) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 067345 0x123", "%i %i %i %n", &s21_a, &s21_b,
                       &s21_c, &s21_n);
  lib_res = sscanf("23254 067345 0x123", "%i %i %i %n", &lib_a, &lib_b, &lib_c,
                   &lib_n);

  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a, lib_b,
         lib_c, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a, s21_b,
         s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
}
END_TEST

START_TEST(test_sscanf_i_p6) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 06733 0x12x3 15", "%d %i %i %i %n", &s21_a,
                       &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("23254 06733 0x12x3 15", "%d %i %i %i %n", &lib_a, &lib_b,
                   &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четверты %d n: %d res: %d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf(
      "s21 первый чар %d второй чар %d третий: %d четверты %d n: %d res: %d\n",
      s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_i_p7) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 06733 0y12 15", "%d %i %i %i %n", &s21_a, &s21_b,
                       &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("23254 06733 0y12 15", "%d %i %i %i %n", &lib_a, &lib_b,
                   &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четверты %d n: %d res: %d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf(
      "s21 первый чар %d второй чар %d третий: %d четверты %d n: %d res: %d\n",
      s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_i_p8) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -06733 -0x123", "%10d %7i %4i %n", &s21_a, &s21_b,
                       &s21_c, &s21_n);
  lib_res = sscanf("23254 -06733 -0x123", "%10d %7i %4i %n", &lib_a, &lib_b,
                   &lib_c, &lib_n);

  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a, lib_b,
         lib_c, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a, s21_b,
         s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_width_p1) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -0673342 -0x12357", "%d %i %4i %n", &s21_a,
                       &s21_b, &s21_c, &s21_n);
  lib_res = sscanf("23254 -0673342 -0x12357", "%d %i %4i %n", &lib_a, &lib_b,
                   &lib_c, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a,
         lib_b, lib_c, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a,
         s21_b, s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_width_p2) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -0673342 -0x2357", "%d %i %5i %n", &s21_a, &s21_b,
                       &s21_c, &s21_n);
  lib_res = sscanf("23254 -0673342 -0x2357", "%d %i %5i %n", &lib_a, &lib_b,
                   &lib_c, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a,
         lib_b, lib_c, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a,
         s21_b, s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_width_p2_linux_only) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -0673342 -0xz2357", "%d %i %3i %n", &s21_a,
                       &s21_b, &s21_c, &s21_n);
  lib_res = sscanf("23254 -0673342 -0xz2357", "%d %i %3i %n", &lib_a, &lib_b,
                   &lib_c, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a,
         lib_b, lib_c, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a,
         s21_b, s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_width_p2_1_linux_only) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -0673342 -0x2357", "%d %i %3i %n", &s21_a, &s21_b,
                       &s21_c, &s21_n);
  lib_res = sscanf("23254 -0673342 -0x2357", "%d %i %3i %n", &lib_a, &lib_b,
                   &lib_c, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a,
         lib_b, lib_c, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a,
         s21_b, s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_width_p3) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_e = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_e = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -0673342 -0xz2357 0x664532", "%d %i %4i %i %i %n",
                       &s21_a, &s21_b, &s21_c, &s21_d, &s21_e, &s21_n);
  lib_res = sscanf("23254 -0673342 -0xz2357 0x664532", "%d %i %4i %i %i %n",
                   &lib_a, &lib_b, &lib_c, &lib_d, &lib_e, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четвёртый: %c пять: %d n: %d "
      "res: "
      "%d\n",
      lib_a, lib_b, lib_c, lib_d, lib_e, lib_n, lib_res);
  printf(
      "s21 первый чар %d второй чар %d третий: %d четвёртый: %c пять: %d n: %d "
      "res: "
      "%d\n",
      s21_a, s21_b, s21_c, s21_d, s21_e, s21_n, s21_res);

  ck_assert_int_eq(s21_n, lib_n);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_e, lib_e);
}
END_TEST

START_TEST(test_sscanf_width_p3_linux_only) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  char s21_d = 0;
  int s21_e = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  char lib_d = 0;
  int lib_e = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("23254 -0673342 -0xz2357 0x664532", "%d %i %4i %c %i %n",
                       &s21_a, &s21_b, &s21_c, &s21_d, &s21_e, &s21_n);
  lib_res = sscanf("23254 -0673342 -0xz2357 0x664532", "%d %i %4i %c %i %n",
                   &lib_a, &lib_b, &lib_c, &lib_d, &lib_e, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четвёртый: %c пять: %d n: %d "
      "res: "
      "%d\n",
      lib_a, lib_b, lib_c, lib_d, lib_e, lib_n, lib_res);
  printf(
      "s21 первый чар %d второй чар %d третий: %d четвёртый: %c пять: %d n: %d "
      "res: "
      "%d\n",
      s21_a, s21_b, s21_c, s21_d, s21_e, s21_n, s21_res);

  ck_assert_int_eq(s21_n, lib_n);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_e, lib_e);
}
END_TEST

START_TEST(test_sscanf_d) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("12345 0789 123", "%d %d %d %n", &s21_a, &s21_b, &s21_c,
                       &s21_n);
  lib_res =
      sscanf("12345 0789 123", "%d %d %d %n", &lib_a, &lib_b, &lib_c, &lib_n);

  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", lib_a, lib_b,
         lib_c, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d n: %d res: %d\n", s21_a, s21_b,
         s21_c, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_long_i) {
  long int s21_a = 0;
  long int s21_b = 0;
  long int s21_c = 0;
  long int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  long int lib_a = 0;
  long int lib_b = 0;
  long int lib_c = 0;
  long int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res =
      s21_sscanf("2147483647 -21474836489 017777777777 0x7fffffff",
                 "%li %li %li %li %n", &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res =
      sscanf("2147483647 -21474836489 017777777777 0x7fffffff",
             "%li %li %li %li %n", &lib_a, &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %ld второй чар %ld третий: %ld четыре %ld  n: %d res: "
      "%d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf(
      "s21 первый чар %ld второй чар %ld третий: %ld четыре %ld n: %d res: "
      "%d\n",
      s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_long_i_p2) {
  long int s21_a = 0;
  long int s21_b = 0;
  long int s21_c = 0;
  long int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  long int lib_a = 0;
  long int lib_b = 0;
  long int lib_c = 0;
  long int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res =
      s21_sscanf("-234235 -2147483 -0177777777 -0x7fffff", "%li %li %li %li %n",
                 &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res =
      sscanf("-234235 -2147483 -0177777777 -0x7fffff", "%li %li %li %li %n",
             &lib_a, &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %ld второй чар %ld третий: %ld четыре %ld  n: %d res: "
      "%d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf(
      "s21 первый чар %ld второй чар %ld третий: %ld четыре %ld n: %d res: "
      "%d\n",
      s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_long_i) {
  long int s21_a = 0;
  long int s21_b = 0;
  long int s21_c = 0;
  long int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  long int lib_a = 0;
  long int lib_b = 0;
  long int lib_c = 0;
  long int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res =
      s21_sscanf("214748364155 -2147483649 020000000001 0x80000001",
                 "%li %li %li %li %n", &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res =
      sscanf("214748364155 -2147483649 020000000001 0x80000001",
             "%li %li %li %li %n", &lib_a, &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %ld второй чар %ld третий: %ld четыре %ld  n: %d res: "
      "%d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf(
      "s21 первый чар %ld второй чар %ld третий: %ld четыре %ld n: %d res: "
      "%d\n",
      s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_owerflow_short_negative_valua_spec_i) {
  short int s21_a = 0;
  short int s21_b = 0;
  short int s21_c = 0;

  int s21_n = 0;
  int s21_res = 0;

  short int lib_a = 0;
  short int lib_b = 0;
  short int lib_c = 0;

  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("-0100002 0x8fa2 -70000", "%hi %hi %hi %n", &s21_a,
                       &s21_b, &s21_c, &s21_n);
  lib_res = sscanf("-0100002 0x8fa2 -70000", "%hi %hi %hi %n", &lib_a, &lib_b,
                   &lib_c, &lib_n);

  printf("lib первый чар %hd n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %hd n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_short_i) {
  short int s21_a = 0;
  short int s21_b = 0;
  short int s21_c = 0;
  short int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  short int lib_a = 0;
  short int lib_b = 0;
  short int lib_c = 0;
  short int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("32767 -32768 077777, 0x7fff", "%hi %hi %hi, %hi %n",
                       &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("32767 -32768 077777, 0x7fff", "%hi %hi %hi, %hi %n", &lib_a,
                   &lib_b, &lib_c, &lib_d, &lib_n);

  printf("первый чар %d второй чар %d третий: %d четыре %d  n: %d res: %d\n",
         lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_short_i) {
  short int s21_a = 0;
  short int s21_b = 0;
  short int s21_c = 0;
  short int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  short int lib_a = 0;
  short int lib_b = 0;
  short int lib_c = 0;
  short int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res =
      s21_sscanf("2147883677 -3279999 0100001 0x8001", "%hi %hi %hi %hi %n",
                 &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("2147883677 -3279999 0100001 0x8001", "%hi %hi %hi %hi %n",
                   &lib_a, &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четыре %d  n: %d res: %d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_spec_i) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res =
      s21_sscanf("2147883677, -020000000537 0x802626ff -0x802626ff",
                 "%i, %i %i %i %n", &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("2147883677, -020000000537 0x802626ff -0x802626ff",
                   "%i, %i %i %i %n", &lib_a, &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четыре %d  n: %d res: %d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_int_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_b, lib_b);
  ck_assert_int_eq(s21_c, lib_c);
  ck_assert_int_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_octal_problematic) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("0327 03273549 01644 04001", "%o %o %o %o %n", &s21_a,
                       &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("0327 03273549 01644 04001", "%o %o %o %o %n", &lib_a,
                   &lib_b, &lib_c, &lib_d, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_uint_eq(s21_b, lib_b);
  ck_assert_uint_eq(s21_c, lib_c);
  ck_assert_uint_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_octal) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("0327 0327 01644 04001", "%o %o %o %o %n", &s21_a,
                       &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("0327 0327 01644 04001", "%o %o %o %o %n", &lib_a, &lib_b,
                   &lib_c, &lib_d, &lib_n);

  printf("lib первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_uint_eq(s21_b, lib_b);
  ck_assert_uint_eq(s21_c, lib_c);
  ck_assert_uint_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_long_octal) {
  long unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  long unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("037777777777", "%lo %n", &s21_a, &s21_n);
  lib_res = sscanf("037777777777", "%lo %n", &lib_a, &lib_n);

  printf("lib первый чар %ld n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %ld n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_long_octal) {
  long unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  long unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("045156223377", "%lo %n", &s21_a, &s21_n);
  lib_res = sscanf("045156223377", "%lo %n", &lib_a, &lib_n);

  printf("lib первый чар %ld n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %ld n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_short_octal) {
  short unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  short unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("0177777", "%ho %n", &s21_a, &s21_n);
  lib_res = sscanf("0177777", "%ho %n", &lib_a, &lib_n);

  printf("lib первый чар %hd n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %hd n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_short_octal) {
  short unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  short unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("02516077", "%ho %n", &s21_a, &s21_n);
  lib_res = sscanf("02516077", "%ho %n", &lib_a, &lib_n);

  printf("lib первый чар %hd n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %hd n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_hex_problematic) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("0x327 0x327f99 0x1007zf01 0x4001", "%x %x %X %X %n",
                       &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("0x327 0x327f99 0x1007zf01 0x4001", "%x %x %X %X %n", &lib_a,
                   &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четыре %d  n: %d res: %d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_uint_eq(s21_b, lib_b);
  ck_assert_uint_eq(s21_c, lib_c);
  ck_assert_uint_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_hex) {
  int s21_a = 0;
  int s21_b = 0;
  int s21_c = 0;
  int s21_d = 0;
  int s21_n = 0;
  int s21_res = 0;

  int lib_a = 0;
  int lib_b = 0;
  int lib_c = 0;
  int lib_d = 0;
  int lib_n = 0;
  int lib_res = 0;

  s21_res = s21_sscanf("0x327 0x327f99 0x1007f01 0x4001", "%x %x %X %X %n",
                       &s21_a, &s21_b, &s21_c, &s21_d, &s21_n);
  lib_res = sscanf("0x327 0x327f99 0x1007f01 0x4001", "%x %x %X %X %n", &lib_a,
                   &lib_b, &lib_c, &lib_d, &lib_n);

  printf(
      "lib первый чар %d второй чар %d третий: %d четыре %d  n: %d res: %d\n",
      lib_a, lib_b, lib_c, lib_d, lib_n, lib_res);
  printf("s21 первый чар %d второй чар %d третий: %d четыре %d n: %d res: %d\n",
         s21_a, s21_b, s21_c, s21_d, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_uint_eq(s21_b, lib_b);
  ck_assert_uint_eq(s21_c, lib_c);
  ck_assert_uint_eq(s21_d, lib_d);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_long_hex) {
  long unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  long unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("0xffffffff,", "%lx, %n", &s21_a, &s21_n);
  lib_res = sscanf("0xffffffff,", "%lx, %n", &lib_a, &lib_n);

  printf("lib первый чар %ld n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %ld n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_long_hex) {
  long unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  long unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("0x129b926ff,", "%lx, %n", &s21_a, &s21_n);
  lib_res = sscanf("0x129b926ff,", "%lx, %n", &lib_a, &lib_n);

  printf("lib первый чар %ld n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %ld n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_short_hex) {
  short unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  short unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("0XFFFF", "%hx %n", &s21_a, &s21_n);
  lib_res = sscanf("0XFFFF", "%hx %n", &lib_a, &lib_n);

  printf("lib первый чар %hd n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %hd n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_overflow_short_hex) {
  short unsigned s21_a = 0;
  int s21_n = 0;
  int s21_res = 0;

  short unsigned lib_a = 0;
  int lib_n = 0;

  int lib_res = 0;

  s21_res = s21_sscanf("0x11387", "%hx %n", &s21_a, &s21_n);
  lib_res = sscanf("0x11387", "%hx %n", &lib_a, &lib_n);

  printf("lib первый чар %hd n: %d res: %d\n", lib_a, lib_n, lib_res);
  printf("s21 первый чар %hd n: %d res: %d\n", s21_a, s21_n, s21_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(s21_a, lib_a);
  ck_assert_int_eq(s21_n, lib_n);
}
END_TEST

START_TEST(test_sscanf_float) {
  char* input_string = "i have 0.0 money";
  char* format_string = "i have %f money";

  float s21_a = 0;
  float s21_res = 0;

  int lib_a = 0;
  int lib_res = 0;

  lib_res = sscanf(input_string, format_string, &lib_a);
  s21_res = s21_sscanf(input_string, format_string, &s21_a);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_float_eq(lib_a, s21_a);
}
END_TEST

START_TEST(test_sscanf_float_2) {
  float s21_a = 0;
  float s21_b = 0;
  int s21_res = 0;

  float lib_a = 0;
  float lib_b = 0;
  int lib_res = 0;

  lib_res = sscanf("1844.654656 1844.654656", "%f %f", &lib_a, &lib_b);
  s21_res = s21_sscanf("1844.654656 1844.654656", "%f %f", &s21_a, &s21_b);

  printf("s21 first: %f second: %f res: %d\n", s21_a, s21_b, s21_res);
  printf("lib first: %f second: %f res: %d\n\n", lib_a, lib_b, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_float_eq(lib_a, s21_a);
  ck_assert_float_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_float_3) {
  float s21_a = 7;
  float s21_b = 0;
  int s21_res = 0;

  float lib_a = 0;
  float lib_b = 0;
  int lib_res = 0;

  lib_res = sscanf("-0.999 -912.12", "%4f %f", &lib_a, &lib_b);
  s21_res = s21_sscanf("-0.999 -912.12", "%4f %f", &s21_a, &s21_b);

  printf("s21 first: %f second: %f res: %d\n", s21_a, s21_b, s21_res);
  printf("lib first: %f second: %f res: %d\n\n", lib_a, lib_b, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_float_eq(lib_a, s21_a);
  ck_assert_float_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_long_float) {
  double s21_a = 7;
  double s21_b = 0;
  int s21_res = 0;

  double lib_a = 0;
  double lib_b = 0;
  int lib_res = 0;

  lib_res = sscanf("1119007199254740992.6424 -1119007199254740992.6424",
                   "%lf %lf", &lib_a, &lib_b);
  s21_res = s21_sscanf("1119007199254740992.6424 -1119007199254740992.6424",
                       "%lf %lf", &s21_a, &s21_b);

  printf("s21 first: %lf second: %lf res: %d\n", s21_a, s21_b, s21_res);
  printf("lib first: %lf second: %lf res: %d\n\n", lib_a, lib_b, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_double_eq(lib_a, s21_a);
  ck_assert_double_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_long_long_float) {
  long double s21_a = 7;
  long double s21_b = 0;
  int s21_res = 0;

  long double lib_a = 0;
  long double lib_b = 0;
  int lib_res = 0;

  lib_res =
      sscanf("79228162514264337593543950336 -79228162514264337593543950336",
             "%Lf %Lf", &lib_a, &lib_b);
  s21_res =
      s21_sscanf("79228162514264337593543950336 -79228162514264337593543950336",
                 "%Lf %Lf", &s21_a, &s21_b);

  printf("s21 first: %Lf second: %Lf res: %d\n", s21_a, s21_b, s21_res);
  printf("lib first: %Lf second: %Lf res: %d\n\n", lib_a, lib_b, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_double_eq(lib_a, s21_a);
  ck_assert_double_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_overflow_long_long_float) {
  long double s21_a = 7;
  long double s21_b = 0;
  int s21_res = 0;

  long double lib_a = 0;
  long double lib_b = 0;
  int lib_res = 0;

  lib_res = sscanf(
      "792281625142643375935439503366354234 "
      "-792281625142643375935439503366354234",
      "%Lf %Lf", &lib_a, &lib_b);
  s21_res = s21_sscanf(
      "792281625142643375935439503366354234 "
      "-792281625142643375935439503366354234",
      "%Lf %Lf", &s21_a, &s21_b);

  printf("s21 first: %Lf second: %Lf res: %d\n", s21_a, s21_b, s21_res);
  printf("lib first: %Lf second: %Lf res: %d\n\n", lib_a, lib_b, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_double_eq(lib_a, s21_a);
  ck_assert_double_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_unsigned) {
  unsigned s21_a = 0;
  unsigned s21_b = 0;
  int s21_res = 0;

  unsigned lib_a = 0;
  unsigned lib_b = 0;
  int lib_res = 0;

  lib_res = sscanf("Unsigned 1: 7, unsigned 2: 123123123",
                   "Unsigned 1: %u, unsigned 2: %u", &lib_a, &lib_b);
  s21_res = s21_sscanf("Unsigned 1: 7, unsigned 2: 123123123",
                       "Unsigned 1: %u, unsigned 2: %u", &s21_a, &s21_b);

  printf("s21 first: %u second: %u res: %d\n", s21_a, s21_b, s21_res);
  printf("lib first: %u second: %u res: %d\n\n", lib_a, lib_b, lib_res);
  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(lib_a, s21_a);
  ck_assert_int_eq(lib_b, s21_b);
}
END_TEST

START_TEST(test_sscanf_long_unsigned) {
  long unsigned s21_a = 0;
  int s21_res = 0;

  long unsigned lib_a = 0;
  int lib_res = 0;

  lib_res = sscanf("4294967295", "%lu", &lib_a);
  s21_res = s21_sscanf("4294967295", "%lu", &s21_a);

  printf("s21 first: %lu res: %d\n", s21_a, s21_res);
  printf("lib first: %lu res: %d\n\n", lib_a, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(lib_a, s21_a);
}
END_TEST

START_TEST(test_sscanf_overflow_long_unsigned) {
  long unsigned s21_a = 0;
  int s21_res = 0;

  long unsigned lib_a = 0;
  int lib_res = 0;

  lib_res = sscanf("59949672955", "%lu", &lib_a);
  s21_res = s21_sscanf("59949672955", "%lu", &s21_a);

  printf("s21 first: %lu res: %d\n", s21_a, s21_res);
  printf("lib first: %lu res: %d\n\n", lib_a, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(lib_a, s21_a);
}
END_TEST

START_TEST(test_sscanf_short_unsigned) {
  short unsigned s21_a = 0;
  int s21_res = 0;

  short unsigned lib_a = 0;
  int lib_res = 0;

  lib_res = sscanf("65535", "%hu", &lib_a);
  s21_res = s21_sscanf("65535", "%hu", &s21_a);

  printf("s21 first: %hu res: %d\n", s21_a, s21_res);
  printf("lib first: %hu res: %d\n\n", lib_a, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(lib_a, s21_a);
}
END_TEST

START_TEST(test_sscanf_overflow_short_unsigned) {
  short unsigned s21_a = 0;
  int s21_res = 0;

  short unsigned lib_a = 0;
  int lib_res = 0;

  lib_res = sscanf("95536555", "%hu", &lib_a);
  s21_res = s21_sscanf("95536555", "%hu", &s21_a);

  printf("s21 first: %hu res: %d\n", s21_a, s21_res);
  printf("lib first: %hu res: %d\n\n", lib_a, lib_res);

  ck_assert_int_eq(lib_res, s21_res);
  ck_assert_uint_eq(lib_a, s21_a);
}
END_TEST

START_TEST(test_sscanf_star_problematic) {
  int s21_res1 = 0;
  int s21_res_res = 0;

  int lib_res1 = 0;
  int lib_res_res = 0;

  lib_res_res =
      sscanf("int: 123, float: -123.0, char: @, unsigned: 0 %, string: cringe",
             "int: %*d, float: %*f, char: %*c, unsigned: %*u %%, string: %n",
             &s21_res1);
  s21_res_res = s21_sscanf(
      "int: 123, float: -123.0, char: @, unsigned: 0 %, string: cringe",
      "int: %*d, float: %*f, char: %*c, unsigned: %*u %%, string: %n",
      &lib_res1);

  ck_assert_int_eq(lib_res_res, s21_res_res);
  ck_assert_int_eq(lib_res1, s21_res1);
}
END_TEST

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

Suite* make_sscanf_suite() {
  Suite* sscanf_suite = suite_create("sscanf");
  TCase* tc_core;
  TCase* tc_linux_only;
  TCase* tc_problem;

  tc_core = tcase_create("Core");
  tc_linux_only = tcase_create("linux_only");
  tc_problem = tcase_create("scanf");

  tcase_add_test(tc_core, test_sscanf_simple_char);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p1);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p2);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p3);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p4);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p5);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p6);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p7);
  tcase_add_test(tc_core, test_sscanf_possible_minus_one_p8);

  tcase_add_test(tc_core, test_sscanf_i_p1);
  tcase_add_test(tc_core, test_sscanf_i_p2);
  tcase_add_test(tc_core, test_sscanf_i_p3);
  tcase_add_test(tc_core, test_sscanf_i_p4);
  tcase_add_test(tc_core, test_sscanf_i_p5);
  tcase_add_test(tc_core, test_sscanf_i_p6);
  tcase_add_test(tc_core, test_sscanf_i_p7);
  tcase_add_test(tc_core, test_sscanf_i_p8);
  tcase_add_test(tc_core, test_sscanf_width_p1);
  tcase_add_test(tc_core, test_sscanf_width_p2);
  tcase_add_test(tc_core, test_sscanf_width_p3);

  tcase_add_test(tc_core, test_sscanf_d);

  tcase_add_test(tc_linux_only, test_sscanf_width_p2_linux_only);
  tcase_add_test(tc_linux_only, test_sscanf_width_p2_1_linux_only);
  tcase_add_test(tc_linux_only, test_sscanf_width_p3_linux_only);

  tcase_add_test(tc_core, test_sscanf_long_i);
  tcase_add_test(tc_core, test_sscanf_long_i_p2);
  tcase_add_test(tc_core, test_sscanf_overflow_long_i);

  tcase_add_test(tc_core, test_sscanf_owerflow_short_negative_valua_spec_i);
  tcase_add_test(tc_core, test_sscanf_short_i);
  tcase_add_test(tc_core, test_sscanf_overflow_short_i);
  tcase_add_test(tc_core, test_sscanf_overflow_long_i);
  tcase_add_test(tc_core, test_sscanf_overflow_spec_i);

  tcase_add_test(tc_core, test_sscanf_octal_problematic);
  tcase_add_test(tc_core, test_sscanf_hex_problematic);

  tcase_add_test(tc_core, test_sscanf_octal);
  tcase_add_test(tc_core, test_sscanf_long_octal);
  tcase_add_test(tc_core, test_sscanf_overflow_long_octal);
  tcase_add_test(tc_core, test_sscanf_short_octal);
  tcase_add_test(tc_core, test_sscanf_overflow_short_octal);

  tcase_add_test(tc_core, test_sscanf_hex);
  tcase_add_test(tc_core, test_sscanf_long_hex);
  tcase_add_test(tc_core, test_sscanf_overflow_long_hex);
  tcase_add_test(tc_problem, test_sscanf_short_hex);
  tcase_add_test(tc_core, test_sscanf_overflow_short_hex);

  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_float_2);
  tcase_add_test(tc_core, test_sscanf_float_3);
  tcase_add_test(tc_core, test_sscanf_long_float);
  tcase_add_test(tc_core, test_sscanf_long_long_float);
  tcase_add_test(tc_core, test_sscanf_overflow_long_long_float);

  tcase_add_test(tc_core, test_sscanf_unsigned);
  tcase_add_test(tc_core, test_sscanf_long_unsigned);
  tcase_add_test(tc_core, test_sscanf_overflow_long_unsigned);
  tcase_add_test(tc_core, test_sscanf_short_unsigned);
  tcase_add_test(tc_core, test_sscanf_overflow_short_unsigned);

  tcase_add_test(tc_core, test_sscanf_star_problematic);

  tcase_add_test(tc_core, test_sscanf_int);
  tcase_add_test(tc_core, test_sscanf_int_2);
  tcase_add_test(tc_core, test_sscanf_int_3);

  // tcase_add_test(tc_core, test_sscanf_unsigned);
  // tcase_add_test(tc_problem, test_sscanf_star);
  // tcase_add_test(tc_core, test_sscanf_non_valid_string);

  suite_add_tcase(sscanf_suite, tc_core);
  suite_add_tcase(sscanf_suite, tc_problem);
#if defined(__linux__)
  suite_add_tcase(sscanf_suite, tc_linux_only);
#endif

  return sscanf_suite;
}

// START_TEST(test_sscanf_non_valid_string) {
//   char* input_string = "  \t   \n   \r   ";
//   char* format_string = "Unsigned 1: %u, unsigned 2: %u";

//   unsigned s21_res1 = 0;
//   unsigned s21_res2 = 0;
//   int s21_res_res = 0;

//   unsigned lib_res1 = 0;
//   unsigned lib_res2 = 0;
//   int lib_res_res = 0;

//   lib_res_res = sscanf(input_string, format_string, &lib_res1, &lib_res2);
//   s21_res_res = s21_sscanf(input_string, format_string, &s21_res1,
//   &s21_res2);

//   ck_assert_int_eq(lib_res_res, s21_res_res);
//   ck_assert_int_eq(lib_res1, s21_res1);
//   ck_assert_int_eq(lib_res2, s21_res2);
// }
// END_TEST
