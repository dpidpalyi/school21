#!/bin/bash

UNAME_OUT="$(uname -s)"
    case "${UNAME_OUT}" in
	Linux*) MACHINE=Linux;;
	Darwin*) MACHINE=Mac;;
	*) MACHINE="UNKNOWN:${UNAME_OUT}"
    esac


S21_GREP=./s21_grep
DIR_TESTS=my_test_files/*.txt

FLAGS=(
	"-i"
	#"-v"
	#"-c"
	#"-l"
	#"-n"
	#"-h"
	#"-s"
	#"-o"
)

PATTERNS_FILES=(
	"my_test_files/no_exist_file.txt"
	"my_test_files/empty"
	"my_test_files/patterns"
)

PATTERNS=(
	"'Nulla'"
	"'^Excepteur'"
	"'sagittis.$'"
	"'\blibero\b'"
	"'ipsum\s'"
	"'sed\|Sed'"
	"'^Integer.*massa.*.$'"
	"'vel\|it\|ita'"
)

SUCCESS_SIMPLE=0
FAIL_SIMPLE=0
SUCCESS_E=0
FAIL_E=0
SUCCESS_F=0
FAIL_F=0

test_simple() {
	RES1=$($S21_GREP $PATTERN $FLAG $FILE 2>/dev/null | shasum -a 256)
	RES2=$(grep $PATTERN $FLAG $FILE 2>/dev/null | shasum -a 256)

	if [ "$RES1" == "$RES2" ]
	then
		((SUCCESS_SIMPLE++))
		if [ "$1" == "-a" ]
		then
			echo "SUCCESS TEST $PATTERN $FLAG $FILE"
		fi
	else
		echo "FAILED TEST $PATTERN $FLAG $FILE"
		((FAIL_SIMPLE++))
	fi
}

test_with_e() {
	RES1=$($S21_GREP -e $PATTERN1 $PATTERN2 $FLAG $FILE 2>/dev/null | shasum -a 256)
	RES2=$(grep -e $PATTERN1 $PATTERN2 $FLAG $FILE 2>/dev/null | shasum -a 256)
	if [ "$RES1" == "$RES2" ]
	then
		((SUCCESS_E++))
		if [ "$1" == "-a" ]
		then
			echo "SUCCESS TEST -e $PATTERN1 $PATTERN2 $FLAG $FILE"
		fi
	else
		((FAIL_E++))
		echo "FAILED TEST -e $PATTERN1 $PATTERN2 $FLAG $FILE"
	fi
}

test_with_f() {
	RES1=$($S21_GREP -f $PATTERNS_FILE $FLAG $FILE1 $FILE2 2>/dev/null | shasum -a 256)
	RES2=$(grep -f $PATTERNS_FILE $FLAG $FILE1 $FILE2 2>/dev/null | shasum -a 256)
	if [ "$RES1" == "$RES2" ]
	then
		((SUCCESS_F++))
		if [ "$1" == "-a" ]
		then
			echo "SUCCESS TEST -f $PATTERNS_FILE $FLAG $FILE1 $FILE2"
		fi
	else
		((FAIL_F++))
		echo "FAILED TEST -f $PATTERNS_FILE $FLAG $FILE1 $FILE2"
	fi
}

test_mem() {
	if [ "$MACHINE" == "Linux" ]
	then 
		valgrind --tool=memcheck --leak-check=yes --log-file="mem.log" \
			$S21_GREP -e "proi" -f $PATTERNS_FILE -iclnhso $DIR_TESTS 2>&1 >/dev/null

		MEM1=$(grep "LEAK SUMMARY:" mem.log)
		MEM2=$(grep "ERROR SUMMARY: [^0]" mem.log)
		rm -rf mem.log
		if [ "$MEM1" == "" ] && [ "$MEM2" == "" ]
		then
			echo "MEMORY TEST SUCCESS"
		else
			echo "MEMORY TEST FAILED -e "proi" -f $PATTERNS_FILE -iclnhso $DIR_TESTS"
		fi
	elif [ "$MACHINE" == "Mac" ]
	then
		leaks -atExit -- $S21_GREP -e "proi" -f $PATTERNS_FILE -iclnhso $DIR_TESTS 2>&1 >/dev/null
		MEM=$?
		if [ "$MEM" == 0 ]
		then
			echo "MEMORY TEST SUCCESS"
		else
			echo "MEMORY TEST FAILED -e "proi" -f $PATTERNS_FILE -iclnhso $DIR_TESTS"
		fi
	fi
}
echo ""
echo "============================"
echo "AUTO TEST WITH SIMPLE REGEXP"
echo "============================"

for FILE in $DIR_TESTS; do
	for PATTERN in ${PATTERNS[@]}; do
		for FLAG in ${FLAGS[@]}; do
			test_simple "$1"
		done
		#FLAG="-ivch"
		#test_simple "$1"
		#FLAG="-io"
		#test_simple "$1"
		#FLAG="-vcns"
		#test_simple "$1"
		#FLAG="-ilh"
		#test_simple "$1"
	done
done

FILE="my_test_files/no_exist_file.txt"
for PATTERN in ${PATTERNS[@]}; do
	for FLAG in ${FLAGS[@]}; do
		test_simple "$1"
	done
	#FLAG="-iclnhso"
	#test_simple "$1"
done

echo "================================="
echo "SUCCESS WITH SIMPLE REGEXP = $SUCCESS_SIMPLE"
echo "FAILED WITH SIMPLE REGEXP = $FAIL_SIMPLE"
echo "================================="

echo ""
echo "==================================="
echo "AUTO TESTS FOR MULTIPLE -e PATTERNS"
echo "   PLEASE WAIT TILL END OF TESTS"
echo "==================================="

for FILE in $DIR_TESTS; do
	for PATTERN1 in ${PATTERNS[@]}; do
		for PATTERN2 in ${PATTERNS[@]}; do
			for FLAG in ${FLAGS[@]}; do
				test_with_e "$1"
			done
			#FLAG="-ivch"
			#test_with_e "$1"
			#FLAG="-io"
			#test_with_e "$1"
			#FLAG="-vcns"
			#test_with_e "$1"
			#FLAG="-ilh"
			#test_with_e "$1"
			#FLAG="-icln"
			#test_with_e "$1"
			#FILE="my_test_files/no_exist_file.txt"
			#test_with_e "$1"
		done
	done
done

echo "========================================="
echo "SUCCESS WITH MULTIPLE -e PATTERNS = $SUCCESS_E"
echo "FAILED WITH MULTIPLE -e PATTERNS = $FAIL_E"
echo "========================================="

echo ""
echo "==========================================="
echo "AUTO TESTS FOR MULTIPLE FILES AND -f OPTION"
echo "       PLEASE WAIT TILL END OF TESTS"
echo "==========================================="

for FILE1 in $DIR_TESTS; do
	for FILE2 in $DIR_TESTS; do
		for PATTERNS_FILE in ${PATTERNS_FILES[@]}; do
			for FLAG in ${FLAGS[@]}; do
				test_with_f "$1"
			done
			#FLAG="-ivch"
			#test_with_f "$1"
			#FLAG="-io"
			#test_with_f "$1"
			#FLAG="-vcns"
			#test_with_f "$1"
			#FLAG="-ilh"
			#test_with_f "$1"
			#FLAG="-icln"
			#test_with_f "$1"
			#FILE="my_test_files/no_exist_file.txt"
			#test_with_f "$1"
		done
	done
done

echo "================================================="
echo "SUCCESS WITH MULTIPLE FILES AND -f OPTION = $SUCCESS_F"
echo "FAILED WITH MULTIPLE FILES AND -f OPTION = $FAIL_F"
echo "================================================="

echo ""
echo "==================="
test_mem
echo "==================="

echo ""
echo "===== FINAL RESULT ====="
echo "SUCCESS TESTS = $((SUCCESS_SIMPLE + SUCCESS_E + SUCCESS_F))"
echo "FAILED TESTS = $((FAIL_SIMPLE + FAIL_E + FAIL_F))"
echo "======== END ==========="
