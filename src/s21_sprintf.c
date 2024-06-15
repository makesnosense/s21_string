#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  set_locale_for_wide_chars();
  DestStr dest = {str, 0};
  SpecOptions spec_opts = {0};
  int fin_result = 0;  // Результат работы функции, пока не используется нигде

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      s21_memset(&spec_opts, 0, sizeof(spec_opts));
      parse_format(&format, args, &spec_opts);
      set_base(&spec_opts);
      set_padding_char(&spec_opts);
      set_exponent_char(&spec_opts);

      switch (*format) {
        case 'c': {
          process_chars(&args, &dest, &spec_opts);
          break;
        }
        case 's': {
          process_strings(&args, &dest, &spec_opts);
          break;
        }
        case 'i':
        case 'd': {
          process_int(&args, &dest, &spec_opts);
          break;
        }
        case 'x':
        case 'X':
        case 'o':
        case 'u': {
          process_unsigned(&args, &dest, &spec_opts);
          break;
        }
        case 'e':
        case 'E': {
          long double input_floating_point_number =
              ingest_floating_point_number(&args, &spec_opts);
          is_negative(input_floating_point_number, &spec_opts);
          process_scientific(&dest, input_floating_point_number, &spec_opts);
          break;
        }
        case 'n': {
          int* counter_n = va_arg(args, int*);
          *counter_n = s21_strlen(dest.str);
          break;
        }
        case 'g':
        case 'G': {
          long double input_floating_point_number =
              ingest_floating_point_number(&args, &spec_opts);
          is_negative(input_floating_point_number, &spec_opts);
          spec_G(&dest, input_floating_point_number, &spec_opts);
          break;
        }
        case 'p': {
          void* pointer_str_input = va_arg(args, void*);
          pointer_to_str(&dest, pointer_str_input, &spec_opts);
          break;
        }
        case 'f': {
          process_floating_point_number(&args, &dest, &spec_opts);
          break;
        }
        case '%': {
          dest.str[dest.curr_ind++] = '%';
          break;
        }
        default:
          break;
      }
    } else {
      dest.str[dest.curr_ind++] = *format;
    }
    format++;
  }
  dest.str[dest.curr_ind] = '\0';
  va_end(args);

  return fin_result;
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
    switch (**format) {
      case '+':
        spec_opts->flag_plus = 1;
        break;
      case '-':
        spec_opts->flag_minus = 1;
        spec_opts->flag_zero = 0;
        break;
      case ' ':
        spec_opts->flag_space = 1;
        break;
      case '0':
        if (spec_opts->flag_minus == 0) {
          spec_opts->flag_zero = 1;
        }
        break;
      case '#':
        spec_opts->flag_sharp = 1;
        break;
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
        spec_opts->is_char = true;
        break;
      }
      case 'X': {
        spec_opts->is_hexadecimal_capital = true;
        break;
      }
      case 'p':
      case 'x': {
        spec_opts->is_hexadecimal = true;
        break;
      }
      case 'o': {
        spec_opts->is_octal = true;
        break;
      }
      case 'f':
      case 'g':
      case 'G':
      case 'e':
      case 'E': {
        spec_opts->is_floating_point_number = true;
        if (**format == 'g') {
          spec_opts->is_spec_g = true;
        } else if (**format == 'G') {
          spec_opts->is_spec_g_capital = true;
        } else if (**format == 'e') {
          spec_opts->is_scientific = true;
        } else if (**format == 'E') {
          spec_opts->is_scientific_capital = true;
        }
        break;
      }
    }
  }
}

void process_chars(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  if (spec_opts->length_l == false) {
    process_narrow_char(args, dest, spec_opts);
  } else {
    process_wide_char(args, dest);
  }
}

void process_narrow_char(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  char input_char = va_arg(*args, int);
  int num_len = get_num_length(input_char, spec_opts);
  // Если ширина больше длины числа, добавляем пробелы в начало
  apply_width(dest, num_len, spec_opts);
  // Обрабатываем флаги
  apply_flags(dest, spec_opts);
  dest->str[dest->curr_ind++] = input_char;
  apply_minus_width(dest, spec_opts);
}

void process_wide_char(va_list* args, DestStr* dest) {
  wchar_t input_char = va_arg(*args, wchar_t);
  char temp[MB_CUR_MAX];
  int len = wctomb(temp, input_char);
  if (len > 0) {
    for (int i = 0; i < len; i++) {
      dest->str[dest->curr_ind++] = temp[i];
    }
  }
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
    process_narrow_string("nan", dest, spec_opts);
  } else if (isinf(input_floating_point_number)) {
    spec_opts->is_floating_point_number = false;
    process_narrow_string("inf", dest, spec_opts);
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
    process_wide_string(args, dest);
  }
}

