#include "run_tests.h"

#include <stdio.h>

int main() {
  int total_number_run = 0;
  int total_number_failed = 0;
  Suite* suites[] = {// make_strlen_suite(),
                     //                  make_strcat_suite(),
                     //                  make_memchr_suite(),
                     //                  make_memcmp_suite(),
                     //                  make_strcpy_suite(),
                     //                  make_memcpy_suite(),
                     //                  make_memmove_suite(),
                     //                  make_memset_suite(),
                     //                  make_strncat_suite(),
                     //                  make_strchr_suite(),
                     //                  make_strncmp_suite(),
                     //                  make_strcmp_suite(),
                     //                  make_strncpy_suite(),
                     //                  make_strspn_suite(),
                     //                  make_strcspn_suite(),
                     //                  make_strrchr_suite(),
                     //                  make_strerror_suite(),
                     //                  make_strpbrk_suite(),
                     //                  make_strstr_suite(),
                     //                  make_strtok_suite(),
                     //                  make_trim_suite(),
                     //                  make_insert_suite(),
                     //                  make_to_lower_suite(),
                     //                  make_to_upper_suite(),
                     //                  make_sprintf_suite(),
                     //                  make_sscanf_suite(),
                     make_external_suite(), NULL};

  for (Suite** current_suite = suites; *current_suite != NULL;
       current_suite++) {
    run_suite(*current_suite, &total_number_run, &total_number_failed);
  }

  printf("Total tests run:\t%d\nTotal tests failed:\t%d\n", total_number_run,
         total_number_failed);
  return (total_number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void run_suite(Suite* current_suite, int* total_number_run,
               int* total_number_failed) {
  SRunner* suite_runner;

  suite_runner = srunner_create(current_suite);
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_run_all(suite_runner, CK_VERBOSE);
  *total_number_run += srunner_ntests_run(suite_runner);
  *total_number_failed += srunner_ntests_failed(suite_runner);

  srunner_free(suite_runner);
}
