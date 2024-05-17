#include <stdio.h>
#include <string.h>
#include "s21_string.h"

void test_strlen();
void test_memchr();
void test_memcmp();
void test_memcpy();


void test_strcat();
void test_strncat();

int main() {
    test_strlen();
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_strcat();
    test_strncat();
}

void test_memchr(){
    printf("---------------------s21_memchr()---------------------\n");
    unsigned char buffer[] = "Hello, World"; // Пример буфера
    int c = 'o';
    s21_size_t n = sizeof(buffer);

    void *result = s21_memchr(buffer, c, n);

    if (result!= NULL) {
        printf("%c\n", *(char *)result);
    } else {
        printf("%c\n", c);
    }

    printf("---------------------memchr()---------------------\n");

    void *result1 = memchr(buffer, c, n);

    if (result!= NULL) {
        printf("%c\n", *(char *)result1);
    } else {
        printf("%c\n", c);
    }
    printf("--------------------------------------------------\n");
    printf("\n");
    printf("\n");
}

void test_memcmp() {
    printf("---------------------s21_memcmp()---------------------\n");
    unsigned char block1[] = {1, 2, 3};
    unsigned char block2[] = {1, 2, 3};
    unsigned char block3[] = {1, 2, 4};

    int result1 = s21_memcmp(block1, block2, sizeof(block1));
    int result2 = s21_memcmp(block1, block3, sizeof(block1));

    printf("%d\n", result1);
    printf("%d\n", result2);

    printf("---------------------memcmp()---------------------\n");

    result1 = memcmp(block1, block2, sizeof(block1));
    result2 = memcmp(block1, block3, sizeof(block1));

    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("--------------------------------------------------\n");
    printf("\n");
    printf("\n");
}

void test_memcpy() {
    printf("---------------------s21_memcpy()---------------------\n");

    char dest[20] = "Hello";
    const char src[] = "World";
    size_t n = 2; 

    s21_memcpy(dest, src, n);
    printf("%s\n", dest); 

    printf("---------------------memcpy()---------------------\n");

    s21_memcpy(dest, src, n);
    printf("%s\n", dest);
    printf("--------------------------------------------------\n");
    printf("\n");
    printf("\n");
}





void test_strcat() {
    printf("---------------------s21_strcat()---------------------\n");
    char str1[10] = "Hel";
    char *str2 = "lo";
    s21_strcat(str1, str2);
    printf("%s\n", str1);
    printf("---------------------strcat()---------------------\n");
    char str3[10] = "Hel";
    char *str4 = "lo";
    s21_strcat(str3, str4);
    printf("%s\n", str3);
    printf("--------------------------------------------------\n");
    printf("\n");
    printf("\n");
}

void test_strncat() {
    printf("---------------------s21_strncat()---------------------\n");
    char str1[10] = "Hel";
    char *str2 = "lo";
    s21_strncat(str1, str2, 1);
    printf("%s\n", str1);
    printf("---------------------strncat()---------------------\n");
    char str3[10] = "Hel";
    char *str4 = "lo";
    strncat(str3, str4, 1);
    printf("%s\n", str3);
    printf("--------------------------------------------------\n");
    printf("\n");
    printf("\n");
}

void test_strlen() {
    printf("---------------------s21_strlen()---------------------\n");
    char *str = "Hello World";
    printf("%zu\n", s21_strlen(str));
    printf("---------------------strlen()---------------------\n");
    printf("%zu\n", s21_strlen(str));
    printf("--------------------------------------------------\n");
    printf("\n");
    printf("\n");
}