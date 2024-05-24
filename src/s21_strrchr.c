#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  int flag = 0;
  const char* p = str + s21_strlen(str) - 1;
  while (p >= str) {
    if (*p == c) {
      flag++;
      break;
    }
    p--;
  }

  return (flag == 0) ? S21_NULL : (char*)p;
}