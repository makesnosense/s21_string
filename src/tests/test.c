#include <stdio.h>
#include <string.h>

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
}

// void test_memchr() {
//   printf("-------------------s21_memchr()-------------------\n");
//   unsigned char buffer[] = "Hello, World";  // Пример буфера
//   int c = 'o';
//   s21_size_t n = sizeof(buffer);

//   void *result = s21_memchr(buffer, c, n);

//   if (result != NULL) {
//     printf("%c\n", *(char *)result);
//   } else {
//     printf("%c\n", c);
//   }

//   printf("---------------------memchr()---------------------\n");

//   void *result1 = memchr(buffer, c, n);

//   if (result != NULL) {
//     printf("%c\n", *(char *)result1);
//   } else {
//     printf("%c\n", c);
//   }
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_memcmp() {
//   printf("-------------------s21_memcmp()-------------------\n");
//   unsigned char block1[] = {1, 2, 3};
//   unsigned char block2[] = {1, 2, 3};
//   unsigned char block3[] = {1, 2, 4};

//   int result1 = s21_memcmp(block1, block2, sizeof(block1));
//   int result2 = s21_memcmp(block1, block3, sizeof(block1));

//   printf("%d\n", result1);
//   printf("%d\n", result2);

//   printf("---------------------memcmp()---------------------\n");

//   result1 = memcmp(block1, block2, sizeof(block1));
//   result2 = memcmp(block1, block3, sizeof(block1));

//   printf("%d\n", result1);
//   printf("%d\n", result2);
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_memcpy() {
//   printf("-------------------s21_memcpy()-------------------\n");

//   char dest[20] = "Hello";
//   const char src[] = "World";
//   size_t n = 2;

//   s21_memcpy(dest, src, n);
//   printf("%s\n", dest);

//   printf("---------------------memcpy()---------------------\n");

//   memcpy(dest, src, n);
//   printf("%s\n", dest);
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_memmove() {
//   printf("------------------s21_memmove()-------------------\n");

//   char dest[20] = "Hello";
//   const char src[] = "World";
//   size_t n = 2;

//   s21_memmove(dest, src, n);
//   printf("%s\n", dest);

//   printf("--------------------memmove()---------------------\n");

//   memmove(dest, src, n);
//   printf("%s\n", dest);
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_memset() {
//   printf("------------------s21_memset()--------------------\n");
//   char dest[20] = "Hello";
//   size_t n = 2;

//   s21_memset(dest, 111, n);
//   printf("%s\n", dest);

//   printf("--------------------memset()----------------------\n");

//   memset(dest, 111, n);
//   printf("%s\n", dest);
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_strcat() {
//   printf("-------------------s21_strcat()-------------------\n");
//   char str1[10] = "Hel";
//   char *str2 = "lo";
//   s21_strcat(str1, str2);
//   printf("%s\n", str1);
//   printf("---------------------strcat()---------------------\n");
//   char str3[10] = "Hel";
//   char *str4 = "lo";
//   strcat(str3, str4);
//   printf("%s\n", str3);
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_strncat() {
//   printf("------------------s21_strncat()-------------------\n");
//   char str1[10] = "Hel";
//   char *str2 = "lo";
//   s21_strncat(str1, str2, 1);
//   printf("%s\n", str1);
//   printf("--------------------strncat()---------------------\n");
//   char str3[10] = "Hel";
//   char *str4 = "lo";
//   strncat(str3, str4, 1);
//   printf("%s\n", str3);
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_strchr() {
//   printf("-------------------s21_strchr()-------------------\n");

//   char *result1 = s21_strchr("Hello", 111);  // 111 = "o"
//   printf("%s\n", result1);

//   printf("---------------------strchr()---------------------\n");

//   char *result2 = strchr("Hello", 111);  // 111 = "o"
//   printf("%s\n", result2);

//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_strcmp() {
//   printf("-------------------s21_strcmp()-------------------\n");

//   const char *str1 = "hello";
//   const char *str2 = "world";

//   int result = s21_strcmp(str1, str2);
//   if (result < 0) {
//     printf("str1 меньше str2: %d\n", result);
//   } else if (result > 0) {
//     printf("str1 больше str2: %d\n", result);
//   } else {
//     printf("str1 и str2 идентичны: %d\n", result);
//   }

//   printf("---------------------strcmp()---------------------\n");

//   int result1 = strcmp(str1, str2);
//   if (result1 < 0) {
//     printf("str1 меньше str2: %d\n", result1);
//   } else if (result1 > 0) {
//     printf("str1 больше str2: %d\n", result1);
//   } else {
//     printf("str1 и str2 идентичны: %d\n", result1);
//   }
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_strncmp() {
//   printf("-------------------s21_strncmp()------------------\n");

//   const char *str1 = "hello";
//   const char *str2 = "helloworld";
//   s21_size_t n = 5;

//   int result = s21_strncmp(str1, str2, n);
//   if (result < 0) {
//     printf("str1 меньше str2 по первым %zu символам: %d\n", n, result);
//   } else if (result > 0) {
//     printf("str1 больше str2 по первым %zu символам: %d\n", n, result);
//   } else {
//     printf("Первые %zu символов str1 и str2 идентичны: %d\n", n, result);
//   }

//   printf("---------------------strcmp()---------------------\n");

//   int result1 = strncmp(str1, str2, n);
//   if (result1 < 0) {
//     printf("str1 меньше str2 по первым %zu символам: %d\n", n, result1);
//   } else if (result1 > 0) {
//     printf("str1 больше str2 по первым %zu символам: %d\n", n, result1);
//   } else {
//     printf("Первые %zu символов str1 и str2 идентичны: %d\n", n, result);
//   }
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

// void test_strcpy() {
//   printf("-------------------s21_strcpy()-------------------\n");

//   char dest[50] = "";
//   char *src = "Hello, World";

//   s21_strcpy(dest, src);
//   printf("%s\n", dest);

//   printf("---------------------strcpy()---------------------\n");

//   char dest1[50] = "";
//   char *src1 = "Hello, World";

//   strcpy(dest1, src1);
//   printf("%s\n", dest1);

//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

void test_strncpy() {
  printf("-------------------s21_strncpy()-------------------\n");

  char dest[50] = "";
  const char *src = "Hello, World";
  s21_size_t n = 5;

  s21_strncpy(dest, src, n);
  printf("%s\n", dest);

  printf("---------------------strncpy()---------------------\n");

  char dest1[50] = "";
  const char *src1 = "Hello, World";

  strncpy(dest1, src1, n);
  printf("%s\n", dest);

  printf("---------------------------------------------------\n");
  printf("\n");
  printf("\n");
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
    char *res1 = s21_strerror(i);
    char *res2 = strerror(i);
    if (!(s21_strcmp(res1, res2))) {
      printf("test number %d: |%s||%s|\n", i, res1, res2);
      break;
    }
  }
  if (i == ERR_COUNT) {
    printf("good\n");
  }
  printf("--------------------------------------------------\n");
  printf("\n");
  printf("\n");
}

// void test_strlen() {
//   printf("-------------------s21_strlen()-------------------\n");
//   char *str = "Hello World";
//   printf("%zu\n", s21_strlen(str));
//   printf("---------------------strlen()---------------------\n");
//   printf("%zu\n", strlen(str));
//   printf("--------------------------------------------------\n");
//   printf("\n");
//   printf("\n");
// }

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

void test_strspn() {
  printf("-------------------s21_strspn()-------------------\n");
  const char *str = "HelloWo";
  const char *str2 = "HeWorld";
  printf("%zu\n", s21_strspn(str, str2));  //
  printf("---------------------strspn()---------------------\n");
  printf("%zu\n", strspn(str, str2));
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