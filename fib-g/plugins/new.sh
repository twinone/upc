#!/bin/bash

if [[ -z "$1" ]]; then
	echo "Usage: $0 <name>"
	exit 1
fi

ORIG="Template"
NAME="$1"

cp -r $ORIG $NAME
for i in {cpp,frag,h,pro,vert}; do 
	mv $NAME/$ORIG.$i $NAME/$NAME.$i
	sed -i "s/Template/$NAME/g" $NAME/$NAME.$i
	sed -i "s/template/$NAME/g" $NAME/$NAME.$i
	cp plugins.pro plugins.pro.bak
	cat plugins.pro.bak |grep -iv $NAME > plugins.pro
	echo "SUBDIRS += $NAME" >> plugins.pro
done
