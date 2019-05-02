TMPFFF1="tesst1" 
TMPFFF2="tesst2" 
MODE="--big-superposition" 
make

for VARIABLE in {1..20}
do
	./divers/generator $MODE > $TMPFFF1
	head -n 2 $TMPFFF1
	./lem-in < $TMPFFF1 > $TMPFFF2
	tail -n 1 $TMPFFF2
	./../lem_in19/lem-in < $TMPFFF1 > $TMPFFF2
	tail -n 1 $TMPFFF2
done