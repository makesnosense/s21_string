#include <stdio.h>

#include "../s21_string.h"

int main() {
  int day, month;    // Целые числа
  float year;        // Число с плавающей точкой
  char string[30];   // Строка
  char f_line[100];  // Отформатированная строка

  // Читаем с терминала
  printf("Введите день: ");
  scanf("%d", &day);
  printf("Введите месяц: ");
  scanf("%d", &month);
  printf("Введите год: ");
  scanf("%f", &year);
  printf("Введите строку: ");
  scanf("%29s", string);

  // Стандартная sprintf
  sprintf(f_line, "%+i-% d-%+f%c%s%c", day, month, year, '\t', string, '@');
  printf("----sprintf-Отформатированная строка: %s\n", f_line);

  // Моя sprintf
  s21_sprintf(f_line, "%+i-% d-%+f%c%s%c", day, month, year, '\t', string, '@');
  printf("s21_sprintf-Отформатированная строка: %s\n", f_line);

  return 0;
}
