#include "s21_string.h"


char *s21_strpbrk(const char *str1, const char *str2) {
    while (*str1!= '\0') {
        for (const char *ptr = str2; *ptr!= '\0'; ptr++) {
            if (*str1 == *ptr) { 
                return (char *)str1;
            }
        }
        str1++;
    }
    return S21_NULL;
}