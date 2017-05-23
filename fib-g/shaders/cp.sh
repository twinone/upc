#!/bin/bash

if [[ -z "$2" ]]; then
	echo "Usage: ./cp.sh <file> <file>";
	exit 1
fi


mkdir -p $2
cp $1/$1.vert $2/$2.vert
cp $1/$1.frag $2/$2.frag

echo "Created $2/$2.vert"
echo "Created $2/$2.frag"
