#include "s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* p = dest;
  while (*p != '\0') {
    p++;
  }
  s21_size_t i = 0;
  while ((i < n) && (*src != '\0')) {
    *p++ = *src++;
    i++;
  }
  *p = '\0';

  return dest;
}
