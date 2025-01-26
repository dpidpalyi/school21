CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
COV := --coverage
LDFLAGS := -lcheck -lm -pthread
OS := $(shell uname -s)
SOURCES := main.cpp mainwindow.cpp mainwindow.h mainwindow.ui qcustomplot.cpp qcustomplot.h CMakeLists.txt Makefile Doxyfile
LIB_DIR := lib
GCOV_DIR := gcov
TEST_DIR := tests
TEST_OBJ_DIR := tests_obj
PROJECT_NAME := SmartCalc
BUILD_DIR := build
INSTALL_DIR := $(shell echo ~)/$(PROJECT_NAME)
DIST_DIR := dist

ifeq ($(OS), Linux)
	LDFLAGS += -lrt -lsubunit
endif

LIBS := $(wildcard $(LIB_DIR)/*.c)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRCS))
LIB_TEST_OBJS := $(patsubst $(LIB_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(LIBS))
EXECUTABLE := test

.PHONY: all build install uninstall dist dvi $(EXECUTABLE) gcov_report clean rebuild clang_n clang_i valgrind

all: $(EXECUTABLE)

build: CMakeLists.txt
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

install: build | $(INSTALL_DIR)
	sudo cmake --install $(BUILD_DIR) --prefix "$(INSTALL_DIR)"

uninstall:
	rm -rf $(INSTALL_DIR)

dist: $(LIB_DIR) $(TEST_DIR) $(SOURCES)
	@mkdir $(DIST_DIR)
	tar -cvzf dist/$(PROJECT_NAME).tgz $(LIB_DIR) $(TEST_DIR) $(SOURCES)

dvi: Doxyfile
	doxygen Doxyfile

$(EXECUTABLE): $(TEST_OBJS) $(LIB_TEST_OBJS)
	$(CC) $(CFLAGS) $(COV) $(TEST_OBJS) $(LIB_TEST_OBJS) $(LDFLAGS) -o $@ 
	./$@

gcov_report: $(EXECUTABLE) | $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter "lib/*"
ifeq ($(OS), Linux)
	xdg-open $(GCOV_DIR)/index.html
else
	open $(GCOV_DIR)/index.html
endif

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(TEST_DIR)/*.h | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(COV) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(COV) -c $< -o $@

$(TEST_OBJ_DIR):
	mkdir $@

$(GCOV_DIR):
	mkdir $@

$(INSTALL_DIR):
	mkdir $@
	
clean:
	rm -rf $(TEST_OBJ_DIR) $(GCOV_DIR) $(EXECUTABLE) $(DIST_DIR) $(BUILD_DIR) docs

rebuild: clean all

clang_n:
	clang-format -n --style=Google *.cpp *.[ch] lib/*.[ch] tests/*.[ch]

clang_i:
	clang-format -i --style=Google *.cpp *.[ch] lib/*.[ch] tests/*.[ch]

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test
