#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* saveptr;

  if (!str) {
    str = saveptr;
  } else {
    saveptr = str;
  }

  if (!*str) return S21_NULL;

  char* token = str;
  char* p = token;

  while (*p != '\0') {
    char* q = (char*)delim;
    while (*q != '\0') {
      if (*p == *q) {
        *p = '\0';
        p += 1;
        break;
      }
      q++;
    }
    if (*p == '\0') break;
    p++;
  }

  return token;
}