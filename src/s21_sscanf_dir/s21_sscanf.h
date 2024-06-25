#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

// Функция для чтения символа
int read_char(const char **str, char *c, int *cnt);

// Функция для чтения строки
int read_string(const char **str, char *s, int *cnt);

// Функция для чтения целого числа
int read_int(const char **str, int *d, int *cnt);

// Функция для чтения беззнакового целого числа
int read_unsigned_int(const char **str, unsigned int *u, int *cnt);

// Функция для чтения вещественного числа
int read_float(const char **str, float *f, int *cnt);

// Функция для чтения шестнадцатеричного числа
int read_hex(const char **str, unsigned int *x, int *cnt);

// Функция s21_sscanf
int s21_sscanf(const char *str, const char *format, ...);

#endif  // S21_SSCANF_H_