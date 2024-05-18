СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TESTS_FOLDER = tests
TARGET = s21_string.a

run: run_tests
	./run_tests


run_tests: $(TESTS_FOLDER)/run_tests.c $(TARGET)
	$(CC) $(FLAGS) $^ -o $@ -lcheck

s21_string.a: s21_strlen.o
	ar rcs $@ $^


s21_strlen.o: s21_strlen.c
	$(CC) $(FLAGS) -c $^