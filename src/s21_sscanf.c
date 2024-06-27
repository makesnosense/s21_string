#include "s21_sscanf.h"

int s21_sscanf(const char* str, const char* format, ...) {
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  InputStr input = {str, 0};
  Opts opts = {0};  // Зануляем структуру с опциями
  int result = 0;  // Количество считанных спецификаторов

  // Проходимся по формат-строке
  while (*format != '\0') {
    if (*format == '%') {
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
          char* c = va_arg(args, char*);
          if (read_char(&str, c, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        }
        case 's': {
          char* s = va_arg(args, char*);
          if (read_string(&str, s, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        }
        case 'd':
        case 'i': {
          int* d = va_arg(args, int*);
          if (read_int(&input, d, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        }
        case 'f': {
          float* f = va_arg(args, float*);
          if (read_float(&str, f, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        }
        case 'u': {
          unsigned int* u = va_arg(args, unsigned int*);
          if (read_unsigned_int(&str, u, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        }
        case 'x':
        case 'X': {
          unsigned int* x = va_arg(args, unsigned int*);
          if (read_hex(&str, x, &opts)) {
            if (!opts.is_star) result++;
            format++;
          }
          break;
        }
        case '%': {
          format++;
          str++;
          break;
        }
        case 'n': {
          int* n = va_arg(args, int*);
          // YA HYU ZNAYET POCHEMU NO TAK RABOTAET
          int temp = opts.count;
          *n = temp;
          // *n = opts.count;
          format++;
          break;
        }
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

// void skip_space(const char **str, Opts *opts) {
//     while (**str == ' ') {
//     (*str)++;
//     opts->count++;
//   }
// }

int parse_pointer(const char** str, void** value, Opts* opts) {
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

  *value = (void*)ptr_value;
  return res;  // Success
}

int read_char(const char** str, char* c, Opts* opts) {
  int result = 0;

  if (**str != '\0') {
    if (!opts->is_star) *c = **str;
    (*str)++;
    opts->count++;
    result = 1;
  }

  return result;
}

int read_string(const char** str, char* s, Opts* opts) {
  int result = 0;

  while (**str != ' ' && **str != '\t' && **str != '\n' && **str != '\0') {
    if (!opts->is_star) *s = **str;
    (*str)++;
    s++;
    opts->count++;
    result = 1;
  }
  *s = '\0';

  return result;
}

int read_int(InputStr* input, int* d, Opts* opts) {
  int result = 0;
  int sign = 1;
  int num = 0;

  if (input->str[input->curr_ind] == '-') {
    sign = -1;
    input->curr_ind++;
    opts->count++;
  }

  while (input->str[input->curr_ind] >= '0' &&
         input->str[input->curr_ind] <= '9') {
    num = num * 10 + (input->str[input->curr_ind] - '0');
    input->curr_ind++;
    opts->count++;
    result = 1;
  }
  if (!opts->is_star) *d = sign * num;

  return result;
}

int read_unsigned_int(const char** str, unsigned int** u, Opts* opts) {
  unsigned int num = 0;
  int result = 0;

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    opts->count++;
    result = 1;
  }
  if (!opts->is_star) *u = num;

  return result;
}

int read_float(const char** str, float* f, Opts* opts) {
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
  if (!opts->is_star) *f = sign * (int_part + frac_part / frac_div);

  return result;
}

int read_hex(const char** str, unsigned int* x, Opts* opts) {
  unsigned int num = 0;
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
  if (!opts->is_star) *x = num;

  return result;
}
