#!/bin/bash

CPLUS_INCLUDE_PATH=~/Downloads/pccts/h/ make all

./parser < test/test.in

./parser --noast < test/test.in | ./main
