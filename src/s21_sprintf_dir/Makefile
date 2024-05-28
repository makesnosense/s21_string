CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror

OBJ = s21_sprintf.c s21_sprintf_main.c ../s21_strcpy.c ../s21_strcat.c ../s21_strlen.c ../s21_memmove.c ../s21_strchr.c
EXE = s21_sprintf

all: cpplint s21_sprintf

s21_sprintf: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

cpplint:
	python3 ../../materials/linters/cpplint.py --extensions=c ../s21_sprintf_dir/*.c

clean:
	rm s21_sprintf

rebuild:
	$(MAKE) clean
	$(MAKE) all