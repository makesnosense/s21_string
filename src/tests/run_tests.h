#ifndef _RUN_TESTS_H_
#define _RUN_TESTS_H_

#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

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

#endif