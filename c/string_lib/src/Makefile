CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
COV := --coverage
LDFLAGS := -lcheck -lm -pthread
OS := $(shell uname -s)
SRC_DIR := src
OBJ_DIR := obj
GCOV_DIR := gcov
TEST_DIR := tests
TEST_OBJ_DIR := tests_obj

ifeq ($(OS), Linux)
	LDFLAGS += -lrt -lsubunit
endif

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SRCS))
SRC_TEST_OBJS := $(patsubst $(SRC_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(SRCS))
LIB := s21_string.a
EXECUTABLE := test

.PHONY: all $(LIB) $(EXECUTABLE) gcov_report clean rebuild clang_n clang_i valgrind

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $@ $^

$(EXECUTABLE): $(TEST_OBJS) $(SRC_TEST_OBJS)
	$(CC) $(CFLAGS) $(COV) $(TEST_OBJS) $(SRC_TEST_OBJS) $(LDFLAGS) -o $@ 
	./$@

gcov_report: $(EXECUTABLE) | $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter "src/*"
ifeq ($(OS), Linux)
	xdg-open $(GCOV_DIR)/index.html
else
	open $(GCOV_DIR)/index.html
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c *.h $(SRC_DIR)/*.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(TEST_DIR)/*.h | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(COV) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(COV) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(TEST_OBJ_DIR):
	mkdir $@

$(GCOV_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR) $(TEST_OBJ_DIR) $(GCOV_DIR) $(EXECUTABLE) $(LIB)

rebuild: clean all

clang_n:
	clang-format -n --style=Google src/*.[ch] tests/*.[ch]

clang_i:
	clang-format -i --style=Google src/*.[ch] tests/*.[ch]

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test
