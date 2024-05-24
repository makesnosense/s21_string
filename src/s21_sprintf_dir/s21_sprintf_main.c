#include <stdio.h>

#include "../s21_string.h"

int main() {
  int day, month;  // Переменные для считывания значений
  float year;
  char formatted_line[100];  // Для хранения отформатированной строки

  printf("Введите день: ");
  scanf("%d", &day);
  printf("Введите месяц: ");
  scanf("%d", &month);
  printf("Введите год: ");
  scanf("%f", &year);

  // Моя sprintf
  s21_sprintf(formatted_line, "%i-%d-%f%c%c", day, month, year, '\t', '@');
  printf("s21_sprintf-Отформатированная строка: %s\n", formatted_line);

  // Стандартная sprintf
  sprintf(formatted_line, "%i-%d-%f%c%c", day, month, year, '\t', '@');
  printf("----sprintf-Отформатированная строка: %s\n", formatted_line);

  return 0;
}
