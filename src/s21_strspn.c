#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len1 = s21_strlen(str1);
  s21_size_t len2 = s21_strlen(str2);
  s21_size_t result = 0;
  int found = 1;

  for (s21_size_t i = 0; i < len1 && found; i++) {
    found = 0;
    for (s21_size_t j = 0; j < len2 && !found; j++) {
      if (str1[i] == str2[j]) {
        found = 1;
      }
    }
    if (found) {
      result++;
    }
  }
  return result;
}
