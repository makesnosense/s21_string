#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
    const char *p = str + s21_strlen(str) - 1;
    while (p >= str) {
        if (*p == c) {
            return (char *)p;
        }
        p--;
    }

    return S21_NULL;
}