#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_string.h"

// Точность для %f по умолчанию
#define F_PRECISION 6
#define MANTISSA_DIGITS 5

// Валидные флаги и спецификаторы
#define VALID_FLAGS "+- 0#"
#define VALID_SPECIFIERS "cdefginsopuxEGX%"
#define VALID_LENGTHS "Llh"

// Макрос для смены знака числа
#define TO_ABS(x) (x) < 0 ? (-x) : (x)

// Опции функции s21_sprintf
typedef struct SpecifierOptions {
  bool flag_plus;   // Флаг '+'
  bool flag_minus;  // Флаг '-'
  bool flag_space;  // Флаг ' '
  bool flag_zero;   // флаг '0'
  bool flag_sharp;  // флаг '#'
  int width;        // Ширина *.
  int precision;    // Точность .*
  int padding;      // Количество пробелов для width
  long double base;
  int padding_char;
  bool length_l;       // Длина l
  bool length_h;       // Длина h
  bool length_big_l;   // Длина L
  bool precision_set;  // Есть ли precision у спецификатора
  bool is_negative;    // Является ли отр. числом
  bool is_float;       // Является ли float/double
  bool is_char;
  bool is_octal;
  bool is_hexadecimal;
  bool is_hexadecimal_capital;

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
void is_negative(long double num, SpecOptions* spec_opts);

// Функция считает длину целого числа
int get_num_length(long double num, SpecOptions* spec_opts);

// Функция обрабатывает значение width для вывода
void apply_width(DestStr* dest, int num_len, SpecOptions* spec_opts);

// Функция обрабатывает флаги '+', '-' и ' '
void apply_flags(DestStr* dest, SpecOptions* spec_opts);

// Вспомогательная функция для itoa
void reverse_num(DestStr* dest, s21_size_t l_index, s21_size_t r_index);

void process_int(va_list* args, DestStr* dest, SpecOptions* spec_opts);
long long int ingest_int(va_list* args, SpecOptions* spec_opts);
long long unsigned ingest_unsinged(va_list* args, SpecOptions* spec_opts);

// Функция записывает целое число в строку dest
int itoa(DestStr* dest, long double input_num, SpecOptions* spec_opts);

// Функция обрабатывает значение width для вывода, флаг '-'
void apply_minus_width(DestStr* dest, SpecOptions* spec_opts);

// Функция записывает целое число в строку dest
// --------готовое решение с обработкой флагов---------
void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts);

// Функция устанавливает корректную presicion
void set_needed_precision(SpecOptions* spec_opts);

void set_base(SpecOptions* spec_opts);

void set_padding_char(SpecOptions* spec_opts);

// Функция для чисел с плавающей точкой:
//  1. Округляет число до нужной точности
//  2. Делит число на целую и дробную часть
void divide_number(long double num, int precision, long double* wh,
                   long double* fr);

// Функция записывает дробную часть числа в строку dest
void fract_to_str(DestStr* dest, long double num, SpecOptions* spec_opts);

// Функция записывает число с плавающей точкой в строку dest
void float_to_str(DestStr* dest, long double input_num, SpecOptions* spec_opts);

void specE(DestStr* dest, double input_num, SpecOptions* spec_opts,
           const char* format);

void wide_char(DestStr* dest, wchar_t input_char);

void wide_str(DestStr* dest, wchar_t* input_string);

void spec_G(DestStr* dest, double double_input, SpecOptions* spec_opts,
            const char* format);

void pointer_to_str(DestStr* dest, void* ptr, SpecOptions* spec_opts);

// double my_round(double x, unsigned int digits);

