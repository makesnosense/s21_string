#include "s21_sscanf.h"

int s21_sscanf(const char* str, const char* format, ...) {
  set_locale_for_wide_chars();
  bool matching_failure = false;
  int result = 0;
  va_list args;
  va_start(args, format);

  InputStr source = {str, 0};
  InputStr fmt_input = {format, 0};
  process_initial_space_and_n(&args, &source, &fmt_input);

  while (we_continue_processing(&fmt_input, &matching_failure)) {
    if (is_space_specifier(&fmt_input)) {
      process_space(&source, &fmt_input);
    } else if (fmt_input.str[fmt_input.curr_ind] == '%') {
      process_specifier(&result, &args, &source, &fmt_input, &matching_failure);
    } else {
      process_foreign_char_in_format(&source, &fmt_input, &matching_failure);
    }
  }
  va_end(args);
  return result;
}

static void process_initial_space_and_n(va_list* args, InputStr* source,
                                        InputStr* fmt_input) {
  while (n_specifier_follows(fmt_input) || is_space_specifier(fmt_input)) {
    if (is_space_specifier(fmt_input)) {
      process_space(source, fmt_input);
    } else {
      process_n(args, source);
      fmt_input->curr_ind += 2;
    }
  }
}

static bool we_continue_processing(InputStr* fmt_input,
                                   bool* matching_failure) {
  bool we_continue = false;
  if (is_end_of_string(fmt_input) == false && *matching_failure == false) {
    we_continue = true;
  }
  return we_continue;
}

static void process_foreign_char_in_format(InputStr* source,
                                           InputStr* fmt_input,
                                           bool* matching_failure) {
  if (fmt_input->str[fmt_input->curr_ind] != source->str[source->curr_ind]) {
    *matching_failure = true;
  } else {
    fmt_input->curr_ind++;
    source->curr_ind++;
  }
}

static void process_specifier(int* sscanf_result, va_list* args,
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
    consume_space(source);
  } else {
    fmt_input->curr_ind++;
    *sscanf_result +=
        consume_specifier(args, source, fmt_input, matching_failure);
    fmt_input->curr_ind++;
  }
}

static void parse_format(InputStr* fmt_input, SpecOptions* spec_opts) {
  spec_opts->is_star = parse_suppression(fmt_input);
  parse_width(fmt_input, spec_opts);
  parse_length(fmt_input, spec_opts);
  parse_specifier(*fmt_input, spec_opts);
  read_next_digit_in_fmt(*fmt_input, spec_opts);
}

static int consume_specifier(va_list* args, InputStr* source,
                             InputStr* fmt_input, bool* matching_failure) {
  int specifier_result = 0;
  SpecOptions spec_opts = {0};
  parse_format(fmt_input, &spec_opts);
  switch (fmt_input->str[fmt_input->curr_ind]) {
    case 'c': {
      specifier_result = process_chars(args, source, &spec_opts);
      break;
    }
    case 'n': {
      process_n(args, source);
      break;
    }
    case 's': {
      specifier_result = process_strings(args, source, &spec_opts);
      break;
    }
    case 'p': {
      specifier_result = read_pointer(args, source, &spec_opts);
      break;
    }
    case 'i':
    case 'd': {
      specifier_result =
          process_int(args, &spec_opts, source, matching_failure);
      break;
    }
    case 'x':
    case 'X':
    case 'o':
    case 'u': {
      specifier_result =
          process_unsigned(args, &spec_opts, source, matching_failure);
      break;
    }
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'f': {
      specifier_result = process_float(args, &spec_opts, source);
      break;
    }
    case '%': {
      process_percent(source);
      break;
    }
  }
  return specifier_result;
}

static void process_percent(InputStr* source) {
  if (source->str[source->curr_ind] == '%') {
    source->curr_ind++;
  }
}

