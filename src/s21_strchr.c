#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
    unsigned char *ptr = (unsigned char *)str;
    int i = 0;
    while(*ptr != '\0'){
        if (ptr[i] == c) { 
            return &ptr[i];
        }
        i++;
    }
    return S21_NULL;
}