int s21_sprintf(char* str, const char* format, ...) {
  setlocale(LC_ALL, "en_US.UTF-8");
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
      set_base(&spec_opts);
      set_padding_char(&spec_opts);

      switch (*format) {
        case 'c': {  // Если c (char)
          if (!spec_opts.length_l) {
            char input_char = va_arg(args, int);
            int num_len = get_num_length(input_char, &spec_opts);

            // Если ширина больше длины числа, добавляем пробелы в начало
            apply_width(&dest, num_len, &spec_opts);

            // Обрабатываем флаги
            apply_flags(&dest, &spec_opts);

            dest.str[dest.curr_ind++] = input_char;
            apply_minus_width(&dest, &spec_opts);
          } else {
            wchar_t input_char = va_arg(args, wchar_t);
            wide_char(&dest, input_char);
          }
          break;
        }

        case 'i':
        case 'd': {
          process_int(&args, &dest, &spec_opts);
          break;
        }
        case 'f': {  // Если f (float)
          long double input_float = 0;
          if (spec_opts.length_big_l) {
            input_float = va_arg(args, long double);
          } else {
            input_float = va_arg(args, double);
          }
          is_negative(input_float, &spec_opts);
          float_to_str(&dest, input_float, &spec_opts);
          break;
        }
        case 's': {
          if (!spec_opts.length_l) {
            char* input_string = va_arg(args, char*);
            s21_strcpy(dest.str + dest.curr_ind, input_string);
            dest.curr_ind += s21_strlen(input_string);
          } else {
            wchar_t* input_string = va_arg(args, wchar_t*);
            wide_str(&dest, input_string);
          }
          break;
        }
        case 'x':
        case 'X':
        case 'o':
        case 'u': {
          unsigned long input_unsingned = 0;

          input_unsingned = ingest_unsinged(&args, &spec_opts);

          // if (spec_opts.length_l) {
          //   input_unsingned = va_arg(args, unsigned long);
          // } else {
          //   input_unsingned = va_arg(args, unsigned);
          // }
          whole_to_str(&dest, input_unsingned, &spec_opts);
          break;
        }
        case 'e':
        case 'E': {
          double double_string = va_arg(args, double);
          is_negative(double_string, &spec_opts);
          specE(&dest, double_string, &spec_opts, format);
          break;
        }
        case 'n': {
          int* counter_n = va_arg(args, int*);
          *counter_n = s21_strlen(dest.str);
          break;
        }
        case 'g':
        case 'G': {
          double double_input = va_arg(args, double);
          is_negative(double_input, &spec_opts);
          spec_G(&dest, double_input, &spec_opts, format);
          break;
        }
        case 'p': {
          void* pointer_str_input = va_arg(args, void*);
          pointer_to_str(&dest, pointer_str_input, &spec_opts);
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

void process_int(va_list* args, DestStr* dest, SpecOptions* spec_opts) {
  long long int input_int = ingest_int(args, spec_opts);
  is_negative(input_int, spec_opts);
  whole_to_str(dest, input_int, spec_opts);
}

long long int ingest_int(va_list* args, SpecOptions* spec_opts) {
  long long int input_int = 0;
  long long int absolute_input = 0;
  if (spec_opts->length_h)  // обрабатываем short
  {
    input_int = va_arg(*args, int);
    absolute_input = TO_ABS(input_int);
    if (absolute_input > SHRT_MAX) {
      input_int = (short)+(input_int);
    }
  } else if (spec_opts->length_l)  // обрабатываем long
  {
    absolute_input = TO_ABS(input_int);
    input_int = va_arg(*args, long int);
    if (absolute_input > LONG_MAX) {
      input_int = (long)+(input_int);
    }
  } else  // обрабатываем простой int
  {
    input_int = va_arg(*args, int);
    absolute_input = TO_ABS(input_int);
    if (absolute_input > INT_MAX) {
      input_int = (int)+(input_int);
    }
  }
  return input_int;
}

long long unsigned ingest_unsinged(va_list* args, SpecOptions* spec_opts) {
  long long unsigned input_unsingned = 0;

  if (spec_opts->length_h)  // обрабатываем short
  {
    input_unsingned = va_arg(*args, unsigned);
    if (input_unsingned > USHRT_MAX) {
      input_unsingned = (short unsigned)+(input_unsingned);
    }
  } else if (spec_opts->length_l)  // обрабатываем long
  {
    input_unsingned = va_arg(*args, long unsigned);
  } else {
    input_unsingned = va_arg(*args, unsigned);
    if (input_unsingned > UINT_MAX) {
      input_unsingned = (unsigned)+(input_unsingned);
    }
  }
  return input_unsingned;
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
        spec_opts->is_float = true;
        break;
      }
    }
  }
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

void parse_format(const char** format, SpecOptions* spec_opts) {
  parse_flags(format, spec_opts);
  parse_width(format, spec_opts);
  parse_precision(format, spec_opts);
  parse_length(format, spec_opts);
  parse_specifier(format, spec_opts);
}

void is_negative(long double num, SpecOptions* spec_opts) {
  spec_opts->is_negative = num < 0.0 ? 1 : 0;
}

int get_num_length(long double num, SpecOptions* spec_opts) {
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

void apply_width(DestStr* dest, int num_len, SpecOptions* spec_opts) {
  int flag_corr;  // Коррекция кол-ва пробелов
  int prec_corr;  // Коррекция кол-ва пробелов

  // Если ширина > длины числа
  if (spec_opts->width > num_len) {
    flag_corr =
        spec_opts->flag_plus || spec_opts->flag_space || spec_opts->is_negative;
    prec_corr =
        spec_opts->precision > num_len ? spec_opts->precision - num_len : 0;

    if (spec_opts->is_float) {
      spec_opts->padding =
          spec_opts->width - num_len - spec_opts->precision - flag_corr - 1;
    } else {
      spec_opts->padding = spec_opts->width - num_len - flag_corr - prec_corr;
    }

    // Если флаг '-' == 0
    if (!spec_opts->flag_minus) {
      for (int i = 0; i < spec_opts->padding; i++)
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
    }
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
  // long double base = 10.0;
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
      // dest->str[dest->curr_ind++] = current_int + '0';
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
    for (int i = 0; i < spec_opts->padding; i++) {
      dest->str[dest->curr_ind++] = ' ';
    }
  }
}

void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts) {
  num = TO_ABS(num);

  int num_len = get_num_length(num, spec_opts);

  if (spec_opts->flag_zero) {
    apply_flags(dest, spec_opts);
  }
  // Если ширина больше длины числа, добавляем пробелы в начало
  apply_width(dest, num_len, spec_opts);

  if (!spec_opts->flag_zero) {
    apply_flags(dest, spec_opts);
  }

  if (!spec_opts->is_float) {
    for (int i = 0; i < spec_opts->precision - num_len; i++)
      dest->str[dest->curr_ind++] = '0';
  }

  // Преобразуем целое число в строку
  itoa(dest, num, spec_opts);

  // Если ширина больше длины числа, добавляем пробелы в конец
  if (!spec_opts->is_float) apply_minus_width(dest, spec_opts);

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
  long double mul = (double)pow(10.0, precision);

  num = lround(num * mul) / mul;

  // Отделяем целую и дробную часть
  *wh = (long long)num;
  *fr = (num - *wh) * mul;
}

void fract_to_str(DestStr* dest, long double input_num,
                  SpecOptions* spec_opts) {
  // Преобразуем целое число в строку и получаем i
  // presicion - i = сколько символов не хватает до нужной точности

  int i = itoa(dest, input_num, spec_opts);

  // Доводим число до нужной точности
  while (i < spec_opts->precision) {
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
  divide_number(input_num, (spec_opts->precision), &whole_part, &fraction_part);

  // Записываем целую часть в строку dest
  whole_to_str(dest, whole_part, spec_opts);

  // if (spec_opts->length_big_l == false) {
  fraction_part = (double)fraction_part;
  // }
  // printf("\n\n%Lf\n\n", fraction_part);

  // Если не спарсили .0 - выводим дробную часть
  if (!(spec_opts->precision_set && !spec_opts->precision)) {
    dest->str[dest->curr_ind++] = '.';

    fract_to_str(dest, fraction_part, spec_opts);
  }
}

void specE(DestStr* dest, double input_num, SpecOptions* spec_opts,
           const char* format) {
  input_num = TO_ABS(input_num);
  long double whole_part = 0;
  long double fraction_part = 0;
  int exponent = 0;
  int sign = 0;  // для обработки знака минуса

  // Обработка нулевого случая
  if (input_num == 0.0) {
    dest->str[dest->curr_ind++] = '0';
    dest->str[dest->curr_ind++] = '.';
    for (int i = 0; i < 6; i++) {  // По умолчанию точность 6
      dest->str[dest->curr_ind++] = '0';
    }
    dest->str[dest->curr_ind++] =
        ((*format == 'e') || (*format == 'g')) ? 'e' : 'E';
    dest->str[dest->curr_ind++] = '+';
    dest->str[dest->curr_ind++] = '0';
    dest->str[dest->curr_ind++] = '0';
    return;
  }

  while (input_num >= 10.0) {
    input_num /= 10.0;
    exponent++;
  }
  while (input_num < 1.0) {
    input_num *= 10.0;
    exponent--;
  }

  if (sign) {
    dest->str[dest->curr_ind++] = '-';
  }

  // Используем float_to_str для форматирования мантиссы
  if (*format == 'g' || *format == 'G') {
    divide_number(input_num, MANTISSA_DIGITS, &whole_part, &fraction_part);

    fraction_part /= pow(10, MANTISSA_DIGITS);
    input_num = whole_part + fraction_part;

    float_to_str(dest, input_num, spec_opts);
    dest->str[dest->curr_ind--] = '\0';
  } else {
    float_to_str(dest, input_num, spec_opts);
  }

  dest->str[dest->curr_ind++] =
      ((*format == 'e') || (*format == 'g')) ? 'e' : 'E';

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

void wide_char(DestStr* dest, wchar_t input_char) {
  char temp[MB_CUR_MAX];
  int len = wctomb(temp, input_char);
  if (len > 0) {
    for (int i = 0; i < len; i++) {
      dest->str[dest->curr_ind++] = temp[i];
    }
  }
}

void wide_str(DestStr* dest, wchar_t* input_string) {
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

void spec_G(DestStr* dest, double double_input, SpecOptions* spec_opts,
            const char* format) {
  double_input = TO_ABS(double_input);
  long double whole_part = 0;
  long double fraction_part = 0;

  divide_number(
      double_input,
      F_PRECISION - get_num_length((long long)double_input, spec_opts),
      &whole_part, &fraction_part);

  long long num_len = get_num_length(whole_part, spec_opts);
  if (num_len <= F_PRECISION) {
    apply_width(dest, num_len, spec_opts);
    apply_flags(dest, spec_opts);
    itoa(dest, double_input, spec_opts);
    if (num_len != F_PRECISION) {
      dest->str[dest->curr_ind++] = '.';
      itoa(dest, lround(fraction_part), spec_opts);
    }

  } else {
    specE(dest, double_input, spec_opts, format);
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
