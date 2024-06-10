#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  const char* result = S21_NULL;
  if (str != S21_NULL) {
    const char* p = str;
    while (*p) p++;
    while (p >= str && result == S21_NULL) {
      if (*p == (char)c) {
        result = p;
      }
      p--;
    }
  }
  return (char*)result;
}
