СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11


TESTS_FOLDER = tests
<<<<<<< HEAD
TARGET = s21_string.a
SRCDmakeIR = .
=======
TESTS_SRC_FILES = $(filter-out $(TESTS_FOLDER)/test.c, $(wildcard $(TESTS_FOLDER)/*.c))


>>>>>>> 45300d0272cdf05541218f4ff6540c0972a14556

STRING_SRC_FILES = $(wildcard *.c)
STRING_OBJ_DIR = object_files
STRING_OBJ_FILES = $(patsubst %.c,$(STRING_OBJ_DIR)/%.o,$(STRING_SRC_FILES))
STRING_LIB = s21_string.a


run: run_tests
	./run_tests
	

test: $(STRING_LIB) run_tests
	./run_tests

<<<<<<< HEAD

run_tests: ./tests/run_tests.c
	$(CC) $(FLAGS) ./tests/run_tests.c lib.a -o run_tests -lcheck

s21_string.a: obj
	ar rcs lib.a *.o

# Шаблонное правило для компиляции каждого.c файла в объектный файл
obj: *.c
	$(CC) $(CFLAGS) -c *.c

# s21_strlen.o: s21_strlen.c
# 	$(CC) $(FLAGS) -c $^

=======
run_tests: $(STRING_LIB) $(TESTS_SRC_FILES)
	$(CC) $(FLAGS) $^ -o $@ -lcheck


$(STRING_LIB): $(STRING_OBJ_FILES)
	ar rcs $@ $^
 

$(STRING_OBJ_DIR)/%.o: %.c
	@mkdir -p $(STRING_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

>>>>>>> 45300d0272cdf05541218f4ff6540c0972a14556
clean:
	rm -drf $(STRING_OBJ_DIR)
	rm -f s21_string.a