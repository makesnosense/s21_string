#include "run_tests.h"

START_TEST(memcmp_first) {
  unsigned char block1[] = {1, 2, 3};
  unsigned char block2[] = {1, 2, 3};
  //   unsigned char block3[] = {1, 2, 4};

  int s21_result = s21_memcmp(block1, block2, sizeof(block1));
  //   int result2 = s21_memcmp(block1, block3, sizeof(block1));

  int lib_result = memcmp(block1, block2, sizeof(block1));
  //   result2 = memcmp(block1, block3, sizeof(block1));

  ck_assert_int_eq(s21_result, lib_result);
}
END_TEST

Suite* make_memcmp_suite() {
  Suite* memcmp_suite = suite_create("memcmp");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, memcmp_first);

  suite_add_tcase(memcmp_suite, tc_core);
  return memcmp_suite;
}
