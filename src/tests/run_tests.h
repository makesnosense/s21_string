#ifndef _RUN_TESTS_H_
#define _RUN_TESTS_H_

#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

Suite* make_strlen_suite();
Suite* make_strcat_suite();
Suite* make_memchr_suite();

#endif