#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  set_locale_for_wide_chars();
  DestStr dest = {str, 0};
  SpecOptions spec_opts = {0};
  va_list args;
  va_start(args, format);
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      s21_memset(&spec_opts, 0, sizeof(spec_opts));
      parse_format(&format, args, &spec_opts);
      set_base(&spec_opts);
      set_padding_char(&spec_opts);
      set_exponent_char(&spec_opts);
      process_specifier(*format, &args, &dest, &spec_opts);
    } else {
      dest.str[dest.curr_ind++] = *format;
    }
    format++;
  }
  dest.str[dest.curr_ind] = '\0';
  va_end(args);
  return dest.curr_ind;
}

void parse_format(const char** format, va_list args, SpecOptions* spec_opts) {
  parse_flags(format, spec_opts);
  parse_width(format, args, spec_opts);
  parse_precision(format, args, spec_opts);
  parse_length(format, spec_opts);
  parse_specifier(format, spec_opts);
}

int is_flag(char ch) {
  char* res = s21_strchr(VALID_FLAGS, ch);
  return res == S21_NULL ? 0 : 1;
}

int is_specifier(char ch) {
  char* res = s21_strchr(VALID_SPECIFIERS, ch);
  return res == S21_NULL ? 0 : 1;
}

int is_length(char ch) {
  char* res = s21_strchr(VALID_LENGTHS, ch);
  return res == S21_NULL ? 0 : 1;
}

void parse_flags(const char** format, SpecOptions* spec_opts) {
  while (is_flag(**format)) {
    if (**format == '+') {
      spec_opts->flag_plus = true;
    } else if (**format == '-') {
      spec_opts->flag_minus = true;
      spec_opts->flag_zero = false;
    } else if (**format == ' ') {
      spec_opts->flag_space = true;
    } else if (**format == '0') {
      spec_opts->flag_zero = true;
    } else {  // scary as hell, but we check validity of flags in is_flag above
      spec_opts->flag_sharp = true;
    }
    (*format)++;
  }
}

void parse_width(const char** format, va_list args, SpecOptions* spec_opts) {
  while (**format != '.' && !is_specifier(**format) && !is_length(**format)) {
    if (isdigit(**format)) {
      spec_opts->width = spec_opts->width * 10 + (**format - '0');
    } else if (**format == '*') {
      spec_opts->width = va_arg(args, int);
    }
    (*format)++;
  }
}

void parse_precision(const char** format, va_list args,
                     SpecOptions* spec_opts) {
  while (!is_specifier(**format) && !is_length(**format)) {
    if (isdigit(**format)) {
      spec_opts->precision = spec_opts->precision * 10 + (**format - '0');
      spec_opts->precision_set = 1;
    } else if (**format == '*') {
      spec_opts->precision = va_arg(args, int);
      spec_opts->precision_set = 1;
    } else if (**format == '.') {
      spec_opts->precision_set = 1;
    }
    (*format)++;
  }
}

void parse_length(const char** format, SpecOptions* spec_opts) {
  while (is_length(**format)) {
    switch (**format) {
      case 'L':
        spec_opts->length_big_l = 1;
        break;
      case 'l':
        spec_opts->length_l = 1;
        break;
      case 'h':
        spec_opts->length_h = 1;
        break;
    }
    (*format)++;
  }
}

void parse_specifier(const char** format, SpecOptions* spec_opts) {
  if (is_specifier(**format)) {
    int current_specifier = **format;
    switch (current_specifier) {
      case 'c': {
        spec_opts->specifier = c;
        break;
      }
      case 'X':
      case 'p':
      case 'x': {
        if (current_specifier == 'X') {
          spec_opts->specifier = X;
        } else if (current_specifier == 'x') {
          spec_opts->specifier = x;
        } else {
          spec_opts->specifier = p;
        }
        spec_opts->is_hexadecimal = true;
        break;
      }
      case 'o': {
        spec_opts->specifier = o;
        break;
      }
      case 'f':
      case 'g':
      case 'G':
      case 'e':
      case 'E': {
        spec_opts->is_floating_point_number = true;
        if (current_specifier == 'g') {
          spec_opts->specifier = g;
          spec_opts->is_g_spec = true;
        } else if (current_specifier == 'G') {
          spec_opts->specifier = G;
          spec_opts->is_g_spec = true;
        } else if (current_specifier == 'e') {
          spec_opts->specifier = e;
          spec_opts->is_scientific = true;
        } else if (current_specifier == 'E') {
          spec_opts->specifier = E;
          spec_opts->is_scientific = true;
        }
        break;
      }
    }
  }
}

void process_specifier(char format_char, va_list* args, DestStr* dest,
                       SpecOptions* spec_opts) {
  switch (format_char) {
    case 'c': {
      process_chars(args, dest, spec_opts);
      break;
    }
    case 's': {
      process_strings(args, dest, spec_opts);
      break;
    }
    case 'i':
    case 'd': {
      process_int(args, dest, spec_opts);
      break;
    }
    case 'x':
    case 'X':
    case 'o':
    case 'u': {
      process_unsigned(args, dest, spec_opts);
      break;
    }
    case 'n': {
      int* counter_n = va_arg(*args, int*);
      *counter_n = s21_strlen(dest->str);
      break;
    }
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G': {
      process_floating_point_number(args, dest, spec_opts);
      break;
    }
    case 'p': {
      process_pointer(args, dest, spec_opts);
      break;
    }
    case '%': {
      dest->str[dest->curr_ind++] = '%';
      break;
    }
    default:
      break;
  }
}

