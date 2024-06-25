#include "s21_sscanf.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// Функция для считывания символа из буфера
int read_char(const char **str, char *c, int *cnt) {
  int result = 0;

  if (**str != '\0') {
    *c = **str;
    (*str)++;
    (*cnt)++;
    result = 1;
  }

  return result;
}

// Функция для считывания строки из буфера
int read_string(const char **str, char *s, int *cnt) {
  while (**str != ' ' && **str != '\t' && **str != '\n' && **str != '\0') {
    *s = **str;
    (*str)++;
    s++;
    (*cnt)++;
  }
  *s = '\0';

  return 1;
}

// Функция для считывания целого числа из буфера
int read_int(const char **str, int *d, int *cnt) {
  int sign = 1;
  int num = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    (*cnt)++;
  }

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    (*cnt)++;
  }
  *d = sign * num;

  return 1;
}

// Функция для считывания целого беззнакового числа из буфера
int read_unsigned_int(const char **str, unsigned int *u, int *cnt) {
  unsigned int num = 0;

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    (*cnt)++;
  }
  *u = num;

  return 1;
}

// Функция для считывания числа с плавающей точкой из буфера
int read_float(const char **str, float *f, int *cnt) {
  int sign = 1;
  int int_part = 0;
  float frac_part = 0.0;
  int frac_div = 1;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    (*cnt)++;
  }

  while (**str >= '0' && **str <= '9') {
    int_part = int_part * 10 + (**str - '0');
    (*str)++;
    (*cnt)++;
  }

  if (**str == '.') {
    (*str)++;
    (*cnt)++;
    while (**str >= '0' && **str <= '9') {
      frac_part = frac_part * 10 + (**str - '0');
      frac_div *= 10;
      (*str)++;
      (*cnt)++;
    }
  }
  *f = sign * (int_part + frac_part / frac_div);

  return 1;
}

// Функция для считывания беззн. целого 16-го числа из буфера
int read_hex(const char **str, unsigned int *x, int *cnt) {
  unsigned int num = 0;
  while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
         (**str >= 'A' && **str <= 'F')) {
    if (**str >= '0' && **str <= '9') {
      num = num * 16 + (**str - '0');
    } else if (**str >= 'a' && **str <= 'f') {
      num = num * 16 + (**str - 'a' + 10);
    } else {
      num = num * 16 + (**str - 'A' + 10);
    }
    (*str)++;
    (*cnt)++;
  }
  *x = num;

  return 1;
}

// Функция для считывания значений из буфера по формату
int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  int result = 0;  // Количество считанных спецификаторов
  int count = 0;  // Количество считанных символов до %n

  // Чек, что format и str не пустые
  if (!str || !format) {
    result = -1;
  } else {
    while (*format != '\0') {
      if (*format == '%') {
        format++;
        switch (*format) {
          case 'c':
            char *c = va_arg(args, char *);
            if (read_char(&str, c, &count)) {
              format++;
              result++;
            }
            break;
          case 's':
            char *s = va_arg(args, char *);
            if (read_string(&str, s, &count)) {
              format++;
              result++;
            }
            break;
          case 'd':
          case 'i':
            int *d = va_arg(args, int *);
            if (read_int(&str, d, &count)) {
              format++;
              result++;
            }
            break;
          case 'f':
            float *f = va_arg(args, float *);
            if (read_float(&str, f, &count)) {
              format++;
              result++;
            }
            break;
          case 'u':
            unsigned int *u = va_arg(args, unsigned int *);
            if (read_unsigned_int(&str, u, &count)) {
              format++;
              result++;
            }
            break;
          case 'x':
          case 'X':
            unsigned int *x = va_arg(args, unsigned int *);
            if (read_hex(&str, x, &count)) {
              format++;
              result++;
            }
            break;
          case '%':
            format++;
            break;
          default:
            break;
        }
      } else {
        format++;
        str++;
      }
    }
  }
  va_end(args);

  return result;
}
