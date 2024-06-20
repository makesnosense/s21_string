#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

// Функция для чтения символа
int read_char(const char **str, char *c);

// Функция для чтения строки
int read_string(const char **str, char *s);

// Функция для чтения целого числа
int read_int(const char **str, int *d);

// Функция для чтения беззнакового целого числа
int read_unsigned_int(const char **str, unsigned int *u);

// Функция для чтения вещественного числа
int read_float(const char **str, float *f);

// Функция для чтения шестнадцатеричного числа
int read_hex(const char **str, unsigned int *x);

// Функция s21_sscanf
int s21_sscanf(const char *str, const char *format, ...);

#endif  // S21_SSCANF_H_