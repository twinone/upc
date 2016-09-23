#!/bin/bash

PROG=example2.o
for i in $(ls samples); do ./$PROG < samples/$i; done

