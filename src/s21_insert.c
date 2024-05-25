#include "s21_string.h"

#include <stdlib.h>

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t len1 = s21_strlen(src);
  s21_size_t len2 = s21_strlen(str);
  int flag = 0;
  char *result = S21_NULL;

  if ((int)start_index < 0 || start_index > len1) {
    flag = 1;
  }
  if (!flag) {
    result = (char *)calloc(len1 + len2 + 1, sizeof(char));
    s21_size_t src_i = 0, str_i = 0, res_i = 0;

    while (res_i < len1 + len2) {
      if (res_i >= start_index && res_i < start_index + len2) {
        result[res_i] = str[str_i];
        str_i++;
      } else {
        result[res_i] = src[src_i];
        src_i++;
      }
      res_i++;
    }
    result[res_i] = '\0';
  }
  return result;
}