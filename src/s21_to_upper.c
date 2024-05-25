#include "s21_string.h"

#include <stdlib.h>

void *s21_to_upper(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *result = (char *)calloc(len + 1, sizeof(char));
  if (result != S21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        result[i] = str[i] - 32;
      } else {
        result[i] = str[i];
      }
    }
  }
  return result;
}