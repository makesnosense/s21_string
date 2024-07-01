#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define VALID_SSCANF_SPECIFIERS "cdinxoX%"
typedef enum SscanfSpecifier { NOT_SET, c, d, i, n, x, o, X } SscanfSpecifier;

typedef struct SpecifierOptions {
  s21_size_t width;
  bool width_set;
  bool is_star;  // Флаг подавления считывания
  SscanfSpecifier specifier;
  bool is_hexadecimal;
  bool is_minus;

} SpecOptions;

typedef struct InputString {
  const char* str;
  s21_size_t curr_ind;
} InputStr;

int consume_specifier(va_list* args, InputStr* source, InputStr* fmt_input,
                      bool* matching_failure);

bool n_specifier_follows(InputStr* fmt_input);
bool is_n_star_present(InputStr* fmt_input);
bool c_specifier_follows(InputStr* fmt_input);

bool is_end_of_string(InputStr* string_structure);
bool is_space(char input_char);
bool is_space_specifier(InputStr* fmt_input);

bool we_continue_consuming(InputStr* source, InputStr* fmt_input,
                           bool* matching_failure);

void consume_space(InputStr* source);
void consume_initial_space_and_n(va_list* args, InputStr* source,
                                 InputStr* fmt_input);

void process_n(va_list* args, InputStr* source, bool n_star);
int read_char(va_list* args, InputStr* source, SpecOptions* spec_opts);
int read_int(va_list* args, SpecOptions* spec_opts, InputStr* source,
             bool* matching_failure);
int read_decimal(InputStr* source, SpecOptions* spec_opts,
                 long unsigned* dest_input_pointer, bool* matching_failure);
int read_hex(InputStr* source, SpecOptions* spec_opts,
             long unsigned* dest_input_pointer, bool* matching_failure);
int read_octal(InputStr* source, SpecOptions* spec_opts,
               long unsigned* dest_input_pointer, bool* matching_failure);

void parce_width_sscanf(InputStr* fmt_input, SpecOptions* spec_opts);

bool parse_suppression(InputStr* fmt_input);

int source_validity_check(InputStr* source, InputStr* format_input,
                          bool* matching_failure);

int consume_specifier(va_list* args, InputStr* source, InputStr* fmt_input,
                      bool* matching_failure);

void process_n(va_list* args, InputStr* source, bool n_star);
int read_char(va_list* args, InputStr* source, SpecOptions* spec_opts);

void parse_width_sscanf(InputStr* fmt_input, SpecOptions* spec_opts);
bool parse_suppression(InputStr* fmt_input);
void set_sscanf_base(SpecOptions* spec_opts);
bool is_sscanf_specifier(char ch);
void parse_sscanf_specifier(InputStr* fmt_input, SpecOptions* spec_opts);

bool is_valid_digit(char incoming_char, s21_size_t base);

s21_size_t get_octal_num_length(InputStr* source, SpecOptions* spec_opts,
                                s21_size_t base);

bool width_limit_reached(s21_size_t bytes_read, SpecOptions* spec_opts);

// // Функция для считывания значений из буфера по формату
// int s21_sscanf(const char *str, const char *format, ...);

// // Функция для чтения строки
// int read_string(const char** str, char* s, SpecOptions* opts);

// // Функция для чтения беззнакового целого числа
// int read_unsigned_int(const char** str, unsigned int* u, SpecOptions*
// opts);

// // Функция для чтения вещественного числа
// int read_float(InputStr* input, float* f, SpecOptions* opts);

// // Функция для чтения шестнадцатеричного числа
// int read_hex(const char** str, unsigned int* x, SpecOptions* opts);

// int parse_pointer(InputStr* input, void** value);

#endif  // S21_SSCANF_H_