#include "run_tests.h"

int main() {
  int number_failed;
  Suite* strlen_suite;
  Suite* strcat_suite;

  SRunner* suite_runner;

  strlen_suite = make_strlen_suite();
  strcat_suite = make_strcat_suite();

  suite_runner = srunner_create(strlen_suite);
  srunner_add_suite(suite_runner, strcat_suite);

  srunner_run_all(suite_runner, CK_VERBOSE);

  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}