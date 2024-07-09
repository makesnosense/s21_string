#include <stdlib.h>

#include "s21_string.h"

// void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
//   s21_size_t len1 = s21_strlen(src);
//   s21_size_t len2 = s21_strlen(str);
//   int flag = 0;
//   char* result = S21_NULL;

//   if ((int)start_index < 0 || start_index > len1) {
//     flag = 1;
//   }
//   if (!flag) {
//     result = (char*)calloc(len1 + len2 + 1, sizeof(char));
//     s21_size_t src_i = 0, str_i = 0, res_i = 0;

//     while (res_i < len1 + len2) {
//       if (res_i >= start_index && res_i < start_index + len2) {
//         result[res_i] = str[str_i];
//         str_i++;
//       } else {
//         result[res_i] = src[src_i];
//         src_i++;
//       }
//       res_i++;
//     }
//     result[res_i] = '\0';
//   }
//   return result;
// }

#include "s21_string.h"
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *buffer = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_length = s21_strlen(src);
    s21_size_t str_length = s21_strlen(str);
    s21_size_t memory_length = src_length + str_length + 1;
    if (start_index <= src_length) {
      buffer = calloc(memory_length, sizeof(char));
      if (buffer != S21_NULL) {
        for (s21_size_t i = 0; i < start_index; i++) {
          buffer[i] = src[i];
        }
        for (s21_size_t i = 0; i < str_length; i++) {
          buffer[i + start_index] = str[i];
        }
        for (s21_size_t i = 0; i < src_length - start_index; i++) {
          buffer[i + start_index + str_length] = src[i + start_index];
        }
        buffer[memory_length - 1] = '\0';
      }
    }
  }
  return buffer;
}