#!/bin/bash

make all

./parser.o < test.in | main.o
