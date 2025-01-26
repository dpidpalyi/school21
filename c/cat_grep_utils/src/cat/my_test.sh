#!/bin/bash

UNAME_OUT="$(uname -s)"
    case "${UNAME_OUT}" in
	Linux*) MACHINE=Linux;;
	Darwin*) MACHINE=Mac;;
	*) MACHINE="UNKNOWN:${UNAME_OUT}"
    esac


S21_CAT=./s21_cat
DIR_TESTS=my_test_files/*.txt
FLAGS=(
	"-b"
	"--number-nonblank"
	"-n"
	"--number"
	"-e"
	"-E"
	"-s"
	"--squeeze-blank"
	"-t"
	"-T"
	"-v"
)
SUCCESS1=0
FAIL1=0
SUCCESS_MULT=0
FAIL_MULT=0

test_1() {
	RES1=$($S21_CAT $FLAG $FILE 2>/dev/null | shasum -a 256)
	RES2=$(cat $FLAG $FILE 2>/dev/null | shasum -a 256)

	if [ "$RES1" == "$RES2" ]
	then
		((SUCCESS1++))
		if [ "$1" == "-a" ]
		then
			echo "SUCCESS TEST $FLAG $FILE"
		fi
	else
		echo "FAILED TEST $FLAG $FILE"
		((FAIL1++))
	fi
}

test_mult() {
	RES1=$($S21_CAT $FLAG $FILE1 $FILE2 2>/dev/null | shasum -a 256)
	RES2=$(cat $FLAG $FILE1 $FILE2 2>/dev/null | shasum -a 256)
	if [ "$RES1" == "$RES2" ]
	then
		((SUCCESS_MULT++))
		if [ "$1" == "-a" ]
		then
			echo "SUCCESS TEST $FLAG $FILE1 $FILE2"
		fi
	else
		echo "FAILED TEST $FLAG $FILE1 $FILE2"
		((FAIL_MULT++))
	fi
}

test_mem() {
	if [ "$MACHINE" == "Linux" ]
	then 
		valgrind --tool=memcheck --leak-check=yes --log-file="mem.log" \
			$S21_CAT -bnestv $DIR_TESTS 2>&1 >/dev/null

		MEM1=$(grep "LEAK SUMMARY:" mem.log)
		MEM2=$(grep "ERROR SUMMARY: [^0]" mem.log)
		rm -rf mem.log
		if [ "$MEM1" == "" ] && [ "$MEM2" == "" ]
		then
			echo "MEMORY TEST SUCCESS"
		else
			echo "MEMORY TEST FAILED -bnestv $DIR_TESTS"
		fi
	elif [ "$MACHINE" == "Mac" ]
	then
		leaks -atExit -- $S21_CAT -bnestv $DIR_TESTS 2>&1 >/dev/null
		MEM=$?
		if [ "$MEM" == 0 ]
		then
			echo "MEMORY TEST SUCCESS"
		else
			echo "MEMORY TEST FAILED -bnestv $DIR_TESTS"
		fi
	fi
}
echo "========================"
echo "MANUAL TEST FOR ONE FILE"
echo "========================"

for FILE in $DIR_TESTS; do
	for FLAG in ${FLAGS[@]}; do
		test_1 "$1"
	done
	FLAG="-bnestv"
	test_1
done

FILE="my_test_files/no_exist_file.txt"
for FLAG in ${FLAGS[@]}; do
	test_1 "$1"
done
FLAG="-bnestv"
test_1 "$1"

echo "=========================="
echo "SUCCESS WITH ONE FILE = $SUCCESS1"
echo "FAILED WITH ONE FILE = $FAIL1"
echo "=========================="

echo ""
echo "==============================="
echo "MANUAL TESTS FOR MULTIPLE FILES"
echo "PLEASE WAIT TILL END OF TESTS!!"
echo "==============================="

for FILE1 in $DIR_TESTS; do
	for FILE2 in $DIR_TESTS; do
		for FLAG in ${FLAGS[@]}; do
			test_mult "$1"
		done
		FLAG="-bnestv"
		test_mult "$1"
                FILE2="my_test_files/no_exist_file.txt"
		test_mult "$1"
	done
done

echo "=================================="
echo "SUCCESS WITH MULTIPLE FILES = $SUCCESS_MULT"
echo "FAILED WITH MULTIPLE FILES = $FAIL_MULT"
echo "=================================="

echo ""
echo "==================="
test_mem
echo "==================="

echo ""
echo "===== FINAL RESULT ====="
echo "SUCCESS TESTS = $((SUCCESS1 + SUCCESS_MULT))"
echo "FAILED TESTS = $((FAIL1 + FAIL_MULT))"
echo "======== END ==========="
