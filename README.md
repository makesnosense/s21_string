 s21_string+

Partial reimplementation of the string.h library (with additions) executed as a practice project at School 21 (formerly 42.fr)

*N.B.: The definition and use of s21_size_t type is part of the educational project requirements.*

### string.h Functions

Implemented string.h functions:
```c
void* memchr(const void *str, int c, size_t n)
int memcmp(const void *str1, const void *str2, size_t n)
void* memcpy(void *dest, const void *src, size_t n)
void* memmove(void *dest, const void *src, size_t n)
void* memset(void *str, int c, size_t n)
char* strcat(char *dest, const char *src)
char* strncat(char *dest, const char *src, size_t n)
char* strchr(const char *str, int c)
int strcmp(const char *str1, const char *str2)
int strncmp(const char *str1, const char *str2, size_t n)
char* strcpy(char *dest, const char *src)
char* strncpy(char *dest, const char *src, size_t n)
size_t strcspn(const char *str1, const char *str2)
char* strerror(int errnum)
size_t strlen(const char *str)
char* strpbrk(const char *str1, const char *str2)
char* strrchr(const char *str, int c)
size_t strspn(const char *str1, const char *str2)
char* strstr(const char *haystack, const char *needle)
char* strtok(char *str, const char *delim)
```

### string processing functions inspired by C# string class methods.
```c
void* to_upper(const char *str)
void* to_lower(const char *str)
void* insert(const char *src, const char *str, size_t start_index) 
void* trim(const char *src, const char *trim_chars)
```