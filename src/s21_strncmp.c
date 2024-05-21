#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; ++i) {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
  }
  return 0;
}