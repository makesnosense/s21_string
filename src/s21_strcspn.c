#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
    const char* p1 = str1;
    const char* p2 = str2;
    while (*p1!= '\0' &&!(*p1 == *p2 || *p2 == '\0')) {
        p1++;
    }

    return p1 - str1;
}