void process_pointer(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  void* pointer_str_input = va_arg(*args, void*);
#if defined(__linux__)
  if (pointer_str_input == 0x0)
    process_narrow_string("(nil)", dest, spec_opts);
  else
    pointer_to_str(dest, pointer_str_input, spec_opts);
#else
  pointer_to_str(dest, pointer_str_input, spec_opts);
#endif
}

void process_chars(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  if (spec_opts->length_l == false) {
    process_narrow_char(args, dest, spec_opts);
  } else {
    process_wide_char(args, dest, spec_opts);
  }
}

void process_narrow_char(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  char input_char = va_arg(*args, int);
  int num_len = get_num_length(input_char, spec_opts);
  // Если ширина больше длины числа, добавляем пробелы в начало
  calculate_padding(num_len, spec_opts);
  apply_width(dest, num_len, spec_opts);
  // Обрабатываем флаги
  apply_flags(dest, spec_opts);
  dest->str[dest->curr_ind++] = input_char;
  apply_minus_width(dest, spec_opts);
}

void process_wide_char(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  wchar_t input_char = va_arg(*args, wchar_t);
  char temp[MB_CUR_MAX];
  int len = wctomb(temp, input_char);
  calculate_padding(len, spec_opts);
  apply_width(dest, len, spec_opts);
  apply_flags(dest, spec_opts);
  if (len > 0) {
    for (int i = 0; i < len; i++) {
      dest->str[dest->curr_ind++] = temp[i];
    }
  }
  apply_minus_width(dest, spec_opts);
}

void process_int(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  long long int input_int = ingest_int(args, spec_opts);

  is_negative(input_int, spec_opts);
  whole_to_str(dest, input_int, spec_opts);
}

void process_floating_point_number(va_list* args, DestStr* dest,
                                   SpecOptions* spec_opts) {
  long double input_floating_point_number =
      ingest_floating_point_number(args, spec_opts);
  is_negative(input_floating_point_number, spec_opts);

  if (isnan(input_floating_point_number)) {
    spec_opts->is_floating_point_number = false;
#if defined(__linux__)
    spec_opts->is_negative = signbit(input_floating_point_number);
#endif
    if (spec_opts->specifier == G || spec_opts->specifier == E) {
      process_narrow_string("NAN", dest, spec_opts);
    } else {
      process_narrow_string("nan", dest, spec_opts);
    }
  } else if (isinf(input_floating_point_number)) {
    spec_opts->is_floating_point_number = false;
    if (spec_opts->specifier == G || spec_opts->specifier == E) {
      process_narrow_string("INF", dest, spec_opts);
    } else {
      process_narrow_string("inf", dest, spec_opts);
    }
  } else if (spec_opts->is_scientific) {
    process_scientific(dest, input_floating_point_number, spec_opts);
  } else if (spec_opts->is_g_spec) {
    process_g_spec(dest, input_floating_point_number, spec_opts);
  } else {
    floating_point_number_to_str(dest, input_floating_point_number, spec_opts);
  }
}

void process_unsigned(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  unsigned long input_unsingned = 0;
  input_unsingned = ingest_unsinged(args, spec_opts);
  whole_to_str(dest, input_unsingned, spec_opts);
}

void process_strings(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  if (spec_opts->length_l == false) {
    char* input_string = va_arg(*args, char*);
    process_narrow_string(input_string, dest, spec_opts);
  } else {
    process_wide_string(args, dest, spec_opts);
  }
}

void process_narrow_string(char* input_string, DestStr* dest,
                           SpecOptions* spec_opts) {
  s21_size_t string_length = s21_strlen(input_string);
  calculate_padding(string_length, spec_opts);
  apply_width(dest, string_length, spec_opts);
  apply_flags(dest, spec_opts);
  s21_strcpy(dest->str + dest->curr_ind, input_string);
  dest->curr_ind += s21_strlen(input_string);
  apply_minus_width(dest, spec_opts);
}

void process_wide_string(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  wchar_t* input_string = va_arg(*args, wchar_t*);
  s21_size_t len = wcstombs(NULL, input_string, 0);
  calculate_padding(len, spec_opts);
  apply_width(dest, len, spec_opts);
  apply_flags(dest, spec_opts);
  if (len != (size_t)-1) {
    char* temp_str = (char*)malloc(len + 1);
    if (temp_str) {
      wcstombs(temp_str, input_string, len + 1);
      s21_strcpy(dest->str + dest->curr_ind, temp_str);
      dest->curr_ind += len;
      free(temp_str);
    }
  }
  apply_minus_width(dest, spec_opts);
}

