#!/bin/bash

SIZE="$1"

for i in input/*${SIZE}*; do echo -en "$i\t\t"; ./test.sh $i -en;echo ""; done
