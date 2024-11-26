#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#define FAILURE
#define SUCCESS

#define S21_NULL (void*)0

#if defined(__APPLE__)
#define ERR_COUNT 106
#define IS_EXCLUDED(x) (0)

#elif defined(__linux__)
#define ERR_COUNT 133
#define IS_EXCLUDED(x) ((x) == 41 || (x) == 58)

#endif

typedef long unsigned s21_size_t;

// Finds the first occurrence of (unsigned char) c in the initial count n (each
// interpreted as unsigned char) of the object pointed to by str.
void* s21_memchr(const void* str, int c, s21_size_t n);

// Compares the first n bytes of the memory areas str1 and str2.
int s21_memcmp(const void* str1, const void* str2, s21_size_t n);

// Copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap.
void* s21_memcpy(void* dest, const void* src, s21_size_t n);

// Copies n bytes from memory area src to memory area dest.
// The memory areas may overlap: copying takes place as though the bytes in src
// are first copied into a temporary array that does not overlap src or dest,
// and the bytes are then copied from the temporary array to dest.
void* s21_memmove(void* dest, const void* src, s21_size_t n);

// Fills the first n bytes of the memory area pointed to by str
// with the constant byte c.
void* s21_memset(void* str, int c, s21_size_t n);

// Appends the src string to the dest string, overwriting the terminating null
// byte ('\0') at the end of dest, and then adds a terminating null byte.
char* s21_strcat(char* dest, const char* src);

// Similar to strcat, except that it will use at most n bytes from src.
char* s21_strncat(char* dest, const char* src, s21_size_t n);

// Returns a pointer to the first occurrence of the character c
// in the string str.
char* s21_strchr(const char* str, int c);

// Compares the two strings str1 and str2.  The comparison is done using
// unsigned characters.
// Returns an integer indicating the result of the comparison:
// 0, if the str1 and str2 are equal;
// a negative value if str1 is less than str2;
// a positive value if str1 is greater than str2.
int s21_strcmp(const char* str1, const char* str2);

// Similar to strcmp, except it compares only the first (at most)
// n bytes of str1 and str2.
int s21_strncmp(const char* str1, const char* str2, s21_size_t n);

// Copies the string pointed to by src,
// into a string at the buffer pointed to by dest
char* s21_strcpy(char* dest, const char* src);

// Copies at most n characters of the character array pointed to by src
// to character array pointed to by dest.
char* s21_strncpy(char* dest, const char* src, s21_size_t n);

// Returns the length of the maximum initial segment of the null-terminated byte
// string pointed to by str1, that consists of only the characters not found in
// the null-terminated byte string pointed to by str2.
s21_size_t s21_strcspn(const char* str1, const char* str2);

// Returns a pointer to a string that describes the error code
// passed in the argument errnum.
char* s21_strerror(int errnum);

// Returns the length of a string, which is the number of characters
// up to the first null terminating character.
s21_size_t s21_strlen(const char* str);

// Scans the null-terminated byte string pointed to by str1 for any character
// from the null-terminated byte string pointed to by str2, and returns a
// pointer to that character.
char* s21_strpbrk(const char* str1, const char* str2);

// Finds the last occurrence of c (after conversion to char as if by (char)c)
// in the null-terminated byte string pointed to by str (each character
// interpreted as unsigned char).
char* s21_strrchr(const char* str, int c);

// Returns the length of the maximum initial segment (span) of the
// null-terminated byte string pointed to by str1, that consists of only the
// characters found in the null-terminated byte string pointed to by str2.
s21_size_t s21_strspn(const char* str1, const char* str2);

// Finds the first occurrence of the null-terminated byte string pointed to by
// needle in the null-terminated byte string pointed to by haystack.
char* s21_strstr(const char* haystack, const char* needle);

// Function breaks a string str into a sequence of zero or more nonempty tokens.
// The delim argument specifies a set of bytes that delimit the tokens in the
// parsed string.
char* s21_strtok(char* str, const char* delim);

// дополнительные функции

// Возвращает копию строки (str), преобразованной в верхний регистр. В случае
// какой-либо ошибки следует вернуть
// значение NULL
void* s21_to_upper(const char* str);

// Возвращает копию строки (str), преобразованной в нижний регистр. В случае
// какой-либо
// ошибки следует вернуть значение NULL
void* s21_to_lower(const char* str);

// Возвращает новую строку, в которой указанная строка (str) вставлена
// в указанную позицию (start_index) в данной строке (src).
//  В случае какой-либо ошибки следует вернуть значение NULL
void* s21_insert(const char* src, const char* str, s21_size_t start_index);

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора
// заданных символов (trim_chars) из данной строки (src).
// В случае какой-либо ошибки следует вернуть значение NULL
void* s21_trim(const char* src, const char* trim_chars);

int s21_sscanf(const char* str, const char* format, ...);

// Отправляет форматированный вывод в строку, на которую указывает str.
int s21_sprintf(char* str, const char* format, ...);

#endif  // SRC_S21_STRING_H_
