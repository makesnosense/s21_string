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
  bool flag_plus;        // Флаг '+'
  bool flag_minus;       // Флаг '-'
  bool flag_space;       // Флаг ' '
  bool flag_zero;        // флаг '0'
  bool flag_sharp;       // флаг '#'
  s21_size_t width;      // Ширина *.
  s21_size_t precision;  // Точность .*
  s21_size_t padding;    // Количество пробелов для width
  long double base;
  int padding_char;
  int exponent_char;
  bool length_l;       // Длина l
  bool length_h;       // Длина h
  bool length_big_l;   // Длина L
  bool precision_set;  // Есть ли precision у спецификатора
  bool is_negative;    // Является ли отр. числом
  bool is_floating_point_number;  // Является ли float/double
  bool is_char;
  bool is_octal;
  bool is_hexadecimal;
  bool is_hexadecimal_capital;
  bool is_scientific;
  bool is_scientific_capital;
  bool is_spec_g;
  bool is_spec_g_capital;

} SpecOptions;

typedef struct DestinationString {
  char* str;
  s21_size_t curr_ind;
} DestStr;

// %[flags][width][.precision][length][specifier]
int s21_sprintf(char* str, const char* format, ...);

int is_flag(char ch);
int is_specifier(char ch);
int is_length(char ch);

void parse_flags(const char** format, SpecOptions* spec_opts);
void parse_width(const char** format, va_list args, SpecOptions* spec_opts);
void parse_precision(const char** format, va_list args, SpecOptions* spec_opts);
void parse_length(const char** format, SpecOptions* spec_opts);
void parse_format(const char** format, va_list args, SpecOptions* spec_opts);
void parse_specifier(const char** format, SpecOptions* spec_opts);

void set_needed_precision(SpecOptions* spec_opts);
void set_base(SpecOptions* spec_opts);
void set_padding_char(SpecOptions* spec_opts);
void set_exponent_char(SpecOptions* spec_opts);

void is_negative(long double num, SpecOptions* spec_opts);
s21_size_t get_num_length(long double num, SpecOptions* spec_opts);

void apply_width(DestStr* dest, s21_size_t num_len, SpecOptions* spec_opts);
void apply_minus_width(DestStr* dest, SpecOptions* spec_opts);
void apply_flags(DestStr* dest, SpecOptions* spec_opts);

void process_chars(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_narrow_char(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_wide_char(va_list* args, DestStr* dest);
void process_strings(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_narrow_string(char* string, DestStr* dest, SpecOptions* spc_opts);
void process_wide_string(va_list* args, DestStr* dest);
void process_int(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_unsigned(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_floating_point_number(va_list* args, DestStr* dest,
                                   SpecOptions* spec_opts);
void process_scientific(DestStr* dest, long double input_num,
                        SpecOptions* spec_opts);
void process_scientific_zero_input(DestStr* dest, SpecOptions* spec_opts);
void process_scientific_for_g_spec(long double input_num, DestStr* dest,
                                   SpecOptions* spec_opts);
void spec_G(DestStr* dest, double double_input, SpecOptions* spec_opts);

long long int ingest_int(va_list* args, SpecOptions* spec_opts);
long long unsigned ingest_unsinged(va_list* args, SpecOptions* spec_opts);
long double ingest_floating_point_number(va_list* args, SpecOptions* spec_opts);

// Функция записывает целое число в строку dest
int itoa(DestStr* dest, long double input_num, SpecOptions* spec_opts);
void reverse_num(DestStr* dest, s21_size_t l_index, s21_size_t r_index);

void floating_point_number_to_str(DestStr* dest, long double input_num,
                                  SpecOptions* spec_opts);
void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts);
void fraction_to_str(DestStr* dest, long double num, SpecOptions* spec_opts);
void pointer_to_str(DestStr* dest, void* ptr, SpecOptions* spec_opts);

void divide_number(long double num, int precision, long double* wh,
                   long double* fr);
long double multiply_by_10_n_times(long double input_num, s21_size_t n);
long double divide_by_10_n_times(long double input_num, s21_size_t n);
long long scale_input_and_calculate_exponent(long double* input_num);
void add_zeros_to_destination(DestStr* dest, s21_size_t n_zeros_to_add);

// Функция устанавливает локаль в зависимости от ОС
void set_locale_for_wide_chars();
