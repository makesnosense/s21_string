#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// Точность для %f по умолчанию
#define F_PRECISION 6
#define VALID_FLAGS "+- "
#define VALID_SPECIFIERS "cidfsu"

// Опции функции s21_sprintf
typedef struct SpecifierOptions {
  bool plus;           // Флаг '+'
  bool minus;          // Флаг '-'
  bool space;          // Флаг ' '
  int width;           // Ширина *.
  int precision;       // Точность .*
  bool precision_set;  // Есть ли precision у спецификатора
} SpecOptions;

// Структура для строки-буфера
typedef struct DestinationString {
  char* str;
  s21_size_t curr_ind;
} DestStr;

// Функция обрабатывает флаги '+', '-' и ' '
void apply_flags(DestStr* dest, long long* num, SpecOptions spec_opts);

// Функция считает длину целого числа
int get_num_length(long long num);

// Функция записывает целое число в строку dest
// нужно знать длину числа
int itoa(DestStr* dest, int num_len, long long num);

// Функция записывает целое число в строку dest
// --------готовое решение с обработкой флагов---------
void whole_to_str(DestStr* dest, long long num, SpecOptions spec_opts);

// Функция записывает дробную часть числа в строку dest
void fract_to_str(DestStr* dest, long long num, int needed_precision);

// Функция для чисел с плавающей точкой:
//  1. Округляет число до нужной точности
//  2. Делит число на целую и дробную часть
void div_num(double num, int precision, long long* wh, double* fr);

// Функция записывает число с плавающей точкой в строку dest
void float_to_str(DestStr* dest, double num, SpecOptions spec_opts);

// Функция возвращает 1, если ch - это флаг
int is_flag(char ch);

// Функция возвращает 1, если ch - это спецификатор
int is_specifier(char ch);

// Функция парсит флаги для спецификатора
void parse_flags(const char** format, SpecOptions* spec_opts);

// Функция парсит ширину для спецификатора
void parse_width(const char** format, SpecOptions* spec_opts);

// Функция парсит точность для спецификатора
void parse_precision(const char** format, SpecOptions* spec_opts);

// %[flags][width][.precision][length][specifier]
int s21_sprintf(char* str, const char* format, ...);

int s21_sprintf(char* str, const char* format, ...) {
  DestStr dest = {str, 0};
  SpecOptions spec_opts = {0};
  int fin_result = 0;  // Результат работы функции, пока не используется нигде

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      s21_memset(&spec_opts, 0, sizeof(spec_opts));
      parse_flags(&format, &spec_opts);
      parse_width(&format, &spec_opts);
      parse_precision(&format, &spec_opts);
      switch (*format) {
        case 'c': {  // Если c (char)
          char input_char = va_arg(args, int);
          dest.str[dest.curr_ind++] = input_char;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
          int input_int = va_arg(args, int);
          whole_to_str(&dest, input_int, spec_opts);
          break;
        }
        case 'f': {  // Если f (float)
          float input_float = va_arg(args, double);
          float_to_str(&dest, input_float, spec_opts);
          break;
        }
        case 's': {
          char* input_string = va_arg(args, char*);
          s21_strcpy(dest.str + dest.curr_ind, input_string);
          dest.curr_ind += s21_strlen(input_string);
          break;
        }
        case 'u': {
          unsigned input_unsingned = va_arg(args, unsigned);
          whole_to_str(&dest, input_unsingned, spec_opts);
          break;
        }
        default:
          break;
      }
    } else {
      dest.str[dest.curr_ind++] = *format;
    }
    spec_opts.plus = 0;
    spec_opts.minus = 0;
    spec_opts.space = 0;
    format++;
  }
  dest.str[dest.curr_ind] = '\0';
  va_end(args);

  return fin_result;
}

void apply_flags(DestStr* dest, long long* num, SpecOptions spec_opts) {
  if (*num < 0) {
    dest->str[dest->curr_ind++] = '-';
    *num *= -1;
  } else if (spec_opts.plus) {
    dest->str[dest->curr_ind++] = '+';
  } else if (spec_opts.space) {
    dest->str[dest->curr_ind++] = ' ';
  }
}

