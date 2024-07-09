#include <stdlib.h>

#include "s21_string.h"

// void* s21_trim(const char* src, const char* trim_chars) {
//   char* result = S21_NULL;
//   if (src) {
//     if (!trim_chars) {
//       trim_chars = " ";
//     }
//     char* ptr_str = (char*)src;
//     char* end_str = (char*)src + s21_strlen(src);
//     for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++) {
//     }
//     for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
//          end_str--) {
//     }
//     result = (char*)calloc(end_str - ptr_str + 1, sizeof(char));

//     s21_strncpy(result, ptr_str, end_str - ptr_str);
//     *(result + (end_str - ptr_str)) = '\0';
//   }
//   return result;
// }

void *x_calloc(size_t nmemb, size_t size) {
  void *pointer = S21_NULL;
  pointer = calloc(nmemb, size);
  if (pointer == S21_NULL) {
    exit(1);
  }
  return pointer;
}

s21_size_t s21_trim_strspn_reverse(const char *str1, const char *str2);

void *s21_trim(const char *src, const char *trim_char) {
  char *buffer = S21_NULL;

  if (src != S21_NULL) {
    s21_size_t length = s21_strlen(src);

    if (trim_char == S21_NULL) {
      trim_char = " ";
    }

    s21_size_t first_trim_num = s21_strspn(src, trim_char);
    s21_size_t last_trim_num = s21_trim_strspn_reverse(src, trim_char);

    if (length != first_trim_num) {
      buffer =
          x_calloc(length - first_trim_num - last_trim_num + 1, sizeof(char));
    } else {
      buffer = x_calloc(1, sizeof(char));
    }

    if (buffer != S21_NULL) {
      if (length != first_trim_num) {
        for (s21_size_t i = 0; i < length - first_trim_num - last_trim_num;
             i++) {
          buffer[i] = src[i + first_trim_num];
        }

        buffer[length - first_trim_num - last_trim_num] = '\0';
      } else {
        buffer[0] = '\0';
      }
    }
  }

  return buffer;
}

s21_size_t s21_trim_strspn_reverse(const char *str1, const char *str2) {
  s21_size_t str1len = s21_strlen(str1);
  s21_size_t str2len = s21_strlen(str2);
  int is_continue = 0;
  int res = 0;

  for (int i = (int)str1len - 1; i > -1 && is_continue == 0; i--) {
    int inner_res = 0;

    for (s21_size_t j = 0; j < str2len && inner_res == 0; j++) {
      if (str1[i] == str2[j]) {
        inner_res++;
      }
    }

    if (inner_res == 0) {
      is_continue++;
      res--;
    }

    res++;
  }

  return res;
}
