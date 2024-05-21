СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -fprofile-arcs -ftest-coverage
ifeq ($(shell uname),Darwin)
    TESTFLAGS:=-lcheck
	GCOVR_THEME = --html-theme github.dark-green
else
    TESTFLAGS:=-lcheck -lm -lsubunit
endif

TESTS_FOLDER = tests
TESTS_SRC_FILES = $(filter-out $(TESTS_FOLDER)/test.c, $(wildcard $(TESTS_FOLDER)/*.c))

STRING_SRC_FILES = $(wildcard *.c)
STRING_OBJ_DIR = object_files
STRING_OBJ_FILES = $(patsubst %.c,$(STRING_OBJ_DIR)/%.o,$(STRING_SRC_FILES))
STRING_LIB = s21_string.a

run: build_tests
	./run_tests

test: clean build_tests
	./run_tests

gcov_report: clean build_tests test
	@gcovr -o gcov_report.html --html --html-self-contained $(GCOVR_THEME) --exclude $(TESTS_FOLDER)	
	@open gcov_report.html

build_tests: $(STRING_LIB) $(TESTS_SRC_FILES)
	$(CC) $(CFLAGS) $^ -o run_tests $(STRING_LIB) $(TESTFLAGS)


$(STRING_LIB): $(STRING_OBJ_FILES)
	ar rcs $@ $^ 
 

$(STRING_OBJ_DIR)/%.o: %.c
	@mkdir -p $(STRING_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@




clean:
	rm -drf $(STRING_OBJ_DIR)
	rm -f s21_string.a
	rm -f run_tests
	rm -f *.gcda *.gcno *.gcov
	rm -f gcov_report.html

	