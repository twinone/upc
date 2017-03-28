#!/bin/bash

mkdir $1
cp skel/skel.vert $1/$1.vert
cp skel/skel.frag $1/$1.frag

echo "Created $1/$1.vert"
echo "Created $1/$1.frag"
