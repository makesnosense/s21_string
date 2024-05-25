#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  const char* p1 = str1;
  const char* p2;
  s21_size_t result = 0;

  int match_found = 0;

  while (*p1 && !match_found) {
    for (p2 = str2; *p2 && !match_found; p2++) {
      if (*p1 == *p2) {
        match_found = 1;
      }
    }
    if (!match_found) {
      p1++;
    }
  }

  result = p1 - str1;

  return result;
}