long long int ingest_int(va_list* args, SpecOptions* spec_opts) {
  long long int input_int = 0;
  long long int absolute_input = 0;
  if (spec_opts->length_h) {  // обрабатываем short
    input_int = va_arg(*args, int);
    absolute_input = TO_ABS(input_int);
    if (absolute_input > SHRT_MAX) {
      input_int = (short)+(input_int);
    }
  } else if (spec_opts->length_l) {  // обрабатываем long
    absolute_input = TO_ABS(input_int);
    input_int = va_arg(*args, long int);
    if (absolute_input > LONG_MAX) {
      input_int = (long)+(input_int);
    }
  } else {  // обрабатываем простой int
    input_int = va_arg(*args, int);
    absolute_input = TO_ABS(input_int);
    if (absolute_input > INT_MAX) {
      input_int = (int)+(input_int);
    }
  }
  return input_int;
}

long double ingest_floating_point_number(va_list* args,
                                         SpecOptions* spec_opts) {
  long double input_floating_point_number = 0;
  if (spec_opts->length_big_l) {
    input_floating_point_number = va_arg(*args, long double);
  } else {
    input_floating_point_number = va_arg(*args, double);
  }
  spec_opts->is_zero = is_zero(input_floating_point_number);
  return input_floating_point_number;
}

long long unsigned ingest_unsinged(va_list* args, SpecOptions* spec_opts) {
  long long unsigned input_unsingned = 0;

  if (spec_opts->length_h) {  // обрабатываем short
    input_unsingned = va_arg(*args, unsigned);
    if (input_unsingned > USHRT_MAX) {
      input_unsingned = (short unsigned)+(input_unsingned);
    }
  } else if (spec_opts->length_l) {  // обрабатываем long
    input_unsingned = va_arg(*args, long unsigned);
  } else {
    input_unsingned = va_arg(*args, unsigned);
    if (input_unsingned > UINT_MAX) {
      input_unsingned = (unsigned)+(input_unsingned);
    }
  }
  spec_opts->is_zero = is_zero(input_unsingned);
  return input_unsingned;
}

void set_base(SpecOptions* spec_opts) {
  if (spec_opts->specifier == o) {
    spec_opts->base = 8.0;
  } else if (spec_opts->is_hexadecimal) {
    spec_opts->base = 16.0;
  } else {
    spec_opts->base = 10.0;
  }
}

void set_padding_char(SpecOptions* spec_opts) {
  if (spec_opts->flag_zero) {
    spec_opts->padding_char = '0';
  } else {
    spec_opts->padding_char = ' ';
  }
}

void set_exponent_char(SpecOptions* spec_opts) {
  if (spec_opts->specifier == e || spec_opts->specifier == g) {
    spec_opts->exponent_char = 'e';
  } else if (spec_opts->specifier == E || spec_opts->specifier == G) {
    spec_opts->exponent_char = 'E';
  }
}

void is_negative(long double num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0.0 ? 1 : 0;
}

// length is 1 for (num >= 0 && num < 1)
s21_size_t get_num_length(long double num, SpecOptions* spec_opts) {
  int num_len = 0;

  if ((num >= 0 && num < 1) || spec_opts->specifier == c) {
    num_len++;
  } else {
    while (num >= 1) {
      num_len++;
      num /= spec_opts->base;
    }
  }
  return num_len;
}

long double multiply_by_10_n_times(long double input_num, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    input_num *= 10;
  }
  return input_num;
}

long double divide_by_10_n_times(long double input_num, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    input_num /= 10;
  }
  return input_num;
}

void add_zeros_to_destination(DestStr* dest, s21_size_t n_zeros_to_add) {
  for (s21_size_t i = 0; i < n_zeros_to_add; i++) {
    dest->str[dest->curr_ind++] = '0';
  }
  dest->str[dest->curr_ind] = '\0';
}

void calculate_padding(s21_size_t num_len, SpecOptions* spec_opts) {
  if (spec_opts->is_g_spec || spec_opts->is_scientific) {
    calculate_padding_ge_spec(num_len, spec_opts);
  } else {
    calculate_padding_not_ge_spec(num_len, spec_opts);
  }
}

void calculate_padding_not_ge_spec(s21_size_t num_len, SpecOptions* spec_opts) {
  int flag_corr = 0;  // Коррекция кол-ва пробелов
  int prec_corr = 0;  // Коррекция кол-ва пробелов
  int sharp_corr = 0;

  int padding_to_add = 0;

  // sharp correction
  if (spec_opts->flag_sharp) {
    if (spec_opts->is_hexadecimal && spec_opts->is_zero == false) {
      sharp_corr = 2;
    } else if (spec_opts->specifier == o && spec_opts->is_zero == false) {
      sharp_corr = 1;
    }
  } else if (spec_opts->specifier == p) {
    sharp_corr = 2;
  }

  flag_corr =
      spec_opts->flag_plus || spec_opts->flag_space || spec_opts->is_negative;

  if (spec_opts->precision > num_len) {
    prec_corr = spec_opts->precision - num_len;
  } else {
    prec_corr = 0;
  }

  if (spec_opts->is_floating_point_number) {
    padding_to_add =
        spec_opts->width - num_len - spec_opts->precision - flag_corr - 1;
  } else {
    padding_to_add =
        spec_opts->width - num_len - flag_corr - prec_corr - sharp_corr;
  }

  spec_opts->padding = (padding_to_add > 0) ? (s21_size_t)padding_to_add : 0;
}

