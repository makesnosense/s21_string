#include "s21_string.h"

void* s21_memmove(void* dest, const void* src, s21_size_t n) {
  unsigned char* pntr1 = dest;
  const unsigned char* pntr2 = src;

  if (pntr1 < pntr2) {
    for (s21_size_t i = 0; i < n; i++) {
      pntr1[i] = pntr2[i];
    }
  } else {
    for (s21_size_t i = n; i != 0; i--) {
      pntr1[i - 1] = pntr2[i - 1];
    }
  }

  return dest;
}
