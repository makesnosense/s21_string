#include "s21_sscanf.h"

void set_sscanf_base(SpecOptions* spec_opts) {
  if (spec_opts->specifier == o) {
    spec_opts->base = 8.0;
  } else if (spec_opts->is_hexadecimal) {
    spec_opts->base = 16.0;
  } else {
    spec_opts->base = 10.0;
  }
}

int s21_sscanf(const char* str, const char* format, ...) {
  bool matching_failure = false;
  int result = 0;
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  InputStr source = {str, 0};
  InputStr fmt_input = {format, 0};
  consume_initial_space_and_n(&args, &source, &fmt_input);

  while (we_continue_consuming(&source, &fmt_input, &matching_failure)) {
    if (is_space(fmt_input.str[fmt_input.curr_ind])) {
      consume_space(&source);
      fmt_input.curr_ind++;
    } else if (fmt_input.str[fmt_input.curr_ind] == '%') {
      if (n_specifier_follows(&fmt_input, NULL) == false &&
          is_end_of_string(&source) == true) {
        result = -1;
        matching_failure = true;

      } else if (is_space(source.str[source.curr_ind]) &&
                 c_specifier_follows(&fmt_input) == false) {
        result = -1;
        matching_failure = true;
      } else {
        result +=
            consume_specifier(&args, &source, &fmt_input, &matching_failure);
      }
    } else {
      if (fmt_input.str[fmt_input.curr_ind] != source.str[source.curr_ind]) {
        matching_failure = true;
      } else {
        fmt_input.curr_ind++;
        source.curr_ind++;
      }
    }
  }
  va_end(args);

  return result;
}

int consume_specifier(va_list* args, InputStr* source, InputStr* fmt_input,
                      bool* matching_failure) {
  int specifier_result = 0;
  SpecOptions spec_opts = {0};
  *matching_failure = 0;
  // s21_memset(&spec_opts, 0, sizeof(spec_opts));
  fmt_input->curr_ind++;

  spec_opts.is_star = parse_suppression(fmt_input);
  parse_width_sscanf(fmt_input, &spec_opts);
  parse_sscanf_specifier(fmt_input, &spec_opts);
  switch (fmt_input->str[fmt_input->curr_ind]) {
    case 'c': {
      specifier_result = read_char(args, source, &spec_opts);
      break;
    }
    case 'n': {
      int* num = va_arg(*args, int*);
      *num = source->curr_ind;
      break;
    }
    case 'i':
    case 'd': {
      specifier_result = read_input_num(args, &spec_opts, source);
      // printf("meow");
    }
  }
  fmt_input->curr_ind++;
  return specifier_result;
}

int read_input_num(va_list* args, SpecOptions* spec_opts, InputStr* source) {
  int read_result = 0;
  // s21_size_t source_remaining = s21_strlen(source->str) - source->curr_ind;
  int* dest_input_pointer = va_arg(*args, int*);
  *dest_input_pointer = 0;

  if (s21_strncmp(&source->str[source->curr_ind], "-", 1) == 0) {
    spec_opts->is_minus = true;
    source->curr_ind++;
  }

  if (s21_strncmp(&source->str[source->curr_ind], "0x", 2) == 0 &&
      spec_opts->specifier == i) {
    spec_opts->base = 16;
    source->curr_ind += 2;
    read_result = read_hex(source, spec_opts, dest_input_pointer);
  } else if (s21_strncmp(&source->str[source->curr_ind], "0", 1) == 0 &&
             spec_opts->specifier == i) {
    spec_opts->base = 8;
    read_result = read_octal(source, spec_opts, dest_input_pointer);
  } else {
    spec_opts->base = 10;
    read_result = read_int(source, spec_opts, dest_input_pointer);
  }
  return read_result;
}

int read_hex(InputStr* source, SpecOptions* spec_opts,
             int* dest_input_pointer) {
  int num = 0;
  int read_result = 0;
  int sign = 1;

  if (spec_opts->is_minus == true) {
    sign = -1;
  }
  // printf("%d", spec_opts->is_star);
  while (is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' &&
         is_valid_digit(source->str[source->curr_ind], spec_opts->base)) {
    if (source->str[source->curr_ind] >= '0' &&
        source->str[source->curr_ind] <= '9') {
      num = num * 16 + (source->str[source->curr_ind] - '0');
    } else if (source->str[source->curr_ind] >= 'a' &&
               source->str[source->curr_ind] <= 'f') {
      num = num * 16 + (source->str[source->curr_ind] - 'a' + 10);
    } else {
      num = num * 16 + (source->str[source->curr_ind] - 'A' + 10);
    }
    source->curr_ind++;
    // opts->count++;
    read_result = 1;
  }
  if (read_result == 1) {
    *dest_input_pointer = num * sign;
  }

  return read_result;
}

