#include "s21_sscanf.h"

// Функция для считывания символа из буфера
int read_char(const char **str, char *c, Opts *opts) {
  int result = 0;

  if (**str != '\0') {
    if (!opts->is_star) *c = **str;
    (*str)++;
    opts->count++;
    result = 1;
  }

  return result;
}

// Функция для считывания строки из буфера
int read_string(const char **str, char *s, Opts *opts) {
  while (**str != ' ' && **str != '\t' && **str != '\n' && **str != '\0') {
    if (!opts->is_star) *s = **str;
    (*str)++;
    s++;
    opts->count++;
  }
  *s = '\0';

  return 1;
}

// Функция для считывания целого числа из буфера
int read_int(const char **str, int *d, Opts *opts) {
  int sign = 1;
  int num = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    opts->count++;
  }

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    opts->count++;
  }
  if (!opts->is_star) *d = sign * num;

  return 1;
}

// Функция для считывания целого беззнакового числа из буфера
int read_unsigned_int(const char **str, unsigned int *u, Opts *opts) {
  unsigned int num = 0;

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    opts->count++;
  }
  if (!opts->is_star) *u = num;

  return 1;
}

// Функция для считывания числа с плавающей точкой из буфера
int read_float(const char **str, float *f, Opts *opts) {
  int sign = 1;
  int int_part = 0;
  float frac_part = 0.0;
  int frac_div = 1;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    opts->count++;
  }

  while (**str >= '0' && **str <= '9') {
    int_part = int_part * 10 + (**str - '0');
    (*str)++;
    opts->count++;
  }

  if (**str == '.') {
    (*str)++;
    opts->count++;
    while (**str >= '0' && **str <= '9') {
      frac_part = frac_part * 10 + (**str - '0');
      frac_div *= 10;
      (*str)++;
      opts->count++;
    }
  }
  if (!opts->is_star) *f = sign * (int_part + frac_part / frac_div);

  return 1;
}

// Функция для считывания беззн. целого 16-го числа из буфера
int read_hex(const char **str, unsigned int *x, Opts *opts) {
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
    opts->count++;
  }
  if (!opts->is_star) *x = num;

  return 1;
}

// Функция для считывания значений из буфера по формату
int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  Opts opts = {0};  // Зануляем структуру с опциями
  int result = 0;  // Количество считанных спецификаторов

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (*format == '*') {
        opts.is_star = 1;
        format++;
      }
      switch (*format) {
        case 'c':
          char *c = va_arg(args, char *);
          if (read_char(&str, c, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        case 's':
          char *s = va_arg(args, char *);
          if (read_string(&str, s, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        case 'd':
        case 'i':
          int *d = va_arg(args, int *);
          if (read_int(&str, d, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        case 'f':
          float *f = va_arg(args, float *);
          if (read_float(&str, f, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        case 'u':
          unsigned int *u = va_arg(args, unsigned int *);
          if (read_unsigned_int(&str, u, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        case 'x':
        case 'X':
          unsigned int *x = va_arg(args, unsigned int *);
          if (read_hex(&str, x, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        case '%':
          format++;
          break;
        case 'n':
          unsigned int *n = va_arg(args, unsigned int *);
          *n = opts.count;
          format++;
          break;
        default:
          break;
      }
    } else {
      opts.count++;
      format++;
      str++;
    }
  }
  va_end(args);

  return result;
}
