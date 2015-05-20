#!/bin/bash

# This script assumes the documentation is generated

DIR=$(dirname $( cd "$( dirname "$0" )" && pwd ))
J_DIR="$DIR/release"
OUT_DIR="$J_DIR/out"
DOC_DIR="$DIR/doc"
TEST_DIR="$DIR/test"

rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

cd "$DIR"
cp src/*.cc src/*.hh $OUT_DIR
cp $J_DIR/makefile $OUT_DIR
cp -r "$DOC_DIR/html" "$OUT_DIR"

cd $OUT_DIR
mv main.cc program.cc
rm comanda.cc comanda.hh token.cc token.hh

cp "$TEST_DIR/jp_"*"entrada.txt" .
cp "$TEST_DIR/jp_"*"sortida.txt" .

if [ "$1" != "jutge" ]; then
	zip -r html.zip html
	bzip2 html.zip
fi
rm -rf html

tar -cf "program.tar" *
rm -rf *.cc *.hh makefile html.zip.bzip2

