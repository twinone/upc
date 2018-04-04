#!/bin/bash

#Source file extension
SRC_EXT=cpp

if [[ -z "$1" ]]; then
	echo "Usage: ./generate.sh <filename>"
	exit 1;
fi

filename=$(basename "$1")
extension="${filename##*.}"

if [[ $extension == $SRC_EXT ]]; then
	TARGET="src/$1"
else
	TARGET="src/$1.cpp"
fi

if [[ -f "$TARGET" ]]; then
	echo "Warning, file already exists, backing up to $TARGET.bak";
	mv "$TARGET" "$TARGET.bak"
fi


cp ".Template.cpp" "$TARGET"
