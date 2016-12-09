#!/bin/bash

CPLUS_INCLUDE_PATH=~/Downloads/pccts/h/ make all

./parser < test.in

./parser --noast < test.in | ./main
