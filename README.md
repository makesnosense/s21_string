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

### s21_sprintf
The s21_sprintf function formats and stores a series of characters and values into the string str according to the format string format.
```c
int s21_sprintf(char* str, const char* format, ...);
```
A format specifier has the following structure:  
`%[flags][width][.precision][length]specifier`

#### `sprintf` specifiers

| Specifier | Output Description |
|-----------|--------------------|
| c         | Character          |
| d         | Signed decimal integer |
| i         | Signed integer (decimal, octal, or hexadecimal) |
| e         | Scientific notation (mantissa/exponent) |
| E         | Scientific notation (mantissa/exponent) using E |
| f         | Decimal floating point |
| g         | Shortest representation of decimal floating point |
| G         | Shortest representation of decimal floating point using E |
| o         | Unsigned octal     |
| s         | String of characters |
| u         | Unsigned decimal integer |
| x         | Unsigned hexadecimal integer (lowercase) |
| X         | Unsigned hexadecimal integer (uppercase) |
| p         | Pointer address    |
| n         | Number of characters printed |
| %         | Percent character   |

#### `sprintf` flags

| Flag | Description |
|------|-------------|
| -    | Left-justify within the field width |
| +    | Include sign for positive numbers |
| (space) | Insert a space for positive numbers |
| #    | Alternate form for certain specifiers |
| 0    | Zero-padding for numbers |

#### `sprintf` width

|-------|-------------|
| (number) | Minimum number of characters to print |
| *     | Width specified as an additional integer argument |

#### `sprintf` precision
| Precision | Description |
|-----------|-------------|
| .number  | Minimum digits for integers; decimal places for floats |
| .*       | Precision specified as an additional integer argument |

#### `sprintf` length
| Length | Description |
|--------|-------------|
| h      | Interpreted as short int |
| l      | Interpreted as long int or wide character |
| L      | Interpreted as long double |

### s21_sscanf
The s21_sscanf function reads data from the string str according to the format string format and assigns the values to the provided variables.
```c
int s21_sscanf(const char* str, const char* format, ...);
```
A format specifier has the following structure:  
`%[*][width][length]specifier`

#### `sscanf` specifiers

| Specifier | Output Description |
|-----------|--------------------|
| c         | Character          |
| d         | Signed decimal integer |
| i         | Signed integer (decimal, octal, or hexadecimal) |
| e         | Decimal or scientific notation |
| E         | Decimal or scientific notation (mantissa/exponent) |
| f         | Decimal floating point |
| g         | Decimal or scientific notation |
| G         | Decimal or scientific notation |
| o         | Unsigned octal     |
| s         | String of characters |
| u         | Unsigned decimal integer |
| x         | Unsigned hexadecimal integer (any case) |
| X         | Unsigned hexadecimal integer (uppercase) |
| p         | Pointer address    |
| n         | Number of characters scanned |
| %         | Percent character   |

#### `sscanf` width
| Width | Description |
|-------|-------------|
| (number) | Minimum number of characters to read |
| *     | Suppresses assignment of read data |


#### `sscanf` length
| Length | Description |
|--------|-------------|
| h      | Interpreted as short int |
| l      | Interpreted as long int or wide character |
| L      | Interpreted as long double |