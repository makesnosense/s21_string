#include "run_tests.h"
#include <stdio.h>
START_TEST(memcmp_first) {
  unsigned char block1[] = {1, 2, 3};
  unsigned char block2[] = {1, 2, 3};

  int s21_result = s21_memcmp(block1, block2, sizeof(block1));

  int lib_result = memcmp(block1, block2, sizeof(block1));

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

START_TEST(memcmp_diff_start) {
  unsigned char block1[] = {4, 2, 3};
  unsigned char block2[] = {1, 2, 3};

  int s21_result = s21_memcmp(block1, block2, sizeof(block1));
  int lib_result = memcmp(block1, block2, sizeof(block1));

  printf("\n%ld\n", sizeof(block1));
  ck_assert_int_eq(s21_result > 0, lib_result > 0);
}
END_TEST

START_TEST(memcmp_diff_middle) {
  unsigned char block1[] = {1, 'a', 3};
  unsigned char block2[] = {1, 'b', 3};

  int s21_result = s21_memcmp(block1, block2, 3);
  int lib_result = memcmp(block1, block2, 3);

  ck_assert_int_eq(s21_result > 0, lib_result > 0);
}
END_TEST

START_TEST(memcmp_diff_end) {
  unsigned char block1[] = {1, 2, 4};
  unsigned char block2[] = {1, 2, 3};

  int s21_result = s21_memcmp(block1, block2, sizeof(block1));
  int lib_result = memcmp(block1, block2, sizeof(block1));

  ck_assert_int_eq(s21_result < 0, lib_result < 0);
}
END_TEST

START_TEST(memcmp_zero_length) {
  unsigned char block1[] = {1, 2, 3};
  unsigned char block2[] = {4, 5, 6};

  int s21_result = s21_memcmp(block1, block2, 0);
  int lib_result = memcmp(block1, block2, 0);

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

Suite* make_memcmp_suite() {
  Suite* memcmp_suite = suite_create("memcmp");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, memcmp_first);
  tcase_add_test(tc_core, memcmp_first);
  tcase_add_test(tc_core, memcmp_diff_start);
  tcase_add_test(tc_core, memcmp_diff_middle);
  tcase_add_test(tc_core, memcmp_diff_end);
  tcase_add_test(tc_core, memcmp_zero_length);

  suite_add_tcase(memcmp_suite, tc_core);
  return memcmp_suite;
}
