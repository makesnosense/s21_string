#include "s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;
  while (*str1 != '\0' && result == S21_NULL) {
    for (const char* ptr = str2; *ptr != '\0'; ptr++) {
      if (*str1 == *ptr) {
        result = (char*)str1;
        break;
      }
    }
    if (result == S21_NULL) {
      str1++;
    }
  }
  return result;
}