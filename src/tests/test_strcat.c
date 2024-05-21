// void test_strcat() {
//     printf("-------------------s21_strcat()-------------------\n");
//     char str1[10] = "Hel";
//     char *str2 = "lo";
//     s21_strcat(str1, str2);
//     printf("%s\n", str1);
//     printf("---------------------strcat()---------------------\n");
//     char str3[10] = "Hel";
//     char *str4 = "lo";
//     s21_strcat(str3, str4);
//     printf("%s\n", str3);
//     printf("--------------------------------------------------\n");
//     printf("\n");
//     printf("\n");
// }

#include "run_tests.h"

START_TEST(first_test) {
  char str1[10] = "Hel";
  char* str2 = "lo";

  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

// START_TEST(second_test) {

// s21_size_t result = s21_strcat("posh");
// ck_assert_int_eq(result, 4);

// }
// END_TEST

Suite* make_strcat_suite() {
  Suite* cat_suite = suite_create("strcat");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, first_test);
  // tcase_add_test(tc_core, second_test);

  suite_add_tcase(cat_suite, tc_core);
  return cat_suite;
}