СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

GCOVFLAGS = -fprofile-arcs -ftest-coverage

TESTS_FOLDER = tests
TESTS_SRC_FILES = $(filter-out $(TESTS_FOLDER)/test.c, $(wildcard $(TESTS_FOLDER)/*.c))



STRING_SRC_FILES = $(wildcard *.c)
STRING_OBJ_DIR = object_files
STRING_OBJ_FILES = $(patsubst %.c,$(STRING_OBJ_DIR)/%.o,$(STRING_SRC_FILES))
STRING_LIB = s21_string.a


run: run_tests
	./run_tests
	for file in s21_strlen.c s21_strncat.c; do \
		gcov $$file; \
	done
	

run_tests: $(STRING_LIB) $(TESTS_SRC_FILES)
	$(CC) $(FLAGS) $(GCOVFLAGS) $^ -o $@ -lcheck


$(STRING_LIB): $(STRING_OBJ_FILES)
	ar rcs $@ $^
 

$(STRING_OBJ_DIR)/%.o: %.c
	@mkdir -p $(STRING_OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

clean:
	rm -drf $(STRING_OBJ_DIR)
	rm -f s21_string.a
	rm -f run_tests
	rm -f *.gcda *.gcno *.gcov