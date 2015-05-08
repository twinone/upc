#!/bin/bash

OUT_DIR=out

rm -rf $OUT_DIR
mkdir -p $OUT_DIR

cp src/*.cc src/*.hh $OUT_DIR
cp makefile_jutge $OUT_DIR/makefile
cd $OUT_DIR
tar -cf "program.tar" *
rm *.cc *.hh makefile