void calculate_padding_ge_spec(s21_size_t num_len, SpecOptions* spec_opts) {
  int flag_corr = 0;  // Коррекция кол-ва пробелов

  int padding_to_add = 0;

  flag_corr =
      spec_opts->flag_plus || spec_opts->flag_space || spec_opts->is_negative;

  padding_to_add = spec_opts->width - num_len - flag_corr;

  spec_opts->padding = (padding_to_add > 0) ? (s21_size_t)padding_to_add : 0;
}

void apply_width(DestStr* dest, s21_size_t num_len, SpecOptions* spec_opts) {
  if (spec_opts->width > num_len) {
    // Если флаг '-' == 0
    if (!spec_opts->flag_minus) {
      for (s21_size_t i = 0; i < spec_opts->padding; i++)
        dest->str[dest->curr_ind++] = spec_opts->padding_char;
    }
  }
}

void apply_flags(DestStr* dest, SpecOptions* spec_opts) {
  if (spec_opts->is_negative) {
    dest->str[dest->curr_ind++] = '-';
  } else if (spec_opts->flag_plus) {
    dest->str[dest->curr_ind++] = '+';
  } else if (spec_opts->flag_space) {
    dest->str[dest->curr_ind++] = ' ';
  } else if (spec_opts->flag_sharp) {
    if (spec_opts->specifier == o) {
      dest->str[dest->curr_ind++] = '0';
    } else if (spec_opts->specifier == x) {
      dest->str[dest->curr_ind++] = '0';
      dest->str[dest->curr_ind++] = 'x';
    } else if (spec_opts->specifier == X) {
      dest->str[dest->curr_ind++] = '0';
      dest->str[dest->curr_ind++] = 'X';
    } else if (spec_opts->is_floating_point_number &&
               spec_opts->precision == 0) {
      spec_opts->flag_sharp = true;
    }
  }
}

void floating_point_number_to_str(DestStr* dest, long double input_num,
                                  SpecOptions* spec_opts) {
  input_num = TO_ABS(input_num);

  long double whole_part = 0;
  long double fraction_part = 0;

  s21_size_t zeros_to_insert = 0;

  // Set default precision if we didn't parse one
  set_needed_precision(spec_opts);

  fraction_part = modfl(input_num, &whole_part);

  whole_to_str(dest, whole_part, spec_opts);
  // Если не спарсили .0 - выводим дробную часть
  if (!(spec_opts->precision_set && !spec_opts->precision)) {
    dest->str[dest->curr_ind++] = '.';

    fraction_part = multiply_by_10_n_times(fraction_part, spec_opts->precision);
    // this is where we round rubbish
    fraction_part = roundl(fraction_part);
    if (spec_opts->precision > get_num_length(fraction_part, spec_opts)) {
      zeros_to_insert =
          spec_opts->precision - get_num_length(fraction_part, spec_opts);
    }

    add_zeros_to_destination(dest, zeros_to_insert);

    int fraction_digits_written = itoa(dest, fraction_part, spec_opts);

    s21_size_t zeros_to_add_on_the_right =
        spec_opts->precision - (zeros_to_insert + fraction_digits_written);

    add_zeros_to_destination(dest, zeros_to_add_on_the_right);

    if (!spec_opts->is_g_spec && !spec_opts->is_scientific) {
      apply_minus_width(dest, spec_opts);
    }

    dest->str[dest->curr_ind] = '\0';
  }

  if (spec_opts->flag_sharp && spec_opts->precision_set &&
      spec_opts->precision == 0) {
    dest->str[dest->curr_ind++] = '.';
  }
}

void reverse_num(DestStr* dest, s21_size_t l_index, s21_size_t r_index) {
  int i = l_index, j = r_index, temp;
  while (i < j) {
    temp = dest->str[i];
    dest->str[i] = dest->str[j];
    dest->str[j] = temp;
    i++;
    j--;
  }
}

int itoa(DestStr* dest, long double input_num, SpecOptions* spec_opts) {
  int current_int = 0;
  int num_len = 0;
  const char* digits = "0123456789abcdef";

  if (spec_opts->specifier == X) {
    digits = "0123456789ABCDEF";
  }

  s21_size_t l_index = dest->curr_ind;

  if (input_num == 0) {
    dest->str[dest->curr_ind++] = '0';
    num_len++;
  } else {
    while (input_num >= 1) {
      current_int = (int)fmodl(input_num, spec_opts->base);
      dest->str[dest->curr_ind++] = digits[current_int];
      input_num /= spec_opts->base;
      num_len++;
    }
    s21_size_t r_index = dest->curr_ind - 1;
    reverse_num(dest, l_index, r_index);
  }
  dest->str[dest->curr_ind] = '\0';

  return num_len;
}

void apply_minus_width(DestStr* dest, SpecOptions* spec_opts) {
  if (spec_opts->flag_minus) {
    for (s21_size_t i = 0; i < spec_opts->padding; i++) {
      dest->str[dest->curr_ind++] = ' ';
    }
  }
}

