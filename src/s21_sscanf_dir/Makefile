CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror

OBJ = s21_sscanf.c s21_sscanf_main.c
EXE = s21_sscanf

all: cpplint s21_sscanf

s21_sscanf: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

cpplint:
	python3 ../../materials/linters/cpplint.py --extensions=c ../s21_sscanf_dir/*.c

clean:
	rm s21_sscanf

rebuild:
	$(MAKE) clean
	$(MAKE) all