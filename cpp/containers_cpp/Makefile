BIN_DIR    ?= build
BUILD_TYPE ?= Debug
BUILD_DIR  ?= $(BIN_DIR)/$(BUILD_TYPE)
$(shell 2>/dev/null echo ${BUILD_TYPE} > ${BIN_DIR}/last_build.txt)


all: build test gcov_report
.PHONY: all
re: clean all
.PHONY: re

configure:
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
.PHONY: configure

debug:   BUILD_TYPE = Debug
release: BUILD_TYPE = Release
build release debug: configure	
	cmake --build $(BUILD_DIR) --parallel 8 -- --output-sync
.PHONY: build release debug

test:
	cmake --build $(BUILD_DIR) --target check
.PHONY: test
retest:
	cmake --build $(BUILD_DIR) --target test
.PHONY: retest

memcheck:
	cmake --build $(BUILD_DIR) --target memcheck
.PHONY: memcheck

gcov_report:
	cmake --build $(BUILD_DIR) --target coverage
.PHONY: gcov_report

LINTFLAGS := --style=google
lint:     LINTFLAGS += -n
lint_fix: LINTFLAGS += -i
lint lint_fix:
	clang-format ${LINTFLAGS} $(shell find tests include -type f -name '*.h' \
	                                                         -or -name '*.cc')
.PHONY: lint lint_fix

clean:
	rm -rf ${BIN_DIR}/$(shell cat ${BIN_DIR}/last_build.txt)
fclean:
	rm -rf $(BIN_DIR) extern/*
.PHONY: clean fclean
