#!/bin/bash

runtest() {
	echo "-----------------"
	echo Running $i
	./test.sh $1 2>&1 |grep "top score"
}

runtest default.cnf
for i in maze*cnf; do
	runtest $i
done
