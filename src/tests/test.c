#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

void test_strerror();
void test_strpbrk();
void test_strrchr();
void test_strstr();
void test_strtok();

void test_to_upper();
void test_to_lower();
void test_insert();
void test_trim();

int main() {
  test_strerror();
  // test_strpbrk();
  // test_strrchr();
  // test_strstr();
  // test_strtok();

  // test_to_upper();
  // test_to_lower();
  // test_insert();
  // test_trim();
}

void test_strerror() {
  printf("--------------------strerror()--------------------\n");
  int i = 0;
  for (; i < ERR_COUNT; i++) {
    char *res1 = strerror(i);
    char *res2 = s21_strerror(i);
    if (strcmp(res1, res2)) {
      printf("test number %d: |%s|                |%s|\n\n\n", i, res1, res2);
    }
  }
  if (i == ERR_COUNT) {
    printf("good\n");
  }
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_strpbrk() {
  printf("-------------------s21_strpbrk()-------------------\n");
  char *str = "Hello";
  char *str2 = "World";
  printf("%s\n", s21_strpbrk(str, str2));
  printf("---------------------strpbrk()---------------------\n");
  printf("%s\n", strpbrk(str, str2));
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_strrchr() {
  printf("-------------------s21_strrchr()-------------------\n");
  char *str = "Helloqhello";
  printf("%s\n", s21_strrchr(str, 113));  // 113 = q
  printf("---------------------strrchr()---------------------\n");
  printf("%s\n", strrchr(str, 113));
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_strstr() {
  printf("-------------------s21_strstr()-------------------\n");
  const char *str = "HelloWorldHello";
  const char *str2 = "World";
  printf("%s\n", s21_strstr(str, str2));  //
  printf("---------------------strstr()---------------------\n");
  printf("%s\n", strstr(str, str2));
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_strtok() {
  printf("-------------------s21_strtok()-------------------\n");
  char str[50] = "HelloWorldHello";
  char *str2 = "World";
  printf("%s\n", s21_strtok(str, str2));  //
  printf("---------------------strtok()---------------------\n");
  printf("%s\n", strtok(str, str2));
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_to_upper() {
  printf("-------------------s21_to_upper()-------------------\n");
  char *str2 = "World";
  char *result = s21_to_upper(str2);
  printf("%s\n", result);
  free(result);
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_to_lower() {
  printf("-------------------s21_to_lower()-------------------\n");
  char *str2 = "wORLD";
  char *result = s21_to_lower(str2);
  printf("%s\n", result);
  free(result);
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_insert() {
  printf("-------------------s21_insert()-------------------\n");
  char *result = s21_insert("Hello", " world", 0);
  printf("%s\n", result);
  free(result);
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}
void test_trim() {
  printf("-------------------s21_trim()-------------------\n");
  char *result = s21_trim("+!!++Abo+ba++00", "+!0-");
  printf("%s\n", result);
  free(result);
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}