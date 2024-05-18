СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TESTS_FOLDER = tests
TARGET = s21_string.a
SRCDIR = .

STRING_SRC_FILES = $(wildcard *.c)
STRING_OBJ_DIR = object_files


run: clean s21_string.a run_tests
	./run_tests


run_tests: $(TESTS_FOLDER)/run_tests.c $(TARGET)
	$(CC) $(FLAGS) $^ -o $@ -lcheck

s21_string.a: $(wildcard $(STRING_OBJ_DIR)/*.o)
	ar rcs $@ $^





# Шаблонное правило для компиляции каждого.c файла в объектный файл
$(STRING_OBJ_DIR)/%.o: %.c
	mkdir -p $(STRING_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# s21_strlen.o: s21_strlen.c
# 	$(CC) $(FLAGS) -c $^



clean:
	rm -drf $(STRING_OBJ_DIR)
	rm -f s21_string.a