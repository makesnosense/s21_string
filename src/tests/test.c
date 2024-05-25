#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include "../s21_string.h"

void test_memchr();
void test_memcmp();
void test_memcpy();
void test_memmove();
void test_memset();
void test_strcat();
void test_strncat();
void test_strchr();
void test_strcmp();
void test_strncmp();
void test_strcpy();
void test_strncpy();
void test_strcspn();
void test_strerror();
void test_strlen();
void test_strpbrk();
void test_strrchr();
void test_strspn();
void test_strstr();
void test_strtok();


void test_to_upper();
void test_to_lower();
void test_insert();
void test_trim();

int main() {
  test_memchr();
  test_memcmp();
  test_memcpy();
  test_memmove();
  test_memset();
  test_strcat();
  test_strncat();
  test_strchr();
  test_strcmp();
  test_strncmp();
  test_strcpy();
  test_strncpy();
  test_strcspn();
  test_strerror();
  test_strlen();
  test_strpbrk();
  test_strrchr();
  test_strspn();
  test_strstr();
  test_strtok();

  test_to_upper();
  test_to_lower();
  test_insert();
  test_trim();
}


void test_strcspn() {
  printf("---------------------strcspn()---------------------\n");

  printf("Тест 1: s21: |%zu|  orig: |%zu|\n", s21_strcspn("hello", "he"),
         strcspn("hello", "he"));
  printf("Тест 2: s21: |%zu|  orig: |%zu|\n", s21_strcspn("world", "o"),
         strcspn("world", "o"));
  printf("Тест 3: s21: |%zu|  orig: |%zu|\n", s21_strcspn("12345", "12"),
         strcspn("12345", "12"));
  printf("Тест 4: s21: |%zu|  orig: |%zu|\n", s21_strcspn("abcde", "bc"),
         strcspn("abcde", "bc"));
  printf("Тест 5: s21: |%zu|  orig: |%zu|\n", s21_strcspn("abcdefg", "fgh"),
         strcspn("abcdefg", "fgh"));
  printf("Тест 6: s21: |%zu|  orig: |%zu|\n", s21_strcspn("", ""),
         strcspn("", ""));
  printf("Тест 7: s21: |%zu|  orig: |%zu|\n", s21_strcspn("a", "b"),
         strcspn("a", "b"));
  printf("Тест 8: s21: |%zu|  orig: |%zu|\n", s21_strcspn("ab", "b"),
         strcspn("ab", "b"));
  printf("Тест 9: s21: |%zu|  orig: |%zu|\n", s21_strcspn("abc", "b"),
         strcspn("abc", "b"));
  printf("Тест 10: s21:|%zu|  orig: |%zu|\n", s21_strcspn("abcd", "d"),
         strcspn("abcd", "d"));

  printf("---------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

void test_strerror() {
  printf("--------------------strerror()--------------------\n");
  int i = 0;
  for (; i < ERR_COUNT; i++) {
    char *res1 = strerror(i);
    char *res2 = s21_strerror(i);
    if (strcmp(res1, res2)) {
      printf("test number %d: |%s|                |%s|\n\n\n", i, res1, res2);
      //break;
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