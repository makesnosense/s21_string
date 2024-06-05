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
#define VALID_LENGTHS "Llh"

// Макрос для смены знака числа
#define TO_ABS(x) (x) < 0 ? (-x) : (x)

// Опции функции s21_sprintf
typedef struct SpecifierOptions {
  bool plus;           // Флаг '+'
  bool minus;          // Флаг '-'
  bool space;          // Флаг ' '
  int width;           // Ширина *.
  int precision;       // Точность .*
  int padding;         // Количество пробелов для width
  bool length_l;       // Длина l
  bool length_h;       // Длина h
  bool length_big_l;   // Длина L
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

// Функция возвращает 1, если ch - это длина
int is_length(char ch);

// Функция парсит флаги для спецификатора
void parse_flags(const char** format, SpecOptions* spec_opts);

// Функция парсит ширину для спецификатора
void parse_width(const char** format, SpecOptions* spec_opts);

// Функция парсит точность для спецификатора
void parse_precision(const char** format, SpecOptions* spec_opts);

// Функция парсит длины l и h
void parse_length(const char** format, SpecOptions* spec_opts);

// Функция парсит сразу весь формат
void parse_format(const char** format, SpecOptions* spec_opts);

// Функция устанавливает флаг is_negative
void is_negative_int(long long num, SpecOptions* spec_opts);

// Функция устанавливает флаг is_negative
void is_negative_float(long double num, SpecOptions* spec_opts);

// Функция считает длину целого числа
int get_num_length(long long num);

// Функция обрабатывает значение width для вывода
void apply_width(DestStr* dest, int num_len, SpecOptions* spec_opts);

// Функция обрабатывает флаги '+', '-' и ' '
void apply_flags(DestStr* dest, SpecOptions spec_opts);

// Вспомогательная функция для itoa
void reverse_num(DestStr* dest, s21_size_t l_index, s21_size_t r_index);

// Функция записывает целое число в строку dest
int itoa(DestStr* dest, long double input_num);

// Функция обрабатывает значение width для вывода, флаг '-'
void apply_minus_width(DestStr* dest, SpecOptions spec_opts);

// Функция записывает целое число в строку dest
// --------готовое решение с обработкой флагов---------
void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts);

// Функция устанавливает корректную presicion
void set_needed_precision(SpecOptions* spec_opts);

// Функция для чисел с плавающей точкой:
//  1. Округляет число до нужной точности
//  2. Делит число на целую и дробную часть
void divide_number(long double num, int precision, long double* wh,
                   long double* fr);

// Функция записывает дробную часть числа в строку dest
void fract_to_str(DestStr* dest, long double num, SpecOptions spec_opts);

