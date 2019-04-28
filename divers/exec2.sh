#!/bin/bash
if [[ -z $1 ]];then
q=20
else
q=$1
fi
c=0
r=0
h=0
cad=0
rad=0
had=0
for ((i=1; i <= $q; i++)); do
./generator --big-superposition > b$i
./lem-in_ad < b$i > f_ad$i
./lem-in < b$i > f$i
if ((`echo $?` != 0)); then
exit
fi
printf "%-9s: " "expected"
e=`cat f$i | grep -m 1 "required:" | grep -o "[0-9][0-9]*"`
echo $e
printf "adef %-9s: " "got"
gad=`cat f_ad$i | grep "^nb_op" | wc -l`
echo $gad
printf "nous %-9s: " "got"
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

if ((gad > e)); then
let had++
fi
if ((gad > e + 2)); then
let cad++
fi
if ((gad > e + 10)); then
let rad++
fi
echo $i
sleep 0.7
done
echo "ns nbr of high : $h/$q"
echo "ns nbr of too high : $c/$q"
echo "ns nbr of way too high : $r/$q"

echo "ad nbr of high : $had/$q"
echo "ad nbr of too high : $cad/$q"
echo "ad nbr of way too high : $rad/$q"
