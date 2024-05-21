#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *pntr1 = dest;
  const unsigned char *pntr2 = src;
  unsigned char temp_arr[n];
  for (s21_size_t i = 0; i < n; i++) {
    temp_arr[i] = pntr2[i];
  }
  for (s21_size_t i = 0; i < n; i++) {
    pntr1[i] = temp_arr[i];
  }
  return dest;
}