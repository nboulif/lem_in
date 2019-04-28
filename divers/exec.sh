#!/bin/bash
if [[ -z $1 ]];then
q=50
else
q=$1
fi
c=0
r=0
h=0
for ((i=1; i <= $q; i++)); do
./generator --big-superposition > b$i
time ./lem-in < b$i > f$i
if ((`echo $?` != 0)); then
exit
fi
printf "%-9s: " "expected"
e=`cat f$i | grep -m 1 "required:" | grep -o "[0-9][0-9]*"`
echo $e
printf "%-9s: " "got"
g=`cat f$i | grep "^L" | wc -l`
echo $g
if ((g > e)); then
let h++
fi
if ((g > e + 2)); then
let c++
fi
if ((g > e + 10)); then
let r++
fi
echo $i
sleep 1
done
echo "nbr of high : $h/$q"
echo "nbr of too high : $c/$q"
echo "nbr of way too high : $r/$q"
