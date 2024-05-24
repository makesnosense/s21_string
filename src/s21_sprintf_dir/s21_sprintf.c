#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

// Функция для преобразования целого числа в строку
char* int_to_str(long long int num) {
  long long int temp_num = num;  // Для подсчета длины строки
  s21_size_t len = 0;            // Длина строки
  int is_negative = 0;           // Является ли отр. числом

  // Если число num отрицательное
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  // Считаем длину числа
  while (temp_num != 0) {
    len++;
    temp_num /= 10;
  }

  // Выделяем память под строку, учитывая знак минуса
  // +1 для нулевого символа конца строки
  int fixed_len = len == 0 ? 1 : len;
  char* str = malloc(fixed_len + 1 + is_negative);

  // Преобразуем число в строку
  if (len == 0) {
    s21_strcpy(str, "0");
  } else {
    s21_size_t i = len - 1;
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
    str[len + is_negative] = '\0';
  }

  return str;
}

int s21_sprintf(char* str, const char* format, ...) {
  int res = 0;  // Результат работы функции

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  s21_size_t str_index = 0;  // Индекс буферной строки
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'c': {  // Если char
          char c = va_arg(args, int);
          str[str_index++] = c;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
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