void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts) {
  num = TO_ABS(num);

  s21_size_t num_len = get_num_length(num, spec_opts);

  if (spec_opts->flag_zero && !spec_opts->is_g_spec &&
      !spec_opts->is_scientific) {
    apply_flags(dest, spec_opts);
  }

  if (!spec_opts->is_g_spec && !spec_opts->is_scientific) {
    calculate_padding(num_len, spec_opts);
    // Если ширина больше длины числа, добавляем пробелы в начало
    apply_width(dest, num_len, spec_opts);
  }
  if (!spec_opts->flag_zero && !spec_opts->is_g_spec &&
      !spec_opts->is_scientific) {
    apply_flags(dest, spec_opts);
  }

  itoa(dest, num, spec_opts);

  if (!spec_opts->is_floating_point_number && !spec_opts->is_g_spec &&
      !spec_opts->is_scientific)
    apply_minus_width(dest, spec_opts);

  dest->str[dest->curr_ind] = '\0';
}

void set_needed_precision(SpecOptions* spec_opts) {
  if (!spec_opts->precision_set) {
    spec_opts->precision = DEFAULT_F_PRECISION;
  }
}

void process_scientific_zero_input(DestStr* dest, SpecOptions* spec_opts) {
  // when input is 0

  dest->str[dest->curr_ind++] = '0';

  s21_size_t zeros_to_print = 0;

  if (spec_opts->precision_set) {
    zeros_to_print = spec_opts->precision;
  } else {
    zeros_to_print = DEFAULT_F_PRECISION;
  }

  if (!(spec_opts->precision_set == true && spec_opts->precision == 0)) {
    dest->str[dest->curr_ind++] = '.';
    for (s21_size_t i = 0; i < zeros_to_print; i++) {
      dest->str[dest->curr_ind++] = '0';
    }
  } else if (spec_opts->precision_set && spec_opts->precision == 0 &&
             spec_opts->flag_sharp) {
    dest->str[dest->curr_ind++] = '.';
  }

  dest->str[dest->curr_ind++] = spec_opts->exponent_char;

  dest->str[dest->curr_ind++] = '+';
  dest->str[dest->curr_ind++] = '0';
  dest->str[dest->curr_ind++] = '0';
}

void process_scientific_standard(DestStr* dest, long double input_num,
                                 SpecOptions* spec_opts) {
  int exponent = 0;

  if (input_num > 1) {
    exponent = calculate_exponent(bank_roundl(input_num));
  } else {
    exponent = calculate_exponent(input_num);
  }
  input_num = scale_input_to_one_digit(input_num);
  if (spec_opts->precision_set && spec_opts->precision == 0) {
    input_num = bank_roundl(input_num);
  }
  floating_point_number_to_str(dest, input_num, spec_opts);
  add_scientific_e_part(exponent, dest, spec_opts);
}

void process_scientific(DestStr* dest, long double input_num,
                        SpecOptions* spec_opts) {
  char scientific_temp_buffer[100] = {'\0'};
  DestStr scientific_temp_dest = {scientific_temp_buffer, 0};

  input_num = TO_ABS(input_num);
  // set_needed_precision(spec_opts);
  if (spec_opts->is_zero) {
    process_scientific_zero_input(&scientific_temp_dest, spec_opts);
  } else {
    process_scientific_standard(&scientific_temp_dest, input_num, spec_opts);
  }

  calculate_padding(scientific_temp_dest.curr_ind, spec_opts);
  apply_flags(dest, spec_opts);
  apply_width(dest, scientific_temp_dest.curr_ind, spec_opts);
  s21_strcpy(dest->str + dest->curr_ind, scientific_temp_dest.str);

  dest->curr_ind += scientific_temp_dest.curr_ind;
  apply_minus_width(dest, spec_opts);
}

void add_scientific_e_part(long long exponent, DestStr* dest,
                           SpecOptions* spec_opts) {
  dest->str[dest->curr_ind++] = spec_opts->exponent_char;

  if (exponent < 0) {
    dest->str[dest->curr_ind++] = '-';
    exponent *= -1;
  } else {
    dest->str[dest->curr_ind++] = '+';
  }
  // экспонента имеет как минимум два знака
  if (exponent < 10) {
    dest->str[dest->curr_ind++] = '0';
  }
  itoa(dest, exponent, spec_opts);
}

long long calculate_exponent(long double input_num) {
  long long exponent = 0;
  if (input_num != 0.0) {
    while (input_num >= 10.0 || input_num < 1.0) {
      if (input_num >= 10.0) {
        input_num /= 10.0;
        exponent++;
      } else {
        input_num *= 10.0;
        exponent--;
      }
    }
  }
  return exponent;
}

long double scale_input_to_one_digit(long double input_num) {
  if (input_num != 0.0) {
    while (input_num >= 10.0 || input_num < 1.0) {
      if (input_num >= 10.0) {
        input_num /= 10.0;
      } else {
        input_num *= 10.0;
      }
    }
  }
  return input_num;
}

bool g_spec_scientific_needed(long double input_num, SpecOptions* spec_opts) {
  bool result = false;

  long double whole_part = 0;
  long double fraction_part = 0;
  fraction_part = modfl(input_num, &whole_part);
  fraction_part = fraction_part - 0;

  s21_size_t whole_part_length_after_rounding =
      get_num_length(bank_roundl(input_num), spec_opts);

  /// set zero precision
  if (spec_opts->precision_set == true && spec_opts->precision == 0 &&
      whole_part_length_after_rounding > 1) {
    result = true;
  }
  // not set precision
  else if (spec_opts->precision_set == false &&
           whole_part_length_after_rounding > DEFAULT_F_PRECISION) {
    result = true;
    // precision set and it's nonzero
  } else if (spec_opts->precision_set == true && spec_opts->precision != 0 &&
             whole_part_length_after_rounding > spec_opts->precision) {
    result = true;
  }
  return result;
}

