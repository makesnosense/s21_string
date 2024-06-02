#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// Точность для %f по умолчанию
#define F_PRECISION 6

// Валидные флаги и спецификаторы
#define VALID_FLAGS "+- "
#define VALID_SPECIFIERS "cidfsu"

// Макрос для смены знака числа
#define TO_ABS(x) (x) < 0 ? -(x) : (x)

// Опции функции s21_sprintf
typedef struct SpecifierOptions {
  bool plus;           // Флаг '+'
  bool minus;          // Флаг '-'
  bool space;          // Флаг ' '
  int width;           // Ширина *.
  int precision;       // Точность .*
  int padding;         // Количество пробелов для width
  bool precision_set;  // Есть ли precision у спецификатора
  bool is_float;       // Является ли float/double
  bool is_negative;    // Является ли отр. числом
} SpecOptions;

// Структура для строки-буфера
typedef struct DestinationString {
  char* str;
  s21_size_t curr_ind;
} DestStr;

// %[flags][width][.precision][length][specifier]
int s21_sprintf(char* str, const char* format, ...);

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

// Функция устанавливает флаг is_negative
void is_negative_int(long long num, SpecOptions* spec_opts);

// Функция устанавливает флаг is_negative
void is_negative_float(double num, SpecOptions* spec_opts);

// Функция считает длину целого числа
int get_num_length(long long num);

// Функция корректирует num_len для случая нуля
int null_correction(int num_len);

// Функция обрабатывает значение width для вывода
void apply_width(DestStr* dest, int num_len, SpecOptions* spec_opts);

// Функция обрабатывает флаги '+', '-' и ' '
void apply_flags(DestStr* dest, SpecOptions spec_opts);

// Функция записывает целое число в строку dest
int itoa(DestStr* dest, int num_len, long long num);

// Функция обрабатывает значение width для вывода, флаг '-'
void apply_minus_width(DestStr* dest, SpecOptions spec_opts);

// Функция записывает целое число в строку dest
// --------готовое решение с обработкой флагов---------
void whole_to_str(DestStr* dest, long long num, SpecOptions* spec_opts);

// Функция устанавливает корректную presicion
void set_needed_precision(SpecOptions* spec_opts);

// Функция для чисел с плавающей точкой:
//  1. Округляет число до нужной точности
//  2. Делит число на целую и дробную часть
void divide_number(double num, int precision, long long* wh, double* fr);

// Функция записывает дробную часть числа в строку dest
void fract_to_str(DestStr* dest, long long num, SpecOptions spec_opts);

// Функция записывает число с плавающей точкой в строку dest
void float_to_str(DestStr* dest, double num, SpecOptions* spec_opts);

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
          long long int input_int = va_arg(args, int);
          is_negative_int(input_int, &spec_opts);

          input_int = TO_ABS(input_int);
          whole_to_str(&dest, input_int, &spec_opts);
          break;
        }
        case 'f': {  // Если f (float)
          spec_opts.is_float = 1;
          float input_float = va_arg(args, double);
          is_negative_float(input_float, &spec_opts);
          input_float = TO_ABS(input_float);
          float_to_str(&dest, input_float, &spec_opts);
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
          whole_to_str(&dest, input_unsingned, &spec_opts);
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
}

void is_negative_int(long long num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0 ? 1 : 0;
}

void is_negative_float(double num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0.0 ? 1 : 0;
}

int get_num_length(long long num) {
  int num_len = 0;

  while (num != 0) {
    num_len++;
    num /= 10;
  }

  return num_len;
}

int null_correction(int num_len) {
  return num_len == 0 ? num_len + 1 : num_len;
}

