#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

// Функция для преобразования целого числа в строку
char* int_to_str(int num) {
  char* str = malloc(20);  // Для типа int хватит
  int is_negative = 0;     // Является ли отр. числом

  // Если число num отрицательное
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  // Считаем длину числа
  int len = 0;
  int temp_num = num;
  while (temp_num != 0) {
    len++;
    temp_num /= 10;
  }

  // Преобразуем число в строку
  if (len == 0) {
    s21_strcpy(str, "0");
  } else {
    int i = len - 1;
    while (i >= 0) {
      str[i] = (num % 10) + '0';
      num /= 10;
      i--;
    }

    // Если число отрицательное, добавляем '-'
    if (is_negative) {
      s21_memmove(str + 1, str, len);
      str[0] = '-';
    }
    str[is_negative ? len + 1 : len] = '\0';
  }

  return str;
}

int s21_sprintf(char* str, const char* format, ...) {
  int res = 0;  // Результат работы функции

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  int str_index = 0;  // Индекс буферной строки
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'c': {  // Если char
          char c = va_arg(args, int);
          str[str_index++] = c;
          break;
        }
        case 'd': {  // Если int
          int d = va_arg(args, int);
          char* d_str = int_to_str(d);

          s21_strcpy(str + str_index, d_str);
          str_index += s21_strlen(d_str);

          if (d_str) free(d_str);
          break;
        }
        default:
          break;
      }
    } else {
      str[str_index++] = *format;
    }
    format++;
  }
  str[str_index] = '\0';
  va_end(args);

  return res;
}
