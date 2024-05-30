#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define F_PRECISION 6

typedef struct SpecifierOptions {
  int plus;    // Флаг '+'
  int minus;   // Флаг '-'
  int space;   // Флаг ' '
  int width;   // Ширина *.
  int prec;    // Точность .*
  int prec_i;  // Опция для целых чисел
  int prec_f;  // Была ли задана precision для спецификатора
} SpecOptions;

typedef struct DestinationString {
  char* str;
  s21_size_t curr_ind;
} DestStr;

void apply_flags(DestStr* dest, long long* num, SpecOptions spec_options,
                 int prec);
int get_num_length(long long num);
int whole_number_to_str(DestStr* dest, int num_len, long long num);
void int_to_str(DestStr* dest, long long num, SpecOptions spec_options,
                int prec);
void div_num(double num, double mul, long long* wh, double* fr);
void float_to_str(DestStr* dest, double num, SpecOptions spec_options);
int is_flag(char* flags, char ch);
int is_specifier(char* specs, char ch);
void parse_flags(char* flags, const char** format_string,
                 SpecOptions* spec_options);
void parse_width(char* specs, const char** format_string,
                 SpecOptions* spec_options);
void parse_precision(char* specs, const char** format_string,
                     SpecOptions* spec_options);

int s21_sprintf(char* str, const char* format, ...);

// %[flags][width][.precision][length][specifier]
int s21_sprintf(char* str, const char* format, ...) {
  DestStr dest = {str, 0};
  int fin_result = 0;  // Результат работы функции, пока не используется нигде
  char* valid_flags = "+- ";
  char* valid_specifiers = "cidfsu";
  SpecOptions spec_options = {0};
  spec_options.prec_i = -1;

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      parse_flags(valid_flags, &format, &spec_options);
      parse_width(valid_specifiers, &format, &spec_options);
      parse_precision(valid_specifiers, &format, &spec_options);
      switch (*format) {
        case 'c': {  // Если c (char)
          char input_char = va_arg(args, int);
          dest.str[dest.curr_ind++] = input_char;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
          int input_decimal = va_arg(args, int);
          int_to_str(&dest, input_decimal, spec_options, spec_options.prec_i);
          break;
        }
        case 'f': {  // Если f (float)
          float input_float = va_arg(args, double);
          float_to_str(&dest, input_float, spec_options);
          break;
        }
        case 's': {
          char* input_string = va_arg(args, char*);
          s21_strcpy(dest.str + dest.curr_ind, input_string);
          dest.curr_ind += s21_strlen(input_string);
          break;
        }
        case 'u': {
          unsigned input_unsingned_int = va_arg(args, unsigned);
          int_to_str(&dest, input_unsingned_int, spec_options,
                     spec_options.prec_i);
          break;
        }
        default:
          break;
      }
    } else {
      dest.str[dest.curr_ind++] = *format;
    }
    spec_options.plus = 0;
    spec_options.minus = 0;
    spec_options.space = 0;
    format++;
  }
  dest.str[dest.curr_ind] = '\0';
  va_end(args);

  return fin_result;
}

// Флаги '+', '-' и ' '
void apply_flags(DestStr* dest, long long* num, SpecOptions spec_options,
                 int precision) {
  if (*num < 0) {
    dest->str[dest->curr_ind++] = '-';
    *num *= -1;
  } else if (spec_options.plus && precision == -1) {
    dest->str[dest->curr_ind++] = '+';
  } else if (spec_options.space && precision == -1) {
    dest->str[dest->curr_ind++] = ' ';
  }
}

// Считаем длину числа
int get_num_length(long long num) {
  int num_len = 0;

  while (num != 0) {
    num_len++;
    num /= 10;
  }

  return num_len;
}

int whole_number_to_str(DestStr* dest, int num_len, long long num) {
  int digits_written = 0;

  if (num_len == 0) {
    dest->str[dest->curr_ind++] = '0';
    digits_written++;
  } else {
    while (num_len != 0) {
      long long temp = pow(10, --num_len);
      dest->str[dest->curr_ind++] = (num / temp) + '0';
      num %= temp;
      digits_written++;
    }
  }
  return digits_written;
}

// Функция для преобразования целого числа в строку
void int_to_str(DestStr* dest, long long input_num, SpecOptions spec_options,
                int precision) {
  // Обрабатываем флаги
  apply_flags(dest, &input_num, spec_options, precision);

  // Считаем длину числа
  int num_len = get_num_length(input_num);

  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности
  int i = whole_number_to_str(dest, num_len, input_num);

  while (i < precision && precision != -1) {
    dest->str[dest->curr_ind++] = '0';
    i++;
  }
  dest->str[dest->curr_ind] = '\0';
}

void div_num(double num, double mul, long long* wh, double* fr) {
  // Округляем дробную часть до нужного числа
  num = round(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

void float_to_str(DestStr* dest, double num, SpecOptions spec_options) {
  double multiplier;  // Множитель для округления числа
  long long whole;    // Целая часть
  double fract;       // Дробная часть

  // Если есть precision, но она == 0
  if (spec_options.prec_f && !spec_options.prec) {
    multiplier = pow(10.0, spec_options.prec);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(dest, whole, spec_options, spec_options.prec_i);

    // Если нет precision
  } else if (!spec_options.prec_f) {
    multiplier = pow(10.0, F_PRECISION);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(dest, whole, spec_options, spec_options.prec_i);
    dest->str[dest->curr_ind++] = '.';
    int_to_str(dest, fract, spec_options, F_PRECISION);

    // Иначе
  } else {
    multiplier = pow(10.0, spec_options.prec);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(dest, whole, spec_options, spec_options.prec_i);
    dest->str[dest->curr_ind++] = '.';
    int_to_str(dest, fract, spec_options, spec_options.prec);
  }
}

int is_flag(char* flags, char ch) {
  char* res = s21_strchr(flags, ch);
  return res == S21_NULL ? 0 : 1;
}

int is_specifier(char* specs, char ch) {
  char* res = s21_strchr(specs, ch);
  return res == S21_NULL ? 0 : 1;
}

void parse_flags(char* valid_flags, const char** format_string,
                 SpecOptions* spec_options) {
  while (is_flag(valid_flags, **format_string)) {
    switch (**format_string) {
      case '+':
        spec_options->plus = 1;
        break;
      case '-':
        spec_options->minus = 1;
        break;
      case ' ':
        spec_options->space = 1;
        break;
      default:
        break;
    }
    (*format_string)++;
  }
}

void parse_width(char* valid_specifiers, const char** format_string,
                 SpecOptions* spec_options) {
  // int res = 0;
  spec_options->width = 0;

  while (**format_string != '.' &&
         !is_specifier(valid_specifiers, **format_string)) {
    if (isdigit(**format_string)) {
      spec_options->width = spec_options->width * 10 + (**format_string - '0');
      // res++;
    }
    (*format_string)++;
  }
}

void parse_precision(char* valid_specifiers, const char** format_string,
                     SpecOptions* spec_options) {
  int res = 0;
  spec_options->prec = 0;

  while (!is_specifier(valid_specifiers, **format_string)) {
    if (isdigit(**format_string)) {
      spec_options->prec = spec_options->prec * 10 + (**format_string - '0');
      res++;
    }
    (*format_string)++;
  }
  spec_options->prec_f = res;
}
