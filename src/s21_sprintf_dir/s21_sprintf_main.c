#include <stdio.h>

#include "../s21_string.h"

int main() {
  int day, month, year;  // Переменные для считывания значений
  char formatted_line[100];  // Для хранения отформатированной строки

  printf("Введите день: ");
  scanf("%d", &day);
  printf("Введите месяц: ");
  scanf("%d", &month);
  printf("Введите год: ");
  scanf("%d", &year);

  // Моя sprintf
  s21_sprintf(formatted_line, "%i-%d-%i%c%c", day, month, year, '\t', '@');
  printf("s21_sprintf-Отформатированная строка: %s\n", formatted_line);

  // Стандартная sprintf
  sprintf(formatted_line, "%i-%d-%i%c%c", day, month, year, '\t', '@');
  printf("----sprintf-Отформатированная строка: %s\n", formatted_line);

  return 0;
}
