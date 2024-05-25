#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

// Функция для преобразования целого числа в строку
char* int_to_str(long long int num) {
  long long int temp_num = num;  // Для подсчета длины строки
  s21_size_t len = 0;            // Длина строки
  int is_negative = 0;           // Является ли отр. числом

  // Если число num отрицательное
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  // Считаем длину числа
  while (temp_num != 0) {
    len++;
    temp_num /= 10;
  }

  // Выделяем память под строку, учитывая знак минуса,
  // нулевой символ и конец строки
  char* str = malloc(len + 3);

  // Преобразуем число в строку
  if (len == 0) {
    s21_strcpy(str, "0");
  } else {
    int i = len - 1;  // Здесь по идее тоже должен быть s21_size_t :)
    while (i >= 0) {
      str[i] = (num % 10) + '0';
      num /= 10;
      i--;
    }

    // Если число отрицательное, добавляем '-'
    if (is_negative) {
      s21_memmove(str + 1, str, len);
      str[0] = '-';
    }
    str[len + is_negative] = '\0';
  }

  return str;
}

char* float_to_str(double num) {
  // Преобразуем целочисленную часть
  char* whole = int_to_str((long long int)num);

  // Преобразуем часть с плавающей точкой
  double frtemp = fabs(fmod(num, 1.0) * pow(10, 6));
  char* fract = int_to_str(frtemp);

  // Считаем размер для маллока
  s21_size_t len = s21_strlen(whole) + s21_strlen(fract) + 3;

  // Аллоцируем память и соединяем части в одну строку
  char* res = malloc(len);
  s21_strcpy(res, whole);
  s21_strcat(res, ".");
  s21_strcat(res, fract);

  // Освобождаем память, выделенную под целую и десятичную части
  free(whole);
  free(fract);

  return res;
}

int s21_sprintf(char* str, const char* format, ...) {
  int res = 0;  // Результат работы функции

  va_list args;  // Список аргументов
  va_start(args, format);  // Инициализируем список аргументов

  s21_size_t str_index = 0;  // Индекс буферной строки
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      switch (*format) {
        case 'c': {  // Если c (char)
          char c = va_arg(args, int);
          str[str_index++] = c;
          break;
        }
        case 'i':  // Если i или d (int)
        case 'd': {
          int d = va_arg(args, int);
          char* d_str = int_to_str(d);

          s21_strcpy(str + str_index, d_str);
          str_index += s21_strlen(d_str);

          if (d_str) free(d_str);
          break;
        }
        case 'f': {  // Если f (float)
          float f = va_arg(args, double);
          char* f_str = float_to_str(f);

          s21_strcpy(str + str_index, f_str);
          str_index += s21_strlen(f_str);

          if (f_str) free(f_str);
          break;
        }
        case 's': {
          char* s = va_arg(args, char*);
          s21_strcpy(str + str_index, s);
          str_index += s21_strlen(s);
          break;
        }
        case 'u': {
          unsigned u = va_arg(args, unsigned);
          char* u_str = int_to_str(u);

          s21_strcpy(str + str_index, u_str);
          str_index += s21_strlen(u_str);

          if (u_str) free(u_str);
        }
        default:
          break;
      }
    } else {
      str[str_index++] = *format;
    }
    format++;
  }
  str[str_index] = '\0';
  va_end(args);

  return res;
}
