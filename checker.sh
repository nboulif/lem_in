#!/bin/bash
if [[ -z $1 ]];then
	q=20
else
	q=$1
fi
for ((x=1; x <= 20; x++)) do
echo $x

# for ((i=1; i <= $q; i++)) do
# echo -n "L$i-"
# cat f$x | grep "L$i-" | wc -l
# done
cat f$x | grep "CROIS"
cat f$x | grep "DIS"
done