#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "s21_string.h"

#define VALID_SSCANF_SPECIFIERS "cdeginopuxEGX%"
#define VALID_SSCANF_LENGTHS "Llh"

typedef enum SscanfSpecifier {
  NOT_SET,
  c,
  d,
  i,
  n,
  o,
  u,
  x,
  X,
} SscanfSpecifier;

typedef enum Length { LENGTH_NOT_SET, h, l, L } Length;

typedef struct SpecifierOptions {
  s21_size_t width;
  bool width_set;
  bool is_star;  // Флаг подавления считывания
  SscanfSpecifier specifier;
  Length length;
  bool is_scientific;
  bool is_hexadecimal;
  bool is_negative;
  bool plus_sign_present;
  char next_digit;

} SpecOptions;

typedef struct InputString {
  const char* str;
  s21_size_t curr_ind;
} InputStr;

static void process_initial_space_and_n(va_list* args, InputStr* source,
                                        InputStr* fmt_input);

static bool we_continue_processing(InputStr* fmt_input, bool* matching_failure);

static void process_foreign_char_in_format(InputStr* source,
                                           InputStr* fmt_input,
                                           bool* matching_failure);
static void process_specifier(int* sscanf_result, va_list* args,
                              InputStr* source, InputStr* fmt_input,
                              bool* matching_failure);

static int consume_specifier(va_list* args, InputStr* source,
                             InputStr* fmt_input, bool* matching_failure);

static void parse_format(InputStr* fmt_input, SpecOptions* spec_opts);
static void parse_width(InputStr* fmt_input, SpecOptions* spec_opts);
static bool parse_suppression(InputStr* fmt_input);
static void parse_length(InputStr* fmt_input, SpecOptions* spec_opts);
static bool is_specifier(char ch);
static void parse_specifier(InputStr fmt_input, SpecOptions* spec_opts);
static void read_next_digit_in_fmt(InputStr fmt_input, SpecOptions* spec_opts);

static bool n_specifier_follows(InputStr* fmt_input);
static bool c_specifier_follows(InputStr* fmt_input);

static void process_percent(InputStr* source);
static void process_space(InputStr* source, InputStr* fmt_input);
static void consume_space(InputStr* source);

static int process_chars(va_list* args, InputStr* source,
                         SpecOptions* spec_opts);
static int read_wide_char(va_list* args, InputStr* source,
                          SpecOptions* spec_opts);
static int read_narrow_char(va_list* args, InputStr* source,
                            SpecOptions* spec_opts);

static void process_n(va_list* args, InputStr* source);

static int process_strings(va_list* args, InputStr* source,
                           SpecOptions* spec_opts);
static int read_wide_string(va_list* args, InputStr* source,
                            SpecOptions* spec_opts);
static int read_narrow_string(va_list* args, InputStr* source,
                              SpecOptions* spec_opts);

static int read_pointer(va_list* args, InputStr* source,
                        SpecOptions* spec_opts);

static int process_int(va_list* args, SpecOptions* spec_opts, InputStr* source,
                       bool* matching_failure);
static int process_unsigned(va_list* args, SpecOptions* spec_opts,
                            InputStr* source, bool* matching_failure);
static int read_decimal(InputStr* source, SpecOptions* spec_opts,
                        long long unsigned* dest_input_pointer,
                        bool* matching_failure);
static int read_hex(InputStr* source, SpecOptions* spec_opts,
                    long long unsigned* dest_input_pointer,
                    bool* matching_failure);
static int read_octal(InputStr* source, SpecOptions* spec_opts,
                      long long unsigned* dest_input_pointer,
                      bool* matching_failure);
static s21_size_t get_octal_num_length(InputStr* source, SpecOptions* spec_opts,
                                       s21_size_t base);
static void write_to_unsigned_pointer(
    va_list* args, SpecOptions* spec_opts,
    long long unsigned temp_long_long_unsigned_destination);
static void write_to_integer_pointer(
    va_list* args, SpecOptions* spec_opts,
    long long unsigned temp_unsigned_destination, int sign);
static bool hexadecimal_prefix_follows(InputStr* source);

static int process_float(va_list* args, SpecOptions* spec_opts,
                         InputStr* source);
static bool is_inf(InputStr* source);
static bool is_nan(InputStr* source);
static int read_float(InputStr* source, long double* dest_input_pointer,
                      SpecOptions* spec_opts);
static int read_whole_part(InputStr* source, long double* int_part,
                           s21_size_t* bytes_read, SpecOptions* spec_opts);
static int read_fractional_part(InputStr* source, long double* frac_part,
                                long long* frac_div, s21_size_t* bytes_read,
                                SpecOptions* spec_opts);
static int read_exponent(InputStr* source, int* exponent, int* exponent_sign,
                         s21_size_t* bytes_read, SpecOptions* spec_opts);
static void write_to_floating_point_number_pointer(
    va_list* args, SpecOptions* spec_opts,
    long double temp_floating_destination);

static bool is_valid_digit(char incoming_char, s21_size_t base);

static bool width_limit_reached(s21_size_t bytes_read, SpecOptions* spec_opts);

static char to_lower_char(char incoming_char);

static void set_locale_for_wide_chars();

static bool is_end_of_string(InputStr* string_structure);
static bool is_space(char input_char);
static bool is_space_specifier(InputStr* fmt_input);

#endif  // S21_SSCANF_H_