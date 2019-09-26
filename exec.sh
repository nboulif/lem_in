if (($# == 0)); then
	echo "NO EXE"
	echo "./exec.sh [-m big] [-n 10] [lem_in_1] [lem_in_2]"
	echo "./exec.sh mode nb_test player1 player2"
	exit 1
fi

lem_in_1=0
lem_in_2=0

param2=0
param3=0
param4=0
param5=0
param6=0

param1=$1
if (($# > 1)); then param2=$2 ; fi
if (($# > 2)); then param3=$3 ; fi
if (($# > 3)); then param4=$4 ; fi
if (($# > 4)); then param5=$5 ; fi
if (($# > 5)); then param6=$6 ; fi

if [[ "$param1" == "-m" ]]; then MODE=$param2
elif [[ "$param3" == "-m" ]]; then MODE=$param4
else MODE="none" ; fi

if [[ "$param1" == "-n" ]]; then NB_TEST=$param2 
elif [[ "$param3" == "-n" ]]; then NB_TEST=$param4
else NB_TEST=9999 ; fi

if [ $MODE == "none" ] && [ $NB_TEST == 9999 ] ; then
	lem_in_1=$param1
	if (($# > 1)); then lem_in_2=$param2; fi
	MODE="big"
	NB_TEST=10
elif [ $MODE == "none" ] && [ $NB_TEST != 9999 ] ; then
	lem_in_1=$param3
	if (($# > 3)); then lem_in_2=$param4; fi
	MODE="big"
elif [ $MODE != "none" ] && [ $NB_TEST == 9999 ] ; then
	lem_in_1=$param3
	if (($# > 3)); then lem_in_2=$param4; fi
	NB_TEST=10
else
	lem_in_1=$param5
	if (($# > 5)); then lem_in_2=$param6; fi
fi

if ! [[ "$MODE" =~ ^(big|big-superposition|flow-one|flow-ten|flow-thousand)$ ]]; then
	echo "UNKNOWN MODE"
	exit 1
fi
re='^[0-9]+$'
if ! [[ $NB_TEST =~ $re ]] ; then
	echo "WRONG NUMBER OF TEST"
	exit 1
fi

total=0
total_2=0
res_min=0
res_equal=0
res_plus_0=0
res_plus_2=0
res_plus_10=0
res_2_min=0
res_2_equal=0
res_2_plus_0=0
res_2_plus_2=0
res_2_plus_10=0

make

echo "MODE = $MODE -- NB TEST = $NB_TEST"
echo "expected vs us (res/total)"
echo "min | equal | plus_0 | plus_2 | plus_10"
for (( INDICE=1; INDICE<=$NB_TEST; INDICE++ ))
do
	MAPS="test_files/$INDICE\_map" 
	RES1="test_files/$INDICE\_ress1" 
	RES2="test_files/$INDICE\_ress2"
	./generator --$MODE > $MAPS
	nb_turn_expected=`sed '2q;d' $MAPS | grep -o "[0-9][0-9]*"`
	./$lem_in_1 < $MAPS > $RES1
	# nb_turn_1=`tail -n 1 $RES1 | grep -o "[0-9][0-9]*"`
	nb_turn_1=`cat $RES1 | grep "^L" | wc -l | bc -l`
	cat $RES1 | grep "nb_ants"
	player_1_res=`echo "$nb_turn_1-$nb_turn_expected" | bc -l`
	if (($player_1_res < 0)); then player_1_color=`tput setaf 2`; let res_min++
	elif (($player_1_res == 0)); then player_1_color=`tput setaf 4`; let res_equal++
	elif (($player_1_res < 3)); then player_1_color=`tput setaf 5`; let res_plus_0++
	elif (($player_1_res < 11)); then player_1_color=`tput setaf 3`; let res_plus_2++
	else player_1_color=`tput setaf 1` ; let res_plus_10++ ;fi
	player_1_color_reset=`tput sgr0`
	total=`echo "$total+$player_1_res " | bc -l`	
	if [ "$lem_in_2" != "0" ] ; then
		./$lem_in_2 < $MAPS > $RES2 
		# nb_turn_2=`tail -n 1 $RES2 | grep -o "[0-9][0-9]*"`
		nb_turn_2=`cat $RES2 | grep "^L" | wc -l | bc -l`
		player_2_res=`echo "$nb_turn_2-$nb_turn_expected" | bc -l`
		if (($player_2_res < 0)); then player_2_color=`tput setaf 2`; let res_2_min++
		elif (($player_2_res == 0)); then player_2_color=`tput setaf 4`; let res_2_equal++
		elif (($player_2_res < 3)); then player_2_color=`tput setaf 5`; let res_2_plus_0++
		elif (($player_2_res < 11)); then player_2_color=`tput setaf 3`; let res_2_plus_2++
		else player_2_color=`tput setaf 1` ; let res_2_plus_10++ ;fi
		player_2_color_reset=`tput sgr0`
		total_2=`echo "$total_2+$player_2_res " | bc -l`
		# printf "$INDICE -- $nb_turn_expected => $nb_turn_1 vs $nb_turn_2 / $player_1_color$player_1_res$player_1_color_reset vs $player_2_color$player_2_res$player_2_color_reset / $total vs $total_2 --- $res_min | $res_equal | $res_plus_0 | $res_plus_2 | $res_plus_10 --- $res_2_min | $res_2_equal | $res_2_plus_0 | $res_2_plus_2 | $res_2_plus_10\\r"

		printf "
$INDICE -- $nb_turn_expected => $nb_turn_1 vs $nb_turn_2 / $player_1_color$player_1_res$player_1_color_reset vs $player_2_color$player_2_res$player_2_color_reset / $total vs $total_2
$res_min | $res_equal | $res_plus_0 | $res_plus_2 | $res_plus_10 
$res_2_min | $res_2_equal | $res_2_plus_0 | $res_2_plus_2 | $res_2_plus_10
"
	else
		printf "
$INDICE -- $nb_turn_expected => $nb_turn_1 / $player_1_color$player_1_res$player_1_color_reset / $total
$res_min | $res_equal | $res_plus_0 | $res_plus_2 | $res_plus_10 
"
	fi
	
	cat $RES1 | grep "DISC\|CROIS\|SPEC"
	# if [[ "$MODE" =~ ^(flow-one|flow-ten|flow-thousand)$ ]]; then
		sleep 0.7
		#sleep 1.1
	# fi
done