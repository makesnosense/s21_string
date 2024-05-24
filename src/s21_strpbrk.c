#include "s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  int flag = 0;
  while (*str1 != '\0') {
    for (const char* ptr = str2; *ptr != '\0'; ptr++) {
      if (*str1 == *ptr) {
        flag++;
        break;
      }
    }
    if(flag == 1){
      break;
    }
    str1++;
  }
  return (flag == 0) ? S21_NULL : (char*)str1;
}