#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *pointer = str;
  while (n > 0) {
    n--;
    *pointer++ = (unsigned char)c;
  }
  return str;
}