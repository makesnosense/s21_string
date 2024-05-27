#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* saveptr = S21_NULL;
  char* token = S21_NULL;

  if (str == S21_NULL) {
    str = saveptr;
  }

  while (*str && s21_strchr(delim, *str)) {
    str++;
  }
  if (*str) {
    token = str;
    while (*str && !s21_strchr(delim, *str)) {
      str++;
    }

    if (*str) {
      *str = '\0';
      saveptr = str + 1;
    } else {
      saveptr = str;
    }
  }
  return token;
}