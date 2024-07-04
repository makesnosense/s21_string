#include "s21_sscanf.h"

int s21_sscanf(const char* str, const char* format, ...) {
  bool matching_failure = false;
  int result = 0;
  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  InputStr source = {str, 0};
  InputStr fmt_input = {format, 0};
  consume_initial_space_and_n(&args, &source, &fmt_input);

  while (we_continue_consuming(&source, &fmt_input, &matching_failure)) {
    if (is_space_specifier(&fmt_input)) {
      consume_space(&source, &fmt_input, true);
    } else if (fmt_input.str[fmt_input.curr_ind] == '%') {
      process_specifier_sscanf(&result, &args, &source, &fmt_input,
                               &matching_failure);
    } else {
      process_foreign_char_in_format(&source, &fmt_input, &matching_failure);
    }
  }

  va_end(args);

  return result;
}

void process_foreign_char_in_format(InputStr* source, InputStr* fmt_input,
                                    bool* matching_failure) {
  if (fmt_input->str[fmt_input->curr_ind] != source->str[source->curr_ind]) {
    *matching_failure = true;
  } else {
    fmt_input->curr_ind++;
    source->curr_ind++;
  }
}

void process_specifier_sscanf(int* sscanf_result, va_list* args,
                              InputStr* source, InputStr* fmt_input,
                              bool* matching_failure) {
  if (n_specifier_follows(fmt_input) == false &&
      is_end_of_string(source) == true) {
    if (*sscanf_result == 0) {
      *sscanf_result = -1;
    }
    *matching_failure = true;

  } else if (is_space(source->str[source->curr_ind]) &&
             c_specifier_follows(fmt_input) == false) {
    consume_space(source, fmt_input, false);
  } else {
    *sscanf_result +=
        consume_specifier(args, source, fmt_input, matching_failure);
  }
}

int consume_specifier(va_list* args, InputStr* source, InputStr* fmt_input,
                      bool* matching_failure) {
  int specifier_result = 0;
  SpecOptions spec_opts = {0};

  fmt_input->curr_ind++;

  spec_opts.is_star = parse_suppression(fmt_input);
  parse_width_sscanf(fmt_input, &spec_opts);
  parse_length_sscanf(fmt_input, &spec_opts);
  parse_sscanf_specifier(fmt_input, &spec_opts);
  read_next_digit_in_fmt(*fmt_input, &spec_opts);

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
    case 's': {
      specifier_result = read_string(args, source, &spec_opts);
      break;
    }
    case 'p': {
      void** dest_input_pointer = va_arg(*args, void**);
      specifier_result = read_pointer(source, dest_input_pointer, &spec_opts);
      break;
    }
    case 'i':
    case 'd': {
      specifier_result =
          process_int_sscanf(args, &spec_opts, source, matching_failure);
      break;
    }
    case 'x':
    case 'X':
    case 'o':
    case 'u': {
      specifier_result =
          process_unsigned_sscanf(args, &spec_opts, source, matching_failure);
      break;
    }
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'f': {
      specifier_result = process_float_sscanf(args, &spec_opts, source);
      break;
    }
    case '%':
      if (source->str[source->curr_ind] == '%') {
        source->curr_ind++;
      }
  }
  fmt_input->curr_ind++;
  return specifier_result;
}

int read_pointer(InputStr* source, void** value, SpecOptions* spec_opts) {
  bool weve_read_at_least_once_successfully = 0;
  unsigned long long ptr_value = 0;

  while (is_space(source->str[source->curr_ind]) == true) {
    source->curr_ind++;
    // printf("\n\n\n\n%c HERE\n\n\n", source->str[source->curr_ind]);
  }

  if (hexadecimal_prefix_follows(source)) {
    source->curr_ind += 2;
  }

  // Чтение шестнадцатеричных цифр
  while (isxdigit(source->str[source->curr_ind])) {
    ptr_value *= 16;
    if (isdigit(source->str[source->curr_ind])) {
      ptr_value += source->str[source->curr_ind] - '0';
    } else if (source->str[source->curr_ind] >= 'a' &&
               source->str[source->curr_ind] <= 'f') {
      ptr_value += source->str[source->curr_ind] - 'a' + 10;
    } else if (source->str[source->curr_ind] >= 'A' &&
               source->str[source->curr_ind] <= 'F') {
      ptr_value += source->str[source->curr_ind] - 'A' + 10;
    }
    source->curr_ind++;
    weve_read_at_least_once_successfully = true;
  }

  // Преобразование ptr_value в указатель и сохранение в value
  if (spec_opts->is_star == false) {
    *value = (void*)ptr_value;
  }
  return weve_read_at_least_once_successfully;
}

