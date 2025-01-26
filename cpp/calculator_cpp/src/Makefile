CC := g++
CFLAGS := -Wall -Wextra -Werror -std=c++17
COV := --coverage
LDFLAGS := -lgtest -lpthread
OS := $(shell uname -s)
DIST_HEADERS := $(wildcard *.h)
DIST_SOURCES := main.cc view.cc view.ui qcustomplot.cc CMakeLists.txt Makefile Doxyfile
GCOV_DIR := gcov
TEST_DIR := tests
TEST_OBJ_DIR := tests_obj

PROJECT_NAME := SmartCalc
BUILD_DIR := build
INSTALL_DIR := $(shell echo ~)/$(PROJECT_NAME)
DIST_DIR := dist

ifeq ($(OS), Linux)
	LDFLAGS += -lrt
endif

SRCS := $(wildcard $*.cc)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cc,$(TEST_OBJ_DIR)/%.o,$(TEST_SRCS))
SRC_TEST_OBJS := $(patsubst $(SRCS),$(TEST_OBJ_DIR)/%.o,$(SRCS))
EXECUTABLE := test

.PHONY: all build install uninstall dist dvi $(EXECUTABLE) gcov_report clean rebuild clang_n clang_i valgrind

all: $(EXECUTABLE)

build: CMakeLists.txt
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

install: build | $(INSTALL_DIR)
	sudo cmake --install $(BUILD_DIR) --prefix "$(INSTALL_DIR)"

uninstall:
	sudo rm -rf $(INSTALL_DIR)

dist: $(DIST_HEADERS) $(DIST_SOURCES)
	@mkdir $(DIST_DIR)
	tar -cvzf dist/$(PROJECT_NAME).tgz $(DIST_HEADERS) $(DIST_SOURCES)

dvi: Doxyfile
	doxygen Doxyfile

$(EXECUTABLE): $(TEST_OBJS) $(LIB_TEST_OBJS)
	$(CC) $(CFLAGS) $(COV) $(TEST_OBJS) $(LIB_TEST_OBJS) $(LDFLAGS) -o $@ 
	./$@

gcov_report: $(EXECUTABLE) | $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter "model.h"
ifeq ($(OS), Linux)
	xdg-open $(GCOV_DIR)/index.html
else
	open $(GCOV_DIR)/index.html
endif

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cc $(TEST_DIR)/*.h | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(COV) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(LIB_DIR)/%.cc | $(TEST_OBJ_DIR)
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
	clang-format -n --style=Google *.cc *.h tests/*.cc

clang_i:
	clang-format -i --style=Google *.cc *.h tests/*.cc

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test
