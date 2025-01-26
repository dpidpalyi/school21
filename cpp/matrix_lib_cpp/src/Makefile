CC := g++
CFLAGS := -Wall -Wextra -Werror -std=c++17
COV := --coverage
LDFLAGS := -lgtest -lm -pthread
OS := $(shell uname -s)
SRC_DIR := lib
OBJ_DIR := obj
GCOV_DIR := gcov
TEST_DIR := tests
TEST_OBJ_DIR := tests_obj

ifeq ($(OS), Linux)
	LDFLAGS += -lrt
endif

SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRCS))
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cc,$(TEST_OBJ_DIR)/%.o,$(TEST_SRCS))
SRC_TEST_OBJS := $(patsubst $(SRC_DIR)/%.cc,$(TEST_OBJ_DIR)/%.o,$(SRCS))
LIB := s21_matrix_oop.a
EXECUTABLE := test

.PHONY: all $(LIB) $(EXECUTABLE) gcov_report clean rebuild clang_n clang_i valgrind

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $@ $^

$(EXECUTABLE): $(TEST_OBJS) $(SRC_TEST_OBJS)
	$(CC) $(CFLAGS) $(COV) $(TEST_OBJS) $(SRC_TEST_OBJS) $(LDFLAGS) -o $@ 
	./$@

gcov_report: $(EXECUTABLE) | $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter "lib/*"
ifeq ($(OS), Linux)
	xdg-open $(GCOV_DIR)/index.html
else
	open $(GCOV_DIR)/index.html
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(SRC_DIR)/*.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cc | $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(COV) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(SRC_DIR)/*.h | $(TEST_OBJ_DIR)
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
	clang-format -n --style=Google $(SRC_DIR)/*.cc $(SRC_DIR)/*.h $(TEST_DIR)/*.cc

clang_i:
	clang-format -i --style=Google $(SRC_DIR)/*.cc $(SRC_DIR)/*.h $(TEST_DIR)/*.cc

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test