int read_string(va_list* args, InputStr* source, SpecOptions* spec_opts) {
  bool weve_read_at_least_once_successfully = 0;
  s21_size_t bytes_read = 0;

  if (spec_opts->is_star == false) {
    char* dest_input_pointer = va_arg(*args, char*);

    while (is_space(source->str[source->curr_ind]) == false &&
           source->str[source->curr_ind] != '\0' &&
           width_limit_reached(bytes_read, spec_opts) == false) {
      *dest_input_pointer = source->str[source->curr_ind];
      dest_input_pointer++;
      weve_read_at_least_once_successfully = true;
      source->curr_ind++;
      bytes_read++;
    }
    *dest_input_pointer = '\0';

  } else {
    while (is_space(source->str[source->curr_ind]) == false &&
           source->str[source->curr_ind] != '\0' &&
           width_limit_reached(bytes_read, spec_opts) == false) {
      source->curr_ind++;
      bytes_read++;
    }
  }

  return weve_read_at_least_once_successfully;
}

int process_float_sscanf(va_list* args, SpecOptions* spec_opts,
                         InputStr* source) {
  int read_result = 0;
  long double temp_floating_destination = 0;

  read_result = read_float(source, &temp_floating_destination, spec_opts);

  write_to_floating_pointer(args, spec_opts, temp_floating_destination);

  return spec_opts->is_star == false ? read_result : 0;
}

void write_to_floating_pointer(va_list* args, SpecOptions* spec_opts,
                               long double temp_floating_destination) {
  if (spec_opts->is_star == false) {
    if (spec_opts->length == l) {
      double* dest_input_pointer = va_arg(*args, double*);
      *dest_input_pointer = (double)temp_floating_destination;
    } else if (spec_opts->length == L) {
      long double* dest_input_pointer = va_arg(*args, long double*);
      *dest_input_pointer = (long double)temp_floating_destination;
    } else {
      float* dest_input_pointer = va_arg(*args, float*);
      *dest_input_pointer = (float)temp_floating_destination;
    }
  }
}

void read_next_digit_in_fmt(InputStr fmt_input, SpecOptions* spec_opts) {
  if (fmt_input.str[fmt_input.curr_ind + 1] != '\0') {
    spec_opts->next_digit = fmt_input.str[fmt_input.curr_ind + 1];
  }
}

void process_n(va_list* args, InputStr* source, bool n_star) {
  if (n_star == false) {
    int* num = va_arg(*args, int*);
    *num = source->curr_ind;
  }
}

int process_unsigned_sscanf(va_list* args, SpecOptions* spec_opts,
                            InputStr* source, bool* matching_failure) {
  int read_result = 0;
  long long unsigned temp_long_long_unsigned_destination = 0;
  if (spec_opts->specifier == o) {
    read_result =
        read_octal(source, spec_opts, &temp_long_long_unsigned_destination,
                   matching_failure);
  } else if (spec_opts->is_hexadecimal) {
    read_result =
        read_hex(source, spec_opts, &temp_long_long_unsigned_destination,
                 matching_failure);
  } else {
    read_result =
        read_decimal(source, spec_opts, &temp_long_long_unsigned_destination,
                     matching_failure);
  }

  write_to_unsigned_pointer(args, spec_opts,
                            temp_long_long_unsigned_destination);

  return spec_opts->is_star == false ? read_result : 0;
}

void write_to_unsigned_pointer(
    va_list* args, SpecOptions* spec_opts,
    long long unsigned temp_long_long_unsigned_destination) {
  if (spec_opts->is_star == false) {
    if (spec_opts->length == h) {
      short unsigned* dest_input_pointer = va_arg(*args, short unsigned*);
      *dest_input_pointer = (short unsigned)temp_long_long_unsigned_destination;
    } else if (spec_opts->length == l) {
      long unsigned* dest_input_pointer = va_arg(*args, long unsigned*);
      *dest_input_pointer = (long unsigned)temp_long_long_unsigned_destination;
    } else {
      unsigned* dest_input_pointer = va_arg(*args, unsigned*);
      *dest_input_pointer = (unsigned)temp_long_long_unsigned_destination;
    }
  }
}

