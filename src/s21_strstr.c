#include "s21_string.h"

char *s21_strstr(const char* haystack, const char* needle) {
    if (!*needle) return (char*) haystack;

    const char* h = haystack;
    const char* n = needle;

    while (*h!= '\0') {
        if (*h == *n) {
            const char *p = h;
            while (*p++ == *(n++));
            if (*(unsigned char*) n == '\0') return (char*) h;
        }
        h++;
    }

    return S21_NULL;
}