СС = gcc
# CFLAGS = -std=c11 -fprofile-arcs -ftest-coverage
CFLAGS = -Wall -Wextra -Werror -std=c11 -fprofile-arcs -ftest-coverage
TESTFLAGS:= -lcheck

ifeq ($(shell uname),Darwin)
	GCOVR_THEME = --html-theme github.dark-green
else
    TESTFLAGS += $(shell pkg-config --libs check) -lm
endif

TESTS_DIR = tests
TESTS_SRC_FILES = $(filter-out $(TESTS_DIR)/test.c, $(wildcard $(TESTS_DIR)/*.c))
GCOV_REPORT_DIR = gcov_report

STRING_SRC_FILES = $(wildcard *.c)
STRING_OBJ_DIR = object_files
STRING_OBJ_FILES = $(patsubst %.c,$(STRING_OBJ_DIR)/%.o,$(STRING_SRC_FILES))
STRING_LIB = s21_string.a

# run: clean build_tests
run: build_tests
	./run_tests

test: clean build_tests
	./run_tests

gcov_report: clean build_tests test
	@mkdir -p $(GCOV_REPORT_DIR)
	@gcovr -o $(GCOV_REPORT_DIR)/gcov_report.html --html --html-self-contained --html-details $(GCOVR_THEME) --exclude $(TESTS_DIR)	
	@open $(GCOV_REPORT_DIR)/gcov_report.html
	rm -f *.gcda *.gcno *.gcov

build_tests: $(TESTS_SRC_FILES) $(STRING_LIB)
	$(CC) $(CFLAGS) $^ -o run_tests $(TESTFLAGS)

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
	rm -drf $(GCOV_REPORT_DIR)