int read_int(InputStr* source, SpecOptions* spec_opts,
             int* dest_input_pointer) {
  int read_result = 0;
  int sign = 1;
  int num = 0;
  // printf("%d", spec_opts->is_star);

  if (spec_opts->is_minus == true) {
    sign = -1;
  }

  while (is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' &&
         is_valid_digit(source->str[source->curr_ind], spec_opts->base)) {
    num = num * 10 + (source->str[source->curr_ind] - '0');
    source->curr_ind++;
    read_result = 1;
  }
  *dest_input_pointer = sign * num;

  return read_result;
}

int read_octal(InputStr* source, SpecOptions* spec_opts,
               int* dest_input_pointer) {
  int read_result = 0;
  int num = 0;
  int sign = 1;

  if (spec_opts->is_minus == true) {
    sign = -1;
  }

  s21_size_t num_length_minus_one =
      get_octal_num_length(source, spec_opts->base);

  s21_size_t power = num_length_minus_one;

  while (is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' &&
         is_valid_digit(source->str[source->curr_ind], spec_opts->base)) {
    char digit = source->str[source->curr_ind];
    num += (digit - '0') * pow(8, power--);
    read_result = 1;
    source->curr_ind++;
  }

  *dest_input_pointer = num * sign;

  return read_result;
}

s21_size_t get_octal_num_length(InputStr* source, s21_size_t base) {
  int num_len_cristal = 0;
  int num_len_dirty = source->curr_ind;

  while (is_space(source->str[num_len_dirty]) == false &&
         source->str[num_len_dirty] != '\0' &&
         is_valid_digit(source->str[num_len_dirty], base)) {
    num_len_cristal++;
    num_len_dirty++;
  }

  return num_len_cristal - 1;
}

bool is_valid_digit(char incoming_char, s21_size_t base) {
  bool char_is_valid = false;
  const char* digits = "0123456789abcdef";
  for (s21_size_t i = 0; i < base && char_is_valid == false; i++) {
    if (incoming_char == digits[i]) {
      char_is_valid = true;
    }
  }
  return char_is_valid;
}

// case 's': {
//   char* s = va_arg(args, char*);
//   if (read_string(&str, s, &spec_opts)) {
//     if (!spec_opts.is_star) result++;
//     fmt_input.curr_ind++;
//   }
//   break;
// }
// case 'd':
// case 'i': {
//   int* d = va_arg(args, int*);
//   if (read_int(&input, d, &spec_opts)) {
//     if (!spec_opts.is_star) result++;
//     fmt_input.curr_ind++;
//     // input.curr_ind++;
//   }
//   break;
// }
// case 'f': {
//   float* f = va_arg(args, float*);
//   if (read_float(&input, f, &spec_opts)) {
//     if (!spec_opts.is_star) result++;
//     fmt_input.curr_ind++;
//     // input.curr_ind++;
//   }
//   break;
// }
// case 'u': {
//   unsigned int* u = va_arg(args, unsigned int*);
//   if (read_unsigned_int(&str, u, &spec_opts)) {
//     if (!spec_opts.is_star) result++;
//     fmt_input.curr_ind++;
//   }
//   break;
// }
// case 'x':
// case 'X': {
//   unsigned int* x = va_arg(args, unsigned int*);
//   if (read_hex(&str, x, &spec_opts)) {
//     if (!spec_opts.is_star) result++;
//     fmt_input.curr_ind++;
//   }
//   break;
// }
// case 'p': {
//   void** address = va_arg(args, void**);
//   if (parse_pointer(&input, address)) {
//     if (!spec_opts.is_star) {
//       result++;
//     };
//     fmt_input.curr_ind++;
//     // input.curr_ind++;
//   }
// } break;
// case '%': {
//   fmt_input.curr_ind++;
//   str++;
//   break;
// }
// case 'n': {
//   int* n = va_arg(args, int*);
//   // YA HYU ZNAYET POCHEMU NO TAK RABOTAET
//   if (input.str[input.curr_ind - 2] == ' ') {
//     int temp = input.curr_ind;
//     *n = temp;
//   }
//   //  else {
//   //   // int temp = spec_opts.count;
//   //   // *n = temp;
//   // }
//   // *n = opts.count;
//   fmt_input.curr_ind++;
//   break;
// }
// default:
//   break;
// }

// else {
//   // spec_opts.count++;
//   fmt_input.curr_ind++;
//   input.curr_ind++;
// }

