#include "s21_string.h"
#include "stdio.h"

s21_size_t s21_strlen(const char* str) {
  s21_size_t res = 0;
  int err_flag = 0;
  if (str == S21_NULL) {
    err_flag = 1;
    fprintf(stderr,
            "error: null argument where non-null required (argument 1)\n");
  } else {
    const char* ptr = str;
    while (*ptr != '\0') {
      ++ptr;
    }
    res = ptr - str;
  }
  return err_flag == 0 ? res : (s21_size_t)-1;
}