int process_int_sscanf(va_list* args, SpecOptions* spec_opts, InputStr* source,
                       bool* matching_failure) {
  int read_result = 0;

  long long unsigned temp_unsigned_destination = 0;

  if (s21_strncmp(&source->str[source->curr_ind], "-", 1) == 0) {
    spec_opts->is_negative = true;
    source->curr_ind++;
  }

  if (hexadecimal_prefix_follows(source) && spec_opts->specifier == i) {
    read_result = read_hex(source, spec_opts, &temp_unsigned_destination,
                           matching_failure);
  } else if (s21_strncmp(&source->str[source->curr_ind], "0", 1) == 0 &&
             spec_opts->specifier == i) {
    read_result = read_octal(source, spec_opts, &temp_unsigned_destination,
                             matching_failure);
  } else {
    read_result = read_decimal(source, spec_opts, &temp_unsigned_destination,
                               matching_failure);
  }

  int sign = spec_opts->is_negative ? -1 : 1;

  write_to_integer_pointer(args, spec_opts, temp_unsigned_destination, sign);

  return spec_opts->is_star == false ? read_result : 0;
}

void write_to_integer_pointer(va_list* args, SpecOptions* spec_opts,
                              long long unsigned temp_unsigned_destination,
                              int sign) {
  if (spec_opts->is_star == false) {
    if (spec_opts->length == h) {
      short* dest_input_pointer = va_arg(*args, short*);
      *dest_input_pointer = sign * (short)temp_unsigned_destination;
    } else if (spec_opts->length == l) {
      long* dest_input_pointer = va_arg(*args, long*);
      *dest_input_pointer = sign * (long)temp_unsigned_destination;
    } else {
      int* dest_input_pointer = va_arg(*args, int*);
      *dest_input_pointer = sign * (int)temp_unsigned_destination;
    }
  }
}

bool hexadecimal_prefix_follows(InputStr* source) {
  bool hexadecimal_prefix_follows = false;
  if ((s21_strncmp(&source->str[source->curr_ind], "0x", 2) == 0 ||
       s21_strncmp(&source->str[source->curr_ind], "0X", 2) == 0)) {
    hexadecimal_prefix_follows = true;
  }
  return hexadecimal_prefix_follows;
}

int read_hex(InputStr* source, SpecOptions* spec_opts,
             long long unsigned* dest_input_pointer, bool* matching_failure) {
  s21_size_t base = 16;
  bool weve_read_at_least_once_successfully = false;
  bool hex_reading_failure = false;
  long long unsigned num = 0;
  s21_size_t bytes_read = 0;

  if (hexadecimal_prefix_follows(source)) {
    source->curr_ind += 2;
    bytes_read += 2;
  }

  while (is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' && *matching_failure == false &&
         hex_reading_failure == false &&
         width_limit_reached(bytes_read, spec_opts) == false) {
    if (is_valid_digit(source->str[source->curr_ind], base)) {
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
      bytes_read++;
      weve_read_at_least_once_successfully = true;
    } else if ((is_valid_digit(source->str[source->curr_ind], base) == false &&
                spec_opts->specifier == i) ||
               (source->str[source->curr_ind] == spec_opts->next_digit)) {
      hex_reading_failure = true;
    } else {
      *matching_failure = true;
    }
  }

  if (bytes_read > 0) {
    weve_read_at_least_once_successfully = true;
    *dest_input_pointer = num;
  }

  return weve_read_at_least_once_successfully;
}

int read_decimal(InputStr* source, SpecOptions* spec_opts,
                 long long unsigned* dest_input_pointer,
                 bool* matching_failure) {
  s21_size_t base = 10;
  bool weve_read_at_least_once_successfully = false;
  bool decimal_reading_failure = false;
  long long unsigned num = 0;
  s21_size_t bytes_read = 0;

  while (is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' && *matching_failure == false &&
         decimal_reading_failure == false &&
         width_limit_reached(bytes_read, spec_opts) == false) {
    if (is_valid_digit(source->str[source->curr_ind], base)) {
      num = num * 10 + (source->str[source->curr_ind] - '0');
      source->curr_ind++;
      bytes_read++;

    } else if (source->str[source->curr_ind] == spec_opts->next_digit) {
      decimal_reading_failure = true;
    } else {
      *matching_failure = true;
    }
  }
  if (bytes_read > 0) {
    weve_read_at_least_once_successfully = true;
    *dest_input_pointer = num;
  }
  return weve_read_at_least_once_successfully;
}