void process_g_spec(DestStr* dest, long double input_num,
                    SpecOptions* spec_opts) {
  char g_spec_temp_buffer[100] = {'\0'};
  DestStr g_spec_temp_dest = {g_spec_temp_buffer, 0};

  input_num = TO_ABS(input_num);
  long double whole_part = 0;
  long double fraction_part = 0;

  fraction_part = modfl(input_num, &whole_part);

  if (g_spec_scientific_needed(input_num, spec_opts)) {
    process_scientific_for_g_spec(&g_spec_temp_dest, input_num, spec_opts);
  } else if (spec_opts->precision_set == true && spec_opts->precision == 0) {
    process_g_spec_zero_precision(&g_spec_temp_dest, input_num, spec_opts);
  } else if (spec_opts->precision_set == false) {
    process_g_spec_not_set_precision(&g_spec_temp_dest, input_num, spec_opts);
  } else if (whole_part == 0 && fraction_part != 0) {
    process_g_spec_zero_wholepart_nonzero_precision(&g_spec_temp_dest,
                                                    input_num, spec_opts);
  } else {
    process_g_spec_nonzero_precision(&g_spec_temp_dest, input_num, spec_opts);
  }

  calculate_padding(g_spec_temp_dest.curr_ind, spec_opts);
  apply_flags(dest, spec_opts);
  apply_width(dest, g_spec_temp_dest.curr_ind, spec_opts);
  s21_strcpy(dest->str + dest->curr_ind, g_spec_temp_dest.str);

  dest->curr_ind += g_spec_temp_dest.curr_ind;
  apply_minus_width(dest, spec_opts);
}

void process_g_spec_zero_precision(DestStr* dest, long double input_num,
                                   SpecOptions* spec_opts) {
  // whole_part_length 0 or 1

  input_num = scale_to_one_digit_significand(input_num);

  s21_size_t decimal_digits_to_round_to = 0;

  if (floorl(input_num) == 0) {  //  я заменил roundl на floorl. в этом условии
                                 //  не нужен правильно округлённый input_num
    decimal_digits_to_round_to = 1;
  }

  input_num = round_to_n_digits(input_num, decimal_digits_to_round_to);

  process_g_spec_not_set_precision(dest, input_num, spec_opts);
}

void process_g_spec_not_set_precision(DestStr* dest, long double input_num,
                                      SpecOptions* spec_opts) {
  if (spec_opts->flag_sharp == true) {
    process_g_spec_not_set_precision_sharp_on(dest, input_num, spec_opts);
  } else {
    process_g_spec_not_set_precision_sharp_off(dest, input_num, spec_opts);
  }
}

void process_g_spec_not_set_precision_sharp_on(DestStr* dest,
                                               long double input_num,
                                               SpecOptions* spec_opts) {
  long double whole_part = 0;
  long double fraction_part = 0;
  fraction_part = modfl(input_num, &whole_part);

  s21_size_t needed_decimal_places = 0;

  s21_size_t whole_part_length = get_num_length(whole_part, spec_opts);

  if (whole_part == 0.0) {
    whole_part_length = 0;
  }

  needed_decimal_places = DEFAULT_F_PRECISION - whole_part_length;

  // whole_part_length always <= DEFAULT_F_PRECISION
  fraction_part = multiply_by_10_n_times(fraction_part, needed_decimal_places);
  fraction_part = bank_roundl(fraction_part);

  itoa(dest, whole_part, spec_opts);

  dest->str[dest->curr_ind++] = '.';
  s21_size_t fraction_part_length = get_num_length_simple(fraction_part);
  whole_part_length = get_num_length_simple(whole_part);
  s21_size_t total_length = whole_part_length + fraction_part_length;

  if (whole_part_length < DEFAULT_F_PRECISION) {
    itoa(dest, llround(fraction_part), spec_opts);
  }
  if (spec_opts->precision_set == false) {
    if (total_length < DEFAULT_F_PRECISION) {
      add_zeros_to_destination(dest, DEFAULT_F_PRECISION - total_length);
    }
    // remove_trailing_zeros(dest, spec_opts);
  } else if (spec_opts->precision_set == true) {
    if (dest->str[dest->curr_ind - 2] == '.' &&
        dest->str[dest->curr_ind - 1] == '0') {
      dest->str[dest->curr_ind--] = '\0';
    }
    if (input_num != 0.0) {
      remove_trailing_zeros(dest, spec_opts);
    }
  }
}

void process_g_spec_not_set_precision_sharp_off(DestStr* dest,
                                                long double input_num,
                                                SpecOptions* spec_opts) {
  long double whole_part = 0;
  long double fraction_part = 0;
  fraction_part = modfl(input_num, &whole_part);

  s21_size_t needed_decimal_places = 0;

  s21_size_t whole_part_length = get_num_length(whole_part, spec_opts);

  if (whole_part == 0.0) {
    whole_part_length = 0;
  }

  needed_decimal_places = DEFAULT_F_PRECISION - whole_part_length;

  fraction_part = multiply_by_10_n_times(fraction_part, needed_decimal_places);
  fraction_part = bank_roundl(fraction_part);

  itoa(dest, whole_part, spec_opts);

  dest->str[dest->curr_ind++] = '.';
  itoa(dest, llround(fraction_part), spec_opts);

  if (dest->str[dest->curr_ind - 2] == '.' &&
      dest->str[dest->curr_ind - 1] == '0') {
    dest->str[dest->curr_ind--] = '\0';
    dest->str[dest->curr_ind--] = '\0';
  }

  if (input_num != 0.0) {
    remove_trailing_zeros(dest, spec_opts);
  }
}

