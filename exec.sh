# MODE="--flow-ten" 
# MODE="--flow-thousand" 
# MODE="--big" 
MODE="--big-superposition"
my_lem_in='./lem-in'
hv_lem_in='./divers/lem-in_hv'
nb_test=100

total=0
res_min=0
res_equal=0
res_plus_0=0
res_plus_2=0
res_plus_10=0

make

echo "MODE = $MODE"
echo "expected vs us (res/total)"
echo "min | equal | plus_0 | plus_2 | plus_10"
for (( INDICE=1; INDICE<=$nb_test; INDICE++ ))
do
	TMPFFF1="test_files/$INDICE\_mapp" 
	TMPFFF2="test_files/$INDICE\_ress" 
	TMPFFF_HV="test_files/$INDICE\_ress_hv" 
	echo "------ $INDICE --------"
	# ./generator $MODE > $TMPFFF1
	$my_lem_in < $TMPFFF1 > $TMPFFF2
	$hv_lem_in < $TMPFFF1 > $TMPFFF_HV
	e1=`sed '2q;d' $TMPFFF1 | grep -o "[0-9][0-9]*"`
	e2=`tail -n 1 $TMPFFF2 | grep -o "[0-9][0-9]*"`
	e_hv=`cat $TMPFFF_HV | grep "^L" | wc -l | bc -l`
	e3=`echo "$e2-$e1" | bc -l`
	e3_hv=`echo "$e_hv-$e1" | bc -l`
	if (($e3 < 0)); then e3c=`tput setaf 2`; let res_min++
	elif (($e3 == 0)); then e3c=`tput setaf 4`; let res_equal++
	elif (($e3 < 3)); then e3c=`tput setaf 5`; let res_plus_0++
	elif (($e3 < 11)); then e3c=`tput setaf 3`; let res_plus_2++
	else e3c=`tput setaf 1` ; let res_plus_10++ ;fi
	e3r=`tput sgr0`
	total=`echo "$total+$e3" | bc -l`	
	echo "$e1-$e2 ($e_hv) ($e3_hv) $e3c$e3$e3r / $total"
	echo "$res_min | $res_equal | $res_plus_0 | $res_plus_2 | $res_plus_10"
	cat $TMPFFF2 | grep "DISC\|CROIS"
	# ./../nboulif/lem-in < $TMPFFF1 > $TMPFFF2
	# tail -n 1 $TMPFFF2
done