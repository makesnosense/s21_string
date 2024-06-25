#include <stdio.h>

#include "s21_sscanf.h"

int main() {
  int int_num;      // Целое число
  float float_num;  // Число с плавающей точкой
  char symbol;      // Символ
  char string[30];  // Строка
  int res;          // Считано спецификаторов
  int n;            // Считанные символы с помощью %n

  // Читаем с терминала
  printf("Введите строку: ");
  fgets(string, 29, stdin);
  printf("\n");

  // Смотрим как отработает s21_sscanf
  printf("Введенная строка: %s", string);

  // Стандартная sscanf
  res = sscanf(string, "%d %f %c %% %n", &int_num, &float_num, &symbol, &n);
  printf("----sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);

  // s21_sscanf
  res = s21_sscanf(string, "%d %f %c %% %n", &int_num, &float_num, &symbol, &n);
  printf("s21_sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n", res);

  return 0;
}