static int read_pointer(va_list* args, InputStr* source,
                        SpecOptions* spec_opts) {
  bool weve_read_at_least_once_successfully = 0;
  unsigned long long ptr_value = 0;
  s21_size_t bytes_read = 0;

  while (is_space(source->str[source->curr_ind]) == true) {
    source->curr_ind++;
  }

  if (hexadecimal_prefix_follows(source)) {
    source->curr_ind += 2;
    bytes_read += 2;
  }

  while (isxdigit(source->str[source->curr_ind]) &&
         width_limit_reached(bytes_read, spec_opts) == false) {
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
    bytes_read++;
    weve_read_at_least_once_successfully = true;
  }

  if (spec_opts->is_star == false && bytes_read > 0) {
    void** dest_input_pointer = va_arg(*args, void**);
    *dest_input_pointer = (void*)ptr_value;
  }
  return spec_opts->is_star == false ? weve_read_at_least_once_successfully : 0;
}

static int process_strings(va_list* args, InputStr* source,
                           SpecOptions* spec_opts) {
  bool weve_read_at_least_once_successfully = 0;

  if (spec_opts->length == l) {
    weve_read_at_least_once_successfully =
        read_wide_string(args, source, spec_opts);
  } else {
    weve_read_at_least_once_successfully =
        read_narrow_string(args, source, spec_opts);
  }

  return weve_read_at_least_once_successfully;
}

static int read_wide_string(va_list* args, InputStr* source,
                            SpecOptions* spec_opts) {
  bool weve_read_at_least_once_successfully = false;
  wchar_t* dest_wide_string_pointer = va_arg(*args, wchar_t*);

  s21_size_t multibyte_length = 0;
  s21_size_t char_count = 0;
  s21_size_t start_index = source->curr_ind;
  mbstate_t state = {0};

  bool should_continue = true;
  while (should_continue &&
         (width_limit_reached(char_count, spec_opts) == false) &&
         source->str[start_index + multibyte_length] != '\0') {
    wchar_t wide_char;
    s21_size_t result =
        mbrtowc(&wide_char, &source->str[start_index + multibyte_length],
                MB_CUR_MAX, &state);

    if (iswspace(wide_char)) {
      should_continue = false;
    } else {
      multibyte_length += result;
      char_count++;
    }
  }
  char* temp_buffer = (char*)malloc(multibyte_length + 1);
  s21_strncpy(temp_buffer, &source->str[start_index], multibyte_length);
  temp_buffer[multibyte_length] = '\0';
  s21_size_t wide_len =
      mbstowcs(dest_wide_string_pointer, temp_buffer, char_count);

  free(temp_buffer);
  dest_wide_string_pointer[wide_len] = L'\0';
  source->curr_ind += multibyte_length;

  if (wide_len > 0) {
    weve_read_at_least_once_successfully = true;
  }
  return weve_read_at_least_once_successfully;
}

