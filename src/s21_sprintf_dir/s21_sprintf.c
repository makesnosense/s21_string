#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

#define F_PRESICION 6

typedef struct Options {
  int plus;    // Флаг '+'
  int minus;   // Флаг '-'
  int space;   // Флаг ' '
  int width;   // Ширина *.
  int prec;    // Точность .*
  int prec_i;  // Параметр для целой части float чисел
} Options;

// Функция для преобразования целого числа в строку
void int_to_str(char* str, s21_size_t* str_len, long long num, Options opts,
                int prec) {
  long long temp_num = num;  // Для подсчета длины строки
  s21_size_t len_num = 0;    // Длина строки
  int is_negative = 0;       // Является ли отр. числом

  // Если число num отрицательное
  if (num < 0) {
    is_negative = 1;
    str[(*str_len)++] = '-';
    num = -num;
  } else if (opts.plus && prec == -1) {
    str[(*str_len)++] = '+';
  }

  // Считаем длину числа
  while (temp_num != 0) {
    len_num++;
    temp_num /= 10;
  }

  // Преобразуем число в строку
  int i = 0;
  if (len_num == 0) {
    str[(*str_len)++] = '0';
    i++;
  } else {
    while (len_num != 0) {
      long long temp = pow(10, --len_num);
      str[(*str_len)++] = (num / temp) + '0';
      num %= temp;
      i++;
    }
  }
  while (i < prec && prec != -1) {
    str[(*str_len)++] = '0';
    i++;
  }
  str[*str_len + (is_negative || opts.plus)] = '\0';
}

void float_to_str(char* str, s21_size_t* str_len, double num, Options opts) {
  // Округляем дробную часть до нужного числа
  double multiplier = pow(10.0, opts.prec);
  num = round(num * multiplier) / multiplier;

  // Отделяем целую и дробную часть
  long long whole = (long long)num;
  double fract = (num - whole) * multiplier;

  // Записываем все в строку
  int_to_str(str, str_len, whole, opts, opts.prec_i);
  str[(*str_len)++] = '.';
  int_to_str(str, str_len, fract, opts, opts.prec);
}

int is_flag(char* flags, char ch) {
  char* res = s21_strchr(flags, ch);
  return res == S21_NULL ? 0 : 1;
}

int s21_sprintf(char* str, const char* format, ...) {
  int res = 0;  // Результат работы функции
  char* flags = "+- ";
  Options opts = {0};
  opts.prec = F_PRESICION;
  opts.prec_i = -1;

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  s21_size_t str_len = 0;  // Индекс буферной строки + её длина
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (is_flag(flags, *format)) {
        switch (*format) {
          case '+':
            printf("FL: %c\n", *format);
            opts.plus = 1;
            format++;
            break;
          case '-':
            printf("FL: %c\n", *format);
            opts.minus = 1;
            format++;
            break;
          case ' ':
            printf("FL: %c\n", *format);
            opts.space = 1;
            format++;
            break;
        }
      }
      switch (*format) {
        case 'c': {  // Если c (char)
          char c = va_arg(args, int);
          str[str_len++] = c;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
          int d = va_arg(args, int);
          int_to_str(str, &str_len, d, opts, opts.prec_i);
          break;
        }
        case 'f': {  // Если f (float)
          float f = va_arg(args, double);
          float_to_str(str, &str_len, f, opts);
          break;
        }
        case 's': {
          char* s = va_arg(args, char*);
          s21_strcpy(str + str_len, s);
          str_len += s21_strlen(s);
          break;
        }
        case 'u': {
          unsigned u = va_arg(args, unsigned);
          int_to_str(str, &str_len, u, opts, opts.prec_i);
          break;
        }
        default:
          break;
      }
    } else {
      str[str_len++] = *format;
    }
    opts.plus = 0;
    opts.minus = 0;
    opts.space = 0;
    format++;
  }
  str[str_len] = '\0';
  va_end(args);

  return res;
}
