#include <stdio.h>

#include "../s21_string.h"
#include "s21_sscanf.h"

int main() {
  int int_num = 0;        // Целое число
  float float_num = 0.0;  // Число с плавающей точкой
  char symbol = '\0';     // Символ
  char string[30];        // Строка
  int res = 0;            // Считано спецификаторов
  int n = 0;  // Считанные символы с помощью %n

  // ТЕСТ 1
  printf("-----------------------------------------------------------\n\n");
  s21_strcpy(string, "123123 -123.123 Q %");
  res = s21_sscanf(string, "%d %f %c %% %n", &int_num, &float_num, &symbol, &n);
  printf("s21_sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);

  res = sscanf(string, "%d %f %c %% %n", &int_num, &float_num, &symbol, &n);
  printf("----sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);

  // ТЕСТ 2
  float_num = 0.0;
  printf("-----------------------------------------------------------\n\n");
  s21_strcpy(string, "3213 -32.32 Q %");
  res = s21_sscanf(string, "%d %f %c %% %n", &int_num, &float_num, &symbol, &n);
  printf("s21_sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);

  res = sscanf(string, "%d %f %c %% %n", &int_num, &float_num, &symbol, &n);
  printf("----sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);
  float_num = 0.0;

  // ТЕСТ 3
  printf("-----------------------------------------------------------\n\n");
  s21_strcpy(string, "3213 -32.32 Q %");
  res = s21_sscanf(string, "%*d %*f %*c %% %n", &n);
  printf("s21_sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);

  res = sscanf(string, "%*d %*f %*c %% %n", &n);
  printf("----sscanf - %%d = %d, %%f = %f, %%c = %c, %%n = %d\n", int_num,
         float_num, symbol, n);
  printf("Считано спецификаторов: %d\n\n", res);

  return 0;
}
