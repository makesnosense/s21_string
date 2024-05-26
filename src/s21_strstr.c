#include "s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  s21_size_t len1 = s21_strlen(haystack);
  s21_size_t len2 = s21_strlen(needle);
  char* result = S21_NULL;

  if (len2 == 0) {
    result = (char*)haystack;
  } else if (len2 <= len1) {
    for (s21_size_t i = 0; i <= len1 - len2; i++) {
      if (s21_strncmp(haystack + i, needle, len2) == 0) {
        result = (char*)(haystack + i);
        break;
      }
    }
  }
  return result;
}