static int read_narrow_string(va_list* args, InputStr* source,
                              SpecOptions* spec_opts) {
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

static bool is_inf(InputStr* source) {
  bool result = false;
  if (s21_strncmp(source->str + source->curr_ind, "inf", 3) == 0 ||
      s21_strncmp(source->str + source->curr_ind, "INF", 3) == 0) {
    result = true;
  }
  return result;
}

static bool is_nan(InputStr* source) {
  bool result = false;
  if (s21_strncmp(source->str + source->curr_ind, "nan", 3) == 0 ||
      s21_strncmp(source->str + source->curr_ind, "NaN", 3) == 0) {
    result = true;
  }
  return result;
}

static int process_float(va_list* args, SpecOptions* spec_opts,
                         InputStr* source) {
  int read_result = 0;
  long double temp_floating_destination = 0;

  if (source->str[source->curr_ind] == '-') {
    spec_opts->is_negative = true;
    source->curr_ind++;
  } else if (source->str[source->curr_ind] == '+') {
    spec_opts->plus_sign_present = true;
    source->curr_ind++;
  }

  if (is_inf(source) || is_nan(source)) {
    float* dest_input_pointer = va_arg(*args, float*);
    float temp_small_floating_destination = 0;

    if (is_inf(source)) {
      temp_small_floating_destination =
          spec_opts->is_negative ? -INFINITY : INFINITY;
    } else {
      temp_small_floating_destination = spec_opts->is_negative ? -NAN : NAN;
    }
    if (spec_opts->is_star == false) {
      *dest_input_pointer = temp_small_floating_destination;
      read_result = true;
    }

  } else {
    read_result = read_float(source, &temp_floating_destination, spec_opts);
    write_to_floating_point_number_pointer(args, spec_opts,
                                           temp_floating_destination);
  }

  return spec_opts->is_star == false ? read_result : 0;
}

static int read_whole_part(InputStr* source, long double* int_part,
                           s21_size_t* bytes_read, SpecOptions* spec_opts) {
  s21_size_t base = 10;
  *int_part = 0;
  int digits_read = 0;

  while (is_valid_digit(source->str[source->curr_ind], base) &&
         !is_space(source->str[source->curr_ind]) &&
         source->str[source->curr_ind] != '\0' &&
         !width_limit_reached(*bytes_read, spec_opts)) {
    *int_part = *int_part * 10 + (source->str[source->curr_ind] - '0');
    source->curr_ind++;
    (*bytes_read)++;
    digits_read++;
  }

  return digits_read;
}

static int read_fractional_part(InputStr* source, long double* frac_part,
                                long long* frac_div, s21_size_t* bytes_read,
                                SpecOptions* spec_opts) {
  s21_size_t base = 10;
  *frac_part = 0.0;
  *frac_div = 1;
  int digits_read = 0;

  if (source->str[source->curr_ind] == '.') {
    (*bytes_read)++;
    source->curr_ind++;
    while (is_valid_digit(source->str[source->curr_ind], base) &&
           !is_space(source->str[source->curr_ind]) &&
           source->str[source->curr_ind] != '\0' &&
           !width_limit_reached(*bytes_read, spec_opts)) {
      *frac_part = *frac_part * 10 + (source->str[source->curr_ind] - '0');
      *frac_div *= 10;
      source->curr_ind++;
      (*bytes_read)++;
      digits_read++;
    }
  }

  return digits_read;
}

static int read_exponent(InputStr* source, int* exponent, int* exponent_sign,
                         s21_size_t* bytes_read, SpecOptions* spec_opts) {
  s21_size_t base = 10;
  *exponent = 0;
  *exponent_sign = 1;
  int digits_read = 0;

  if ((source->str[source->curr_ind] == 'e' ||
       source->str[source->curr_ind] == 'E') &&
      !width_limit_reached(*bytes_read, spec_opts)) {
    source->curr_ind++;
    (*bytes_read)++;

    if (source->str[source->curr_ind] == '-') {
      *exponent_sign = -1;
      source->curr_ind++;
      (*bytes_read)++;
    } else if (source->str[source->curr_ind] == '+') {
      source->curr_ind++;
      (*bytes_read)++;
    }

    while (is_valid_digit(source->str[source->curr_ind], base) &&
           !is_space(source->str[source->curr_ind]) &&
           source->str[source->curr_ind] != '\0' &&
           !width_limit_reached(*bytes_read, spec_opts)) {
      *exponent = *exponent * 10 + (source->str[source->curr_ind] - '0');
      source->curr_ind++;
      (*bytes_read)++;
      digits_read++;
    }
  }

  return digits_read;
}

static int read_float(InputStr* source, long double* dest_input_pointer,
                      SpecOptions* spec_opts) {
  int sign = spec_opts->is_negative ? -1 : 1;
  long double whole_part = 0;
  long double fraction_part = 0.0;
  long long fraction_divisor = 1;
  int exponent = 0;
  int exponent_sign = 1;
  s21_size_t bytes_read = 0;
  bool weve_read_at_least_once_successfully = false;

  int wholepart_digits =
      read_whole_part(source, &whole_part, &bytes_read, spec_opts);
  int fraction_part_digits = read_fractional_part(
      source, &fraction_part, &fraction_divisor, &bytes_read, spec_opts);
  int exponent_digits =
      read_exponent(source, &exponent, &exponent_sign, &bytes_read, spec_opts);

  if (wholepart_digits + fraction_part_digits + exponent_digits > 0) {
    weve_read_at_least_once_successfully = true;
    long double mantissa = whole_part + (fraction_part / fraction_divisor);
    *dest_input_pointer = sign * mantissa * powl(10, exponent_sign * exponent);
  }

  return weve_read_at_least_once_successfully;
}

static void write_to_floating_point_number_pointer(
    va_list* args, SpecOptions* spec_opts,
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

static void read_next_digit_in_fmt(InputStr fmt_input, SpecOptions* spec_opts) {
  if (fmt_input.str[fmt_input.curr_ind + 1] != '\0') {
    spec_opts->next_digit = fmt_input.str[fmt_input.curr_ind + 1];
  }
}

static void process_n(va_list* args, InputStr* source) {
  int* num = va_arg(*args, int*);
  *num = source->curr_ind;
}

static int process_unsigned(va_list* args, SpecOptions* spec_opts,
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

static void write_to_unsigned_pointer(
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

static int process_int(va_list* args, SpecOptions* spec_opts, InputStr* source,
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

static void write_to_integer_pointer(
    va_list* args, SpecOptions* spec_opts,
    long long unsigned temp_unsigned_destination, int sign) {
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

static bool hexadecimal_prefix_follows(InputStr* source) {
  bool hexadecimal_prefix_follows = false;
  if ((s21_strncmp(&source->str[source->curr_ind], "0x", 2) == 0 ||
       s21_strncmp(&source->str[source->curr_ind], "0X", 2) == 0)) {
    hexadecimal_prefix_follows = true;
  }
  return hexadecimal_prefix_follows;
}

static int read_hex(InputStr* source, SpecOptions* spec_opts,
                    long long unsigned* dest_input_pointer,
                    bool* matching_failure) {
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

static int read_decimal(InputStr* source, SpecOptions* spec_opts,
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

static int read_octal(InputStr* source, SpecOptions* spec_opts,
                      long long unsigned* dest_input_pointer,
                      bool* matching_failure) {
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

static bool width_limit_reached(s21_size_t bytes_read, SpecOptions* spec_opts) {
  bool limit_reached = false;
  s21_size_t limit = spec_opts->width;
  if (spec_opts->is_negative || spec_opts->plus_sign_present) {
    limit -= 1;
  }

  if (spec_opts->width_set == true && bytes_read >= limit) {
    limit_reached = true;
  }
  return limit_reached;
}

static int process_chars(va_list* args, InputStr* source,
                         SpecOptions* spec_opts) {
  int specifier_result = 0;
  if (spec_opts->length == l) {
    specifier_result = read_wide_char(args, source, spec_opts);
  } else {
    specifier_result = read_narrow_char(args, source, spec_opts);
  }
  return specifier_result;
}

static int read_wide_char(va_list* args, InputStr* source,
                          SpecOptions* spec_opts) {
  int read_result = 0;
  wchar_t* dest_wchar_ptr = va_arg(*args, wchar_t*);
  wchar_t wide_char = 0;
  int len = mbtowc(&wide_char, &source->str[source->curr_ind], MB_CUR_MAX);

  if (len > 0) {
    *dest_wchar_ptr = wide_char;
    source->curr_ind += len;
    read_result++;
  }
#if defined(__APPLE__)
  if (len == -1) {
    source->curr_ind++;
  }
#endif

  return read_result;
};

static int read_narrow_char(va_list* args, InputStr* source,
                            SpecOptions* spec_opts) {
  int read_result = 0;
  if (spec_opts->is_star == false) {
    char* dest_char_ptr = va_arg(*args, char*);
    *dest_char_ptr = source->str[source->curr_ind];
    read_result++;
  }
  source->curr_ind++;
  return read_result;
};

static s21_size_t get_octal_num_length(InputStr* source, SpecOptions* spec_opts,
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

static bool is_valid_digit(char incoming_char, s21_size_t base) {
  bool char_is_valid = false;
  incoming_char = to_lower_char(incoming_char);
  const char* digits = "0123456789abcdef";
  for (s21_size_t i = 0; i < base && char_is_valid == false; i++) {
    if (incoming_char == digits[i]) {
      char_is_valid = true;
    }
  }
  return char_is_valid;
}

static char to_lower_char(char incoming_char) {
  char temp_incoming_char;
  if (incoming_char >= 'A' && incoming_char <= 'Z') {
    temp_incoming_char = incoming_char + ('a' - 'A');
  } else {
    temp_incoming_char = incoming_char;
  }
  return temp_incoming_char;
}

static bool n_specifier_follows(InputStr* fmt_input) {
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

static bool c_specifier_follows(InputStr* fmt_input) {
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

static bool is_end_of_string(InputStr* string_structure) {
  return string_structure->str[string_structure->curr_ind] == '\0';
}

static bool is_space(char input_char) {
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

static bool is_space_specifier(InputStr* fmt_input) {
  return is_space(fmt_input->str[fmt_input->curr_ind]);
}

static void process_space(InputStr* source, InputStr* fmt_input) {
  consume_space(source);
  fmt_input->curr_ind++;
}

static void consume_space(InputStr* source) {
  while (is_space(source->str[source->curr_ind])) {
    source->curr_ind++;
  }
}

static bool parse_suppression(InputStr* fmt_input) {
  bool star_present = false;
  if (fmt_input->str[fmt_input->curr_ind] == '*') {
    star_present = true;
    fmt_input->curr_ind++;
  }
  return star_present;
}

static bool is_specifier(char ch) {
  char* res = s21_strchr(VALID_SSCANF_SPECIFIERS, ch);
  return res != S21_NULL;
}

static void parse_specifier(InputStr fmt_input, SpecOptions* spec_opts) {
  if (is_specifier(fmt_input.str[fmt_input.curr_ind])) {
    char current_specifier = fmt_input.str[fmt_input.curr_ind];
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
      case 'e':
      case 'E': {
        spec_opts->is_scientific = true;
        break;
      }
    }
  }
}

static void parse_width(InputStr* fmt_input, SpecOptions* spec_opts) {
  while (is_valid_digit(fmt_input->str[fmt_input->curr_ind], 10)) {
    spec_opts->width =
        spec_opts->width * 10 + (fmt_input->str[fmt_input->curr_ind] - '0');
    fmt_input->curr_ind++;
    spec_opts->width_set = true;
  }
}

static bool is_length(char ch) {
  char* res = s21_strchr(VALID_SSCANF_LENGTHS, ch);
  return res == S21_NULL ? false : true;
}

static void parse_length(InputStr* fmt_input, SpecOptions* spec_opts) {
  char current_format_char = fmt_input->str[fmt_input->curr_ind];

  if (is_length(current_format_char)) {
    if (current_format_char == 'L') {
      spec_opts->length = L;
    } else if (current_format_char == 'l') {
      spec_opts->length = l;
    } else {
      spec_opts->length = h;
    }
    fmt_input->curr_ind++;
  }
}

static void set_locale_for_wide_chars() {
#if defined(__APPLE__)
  setlocale(LC_ALL, "en_US.UTF-8");

#elif defined(__linux__)
  setlocale(LC_ALL, "C.UTF-8");

#endif
}
