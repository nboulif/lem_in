#!/bin/bash
if [[ -z $1 ]];then
	q=20
else
	q=$1
fi
for ((i=1; i <= $q; i++)) do
cat f45 | grep "^L" | grep "L$i-" | wc -l
done
