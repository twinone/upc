#!/bin/bash

OUT="programhs.txt"

if [[ -z "$1" ]]; then
	TEST="tests/test.in"
else
	TEST="$1"
fi



make all

./reader < $TEST > $OUT

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

./program

echo ""
echo "======================================================="
echo ""
