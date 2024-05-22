#include "run_tests.h"

START_TEST(test_memmove_empty) {
  char src[1] = {0};
  char dest[1];

  void* result = s21_memmove(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_memmove_content) {
  char src[] = "Hello, world!";
  char dest[20];

  void* result = s21_memmove(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, src, sizeof(src));
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_memmove_overlap_forward) {
  char src[] = "Overlap example";
  char* dest = src + 2;

  void* result = s21_memmove(dest, src, 10);
  ck_assert_mem_eq(dest, "Overlap ex", 10);
  ck_assert_ptr_eq(result, dest);
}
END_TEST

// START_TEST(test_memmove_overlap_backward) {
//   char src[] = "Another overlap example";
//   char* dest = src;

//   void* result = s21_memmove(dest, src + 5, 10);
//   ck_assert_mem_eq(dest, "overlap exa", 10);
//   ck_assert_mem_eq(
//       dest, "overlap exaple",
//       strlen("overlap exaple"));
//   ck_assert_ptr_eq(result, dest);
// }
// END_TEST

Suite* make_memmove_suite() {
  Suite* memmove_suite = suite_create("memmove");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_memmove_empty);
  tcase_add_test(tc_core, test_memmove_content);
  tcase_add_test(tc_core, test_memmove_overlap_forward);
  // tcase_add_test(tc_core, test_memmove_overlap_backward);

  suite_add_tcase(memmove_suite, tc_core);
  return memmove_suite;
}
