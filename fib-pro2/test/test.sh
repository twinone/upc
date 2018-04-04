#!/bin/bash
# Run test cases against the program
# Usage: ./test.sh [case]
# All test cases should end with .in and .out and contain no spaces

EXEC="./taskman"
TEST_DIR=test
DIFF_CMD=$(which colordiff)
if [ -z "$DIFF_CMD" ]; then DIFF_CMD=$(which diff); fi

if [ -z "$1" ]; then
	TESTS=$(ls "$TEST_DIR"|grep "\\.in"|sed 's/\.in//')
else
	TESTS="$1"
fi

for test in $TESTS; do
	outfile=$(tempfile)
	"$EXEC" < "$TEST_DIR/${test}.in" > "$outfile"
	d=$("$DIFF_CMD" "$TEST_DIR/${test}.out" "$outfile")
	if [ "$?" == "0" ]; then
		echo "Test case $test [ OK ]"
	else
		echo "Test case $test [ ERR ]"
#		echo "Yout output:"
#		cat $outfile
#		echo "---- correct:"
#		cat "$TEST_DIR/${test}.out"
		echo "---- diff:"
		"$DIFF_CMD" "$TEST_DIR/${test}.out" "$outfile"
	fi
done