int read_octal(InputStr* source, SpecOptions* spec_opts,
               long long unsigned* dest_input_pointer, bool* matching_failure) {
  bool weve_read_at_least_once_successfully = false;
  bool not_octal_but_we_continue_with_decimal = false;
  s21_size_t base = 8;

  long long unsigned num = 0;
  s21_size_t bytes_read = 0;

  s21_size_t num_length_minus_one =
      get_octal_num_length(source, spec_opts, base);
  s21_size_t power = num_length_minus_one;

  while (is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' && *matching_failure == false &&
         not_octal_but_we_continue_with_decimal == false &&
         width_limit_reached(bytes_read, spec_opts) == false) {
    if (is_valid_digit(source->str[source->curr_ind], base) == true) {
      char digit = source->str[source->curr_ind];
      num += (digit - '0') * pow(8, power--);
      weve_read_at_least_once_successfully = true;
      source->curr_ind++;
      bytes_read++;
    } else if ((is_valid_digit(source->str[source->curr_ind], 10) &&
                spec_opts->specifier == i) ||
               (source->str[source->curr_ind] == spec_opts->next_digit)) {
      not_octal_but_we_continue_with_decimal = true;
    } else {
      *matching_failure = true;
    }
  }
  if (weve_read_at_least_once_successfully) {
    *dest_input_pointer = num;
  }
  return weve_read_at_least_once_successfully;
}

