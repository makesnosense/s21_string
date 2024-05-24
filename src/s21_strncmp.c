#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int result = 0;
  s21_size_t i = 0;
  while (i < n) {
    unsigned char u1 = (unsigned char)str1[i];
    unsigned char u2 = (unsigned char)str2[i];
    if (u1 == '\0' || u2 == '\0' || u1 != u2) {
      result = (int)u1 - u2;
      break;
    }
    i++;
  }
  return result;
}