#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct SpecifierOptions {
  int width;     // Ширина
  bool is_star;  // Флаг подавления считывания
} SpecOptions;

typedef struct InputString {
  const char* str;
  s21_size_t curr_ind;
} InputStr;

// Функция для чтения символа
int read_char(InputStr* input, char* c, SpecOptions* opts);

// Функция для чтения строки
int read_string(const char** str, char* s, SpecOptions* opts);

// Функция для чтения целого числа
int read_int(InputStr* input, int* d, SpecOptions* opts);

// Функция для чтения беззнакового целого числа
int read_unsigned_int(const char** str, unsigned int* u, SpecOptions* opts);

// Функция для чтения вещественного числа
int read_float(InputStr* input, float* f, SpecOptions* opts);

// Функция для чтения шестнадцатеричного числа
int read_hex(const char** str, unsigned int* x, SpecOptions* opts);

int parse_pointer(InputStr* input, void** value, SpecOptions* opts);

void skip_space(InputStr* input);

// // Функция для считывания значений из буфера по формату
// int s21_sscanf(const char *str, const char *format, ...);

#endif  // S21_SSCANF_H_