#include "s21_sscanf.h"

// buff сайз для %*s
#define BUFF_SIZE 1000

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  Opts opts = {0};  // Зануляем структуру с опциями
  int result = 0;  // Количество считанных спецификаторов

  // Проходимся по формат-строке
  while (*format != '\0') {
    if (*format == '%') {
      opts.is_star = false;
      opts.width = 0;
      format++;
      // Считываем * если есть
      if (*format == '*') {
        opts.is_star = 1;
        format++;
      }
      // Проверяем наличие цифр после %
      while (*format >= '0' && *format <= '9') {
        opts.width = opts.width * 10 + (*format - '0');
        format++;
      }
      switch (*format) {
        case 'c': {
          if (opts.is_star) {
            char c = '\0';
            if (read_char(&str, &c, &opts)) {
              format++;
            }
          } else {
            char *c = va_arg(args, char *);
            if (read_char(&str, c, &opts)) {
              result++;
              format++;
            }
          }
          break;
        }
        case 's': {
          if (opts.is_star) {
            char s[BUFF_SIZE];
            if (read_string(&str, s, &opts)) {
              format++;
            }
          } else {
            char *s = va_arg(args, char *);
            if (read_string(&str, s, &opts)) {
              result++;
              format++;
            }
          }
          break;
        }
        case 'd':
        case 'i': {
          if (opts.is_star) {
            int d = 0;
            if (read_int(&str, &d, &opts)) {
              format++;
            }
          } else {
            int *d = va_arg(args, int *);
            if (read_int(&str, d, &opts)) {
              result++;
              format++;
            }
          }
          break;
        }
        case 'f': {
          if (opts.is_star) {
            float f = 0.0;
            if (read_float(&str, &f, &opts)) {
              format++;
            }
          } else {
            float *f = va_arg(args, float *);
            if (read_float(&str, f, &opts)) {
              result++;
              format++;
            }
          }
          break;
        }
        case 'u': {
          if (opts.is_star) {
            unsigned u = 0;
            if (read_unsigned(&str, &u, &opts)) {
              format++;
            }
          } else {
            unsigned *u = va_arg(args, unsigned *);
            if (read_unsigned(&str, u, &opts)) {
              result++;
              format++;
            }
          }
          break;
        }
        case 'x':
        case 'X': {
          if (opts.is_star) {
            unsigned x = 0;
            if (read_unsigned(&str, &x, &opts)) {
              format++;
            }
          } else {
            unsigned *x = va_arg(args, unsigned *);
            if (read_hex(&str, x, &opts)) {
              result++;
              format++;
            }
          }
          break;
        }
        case '%': {
          opts.count++;
          format++;
          str++;
          break;
        }
        case 'n': {
          int *n = va_arg(args, int *);
          *n = opts.count;
          format++;
          break;
        }
        default:
          break;
      }
    } else if (*format == *str) {
      opts.count++;
      format++;
      str++;
    } else {
      format++;
    }
  }
  va_end(args);

  return result;
}

// void skip_space(const char **str, Opts *opts) {
//     while (**str == ' ') {
//     (*str)++;
//     opts->count++;
//   }
// }

int parse_pointer(const char **str, void **value, Opts *opts) {
  int res = 0;

  // Skip "0x" and increment count by 2
  (*str) += 2;

  // Convert hexadecimal value to pointer
  unsigned long int ptr_value = 0;
  while (isxdigit(**str)) {
    ptr_value *= 16;
    if (isdigit(**str)) {
      ptr_value += **str - '0';
    } else if (**str >= 'a' && **str <= 'f') {
      ptr_value += **str - 'a' + 10;
    } else if (**str >= 'A' && **str <= 'F') {
      ptr_value += **str - 'A' + 10;
    }
    (*str)++;
    opts->count++;
    res = 1;
  }

  *value = (void *)ptr_value;
  return res;  // Success
}

int read_char(const char **str, char *c, Opts *opts) {
  int result = 0;

  if (**str != '\0') {
    *c = **str;
    (*str)++;
    opts->count++;
    result = 1;
  }

  return result;
}

int read_string(const char **str, char *s, Opts *opts) {
  int result = 0;

  while (**str != ' ' && **str != '\t' && **str != '\n' && **str != '\0') {
    opts->count++;
    *s = **str;
    (*str)++;
    s++;
    result = 1;
  }
  *s = '\0';

  return result;
}

int read_int(const char **str, int *d, Opts *opts) {
  int result = 0;
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
    result = 1;
  }
  *d = sign * num;

  return result;
}

int read_unsigned(const char **str, unsigned int *u, Opts *opts) {
  unsigned num = 0;
  int result = 0;

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    opts->count++;
    result = 1;
  }
  *u = num;

  return result;
}

int read_float(const char **str, float *f, Opts *opts) {
  int sign = 1;
  int int_part = 0;
  float frac_part = 0.0;
  int frac_div = 1;
  int result = 0;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    opts->count++;
  }

  while (**str >= '0' && **str <= '9') {
    int_part = int_part * 10 + (**str - '0');
    (*str)++;
    opts->count++;
    result = 1;
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
  *f = sign * (int_part + frac_part / frac_div);

  return result;
}

int read_hex(const char **str, unsigned *x, Opts *opts) {
  unsigned num = 0;
  int result = 0;

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
    result = 1;
  }
  *x = num;

  return result;
}
