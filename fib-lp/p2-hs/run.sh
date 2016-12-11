#!/bin/bash

if [[ -z "$1" ]]; then
	TEST="test/test.in"
else
	TEST="$1"
fi

CPLUS_INCLUDE_PATH=~/Downloads/pccts/h/ make all

./parser < $TEST

./parser --noast < $TEST | ./main
