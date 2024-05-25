#include "run_tests.h"

int main() {
  int number_failed;
  Suite* strlen_suite;
  Suite* strcat_suite;
  Suite* memchr_suite;
  Suite* memcmp_suite;
  Suite* strcpy_suite;
  Suite* memcpy_suite;
  Suite* memmove_suite;
  Suite* memset_suite;
  Suite* strncat_suite;
  Suite* strchr_suite;
  Suite* strncmp_suite;
  Suite* strcmp_suite;
  Suite* strncpy_suite;
  Suite* strspn_suite;
  Suite* strcspn_suite;
  Suite* strrchr_suite;

  SRunner* suite_runner;

  strlen_suite = make_strlen_suite();
  strcat_suite = make_strcat_suite();
  memchr_suite = make_memchr_suite();
  memcmp_suite = make_memcmp_suite();
  strcpy_suite = make_strcpy_suite();
  memcpy_suite = make_memcpy_suite();
  memmove_suite = make_memmove_suite();
  memset_suite = make_memset_suite();
  strncat_suite = make_strncat_suite();
  strchr_suite = make_strchr_suite();
  strncmp_suite = make_strncmp_suite();
  strcmp_suite = make_strcmp_suite();
  strncpy_suite = make_strncpy_suite();
  strspn_suite = make_strspn_suite();
  strcspn_suite = make_strcspn_suite();
  strrchr_suite = make_strrchr_suite();

  suite_runner = srunner_create(strlen_suite);

  srunner_add_suite(suite_runner, strcat_suite);
  srunner_add_suite(suite_runner, memchr_suite);
  srunner_add_suite(suite_runner, memcmp_suite);
  srunner_add_suite(suite_runner, strcpy_suite);
  srunner_add_suite(suite_runner, memcpy_suite);
  srunner_add_suite(suite_runner, memmove_suite);
  srunner_add_suite(suite_runner, memset_suite);
  srunner_add_suite(suite_runner, strncat_suite);
  srunner_add_suite(suite_runner, strchr_suite);
  srunner_add_suite(suite_runner, strncmp_suite);
  srunner_add_suite(suite_runner, strcmp_suite);
  srunner_add_suite(suite_runner, strncpy_suite);
  srunner_add_suite(suite_runner, strspn_suite);
  srunner_add_suite(suite_runner, strcspn_suite);
  srunner_add_suite(suite_runner, strrchr_suite);

  srunner_run_all(suite_runner, CK_VERBOSE);

  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}