int get_num_length(long long num) {
  int num_len = 0;

  while (num != 0) {
    num_len++;
    num /= 10;
  }

  return num_len;
}

int itoa(DestStr* dest, int num_len, long long num) {
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
  dest->str[dest->curr_ind] = '\0';

  return digits_written;
}

void float_to_str(DestStr* dest, double input_num, SpecOptions spec_opts) {
  long long whole_part;  // Целая часть
  double fraction_part;  // Дробная часть

  div_num(input_num, spec_opts.precision, &whole_part, &fraction_part);
  /// здесь еще докидываются потенциально пробелы для width

  int needed_precision = F_PRECISION;
  whole_to_str(dest, whole_part, spec_opts);

  if (spec_opts.precision_set) {
    needed_precision = spec_opts.precision;
  }

  if (!(spec_opts.precision_set && spec_opts.precision == 0)) {
    dest->str[dest->curr_ind++] = '.';
    fract_to_str(dest, fraction_part, needed_precision);
  }

  // // эта часть определяет to which extent надо распечатывать fraction part
  // if (spec_opts.precision_set && spec_opts.precision == 0) {
  //   ;
  // }  // default six
  // else if (!spec_opts.precision_set) {
  //   dest->str[dest->curr_ind++] = '.';
  //   fract_to_str(dest, fraction_part, F_PRECISION);
  // } else {
  //   dest->str[dest->curr_ind++] = '.';
  //   fract_to_str(dest, fraction_part, spec_opts.precision);
  // }
}

void whole_to_str(DestStr* dest, long long num, SpecOptions spec_opts) {
  // Обрабатываем флаги
  apply_flags(dest, &num, spec_opts);

  // Считаем длину числа
  int num_len = get_num_length(num);

  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности
  itoa(dest, num_len, num);

  // Добавляем нуль-терминатор
  dest->str[dest->curr_ind] = '\0';
}

void fract_to_str(DestStr* dest, long long input_num, int needed_precision) {
  // Считаем длину числа
  int num_len = get_num_length(input_num);

  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности
  int i = itoa(dest, num_len, input_num);

  // Доводим число до нужной точности
  while (i < needed_precision) {
    dest->str[dest->curr_ind++] = '0';
    i++;
  }
  dest->str[dest->curr_ind] = '\0';
}

void div_num(double num, int precision, long long* wh, double* fr) {
  // Округляем дробную часть до нужного числа
  double mul = pow(10.0, precision);
  num = round(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

int is_flag(char ch) {
  char* res = s21_strchr(VALID_FLAGS, ch);
  return res == S21_NULL ? 0 : 1;
}

int is_specifier(char ch) {
  char* res = s21_strchr(VALID_SPECIFIERS, ch);
  return res == S21_NULL ? 0 : 1;
}

void parse_flags(const char** format, SpecOptions* spec_opts) {
  while (is_flag(**format)) {
    switch (**format) {
      case '+':
        spec_opts->plus = 1;
        break;
      case '-':
        spec_opts->minus = 1;
        break;
      case ' ':
        spec_opts->space = 1;
        break;
      default:
        break;
    }
    (*format)++;
  }
}

void parse_width(const char** format, SpecOptions* spec_opts) {
  spec_opts->width = 0;
  while (**format != '.' && !is_specifier(**format)) {
    if (isdigit(**format)) {
      spec_opts->width = spec_opts->width * 10 + (**format - '0');
    }
    (*format)++;
  }
}

void parse_precision(const char** format, SpecOptions* spec_opts) {
  while (!is_specifier(**format)) {
    if (isdigit(**format)) {
      spec_opts->precision = spec_opts->precision * 10 + (**format - '0');
      spec_opts->precision_set = 1;
    }
    (*format)++;
  }
  // spec_opts->precision =
  //     spec_opts->precision_set == 0 ? F_PRECISION : spec_opts->precision;
}
