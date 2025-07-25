#ifndef SRC_TESTS_RUN_TESTS_H_
#define SRC_TESTS_RUN_TESTS_H_

#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

void run_suite(Suite* current_suite, int* total_number_run,
               int* total_number_failed);

Suite* make_strlen_suite();
Suite* make_strcat_suite();
Suite* make_memchr_suite();
Suite* make_memcmp_suite();
Suite* make_strcpy_suite();
Suite* make_memcpy_suite();
Suite* make_memmove_suite();
Suite* make_memset_suite();
Suite* make_strncat_suite();
Suite* make_strchr_suite();
Suite* make_strncmp_suite();
Suite* make_strcmp_suite();
Suite* make_strncpy_suite();
Suite* make_strspn_suite();
Suite* make_strcspn_suite();
Suite* make_strrchr_suite();
Suite* make_strerror_suite();
Suite* make_strpbrk_suite();
Suite* make_strstr_suite();
Suite* make_strtok_suite();
Suite* make_trim_suite();
Suite* make_insert_suite();
Suite* make_to_upper_suite();
Suite* make_to_lower_suite();
Suite* make_sprintf_suite();
Suite* make_sscanf_suite();
Suite* make_external_suite();

#endif  // SRC_TESTS_RUN_TESTS_H_
