#include "s21_string.h"

// void* s21_memchr(const void* str, int c, s21_size_t n) {
//   unsigned char* ptr = (unsigned char*)str;
//   if (n > sizeof(ptr)) {
//     return S21_NULL;
//   }
//   for (s21_size_t i = 0; i < n; ++i) {
//     if (ptr[i] == c) {
//       return &ptr[i];
//     }
//   }
//   return S21_NULL;
// }

void* s21_memchr(const void* str, int c, s21_size_t n) {
  unsigned char* ptr = (unsigned char*)str;
  void* result = S21_NULL;
  for (s21_size_t i = 0; i < n; ++i) {
    if (ptr[i] == (unsigned char)c) {  //
      result = &ptr[i];
      break;  //
    }
  }

  return result;
}