void process_g_spec_zero_wholepart_nonzero_precision(DestStr* dest,
                                                     long double input_num,
                                                     SpecOptions* spec_opts) {
  input_num = round_to_n_digits(input_num, spec_opts->precision);
  floating_point_number_to_str(dest, input_num, spec_opts);

  if (input_num != 0.0 && spec_opts->flag_sharp == false) {
    remove_trailing_zeros(dest, spec_opts);
  }
}

void process_g_spec_nonzero_precision(DestStr* dest, long double input_num,
                                      SpecOptions* spec_opts) {
  long double whole_part = 0;
  long double fraction_part = 0;
  bool print_fraction = true;

  fraction_part = modfl(input_num, &whole_part);
  s21_size_t whole_part_length = get_num_length_simple(whole_part);

  fraction_part *= powl(10, (spec_opts->precision - whole_part_length));

  s21_size_t fraction_part_length = get_num_length_simple(fraction_part);
  s21_size_t rounded_fraction_part_length =
      get_num_length_simple(bank_roundl(fraction_part));

  if (rounded_fraction_part_length > fraction_part_length) {
    whole_part++;
    print_fraction = false;
  }

  if (spec_opts->precision <= whole_part_length) {
    input_num = bank_roundl(input_num);
    whole_to_str(dest, input_num, spec_opts);
  } else {
    whole_to_str(dest, whole_part, spec_opts);
  }
  if (spec_opts->precision > 1 && fraction_part != 0 &&
      spec_opts->precision != whole_part_length && print_fraction == true) {
    dest->str[dest->curr_ind++] = '.';

    itoa(dest, bank_roundl(fraction_part), spec_opts);

    if (input_num != 0.0 && spec_opts->flag_sharp == false) {
      remove_trailing_zeros(dest, spec_opts);
    }

  } else if (spec_opts->flag_sharp == true) {
    whole_part_length = get_num_length_simple(whole_part);

    dest->str[dest->curr_ind++] = '.';
    add_zeros_to_destination(dest, spec_opts->precision - whole_part_length);
  }
}

void process_scientific_for_g_spec(DestStr* dest, long double input_num,
                                   SpecOptions* spec_opts) {
  if (spec_opts->precision_set) {
    process_scientific_for_g_spec_precision_set(dest, input_num, spec_opts);
  } else {
    process_scientific_for_g_spec_not_set_precision(dest, input_num, spec_opts);
  }
}

void process_scientific_for_g_spec_not_set_precision(DestStr* dest,
                                                     long double input_num,
                                                     SpecOptions* spec_opts) {
  int exponent = 0;

  if (input_num > 1) {
    exponent = calculate_exponent(bank_roundl(input_num));
  } else {
    exponent = calculate_exponent(input_num);
  }
  input_num = scale_input_to_one_digit(bank_roundl(input_num));

  input_num = round_to_n_digits(input_num, MANTISSA_DIGITS);

  floating_point_number_to_str(dest, input_num, spec_opts);

  dest->str[dest->curr_ind--] = '\0';

  remove_trailing_zeros(dest, spec_opts);

  add_scientific_e_part(exponent, dest, spec_opts);
}

bool g_spec_exponent_increment_check(long double input_num,
                                     SpecOptions* spec_opts) {
  bool result = false;

  // printf("Precision \n%lu\n", spec_opts->precision);
  // long double initial_input_num = input_num;
  // printf("Initial \n%Lf\n", input_num);

  input_num = scale_input_to_n_digits(input_num, spec_opts->precision);

  long double initial_input_num = input_num;
  // printf("Initial 2\n%Lf\n", initial_input_num);
  input_num = bank_roundl(input_num);
  if (get_num_length_simple(initial_input_num) !=
      get_num_length_simple(input_num)) {
    result = true;
  }

  // printf("After \n%Lf\n", input_num);

  return result;
};

void process_g_spec_significand_part_nonzero_precision(DestStr* dest,
                                                       long double input_num,
                                                       SpecOptions* spec_opts) {
  long double whole_part = 0;
  long double fraction_part = 0;

  if (g_spec_exponent_increment_check(input_num, spec_opts)) {
    input_num = scale_input_to_one_digit(bank_roundl(input_num));
  }

  fraction_part = modfl(input_num, &whole_part);

  s21_size_t whole_part_length = get_num_length(whole_part, spec_opts);
  if (spec_opts->precision <= whole_part_length) {
    input_num = bank_roundl(input_num);
    whole_to_str(dest, input_num, spec_opts);
  } else {
    whole_to_str(dest, whole_part, spec_opts);
  }
  if (spec_opts->precision > 1 && fraction_part != 0 &&
      spec_opts->precision != whole_part_length) {
    dest->str[dest->curr_ind++] = '.';

    fraction_part *= pow(10, spec_opts->precision - whole_part_length);
    // printf("\n\n\n%Lf\n\n\n", fraction_part);
    itoa(dest, bank_roundl(fraction_part), spec_opts);

    if (input_num != 0.0) {
      remove_trailing_zeros(dest, spec_opts);
    }
  } else if (spec_opts->flag_sharp == true) {
    dest->str[dest->curr_ind++] = '.';
    add_zeros_to_destination(dest, spec_opts->precision);
  }
}

