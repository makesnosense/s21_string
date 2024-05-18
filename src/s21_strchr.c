#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
    if (!str) return S21_NULL;
    const char *ptr = str;
    while (*ptr!= '\0') {
        if (*ptr == c) {
            return (char *)ptr;
        }
        ptr++;
    }

    return S21_NULL;
}
