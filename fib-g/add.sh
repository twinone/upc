#!/bin/bash

if [[ -z "$1" ]]; then
	echo "Usage: ./mk.sh <file>";
	exit 1
fi

pushd $1
git add .
git commit -am "Add $1"
popd