void process_scientific_for_g_spec_precision_set(DestStr* dest,
                                                 long double input_num,
                                                 SpecOptions* spec_opts) {
  int exponent = 0;

  exponent = calculate_exponent(input_num);

  if (g_spec_exponent_increment_check(input_num, spec_opts)) {
    exponent++;
  }

  input_num = scale_input_to_n_digits(input_num, spec_opts->precision);

  input_num = bank_roundl(input_num);

  input_num = scale_input_to_one_digit(input_num);

  input_num = round_to_n_digits(input_num, spec_opts->precision);

  if ((spec_opts->precision_set && spec_opts->precision == 0)) {
    input_num = bank_roundl(input_num);
  }

  if (spec_opts->precision == 0) {
    process_g_spec_zero_precision(dest, input_num, spec_opts);
  } else {
    process_g_spec_significand_part_nonzero_precision(dest, input_num,
                                                      spec_opts);

    // remove_trailing_zeros(dest, spec_opts);
  }

  if (dest->str[dest->curr_ind - 1] == '0') {
    dest->str[dest->curr_ind--] = '\0';
  }
  if (!(spec_opts->flag_sharp) && dest->str[dest->curr_ind - 1] == '.') {
    dest->str[dest->curr_ind--] = '\0';
  }

  add_scientific_e_part(exponent, dest, spec_opts);
}

void pointer_to_str(DestStr* dest, void* ptr, SpecOptions* spec_opts) {
  uintptr_t address = (uintptr_t)ptr;
  long long num_len = get_num_length(address, spec_opts);

  calculate_padding(num_len, spec_opts);
  apply_width(dest, num_len,
              spec_opts);  // мы добовляем двойку что бы покрыть два
                           // дополнительных символа
  apply_flags(dest, spec_opts);
  dest->str[dest->curr_ind++] = '0';
  dest->str[dest->curr_ind++] = 'x';

  itoa(dest, address, spec_opts);

  apply_minus_width(dest, spec_opts);
}

void set_locale_for_wide_chars() {
#if defined(__APPLE__)
  setlocale(LC_ALL, "en_US.UTF-8");

#elif defined(__linux__)
  setlocale(LC_ALL, "C.UTF-8");

#endif
}

long double round_to_n_digits(long double input_num, s21_size_t n_digits) {
  long double whole_part = 0;
  long double fraction_part = 0;
  fraction_part = modfl(input_num, &whole_part);

  fraction_part = multiply_by_10_n_times(fraction_part, n_digits);
  fraction_part = roundl(fraction_part);
  fraction_part = divide_by_10_n_times(fraction_part, n_digits);

  input_num = whole_part + fraction_part;
  return input_num;
}

long double scale_to_one_digit_significand(long double input_num) {
  long double result = 0;
  if (input_num < 10) {
    result = input_num;
  } else {
    int exponent = (int)floor(log10(input_num));
    result = input_num / pow(10, exponent);
  }
  return result;
}

s21_size_t get_num_length_simple(long double num) {
  int num_len = 0;

  if ((num >= 0 && num < 1)) {
    num_len++;
  } else {
    while (num >= 1) {
      num_len++;
      num /= 10.0;
    }
  }
  return num_len;
}

long double scale_input_to_n_digits(long double input_num, s21_size_t n) {
  if (input_num != 0.0) {
    if (n == 0) {
      n = 1;
    }
    while (get_num_length_simple(input_num) != n) {
      if (get_num_length_simple(input_num) > n) {
        input_num /= 10.0;
      } else {
        input_num *= 10.0;
      }
    }
  }
  return input_num;
}

void remove_trailing_zeros(DestStr* dest, SpecOptions* spec_opts) {
  while (dest->curr_ind > 0 && dest->str[dest->curr_ind - 1] == '0') {
    dest->str[dest->curr_ind - 1] = '\0';
    dest->curr_ind--;
  }
  if (dest->str[dest->curr_ind - 1] == '.' &&
      spec_opts->flag_sharp == false) {  // ВРЕМЕННО !!!
    dest->str[dest->curr_ind - 1] = '\0';
    dest->curr_ind--;
  }
}

long double bank_roundl(long double input_num) {
  long double result;
  long double whole_part;
  long double fraction_part = modfl(input_num, &whole_part);
  if (fmodl(whole_part, 2.0) == 0) {
    if (fraction_part <= 0.5L) {
      result = floor(input_num);
    } else {
      result = ceil(input_num);
    }
  } else {
    if (fraction_part >= 0.5L) {
      result = ceil(input_num);
    } else {
      result = floor(input_num);
    }
  }
  return result;
}

bool is_zero(long double input_num) { return fabsl(input_num) < EPSILON; }