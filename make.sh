#!/bin/bash

rm -rf upc
mkdir upc
pushd upc
git init
git commit --allow-empty -m "Initial commit"

for i in $(cat ../repos.txt); do
	echo $i
	git clone gh:twinone/$i tmp-$i
	
	pushd tmp-$i # in every repo's folder:
	git filter-branch --tree-filter 'mkdir -p /tmp/bla; mv * .gitignor* /tmp/bla; mkdir '"$i"'; mv /tmp/bla/* '"$i"'/; rm -rf /tmp/bla' --prune-empty -- --all
	popd	
done
popd

rm -rf out
mkdir out
pushd out

git init
git commit --allow-empty -m "Initial commit"


for i in $(cat ../repos.txt); do
	git remote add $i ../upc/tmp-$i
done

git fetch --all


for i in $(cat ../repos.txt); do
	git checkout -b $i $i/master
	git checkout master
	git merge $i --allow-unrelated-histories -m "Merge $i"
done

popd

