#include "s21_sscanf.h"

int s21_sscanf(const char* str, const char* format, ...) {
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  InputStr input = {str, 0};
  InputStr fmt_input = {format, 0};

  SpecOptions spec_opts = {0};  // Зануляем структуру с опциями
  int result = 0;  // Количество считанных спецификаторов

  // Проходимся по формат-строке
  while (fmt_input.str[fmt_input.curr_ind] != '\0') {
    // skip_space(&input);

    if (fmt_input.str[fmt_input.curr_ind] == '%') {
      s21_memset(&spec_opts, 0, sizeof(spec_opts));
      fmt_input.curr_ind++;

      parse_suppression(&fmt_input, &spec_opts);

      parse_width(&fmt_input, &spec_opts);

      switch (fmt_input.str[fmt_input.curr_ind]) {
        case 'c': {
          char* dest_char_ptr = va_arg(args, char*);
          if (read_char(&input, dest_char_ptr, &spec_opts)) {
            if (!spec_opts.is_star) result++;
            format++;
            // input.curr_ind++;
          }
          break;
        }
        case 's': {
          char* s = va_arg(args, char*);
          if (read_string(&str, s, &spec_opts)) {
            if (!spec_opts.is_star) result++;
            fmt_input.curr_ind++;
          }
          break;
        }
        case 'd':
        case 'i': {
          int* d = va_arg(args, int*);
          if (read_int(&input, d, &spec_opts)) {
            if (!spec_opts.is_star) result++;
            fmt_input.curr_ind++;
            // input.curr_ind++;
          }
          break;
        }
        case 'f': {
          float* f = va_arg(args, float*);
          if (read_float(&input, f, &spec_opts)) {
            if (!spec_opts.is_star) result++;
            fmt_input.curr_ind++;
            // input.curr_ind++;
          }
          break;
        }
        case 'u': {
          unsigned int* u = va_arg(args, unsigned int*);
          if (read_unsigned_int(&str, u, &spec_opts)) {
            if (!spec_opts.is_star) result++;
            fmt_input.curr_ind++;
          }
          break;
        }
        case 'x':
        case 'X': {
          unsigned int* x = va_arg(args, unsigned int*);
          if (read_hex(&str, x, &spec_opts)) {
            if (!spec_opts.is_star) result++;
            fmt_input.curr_ind++;
          }
          break;
        }
        case 'p': {
          void** address = va_arg(args, void**);
          if (parse_pointer(&input, address)) {
            if (!spec_opts.is_star) result++;
            fmt_input.curr_ind++;
            // input.curr_ind++;
          }
        } break;
        case '%': {
          fmt_input.curr_ind++;
          str++;
          break;
        }
        case 'n': {
          int* n = va_arg(args, int*);
          // YA HYU ZNAYET POCHEMU NO TAK RABOTAET
          if (input.str[input.curr_ind - 2] == ' ') {
            int temp = input.curr_ind;
            *n = temp;
          }
          //  else {
          //   // int temp = spec_opts.count;
          //   // *n = temp;
          // }
          // *n = opts.count;
          fmt_input.curr_ind++;
          break;
        }
        default:
          break;
      }
    } else {
      // spec_opts.count++;
      fmt_input.curr_ind++;
      input.curr_ind++;
    }
  }
  va_end(args);

  return result;
}
void parse_width(InputStr* fmt_input, SpecOptions* spec_opts) {
  while (fmt_input->str[fmt_input->curr_ind] >= '0' &&
         fmt_input->str[fmt_input->curr_ind] <= '9') {
    spec_opts->width =
        spec_opts->width * 10 + (fmt_input->str[fmt_input->curr_ind] - '0');
    fmt_input->curr_ind++;
  }
}

void parse_suppression(InputStr* fmt_input, SpecOptions* spec_opts) {
  if (fmt_input->str[fmt_input->curr_ind] == '*') {
    spec_opts->is_star = true;
    fmt_input->curr_ind++;
  }
}

