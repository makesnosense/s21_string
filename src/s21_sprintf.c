#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define F_PRESICION 6

typedef struct Options {
  int plus;    // Флаг '+'
  int minus;   // Флаг '-'
  int space;   // Флаг ' '
  int width;   // Ширина *.
  int prec;    // Точность .*
  int prec_i;  // Опция для целых чисел
  int prec_f;  // Была ли задана precision для спецификатора
} Options;

typedef struct DestinationString {
  char* str;
  s21_size_t curr_ind;
} DestStr;

void apply_flags(DestStr* dest, long long* num, Options opts, int prec);
int get_num_length(long long num);
int whole_number_to_str(DestStr* dest, int num_len, long long num);
void int_to_str(DestStr* dest, long long num, Options opts, int prec);
void div_num(double num, double mul, long long* wh, double* fr);
void float_to_str(DestStr* dest, double num, Options opts);
int is_flag(char* flags, char ch);
int is_spec(char* specs, char ch);
void parse_flags(char* flags, const char** format, Options* opts);
void parse_width(char* specs, const char** format, Options* opts);
void parse_precision(char* specs, const char** format, Options* opts);

int s21_sprintf(char* str, const char* format, ...);

// %[flags][width][.precision][length][specifier]
int s21_sprintf(char* str, const char* format, ...) {
  DestStr dest = {str, 0};
  int res = 0;  // Результат работы функции
  char* flags = "+- ";
  char* specs = "cidfsu";
  Options opts = {0};
  opts.prec_i = -1;

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      parse_flags(flags, &format, &opts);
      parse_width(specs, &format, &opts);
      parse_precision(specs, &format, &opts);
      switch (*format) {
        case 'c': {  // Если c (char)
          char c = va_arg(args, int);
          dest.str[dest.curr_ind++] = c;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
          int d = va_arg(args, int);
          int_to_str(&dest, d, opts, opts.prec_i);
          break;
        }
        case 'f': {  // Если f (float)
          float input_float = va_arg(args, double);
          float_to_str(&dest, input_float, opts);
          break;
        }
        case 's': {
          char* s = va_arg(args, char*);
          s21_strcpy(dest.str + dest.curr_ind, s);
          dest.curr_ind += s21_strlen(s);
          break;
        }
        case 'u': {
          unsigned u = va_arg(args, unsigned);
          int_to_str(&dest, u, opts, opts.prec_i);
          break;
        }
        default:
          break;
      }
    } else {
      dest.str[dest.curr_ind++] = *format;
    }
    opts.plus = 0;
    opts.minus = 0;
    opts.space = 0;
    format++;
  }
  dest.str[dest.curr_ind] = '\0';
  va_end(args);

  return res;
}

// Флаги '+', '-' и ' '
void apply_flags(DestStr* dest, long long* num, Options opts, int prec) {
  if (*num < 0) {
    dest->str[dest->curr_ind++] = '-';
    *num *= -1;
  } else if (opts.plus && prec == -1) {
    dest->str[dest->curr_ind++] = '+';
  } else if (opts.space) {
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

// Преобразуем число в строку
int whole_number_to_str(DestStr* dest, int num_len, long long num) {
  int res = 0;

  if (num_len == 0) {
    dest->str[dest->curr_ind++] = '0';
    res++;
  } else {
    while (num_len != 0) {
      long long temp = pow(10, --num_len);
      dest->str[dest->curr_ind++] = (num / temp) + '0';
      num %= temp;
      res++;
    }
  }
  return res;
}

// Функция для преобразования целого числа в строку
void int_to_str(DestStr* dest, long long num, Options opts, int prec) {
  // Обрабатываем флаги
  apply_flags(dest, &num, opts, prec);

  // Считаем длину числа
  int num_len = get_num_length(num);

  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности
  int i = whole_number_to_str(dest, num_len, num);

  while (i < prec && prec != -1) {
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

void float_to_str(DestStr* dest, double num, Options opts) {
  double multiplier;  // Множитель для округления числа
  long long whole;    // Целая часть
  double fract;       // Дробная часть

  // Если считали precision, но она == 0
  if (opts.prec_f && !opts.prec) {
    multiplier = pow(10.0, opts.prec);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(dest, whole, opts, opts.prec_i);

    // Если не считали precision
  } else if (!opts.prec_f) {
    multiplier = pow(10.0, F_PRESICION);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(dest, whole, opts, opts.prec_i);
    dest->str[dest->curr_ind++] = '.';
    int_to_str(dest, fract, opts, F_PRESICION);

    // Иначе
  } else {
    multiplier = pow(10.0, opts.prec);
    div_num(num, multiplier, &whole, &fract);

    int_to_str(dest, whole, opts, opts.prec_i);
    dest->str[dest->curr_ind++] = '.';
    int_to_str(dest, fract, opts, opts.prec);
  }
}

int is_flag(char* flags, char ch) {
  char* res = s21_strchr(flags, ch);
  return res == S21_NULL ? 0 : 1;
}

int is_spec(char* specs, char ch) {
  char* res = s21_strchr(specs, ch);
  return res == S21_NULL ? 0 : 1;
}

void parse_flags(char* flags, const char** format, Options* opts) {
  while (is_flag(flags, **format)) {
    switch (**format) {
      case '+':
        opts->plus = 1;
        break;
      case '-':
        opts->minus = 1;
        break;
      case ' ':
        opts->space = 1;
        break;
      default:
        break;
    }
    (*format)++;
  }
}

void parse_width(char* specs, const char** format, Options* opts) {
  int res = 0;
  opts->width = 0;

  while (**format != '.' && !is_spec(specs, **format)) {
    if (isdigit(**format)) {
      opts->width = opts->width * 10 + (**format - '0');
      res++;
    }
    (*format)++;
  }
}

void parse_precision(char* specs, const char** format, Options* opts) {
  int res = 0;
  opts->prec = 0;

  while (!is_spec(specs, **format)) {
    if (isdigit(**format)) {
      opts->prec = opts->prec * 10 + (**format - '0');
      res++;
    }
    (*format)++;
  }
  opts->prec_f = res;
}