// Функция записывает число с плавающей точкой в строку dest
void float_to_str(DestStr* dest, long double input_num, SpecOptions* spec_opts);

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
      parse_format(&format, &spec_opts);
      switch (*format) {
        case 'c': {  // Если c (char)
          char input_char = va_arg(args, int);
          dest.str[dest.curr_ind++] = input_char;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
          long long int input_int = 0;
          if (spec_opts.length_l) {
            input_int = va_arg(args, long int);
          } else {
            input_int = va_arg(args, int);
          }
          is_negative_int(input_int, &spec_opts);
          whole_to_str(&dest, input_int, &spec_opts);
          break;
        }
        case 'f': {  // Если f (float)
          spec_opts.is_float = 1;
          long double input_float = 0;
          if (spec_opts.length_big_l) {
            input_float = va_arg(args, long double);
          } else {
            input_float = va_arg(args, double);
          }

          is_negative_float(input_float, &spec_opts);

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
          unsigned long input_unsingned = 0;
          if (spec_opts.length_l) {
            input_unsingned = va_arg(args, unsigned long);
          } else {
            input_unsingned = va_arg(args, unsigned);
          }
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

int is_length(char ch) {
  char* res = s21_strchr(VALID_LENGTHS, ch);
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
  while (**format != '.' && !is_specifier(**format) && !is_length(**format)) {
    if (isdigit(**format)) {
      spec_opts->width = spec_opts->width * 10 + (**format - '0');
    }
    (*format)++;
  }
}

void parse_precision(const char** format, SpecOptions* spec_opts) {
  while (!is_specifier(**format) && !is_length(**format)) {
    if (isdigit(**format)) {
      spec_opts->precision = spec_opts->precision * 10 + (**format - '0');
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
      default:
        break;
    }
    (*format)++;
  }
}

void parse_format(const char** format, SpecOptions* spec_opts) {
  parse_flags(format, spec_opts);
  parse_width(format, spec_opts);
  parse_precision(format, spec_opts);
  parse_length(format, spec_opts);
}

void is_negative_int(long long num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0 ? 1 : 0;
}

void is_negative_float(long double num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0.0 ? 1 : 0;
}

int get_num_length(long long num) {
  int num_len = 0;

  if (num == 0) {
    num_len++;
  } else {
    while (num != 0) {
      num_len++;
      num /= 10;
    }
  }

  return num_len;
}

void apply_width(DestStr* dest, int num_len, SpecOptions* spec_opts) {
  int flag_corr;  // Коррекция кол-ва пробелов
  int prec_corr;  // Коррекция кол-ва пробелов

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

int itoa(DestStr* dest, long double input_num) {
  int current_int = 0;
  int num_len = 0;
  long double base = 10.0;
  s21_size_t l_index = dest->curr_ind;

  if (input_num == 0) {
    dest->str[dest->curr_ind++] = '0';
    num_len++;
  } else {
    while (input_num >= 1) {
      current_int = (int)fmodl(input_num, base);
      dest->str[dest->curr_ind++] = current_int + '0';
      input_num /= base;
      num_len++;
    }
    s21_size_t r_index = dest->curr_ind - 1;
    reverse_num(dest, l_index, r_index);
  }
  dest->str[dest->curr_ind] = '\0';

  return num_len;
}

void apply_minus_width(DestStr* dest, SpecOptions spec_opts) {
  // Если ширина > длины числа и флаг '-' == 1
  if (spec_opts.minus) {
    for (int i = 0; i < spec_opts.padding; i++) {
      dest->str[dest->curr_ind++] = ' ';
    }
  }
}

void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts) {
  num = TO_ABS(num);

  int num_len = get_num_length(num);
  // Если ширина больше длины числа, добавляем пробелы в начало
  apply_width(dest, num_len, spec_opts);

  // Обрабатываем флаги
  apply_flags(dest, *spec_opts);

  if (!spec_opts->is_float) {
    for (int i = 0; i < spec_opts->precision - num_len; i++)
      dest->str[dest->curr_ind++] = '0';
  }

  // Преобразуем целое число в строку
  itoa(dest, num);

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

void divide_number(long double num, int precision, long double* wh,
                   long double* fr) {
  // Округляем дробную часть до нужного числа
  long double mul = (float)pow(10.0, precision);

  num = round(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

void fract_to_str(DestStr* dest, long double input_num, SpecOptions spec_opts) {
  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности

  int i = itoa(dest, input_num);

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

void float_to_str(DestStr* dest, long double input_num,
                  SpecOptions* spec_opts) {
  input_num = TO_ABS(input_num);
  long double whole_part = 0;     // Целая часть
  long double fraction_part = 0;  // Дробная часть

  // Если спарсили precision, то присваиваем его значение
  set_needed_precision(spec_opts);

  // Делим число на целую и дробную часть
  divide_number(input_num, spec_opts->precision, &whole_part, &fraction_part);

  // Записываем целую часть в строку dest
  whole_to_str(dest, whole_part, spec_opts);

  // if (spec_opts->length_big_l == false) {
  fraction_part = (float)fraction_part;
  // }
  // printf("\n\n%Lf\n\n", fraction_part);

  // Если не спарсили .0 - выводим дробную часть
  if (!(spec_opts->precision_set && !spec_opts->precision)) {
    dest->str[dest->curr_ind++] = '.';

    fract_to_str(dest, fraction_part, *spec_opts);
  }
}
