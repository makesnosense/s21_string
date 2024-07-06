#include "run_tests.h"

START_TEST(test_memcpy_empty) {
  char src[1] = {0};
  char dest[1];

  void* result = s21_memcpy(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_memcpy_content) {
  char src[] = "Hello, world!";
  char dest[20];
  void* result = s21_memcpy(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
  ck_assert_ptr_eq(result, dest);
}
END_TEST

Suite* make_memcpy_suite() {
  Suite* memcpy_suite = suite_create("memcpy");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memcpy_empty);
  tcase_add_test(tc_core, test_memcpy_content);

  suite_add_tcase(memcpy_suite, tc_core);
  return memcpy_suite;
}
