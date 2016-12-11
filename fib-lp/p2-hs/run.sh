#!/bin/bash

OUT="programhs.txt"

if [[ -z "$1" ]]; then
	TEST="test/test.in"
else
	TEST="$1"
fi



CPLUS_INCLUDE_PATH=~/Downloads/pccts/h/ make clean all

./parser < $TEST > $OUT

echo ""
echo "====================== PROGRAM ========================"
echo ""

cat $TEST

echo ""
echo "======================  AST    ========================"
echo ""

cat $OUT

echo ""
echo "====================== OUTPUT  ========================"
echo ""

./main < $OUT

echo ""
echo "======================================================="
echo ""