bool width_limit_reached(s21_size_t bytes_read, SpecOptions* spec_opts) {
  bool limit_reached = false;
  s21_size_t limit = spec_opts->width;
  if (spec_opts->is_negative) {
    limit -= 1;
  }

  if (spec_opts->width_set == true && bytes_read >= limit) {
    limit_reached = true;
  }

  return limit_reached;
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

int read_float(InputStr* source, long double* dest_input_pointer,
               SpecOptions* spec_opts) {
  int sign = 1;
  long double int_part = 0;
  long double frac_part = 0.0;
  long long frac_div = 1;
  bool weve_read_at_least_once_successfully = 0;
  s21_size_t bytes_read = 0;
  s21_size_t base = 10;
  if (source->str[source->curr_ind] == '-') {
    sign = -1;
    source->curr_ind++;
    bytes_read++;
  }

  while (is_valid_digit(source->str[source->curr_ind], base) &&
         is_space(source->str[source->curr_ind]) == false &&
         source->str[source->curr_ind] != '\0' &&
         width_limit_reached(bytes_read, spec_opts) == false) {
    int_part = int_part * 10 + (source->str[source->curr_ind] - '0');
    source->curr_ind++;
    bytes_read++;
    weve_read_at_least_once_successfully = true;
  }

  if (source->str[source->curr_ind] == '.') {
    bytes_read++;
    source->curr_ind++;
    while (is_valid_digit(source->str[source->curr_ind], base) &&
           is_space(source->str[source->curr_ind]) == false &&
           source->str[source->curr_ind] != '\0' &&
           width_limit_reached(bytes_read, spec_opts) == false) {
      frac_part = frac_part * 10 + (source->str[source->curr_ind] - '0');
      frac_div *= 10;
      source->curr_ind++;
      bytes_read++;
    }
  }

  if (bytes_read > 0) {
    weve_read_at_least_once_successfully = true;
    *dest_input_pointer = sign * (int_part + (frac_part / frac_div));
  }

  return weve_read_at_least_once_successfully;
}

s21_size_t get_octal_num_length(InputStr* source, SpecOptions* spec_opts,
                                s21_size_t base) {
  int num_len_result = 0;
  int temp_curr_ind = source->curr_ind;
  s21_size_t bytes_read = 0;

  while (is_space(source->str[temp_curr_ind]) == false &&
         source->str[temp_curr_ind] != '\0' &&
         width_limit_reached(bytes_read, spec_opts) == false &&
         is_valid_digit(source->str[temp_curr_ind], base)) {
    num_len_result++;
    temp_curr_ind++;
    bytes_read++;
  }
  // -1 because it is used for power of 8s later, ending with zero
  return num_len_result - 1;
}

bool is_valid_digit(char incoming_char, s21_size_t base) {
  bool char_is_valid = false;
  incoming_char = to_lower_char(incoming_char);
  // printf("\n\n\n\n%c\n\n\n\n", incoming_char);
  const char* digits = "0123456789abcdef";
  for (s21_size_t i = 0; i < base && char_is_valid == false; i++) {
    if (incoming_char == digits[i]) {
      char_is_valid = true;
    }
  }
  return char_is_valid;
}

char to_lower_char(char incoming_char) {
  char temp_incoming_char;
  if (incoming_char >= 'A' && incoming_char <= 'Z') {
    temp_incoming_char = incoming_char + ('a' - 'A');
  } else {
    temp_incoming_char = incoming_char;
  }
  return temp_incoming_char;
}

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

bool n_specifier_follows(InputStr* fmt_input) {
  bool it_follows = false;
  s21_size_t fmt_characters_remaining =
      s21_strlen(fmt_input->str) - fmt_input->curr_ind;

  if (fmt_characters_remaining >= 2) {
    if (s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%n", 2) == 0) {
      it_follows = true;
    }
  }
  if (fmt_characters_remaining >= 3) {
    if (s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%*n", 3) == 0) {
      it_follows = true;
    }
  }
  return it_follows;
}

bool is_n_star_present(InputStr* fmt_input) {
  bool star_present = false;
  s21_size_t fmt_characters_remaining =
      s21_strlen(fmt_input->str) - fmt_input->curr_ind;

  if (fmt_characters_remaining >= 3) {
    if (s21_strncmp(&fmt_input->str[fmt_input->curr_ind], "%*n", 3) == 0) {
      star_present = true;
    }
  }

  return star_present;
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
  if (is_end_of_string(fmt_input) == false && *matching_failure == false) {
    printf("\n\ncurr ind %lu\n", source->curr_ind);
    we_continue = true;
    // if (is_end_of_string(source) == false || is_space_specifier(fmt_input)) {
    //   we_continue = true;
    // } else {
    //   we_continue =
    //       n_specifier_follows(fmt_input) || c_specifier_follows(fmt_input);
    // }
  }
  return we_continue;
}

void consume_space(InputStr* source, InputStr* fmt_input,
                   bool increment_format_index) {
  while (is_space(source->str[source->curr_ind])) {
    source->curr_ind++;
  }
  if (increment_format_index == true) {
    fmt_input->curr_ind++;
  }
}

void consume_initial_space_and_n(va_list* args, InputStr* source,
                                 InputStr* fmt_input) {
  while (n_specifier_follows(fmt_input) || is_space_specifier(fmt_input)) {
    if (is_space_specifier(fmt_input)) {
      consume_space(source, fmt_input, true);
    } else if (n_specifier_follows(fmt_input)) {
      bool n_star_present = is_n_star_present(fmt_input);
      process_n(args, source, n_star_present);
      if (n_star_present) {
        fmt_input->curr_ind += 3;
      } else {
        fmt_input->curr_ind += 2;
      }
    }
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

// void set_sscanf_base(SpecOptions* spec_opts) {
//   if (spec_opts->specifier == o) {
//     spec_opts->base = 8;
//   } else if (spec_opts->is_hexadecimal) {
//     spec_opts->base = 16;
//   } else {
//     spec_opts->base = 10;
//   }
// }

void parse_sscanf_specifier(InputStr* fmt_input, SpecOptions* spec_opts) {
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
        spec_opts->is_hexadecimal = true;
        break;
      }
      case 'o': {
        spec_opts->specifier = o;
        break;
      }
    }
  }
}

void parse_width_sscanf(InputStr* fmt_input, SpecOptions* spec_opts) {
  while (is_valid_digit(fmt_input->str[fmt_input->curr_ind], 10)) {
    spec_opts->width =
        spec_opts->width * 10 + (fmt_input->str[fmt_input->curr_ind] - '0');
    fmt_input->curr_ind++;
    spec_opts->width_set = true;
  }
}

bool is_length_sscanf(char ch) {
  char* res = s21_strchr(VALID_SSCANF_LENGTHS, ch);
  return res == S21_NULL ? false : true;
}

void parse_length_sscanf(InputStr* fmt_input, SpecOptions* spec_opts) {
  if (is_length_sscanf(fmt_input->str[fmt_input->curr_ind])) {
    switch (fmt_input->str[fmt_input->curr_ind]) {
      case 'L':
        spec_opts->length = L;
        break;
      case 'l':
        spec_opts->length = l;
        break;
      case 'h':
        spec_opts->length = h;
        break;
    }
    fmt_input->curr_ind++;
  }
}

//   *value = (void*)ptr_value;
//   return res;  // Success
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