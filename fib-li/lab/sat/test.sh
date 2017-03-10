#!/bin/bash


CNF="$1"
NAME=$(echo $CNF|cut -d/ -f2)
O="$2"


sat=$(cat resum.txt|grep -A2 $NAME|tail -n1)

expected_time=$(cat resum.txt|grep -A3 $NAME|tail -n1|cut -d" " -f2)
echo $O "$expected_time\t"

pico_time=$((TIME=%U time picosat $CNF > /dev/null) 2>&1)
echo $O "$pico_time\t"


my_time=$((TIME=%U time ./SAT < $CNF > /dev/null) 2>&1)
echo $O "$my_time\t"
echo $O "$sat\t"