void process_narrow_string(char* input_string, DestStr* dest,
                           SpecOptions* spec_opts) {
  apply_width(dest, s21_strlen(input_string), spec_opts);
  apply_flags(dest, spec_opts);
  s21_strcpy(dest->str + dest->curr_ind, input_string);
  dest->curr_ind += s21_strlen(input_string);
  apply_minus_width(dest, spec_opts);
}

void process_wide_string(va_list* args, DestStr* dest) {
  wchar_t* input_string = va_arg(*args, wchar_t*);
  size_t len = wcstombs(NULL, input_string, 0);
  if (len != (size_t)-1) {
    char* temp_str = (char*)malloc(len + 1);
    if (temp_str) {
      wcstombs(temp_str, input_string, len + 1);
      s21_strcpy(dest->str + dest->curr_ind, temp_str);
      dest->str += len;
      free(temp_str);
    }
  }
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
    // printf("\nLongDouble: %.18Lf\n", input_floating_point_number);
  } else {
    input_floating_point_number = va_arg(*args, double);
    // printf("\nDouble: %.18Lf\n", input_floating_point_number);
  }
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
  return input_unsingned;
}

void set_base(SpecOptions* spec_opts) {
  if (spec_opts->is_octal) {
    spec_opts->base = 8.0;
  } else if (spec_opts->is_hexadecimal || spec_opts->is_hexadecimal_capital) {
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
  if (spec_opts->is_scientific || spec_opts->is_spec_g) {
    spec_opts->exponent_char = 'e';
  } else if (spec_opts->is_scientific_capital || spec_opts->is_spec_g_capital) {
    spec_opts->exponent_char = 'E';
  }
}

void is_negative(long double num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0.0 ? 1 : 0;
}

s21_size_t get_num_length(long double num, SpecOptions* spec_opts) {
  int num_len = 0;

  if (num == 0 || spec_opts->is_char) {
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

void apply_width(DestStr* dest, s21_size_t num_len, SpecOptions* spec_opts) {
  int flag_corr;  // Коррекция кол-ва пробелов
  int prec_corr;  // Коррекция кол-ва пробелов

  // Если ширина > длины числа
  if (spec_opts->width > num_len) {
    flag_corr =
        spec_opts->flag_plus || spec_opts->flag_space || spec_opts->is_negative;
    prec_corr = (s21_size_t)spec_opts->precision > num_len
                    ? spec_opts->precision - num_len
                    : 0;

    if (spec_opts->is_floating_point_number) {
      spec_opts->padding =
          spec_opts->width - num_len - spec_opts->precision - flag_corr - 1;
    } else {
      spec_opts->padding = spec_opts->width - num_len - flag_corr - prec_corr;
    }

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
    if (spec_opts->is_octal) {
      dest->str[dest->curr_ind++] = '0';
    } else if (spec_opts->is_hexadecimal) {
      dest->str[dest->curr_ind++] = '0';
      dest->str[dest->curr_ind++] = 'x';
    } else if (spec_opts->is_hexadecimal_capital) {
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

  long double whole_part = 0;     // Целая часть
  long double fraction_part = 0;  // Дробная часть

  s21_size_t zeros_to_insert = 0;

  // Set default precision if we didn't parse one
  set_needed_precision(spec_opts);

  fraction_part = modfl(input_num, &whole_part);

  // Записываем целую часть в строку dest
  whole_to_str(dest, whole_part, spec_opts);
  // Если не спарсили .0 - выводим дробную часть
  if (!(spec_opts->precision_set && !spec_opts->precision)) {
    dest->str[dest->curr_ind++] = '.';

    fraction_part = multiply_by_10_n_times(fraction_part, spec_opts->precision);
    // this is where we round rubbish
    fraction_part = roundl(fraction_part);
    zeros_to_insert =
        spec_opts->precision - get_num_length(fraction_part, spec_opts);

    add_zeros_to_destination(dest, zeros_to_insert);

    int fraction_digits_written = itoa(dest, fraction_part, spec_opts);

    s21_size_t zeros_to_add_on_the_right =
        spec_opts->precision - (zeros_to_insert + fraction_digits_written);

    add_zeros_to_destination(dest, zeros_to_add_on_the_right);

    // Добавляем пробелы в конец, если флаг '-'
    apply_minus_width(dest, spec_opts);

    // Добавляем нуль-терминатор
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

  if (spec_opts->is_hexadecimal_capital) {
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
  // Если ширина > длины числа и флаг '-' == 1
  if (spec_opts->flag_minus) {
    for (s21_size_t i = 0; i < spec_opts->padding; i++) {
      dest->str[dest->curr_ind++] = ' ';
    }
  }
}

void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts) {
  num = TO_ABS(num);

  s21_size_t num_len = get_num_length(num, spec_opts);

  if (spec_opts->flag_zero) {
    apply_flags(dest, spec_opts);
  }
  // Если ширина больше длины числа, добавляем пробелы в начало
  apply_width(dest, num_len, spec_opts);

  if (!spec_opts->flag_zero) {
    apply_flags(dest, spec_opts);
  }

  // Преобразуем целое число в строку
  itoa(dest, num, spec_opts);

  // Если ширина больше длины числа, добавляем пробелы в конец
  if (!spec_opts->is_floating_point_number) apply_minus_width(dest, spec_opts);

  // Добавляем нуль-терминатор
  dest->str[dest->curr_ind] = '\0';
}

void set_needed_precision(SpecOptions* spec_opts) {
  if (!spec_opts->precision_set) {
    spec_opts->precision = F_PRECISION;
  }
}

void divide_number(long double num, int precision, long double* wh,
                   long double* fr) {
  // Округляем дробную часть до нужного числа
  // long double mul = (double)pow(10.0, precision);
  long double mul = powl(10.0, precision);

  num = llround(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

void process_scientific_zero_input(DestStr* dest, SpecOptions* spec_opts) {
  // Обработка нулевого случая
  dest->str[dest->curr_ind++] = '0';

  if (!(spec_opts->precision_set == true && spec_opts->precision == 0)) {
    dest->str[dest->curr_ind++] = '.';
    for (s21_size_t i = 0; i < spec_opts->precision; i++) {
      dest->str[dest->curr_ind++] = '0';
    }
  }

  dest->str[dest->curr_ind++] = spec_opts->exponent_char;

  dest->str[dest->curr_ind++] = '+';
  dest->str[dest->curr_ind++] = '0';
  dest->str[dest->curr_ind++] = '0';
}

void process_scientific_for_g_spec(long double input_num, DestStr* dest,
                                   SpecOptions* spec_opts) {
  long double whole_part = 0;
  long double fraction_part = 0;
  if (spec_opts->precision_set == false) {
    divide_number(input_num, MANTISSA_DIGITS, &whole_part, &fraction_part);

    fraction_part /= pow(10, MANTISSA_DIGITS);
    input_num = whole_part + fraction_part;

    floating_point_number_to_str(dest, input_num, spec_opts);

    dest->str[dest->curr_ind--] = '\0';

  } else if (spec_opts->precision_set) {
    divide_number(input_num, MANTISSA_DIGITS - 1, &whole_part, &fraction_part);

    fraction_part /= pow(10, MANTISSA_DIGITS);
    input_num = whole_part + fraction_part;

    floating_point_number_to_str(dest, input_num, spec_opts);
    spec_opts->precision -= 1;
    if (dest->str[dest->curr_ind - 1] == '0') {
      dest->str[dest->curr_ind--] = '\0';
    }
    if (!(spec_opts->flag_sharp) && dest->str[dest->curr_ind - 1] == '.') {
      dest->str[dest->curr_ind--] = '\0';
    }
  }
};

void process_scientific(DestStr* dest, long double input_num,
                        SpecOptions* spec_opts) {
  input_num = TO_ABS(input_num);
  set_needed_precision(spec_opts);
  int exponent = 0;
  if (input_num == 0.0) {
    process_scientific_zero_input(dest, spec_opts);
  } else {
    exponent = scale_input_and_calculate_exponent(&input_num);
    // Используем floating_point_number_to_str для форматирования мантиссы
    if (spec_opts->is_spec_g || spec_opts->is_spec_g_capital) {
      process_scientific_for_g_spec(input_num, dest, spec_opts);
    } else {
      floating_point_number_to_str(dest, input_num, spec_opts);
    }

    dest->str[dest->curr_ind++] = spec_opts->exponent_char;

    if (exponent < 0) {
      dest->str[dest->curr_ind++] = '-';
      exponent *= -1;
    } else {
      dest->str[dest->curr_ind++] = '+';
    }
    // Убедитесь, что экспонента имеет как минимум два знака
    if (exponent < 10) {
      dest->str[dest->curr_ind++] = '0';
    }
    itoa(dest, exponent, spec_opts);
  }
}

long long scale_input_and_calculate_exponent(long double* input_num) {
  long long exponent = 0;

  while (*input_num >= 10.0 || *input_num < 1.0) {
    if (*input_num >= 10.0) {
      *input_num /= 10.0;
      exponent++;
    } else {
      *input_num *= 10.0;
      exponent--;
    }
  }
  return exponent;
}

void spec_G(DestStr* dest, double double_input, SpecOptions* spec_opts) {
  double_input = TO_ABS(double_input);
  long double whole_part = 0;
  long double fraction_part = 0;

  s21_size_t needed_precision = 0;

  s21_size_t whole_part_length = get_num_length(ceill(double_input), spec_opts);

  if (whole_part_length <= F_PRECISION) {
    if (spec_opts->precision > F_PRECISION) {
      needed_precision = spec_opts->precision;
    } else if (ceill(double_input) == 0) {
      needed_precision = F_PRECISION;
    } else {
      needed_precision = F_PRECISION - whole_part_length;
    }
  }

  fraction_part = modfl(double_input, &whole_part);
  fraction_part = multiply_by_10_n_times(fraction_part, needed_precision);
  fraction_part = llround(fraction_part);

  if ((whole_part_length <= F_PRECISION) &&
      (spec_opts->precision_set == false)) {
    whole_to_str(dest, whole_part, spec_opts);
    if (whole_part_length != F_PRECISION) {
      dest->str[dest->curr_ind++] = '.';
      itoa(dest, llround(fraction_part), spec_opts);

      if (dest->str[dest->curr_ind - 2] == '.' &&
          dest->str[dest->curr_ind - 1] == '0') {
        dest->str[dest->curr_ind--] = '\0';
        dest->str[dest->curr_ind--] = '\0';
      }
      for (int i = 0; i < 6; i++) {
        if (dest->str[dest->curr_ind - 1] == '0' && double_input != 0) {
          dest->str[dest->curr_ind--] = '\0';
        }
      }
    }

  } else if (spec_opts->precision_set && spec_opts->precision <= F_PRECISION &&
             spec_opts->precision >= whole_part_length) {
    whole_to_str(dest, whole_part, spec_opts);

    if (fraction_part != 0) {
      dest->str[dest->curr_ind++] = '.';

      fraction_part /= pow(10, F_PRECISION - spec_opts->precision);

      if ((int)fraction_part != 0 && spec_opts->precision != 0 &&
          spec_opts->flag_sharp == false) {
        itoa(dest, llround(fraction_part), spec_opts);
      } else {
        for (s21_size_t i = 0; i < spec_opts->precision - whole_part_length;
             i++) {
          dest->str[dest->curr_ind++] = '0';
        }
      }
    }

    if (dest->str[dest->curr_ind - 2] == '.' &&
        dest->str[dest->curr_ind - 1] == '0') {
      dest->str[dest->curr_ind--] = '\0';
    }
    if (spec_opts->flag_sharp == false &&
        dest->str[dest->curr_ind - 1] == '.') {
      dest->str[dest->curr_ind--] = '\0';
    }

    for (int i = 0; i < 6; i++) {
      if (dest->str[dest->curr_ind - 1] == '0' && double_input != 0) {
        dest->str[dest->curr_ind--] = '\0';
      }
    }

  } else if (double_input < 10) {
    whole_to_str(dest, whole_part, spec_opts);

    if (fraction_part != 0 && spec_opts->precision != 0) {
      dest->str[dest->curr_ind++] = '.';

      if (spec_opts->precision == 0) {
        fraction_part /= pow(10, F_PRECISION - spec_opts->precision - 1);
      }

      itoa(dest, fraction_part, spec_opts);
    }

    for (int i = 0; i < 18; i++) {
      if (dest->str[dest->curr_ind - 1] == '0' && double_input != 0) {
        dest->str[dest->curr_ind--] = '\0';
      }
    }
  } else {
    process_scientific(dest, double_input, spec_opts);
  }
}

void pointer_to_str(DestStr* dest, void* ptr, SpecOptions* spec_opts) {
  uintptr_t addres = (uintptr_t)ptr;
  long long num_len = get_num_length(addres, spec_opts);

  apply_width(dest, num_len + 2,
              spec_opts);  // мы добовляем двойку что бы покрыть два
                           // дополнительных символа
  apply_flags(dest, spec_opts);
  dest->str[dest->curr_ind++] = '0';
  dest->str[dest->curr_ind++] = 'x';

  itoa(dest, addres, spec_opts);
}

void set_locale_for_wide_chars() {
#if defined(__APPLE__)
  setlocale(LC_ALL, "en_US.UTF-8");

#elif defined(__linux__)
  setlocale(LC_ALL, "C.UTF-8");

#endif
}
