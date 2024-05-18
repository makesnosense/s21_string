СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TESTS_FOLDER = tests
TARGET = s21_string.a
SRCDmakeIR = .

STRING_SRC_FILES = $(wildcard *.c)
STRING_OBJ_DIR = object_files


run: clean s21_string.a run_tests
	./run_tests


run_tests: ./tests/run_tests.c
	$(CC) $(FLAGS) ./tests/run_tests.c lib.a -o run_tests -lcheck

s21_string.a: obj
	ar rcs lib.a *.o

# Шаблонное правило для компиляции каждого.c файла в объектный файл
obj: *.c
	$(CC) $(CFLAGS) -c *.c

# s21_strlen.o: s21_strlen.c
# 	$(CC) $(FLAGS) -c $^

clean:
	rm -drf $(STRING_OBJ_DIR)
	rm -f s21_string.a