void apply_width(DestStr* dest, int num_len, SpecOptions* spec_opts) {
  int flag_corr;  // Коррекция кол-ва пробелов
  int prec_corr;  // Коррекция кол-ва пробелов

  // Коррекция для нуля
  num_len = null_correction(num_len);

  // Если ширина > длины числа
  if (spec_opts->width > num_len) {
    flag_corr = spec_opts->plus || spec_opts->space || spec_opts->is_negative;
    prec_corr =
        spec_opts->precision > num_len ? spec_opts->precision - num_len : 0;

    if (spec_opts->is_float) {
      spec_opts->padding =
          spec_opts->width - num_len - spec_opts->precision - flag_corr - 1;
    } else {
      spec_opts->padding = spec_opts->width - num_len - flag_corr - prec_corr;
    }

    // Если флаг '-' == 0
    if (!spec_opts->minus) {
      for (int i = 0; i < spec_opts->padding; i++)
        dest->str[dest->curr_ind++] = ' ';
    }
  }
}

void apply_flags(DestStr* dest, SpecOptions spec_opts) {
  if (spec_opts.is_negative) {
    dest->str[dest->curr_ind++] = '-';
  } else if (spec_opts.plus) {
    dest->str[dest->curr_ind++] = '+';
  } else if (spec_opts.space) {
    dest->str[dest->curr_ind++] = ' ';
  }
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

void apply_minus_width(DestStr* dest, SpecOptions spec_opts) {
  // Если ширина > длины числа и флаг '-' == 1
  if (spec_opts.minus) {
    for (int i = 0; i < spec_opts.padding; i++) {
      dest->str[dest->curr_ind++] = ' ';
    }
  }
}

void whole_to_str(DestStr* dest, long long num, SpecOptions* spec_opts) {
  // Считаем длину числа
  int num_len = get_num_length(num);
  // num = (-1) * (num);
  // printf("\n%lld\n", num);
  // Если ширина больше длины числа, добавляем пробелы в начало
  apply_width(dest, num_len, spec_opts);

  // Обрабатываем флаги
  apply_flags(dest, *spec_opts);

  if (!spec_opts->is_float) {
    num_len = null_correction(num_len);
    for (int i = 0; i < spec_opts->precision - num_len; i++)
      dest->str[dest->curr_ind++] = '0';
  }

  // Преобразуем целое число в строку
  itoa(dest, num_len, num);

  // Если ширина больше длины числа, добавляем пробелы в конец
  if (!spec_opts->is_float) apply_minus_width(dest, *spec_opts);

  // Добавляем нуль-терминатор
  dest->str[dest->curr_ind] = '\0';
}

void set_needed_precision(SpecOptions* spec_opts) {
  if (!spec_opts->precision_set) {
    spec_opts->precision = F_PRECISION;
  }
}

void divide_number(double num, int precision, long long* wh, double* fr) {
  // Округляем дробную часть до нужного числа
  double mul = pow(10.0, precision);
  num = round(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

void fract_to_str(DestStr* dest, long long input_num, SpecOptions spec_opts) {
  // Считаем длину числа
  int num_len = get_num_length(input_num);

  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности
  int i = itoa(dest, num_len, input_num);

  // Доводим число до нужной точности
  while (i < spec_opts.precision) {
    dest->str[dest->curr_ind++] = '0';
    i++;
  }

  // Добавляем пробелы в конец, если флаг '-'
  apply_minus_width(dest, spec_opts);

  // Добавляем нуль-терминатор
  dest->str[dest->curr_ind] = '\0';
}

void float_to_str(DestStr* dest, double input_num, SpecOptions* spec_opts) {
  long long whole_part;  // Целая часть
  double fraction_part;  // Дробная часть

  // Если спарсили precision, то присваиваем его значение
  set_needed_precision(spec_opts);

  // Делим число на целую и дробную часть
  divide_number(input_num, spec_opts->precision, &whole_part, &fraction_part);

  // Записываем целую часть в строку dest
  whole_to_str(dest, whole_part, spec_opts);

  // Если не спарсили .0 - выводим дробную часть
  if (!(spec_opts->precision_set && !spec_opts->precision)) {
    dest->str[dest->curr_ind++] = '.';
    fract_to_str(dest, fraction_part, *spec_opts);
  }
}
