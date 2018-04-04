#!/bin/bash

if [[ -z "$2" ]]; then echo "Usage: $0 <file> <round>"; exit; fi

file=Twinone"$1".log
rnd="$2"
next=$(($rnd + 10))


if [[ -n "$3" ]]; then next=$3; fi

#echo $file $rnd $next
#echo grep -ne "___BEGIN_ROUND_""${rnd}$" "$file"

X=$(grep -ne "___BEGIN_ROUND_""${rnd}$" "$file"|cut -d: -f1)
Y=$(grep -ne "___BEGIN_ROUND_""${next}$" "$file"|cut -d: -f1)

#echo $X $Y

tail -n +$X $file | head -n $(($Y-$X+1))|less