bool n_specifier_follows(InputStr* fmt_input, bool* n_star_present) {
  bool it_follows = false;
  if (fmt_input->str[fmt_input->curr_ind] == '%' &&
      fmt_input->str[fmt_input->curr_ind + 1] == 'n') {
    it_follows = true;
  } else if (fmt_input->str[fmt_input->curr_ind + 1] != '\0') {
    if (fmt_input->str[fmt_input->curr_ind] == '%' &&
        fmt_input->str[fmt_input->curr_ind + 1] == '*' &&
        fmt_input->str[fmt_input->curr_ind + 2] == 'n') {
      if (n_star_present != NULL) {
        *n_star_present = true;
      }
      it_follows = true;
    }
  }
  return it_follows;
}

bool c_specifier_follows(InputStr* fmt_input) {
  bool it_follows = false;
  s21_size_t fmt_characters_remaining =
      s21_strlen(fmt_input->str) - fmt_input->curr_ind;

  if (fmt_characters_remaining >= 2) {
    if (s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%c", 2) == 0) {
      it_follows = true;
    }
  }
  if (fmt_characters_remaining >= 3) {
    if (s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%lc", 3) == 0 ||
        s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%*c", 3) == 0) {
      it_follows = true;
    }
  }
  if (fmt_characters_remaining >= 4) {
    if (s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%*lc", 4) == 0) {
      it_follows = true;
    }
  }
  return it_follows;
}

bool is_end_of_string(InputStr* string_structure) {
  return string_structure->str[string_structure->curr_ind] == '\0';
}

bool is_space(char input_char) {
  bool result = false;
  char* space_chars = "\t\n\v\f\r ";
  for (s21_size_t i = 0; i < s21_strlen(space_chars); i++) {
    if (space_chars[i] == input_char) {
      result = true;
      break;
    }
  }
  return result;
}

bool is_space_specifier(InputStr* fmt_input) {
  return is_space(fmt_input->str[fmt_input->curr_ind]);
}

bool we_continue_consuming(InputStr* source, InputStr* fmt_input,
                           bool* matching_failure) {
  bool we_continue = false;
  bool n_star_present = false;
  if (is_end_of_string(fmt_input) == false && *matching_failure == false) {
    if (is_end_of_string(source) == false) {
      we_continue = true;
    } else {
      we_continue = n_specifier_follows(fmt_input, &n_star_present) ||
                    c_specifier_follows(fmt_input);
    }
  }
  return we_continue;
}

void consume_space(InputStr* source) {
  while (is_space(source->str[source->curr_ind])) {
    source->curr_ind++;
  }
}

void consume_initial_space_and_n(va_list* args, InputStr* source,
                                 InputStr* fmt_input) {
  bool n_star_present = false;
  while (n_specifier_follows(fmt_input, &n_star_present) ||
         is_space_specifier(fmt_input)) {
    if (is_space_specifier(fmt_input)) {
      consume_space(source);
      fmt_input->curr_ind++;
    } else if (n_specifier_follows(fmt_input, &n_star_present)) {
      process_n(args, source, n_star_present);
      if (n_star_present) {
        fmt_input->curr_ind += 3;
      } else {
        fmt_input->curr_ind += 2;
      }
    }
  }
}

void process_n(va_list* args, InputStr* source, bool n_star) {
  if (n_star == false) {
    int* num = va_arg(*args, int*);
    *num = source->curr_ind;
  }
}

int read_char(va_list* args, InputStr* source, SpecOptions* spec_opts) {
  int read_result = 0;
  if (spec_opts->is_star == false) {
    char* dest_char_ptr = va_arg(*args, char*);
    *dest_char_ptr = source->str[source->curr_ind];
    read_result++;
  }
  source->curr_ind++;
  return read_result;
};

void parse_width_sscanf(InputStr* fmt_input, SpecOptions* spec_opts) {
  while (fmt_input->str[fmt_input->curr_ind] >= '0' &&
         fmt_input->str[fmt_input->curr_ind] <= '9') {
    spec_opts->width =
        spec_opts->width * 10 + (fmt_input->str[fmt_input->curr_ind] - '0');
    fmt_input->curr_ind++;
  }
}

bool parse_suppression(InputStr* fmt_input) {
  bool star_present = false;
  if (fmt_input->str[fmt_input->curr_ind] == '*') {
    star_present = true;
    fmt_input->curr_ind++;
  }
  return star_present;
}

bool is_sscanf_specifier(char ch) {
  char* res = s21_strchr(VALID_SSCANF_SPECIFIERS, ch);
  return res != S21_NULL;
}

