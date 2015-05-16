#!/bin/bash

# This script assumes the documentation is generated

DIR=$(dirname $( cd "$( dirname "$0" )" && pwd ))
J_DIR="$DIR/jutge"
OUT_DIR="$J_DIR/out"
DOC_DIR="$DIR/doc"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

cd "$DIR"
cp src/*.cc src/*.hh $OUT_DIR
cp $J_DIR/makefile $OUT_DIR
cd $OUT_DIR

mv main.cc program.cc
tar -cf "program.tar" *
rm *.cc *.hh makefile
