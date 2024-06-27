#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct Options {
  int count;  // Количество считанных символов для %n
  int width;     // Ширина
  bool is_star;  // Флаг подавления считывания
} Opts;

typedef struct InputString {
  const char* str;
  s21_size_t curr_ind;
} InputStr;

// Функция для чтения символа
int read_char(const char** str, char* c, Opts* opts);

// Функция для чтения строки
int read_string(const char** str, char* s, Opts* opts);

// Функция для чтения целого числа
int read_int(InputStr* input, int* d, Opts* opts);

// Функция для чтения беззнакового целого числа
int read_unsigned_int(const char** str, unsigned int* u, Opts* opts);

// Функция для чтения вещественного числа
int read_float(const char** str, float* f, Opts* opts);

// Функция для чтения шестнадцатеричного числа
int read_hex(const char** str, unsigned int* x, Opts* opts);

// // Функция для считывания значений из буфера по формату
// int s21_sscanf(const char *str, const char *format, ...);

#endif  // S21_SSCANF_H_