void skip_space(InputStr* input) {
  while (input->str[input->curr_ind + 1] == ' ') {
    input->curr_ind++;
  }
}

int parse_pointer(InputStr* input, void** value) {
  int res = 0;

  // Skip "0x" and increment count by 2
  // input->curr_ind += 1;
  // printf("\n\n.%c.\n\n", input->str[input->curr_ind]);

  // Convert hexadecimal value to pointer
  unsigned long int ptr_value = 0;
  while (isxdigit(input->str[input->curr_ind])) {
    ptr_value *= 16;
    if (isdigit(input->str[input->curr_ind])) {
      ptr_value += input->str[input->curr_ind] - '0';
    } else if (input->str[input->curr_ind] >= 'a' &&
               input->str[input->curr_ind] <= 'f') {
      ptr_value += input->str[input->curr_ind] - 'a' + 10;
    } else if (input->str[input->curr_ind] >= 'A' &&
               input->str[input->curr_ind] <= 'F') {
      ptr_value += input->str[input->curr_ind] - 'A' + 10;
    }
    input->curr_ind++;
    // opts->count++;
    res = 1;
  }

  *value = (void*)ptr_value;
  return res;  // Success
}

int read_char(InputStr* input, char* c, SpecOptions* opts) {
  int result = 0;
  // printf("\n\n%lu\n\n", input->curr_ind);
  /// here to add \t and n
  if (input->str[input->curr_ind] != '\0') {
    if (!opts->is_star) *c = input->str[input->curr_ind];
    input->curr_ind++;
    // opts->count++;
    result = 1;
  }

  return result;
}

int read_string(const char** str, char* s, SpecOptions* opts) {
  int result = 0;

  while (**str != ' ' && **str != '\t' && **str != '\n' && **str != '\0') {
    // opts->count++;
    *s = **str;
    (*str)++;
    s++;
    // opts->count++;
    result = 1;
  }
  *s = '\0';

  return result;
}

int read_int(InputStr* input, int* d, SpecOptions* opts) {
  int result = 0;
  int sign = 1;
  int num = 0;

  if (input->str[input->curr_ind] == '-') {
    sign = -1;
    input->curr_ind++;
    // opts->count++;
  }

  while (input->str[input->curr_ind] >= '0' &&
         input->str[input->curr_ind] <= '9') {
    num = num * 10 + (input->str[input->curr_ind] - '0');
    input->curr_ind++;
    // opts->count++;
    result = 1;
  }
  *d = sign * num;

  return result;
}

int read_unsigned_int(const char** str, unsigned int* u, SpecOptions* opts) {
  unsigned int num = 0;
  int result = 0;

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + (**str - '0');
    (*str)++;
    // opts->count++;
    result = 1;
  }
  *u = num;

  return result;
}

int read_float(InputStr* input, float* f, SpecOptions* opts) {
  int sign = 1;
  int int_part = 0;
  float frac_part = 0.0;
  int frac_div = 1;
  int result = 0;

  if (input->str[input->curr_ind] == '-') {
    sign = -1;
    input->curr_ind++;
    // opts->count++;
  }

  while (input->str[input->curr_ind] >= '0' &&
         input->str[input->curr_ind] <= '9') {
    int_part = int_part * 10 + (input->str[input->curr_ind] - '0');
    input->curr_ind++;
    // opts->count++;
    result = 1;
  }

  if (input->str[input->curr_ind] == '.') {
    input->curr_ind++;
    // opts->count++;
    while (input->str[input->curr_ind] >= '0' &&
           input->str[input->curr_ind] <= '9') {
      frac_part = frac_part * 10 + (input->str[input->curr_ind] - '0');
      frac_div *= 10;
      input->curr_ind++;
      // opts->count++;
    }
  }
  *f = sign * (int_part + frac_part / frac_div);

  return result;
}

int read_hex(const char** str, unsigned int* x, SpecOptions* opts) {
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
    // opts->count++;
    result = 1;
  }
  *x = num;

  return result;
}
