#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    const char* ptr = str;
    while (*ptr != '\0' && *ptr != c) {
      ptr++;
    }
    if (*ptr == c) {
      result = (char*)ptr;
    }
  }
  return result;
}