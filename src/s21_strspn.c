#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
    if (!*str1 ||!*str2) return 0;

    s21_size_t count = 0;
    while (*str1!= '\0') {
        int found = 0;
        while (*str2!= '\0' && *str1!= *str2) {
            str2++;
        }
        if (*str2 == *str1) {
            found = 1;
            break;
        }
        if (found) {
            str1++;
            continue;
        }
        break;
    }
    return count;
}