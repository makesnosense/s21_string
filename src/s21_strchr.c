#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    const char* ptr = str;
    while (*ptr != '\0' || (c == '\0' && *ptr == '\0')) {
      if (*ptr == c) {
        result = (char*)ptr;
        break;
      }
      ptr++;
    }
  }
  return result;
}