void parse_sscanf_specifier(InputStr* fmt_input, SpecOptions* spec_opts) {
  // printf("\n\n%c\n\n", fmt_input->str[fmt_input->curr_ind]);
  if (is_sscanf_specifier(fmt_input->str[fmt_input->curr_ind])) {
    char current_specifier = fmt_input->str[fmt_input->curr_ind];
    switch (current_specifier) {
      case 'c': {
        spec_opts->specifier = c;
        break;
      }
      case 'd': {
        spec_opts->specifier = d;
        break;
      }
      case 'i': {
        // printf("\n\n\n\ndfgyuigrflslfopjgkfpwlrg\n\n\n\n\n");
        spec_opts->specifier = i;
        break;
      }
      case 'x':
      case 'X': {
        if (current_specifier == 'x') {
          spec_opts->specifier = x;
        }
        if (current_specifier == 'X') {
          spec_opts->specifier = X;
        }
        break;
      }
      case 'o': {
        spec_opts->specifier = o;
        break;
      }
    }
  }
}

// int read_int(InputStr* input, int* d, SpecOptions* opts) {
//   int result = 0;
//   int sign = 1;
//   int num = 0;
//   printf("%d", opts->is_star);

//   if (input->str[input->curr_ind] == '-') {
//     sign = -1;
//     input->curr_ind++;
//     // opts->count++;
//   }

//   while (input->str[input->curr_ind] >= '0' &&
//          input->str[input->curr_ind] <= '9') {
//     num = num * 10 + (input->str[input->curr_ind] - '0');
//     input->curr_ind++;
//     // opts->count++;
//     result = 1;
//   }
//   *d = sign * num;

//   return result;
// }

// int parse_pointer(InputStr* input, void** value) {
//   int res = 0;

//   // Skip "0x" and increment count by 2
//   // input->curr_ind += 1;
//   // printf("\n\n.%c.\n\n", input->str[input->curr_ind]);

//   // Convert hexadecimal value to pointer
//   unsigned long int ptr_value = 0;
//   while (isxdigit(input->str[input->curr_ind])) {
//     ptr_value *= 16;
//     if (isdigit(input->str[input->curr_ind])) {
//       ptr_value += input->str[input->curr_ind] - '0';
//     } else if (input->str[input->curr_ind] >= 'a' &&
//                input->str[input->curr_ind] <= 'f') {
//       ptr_value += input->str[input->curr_ind] - 'a' + 10;
//     } else if (input->str[input->curr_ind] >= 'A' &&
//                input->str[input->curr_ind] <= 'F') {
//       ptr_value += input->str[input->curr_ind] - 'A' + 10;
//     }
//     input->curr_ind++;
//     // opts->count++;
//     res = 1;
//   }

//   *value = (void*)ptr_value;
//   return res;  // Success
// }

// int read_char(InputStr* source, SpecOptions* opts) {
//   int result = 0;

//   // printf("\n\n%lu\n\n", input->curr_ind);
//   /// here to add \t and n
//   if (input->str[input->curr_ind] != '\0') {
//     if (!opts->is_star) *c = input->str[input->curr_ind];
//     input->curr_ind++;
//     // opts->count++;
//     result = 1;
//   }

//   return result;
// }

// int read_string(const char** str, char* s, SpecOptions* opts) {
//   int result = 0;
//   printf("%d", opts->is_star);
//   while (**str != ' ' && **str != '\t' && **str != '\n' && **str != '\0') {
//     // opts->count++;
//     *s = **str;
//     (*str)++;
//     s++;
//     // opts->count++;
//     result = 1;
//   }
//   *s = '\0';

//   return result;
// }

// int read_int(InputStr* input, int* d, SpecOptions* opts) {
//   int result = 0;
//   int sign = 1;
//   int num = 0;
//   printf("%d", opts->is_star);

//   if (input->str[input->curr_ind] == '-') {
//     sign = -1;
//     input->curr_ind++;
//     // opts->count++;
//   }

//   while (input->str[input->curr_ind] >= '0' &&
//          input->str[input->curr_ind] <= '9') {
//     num = num * 10 + (input->str[input->curr_ind] - '0');
//     input->curr_ind++;
//     // opts->count++;
//     result = 1;
//   }
//   *d = sign * num;

//   return result;
// }

// int read_unsigned_int(const char** str, unsigned int* u, SpecOptions* opts)
// {
//   unsigned int num = 0;
//   int result = 0;
//   printf("%d", opts->is_star);

//   while (**str >= '0' && **str <= '9') {
//     num = num * 10 + (**str - '0');
//     (*str)++;
//     // opts->count++;
//     result = 1;
//   }
//   *u = num;

