# MODE="--flow-ten" 
# MODE="--flow-thousand" 
MODE="--big" 
# MODE="--big-superposition" 
make
total=0
res_min=0
res_equal=0
res_plus_0=0
res_plus_2=0
res_plus_10=0
echo "expected vs us (res/total)"
echo "min | equal | plus_0 | plus_2 | plus_10"
for INDICE in {1..100}
do
	TMPFFF1="test_files/$INDICE\_mapp" 
	TMPFFF2="test_files/$INDICE\_ress" 
	echo "------ $INDICE --------"
	./generator $MODE > $TMPFFF1
	./lem-in < $TMPFFF1 > $TMPFFF2
	e1=`sed '2q;d' $TMPFFF1 | grep -o "[0-9][0-9]*"`
	e2=`tail -n 1 $TMPFFF2 | grep -o "[0-9][0-9]*"`
	e3=`echo "$e2-$e1" | bc -l`
	total=`echo "$total+$e3" | bc -l`	
	echo "$e1-$e2 ($e3/$total)"
	if (($e3 < 0)); then
	let res_min++
	elif (($e3 == 0)); then
	let res_equal++
	elif (($e3 < 3)); then
	let res_plus_0++
	elif (($e3 < 11)); then
	let res_plus_2++
	else
	let res_plus_10++
	fi
	echo "$res_min | $res_equal | $res_plus_0 | $res_plus_2 | $res_plus_10"
	cat $TMPFFF2 | grep "DISC\|CROIS"
	# ./../nboulif/lem-in < $TMPFFF1 > $TMPFFF2
	# tail -n 1 $TMPFFF2
done