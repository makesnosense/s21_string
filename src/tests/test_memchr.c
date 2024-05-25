#include "run_tests.h"

START_TEST(hello_world_test) {
  unsigned char buffer[] = "Hello, World";

  int c = 'o';
  s21_size_t n = sizeof(buffer);

  void* s21_result = s21_memchr(buffer, c, n);
  void* lib_result = memchr(buffer, c, n);

  ck_assert_pstr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_find_in_middle) {
  char buffer[] = "Hello, how are you?";
  int c = 'h';
  s21_size_t n = sizeof(buffer);

  void* s21_result = s21_memchr(buffer, c, n);
  void* lib_result = memchr(buffer, c, n);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_find_at_end) {
  char buffer[] = "The end is near!";
  int c = '!';
  s21_size_t n = sizeof(buffer);

  void* s21_result = s21_memchr(buffer, c, n);
  void* lib_result = memchr(buffer, c, n);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_character_not_found) {
  char buffer[] = "No such character";
  int c = 'z';
  s21_size_t n = sizeof(buffer);

  void* s21_result = s21_memchr(buffer, c, n);
  void* lib_result = memchr(buffer, c, n);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_zero_length) {
  char buffer[] = "Empty search";
  int c = 'E';
  s21_size_t n = 0;

  void* s21_result = s21_memchr(buffer, c, n);
  void* lib_result = memchr(buffer, c, n);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

START_TEST(test_large_n_no_char) {
  char buffer[] = "Short buffer";
  int c = 'x';
  s21_size_t n = sizeof(buffer) + 10;

  void* s21_result = s21_memchr(buffer, c, n);
  void* lib_result = memchr(buffer, c, n);

  ck_assert_ptr_eq(s21_result, lib_result);
}
END_TEST

Suite* make_memchr_suite() {
  Suite* memchr_suite = suite_create("memchr");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, hello_world_test);
  tcase_add_test(tc_core, test_find_in_middle);
  tcase_add_test(tc_core, test_find_at_end);
  tcase_add_test(tc_core, test_character_not_found);
  tcase_add_test(tc_core, test_zero_length);
  tcase_add_test(tc_core, test_large_n_no_char);

  suite_add_tcase(memchr_suite, tc_core);
  return memchr_suite;
}
