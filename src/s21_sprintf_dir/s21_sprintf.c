#include <ctype.h>
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
  int prec_f;  // Считалось ли precision для спецификатора
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
  } else if (opts.space) {
    str[(*str_len)++] = ' ';
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

void div_num(double num, double mul, long long* wh, double* fr) {
  // Округляем дробную часть до нужного числа
  num = round(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

void float_to_str(char* str, s21_size_t* str_len, double num, Options opts) {
  double multiplier;  // Множитель для округления числа
  long long whole;    // Целая часть
  double fract;       // Дробная часть

  // Если считали precision, но она == 0
  if (opts.prec_f && !opts.prec) {
    multiplier = pow(10.0, opts.prec);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(str, str_len, whole, opts, opts.prec_i);

    // Если не считали precision
  } else if (!opts.prec_f) {
    multiplier = pow(10.0, F_PRESICION);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(str, str_len, whole, opts, opts.prec_i);
    str[(*str_len)++] = '.';
    int_to_str(str, str_len, fract, opts, F_PRESICION);

    // Иначе
  } else {
    multiplier = pow(10.0, opts.prec);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(str, str_len, whole, opts, opts.prec_i);
    str[(*str_len)++] = '.';
    int_to_str(str, str_len, fract, opts, opts.prec);
  }
}

int is_flag(char* flags, char ch) {
  char* res = s21_strchr(flags, ch);
  return res == S21_NULL ? 0 : 1;
}

int is_spec(char* specs, char ch) {
  char* res = s21_strchr(specs, ch);
  return res == S21_NULL ? 0 : 1;
}

void parse_flags(char* flags, const char** format, Options* opts) {
  while (is_flag(flags, **format)) {
    switch (**format) {
      case '+':
        opts->plus = 1;
        break;
      case '-':
        opts->minus = 1;
        break;
      case ' ':
        opts->space = 1;
        break;
      default:
        break;
    }
    (*format)++;
  }
}

void parse_width(char* specs, const char** format, Options* opts) {
  int res = 0;
  opts->width = 0;

  while (**format != '.' && !is_spec(specs, **format)) {
    if (isdigit(**format)) {
      opts->width = opts->width * 10 + (**format - '0');
      res++;
    }
    (*format)++;
  }
}

void parse_precision(char* specs, const char** format, Options* opts) {
  int res = 0;
  opts->prec = 0;

  while (!is_spec(specs, **format)) {
    if (isdigit(**format)) {
      opts->prec = opts->prec * 10 + (**format - '0');
      res++;
    }
    (*format)++;
  }
  opts->prec_f = res;
}

int s21_sprintf(char* str, const char* format, ...) {
  int res = 0;  // Результат работы функции
  char* flags = "+- ";
  char* specs = "cidfsu";
  Options opts = {0};
  opts.prec_i = -1;

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  s21_size_t str_len = 0;  // Индекс буферной строки aka её длина
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      parse_flags(flags, &format, &opts);
      parse_width(specs, &format, &opts);
      parse_precision(specs, &format, &opts);
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
