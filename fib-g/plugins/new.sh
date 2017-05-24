#!/bin/bash

if [[ -z "$2" ]]; then
	echo "Usage: $0 <name> [origname]"
	exit 1
fi

ORIG="$2"
echo "Copying from template $ORIG"

NAME="$1"

cp -r $ORIG $NAME
for i in {cpp,frag,h,pro,vert}; do 
	rm $ORIG/Makefile -f
	mv $NAME/$ORIG.$i $NAME/$NAME.$i
	sed -i "s/$ORIG/$NAME/g" $NAME/$NAME.$i
	cp plugins.pro plugins.pro.bak
	cat plugins.pro.bak |grep -iv $NAME > plugins.pro
	echo "SUBDIRS += $NAME" >> plugins.pro
done
