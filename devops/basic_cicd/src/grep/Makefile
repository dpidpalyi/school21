CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

.PHONY: all

all: build

.PHONY: build

build: s21_grep

s21_grep: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clang_i

clang_i:
	clang-format --style=Google -i *.c *.h

.PHONY: clang_n

clang_n:
	clang-format --style=Google -n *.c *.h

.PHONY: cppcheck

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

.PHONY: valgrind

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep -vcns -e "Nulla" -f my_test_files/patterns my_test_files/empty.txt my_test_files/lorem.txt

.PHONY: test

test:
	bash my_test.sh -a

.PHONY: clean

clean:
	rm -rf *.o *.out s21_grep

.PHONY: rebuild

rebuild: clean build
