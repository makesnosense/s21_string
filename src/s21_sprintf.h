#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include <ctype.h>
#include <float.h>
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

#define DEFAULT_F_PRECISION 6
#define MANTISSA_DIGITS 5
#define EPSILON (LDBL_EPSILON * 100)

#define VALID_FLAGS "+- 0#"
#define VALID_SPECIFIERS "cdefginsopuxEFGX%"
#define VALID_LENGTHS "Llh"

#define TO_ABS(x) (x) < 0 ? (-x) : (x)

typedef enum Specifier {
  NOT_SET,
  c,
  d,
  e,
  E,
  f,
  g,
  G,
  i,
  n,
  s,
  o,
  p,
  u,
  x,
  X
} Specifier;

typedef struct SpecifierOptions {
  bool flag_plus;
  bool flag_minus;
  bool flag_space;
  bool flag_zero;
  bool flag_sharp;
  s21_size_t width;      // width *.
  s21_size_t precision;  // precision .*
  s21_size_t padding;    // n spaces for width
  long double base;
  int padding_char;
  int exponent_char;
  bool length_l;
  bool length_h;
  bool length_big_l;
  bool precision_set;  // if precision is set
  bool is_zero;
  bool is_negative;
  bool is_decimal_integer;
  bool is_floating_point_number;
  bool is_hexadecimal;
  bool is_g_spec;
  bool is_unsigned_type;
  Specifier specifier;
  bool is_scientific;
} SpecOptions;

typedef struct DestinationString {
  char* str;
  s21_size_t curr_ind;
} DestStr;

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
s21_size_t get_num_length_simple(long double num);

void apply_flags(DestStr* dest, SpecOptions* spec_opts);
void calculate_padding(s21_size_t num_len, SpecOptions* spec_opts);
void calculate_padding_not_ge_spec(s21_size_t num_len, SpecOptions* spec_opts);
void calculate_padding_ge_spec(s21_size_t num_len, SpecOptions* spec_opts);
void calculate_padding_diopux(s21_size_t num_len, SpecOptions* spec_opts);

void apply_width(DestStr* dest, s21_size_t num_len, SpecOptions* spec_opts);
void apply_minus_width(DestStr* dest, SpecOptions* spec_opts);

void process_specifier(char format_char, va_list* args, DestStr* dest,
                       SpecOptions* spec_opts);
void process_pointer(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_chars(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_narrow_char(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_wide_char(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_strings(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_narrow_string(char* string, DestStr* dest, SpecOptions* spc_opts);
void process_wide_string(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_int(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_unsigned(va_list* args, DestStr* dest, SpecOptions* spec_opts);
void process_floating_point_number(va_list* args, DestStr* dest,
                                   SpecOptions* spec_opts);
void process_scientific(DestStr* dest, long double input_num,
                        SpecOptions* spec_opts);
void process_scientific_standard(DestStr* dest, long double input_num,
                                 SpecOptions* spec_opts);
void process_scientific_zero_input(DestStr* dest, SpecOptions* spec_opts);
void add_scientific_e_part(long long exponent, DestStr* dest,
                           SpecOptions* spec_opts);

void process_g_spec(DestStr* dest, long double input_num,
                    SpecOptions* spec_opts);
bool g_spec_scientific_needed(long double input_num, SpecOptions* spec_opts);

void process_g_spec_not_set_precision(DestStr* dest, long double input_num,
                                      SpecOptions* spec_opts);

void process_g_spec_not_set_precision_sharp_on(DestStr* dest,
                                               long double input_num,
                                               SpecOptions* spec_opts);

void process_g_spec_not_set_precision_sharp_off(DestStr* dest,
                                                long double input_num,
                                                SpecOptions* spec_opts);

void process_g_spec_zero_precision(DestStr* dest, long double input_num,
                                   SpecOptions* spec_opts);
void process_g_spec_nonzero_precision(DestStr* dest, long double input_num,
                                      SpecOptions* spec_opts);
void process_g_spec_zero_wholepart_nonzero_precision(DestStr* dest,
                                                     long double input_num,
                                                     SpecOptions* spec_opts);

void process_scientific_for_g_spec(DestStr* dest, long double input_num,
                                   SpecOptions* spec_opts);

void process_scientific_for_g_spec_not_set_precision(DestStr* dest,
                                                     long double input_num,
                                                     SpecOptions* spec_opts);
void process_scientific_for_g_spec_precision_set(DestStr* dest,
                                                 long double input_num,
                                                 SpecOptions* spec_opts);

long long int ingest_int(va_list* args, SpecOptions* spec_opts);
long long unsigned ingest_unsinged(va_list* args, SpecOptions* spec_opts);
long double ingest_floating_point_number(va_list* args, SpecOptions* spec_opts);

int itoa(DestStr* dest, long double input_num, SpecOptions* spec_opts);
void reverse_num(DestStr* dest, s21_size_t l_index, s21_size_t r_index);

void floating_point_number_to_str(DestStr* dest, long double input_num,
                                  SpecOptions* spec_opts);
void whole_to_str(DestStr* dest, long double num, SpecOptions* spec_opts);
void pointer_to_str(DestStr* dest, void* ptr, SpecOptions* spec_opts);

long double round_to_n_digits(long double input_num, s21_size_t n_digits);
long double multiply_by_10_n_times(long double input_num, s21_size_t n);
long double divide_by_10_n_times(long double input_num, s21_size_t n);
long long calculate_exponent(long double input_num);
long double scale_input_to_one_digit(long double input_num);
long double scale_input_to_n_digits(long double input_num, s21_size_t n);
void add_zeros_to_destination(DestStr* dest, s21_size_t n_zeros_to_add);
long double scale_to_one_digit_significand(long double input_num);
void remove_trailing_zeros(DestStr* dest, SpecOptions* spec_opts);
long double bank_roundl(long double input_num);
bool is_zero(long double input_num);
bool is_diopux(SpecOptions* spec_opts);
void set_locale_for_wide_chars();

#endif  // SRC_S21_SPRINTF_H_