//   return result;
// }

// int read_float(InputStr* input, float* f, SpecOptions* opts) {
//   int sign = 1;
//   int int_part = 0;
//   float frac_part = 0.0;
//   int frac_div = 1;
//   int result = 0;
//   printf("%d", opts->is_star);
//   if (input->str[input->curr_ind] == '-') {
//     sign = -1;
//     input->curr_ind++;
//     // opts->count++;
//   }

//   while (input->str[input->curr_ind] >= '0' &&
//          input->str[input->curr_ind] <= '9') {
//     int_part = int_part * 10 + (input->str[input->curr_ind] - '0');
//     input->curr_ind++;
//     // opts->count++;
//     result = 1;
//   }

//   if (input->str[input->curr_ind] == '.') {
//     input->curr_ind++;
//     // opts->count++;
//     while (input->str[input->curr_ind] >= '0' &&
//            input->str[input->curr_ind] <= '9') {
//       frac_part = frac_part * 10 + (input->str[input->curr_ind] - '0');
//       frac_div *= 10;
//       input->curr_ind++;
//       // opts->count++;
//     }
//   }
//   *f = sign * (int_part + frac_part / frac_div);

//   return result;
// }

// int read_hex(const char** str, unsigned int* x, SpecOptions* opts) {
//   unsigned int num = 0;
//   int result = 0;
//   printf("%d", opts->is_star);
//   while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f')
//   ||
//          (**str >= 'A' && **str <= 'F')) {
//     if (**str >= '0' && **str <= '9') {
//       num = num * 16 + (**str - '0');
//     } else if (**str >= 'a' && **str <= 'f') {
//       num = num * 16 + (**str - 'a' + 10);
//     } else {
//       num = num * 16 + (**str - 'A' + 10);
//     }
//     (*str)++;
//     // opts->count++;
//     result = 1;
//   }
//   *x = num;

//   return result;
// }

// bool format_string_starts_with_char_spec(InputStr* fmt_input) {
//   bool result = false;
//   s21_size_t fmt_len = s21_strlen(fmt_input->str);

//   if (fmt_len >= 2) {
//     if (fmt_input->str[0] == '%' && fmt_input->str[1] == 'c') {
//       result = true;
//     }
//   } else if (fmt_len >= 3) {
//     if (fmt_input->str[0] == '%' && fmt_input->str[1] == 'l' &&
//         fmt_input->str[2] == 'c') {
//       result = true;
//     } else if (fmt_input->str[0] == '%' && fmt_input->str[1] == '*' &&
//                fmt_input->str[2] == 'c') {
//       result = true;
//     }
//   } else if (fmt_len >= 4) {
//     if (fmt_input->str[0] == '%' && fmt_input->str[1] == '*' &&
//         fmt_input->str[2] == 'l' && fmt_input->str[3] == 'c') {
//       result = true;
//     }
//   }
//   return result;
// }

// int source_validity_check(InputStr* source, InputStr* fmt_input,
//                           bool* matching_failure) {
//   bool char_found = false;
//   int i = 0;

//   s21_size_t source_characters_remaining =
//       s21_strlen(source->str) - source->curr_ind;

//   if (source_characters_remaining == 0) {
//     while (source->str[i] != '\0') {
//       if (char_found == false) {
//         char_found = format_string_starts_with_char_spec(fmt_input);
//       }
//     }
//     if (char_found == false) {
//       *matching_failure = true;
//     }
//     return char_found ? 0 : -1;
//   }

// bool c_specifier_follows(InputStr* fmt_input) {
//   bool result = false;
//   s21_size_t fmt_characters_remaining =
//       s21_strlen(fmt_input->str) - fmt_input->curr_ind;

//   if (fmt_characters_remaining >= 2) {
//     if (fmt_input->str[fmt_input->curr_ind] == '%' &&
//         fmt_input->str[fmt_input->curr_ind + 1] == 'c') {
//       result = true;
//     }
//   } else if (fmt_characters_remaining >= 3) {
//     if (fmt_input->str[0] == '%' && fmt_input->str[1] == 'l' &&
//         fmt_input->str[2] == 'c') {
//       result = true;
//     } else if (fmt_input->str[0] == '%' && fmt_input->str[1] == '*' &&
//                fmt_input->str[2] == 'c') {
//       result = true;
//     }
//   } else if (fmt_characters_remaining >= 4) {
//     if (fmt_input->str[0] == '%' && fmt_input->str[1] == '*' &&
//         fmt_input->str[2] == 'l' && fmt_input->str[3] == 'c') {
//       result = true;
//     }
//   }
//   return result;
// }