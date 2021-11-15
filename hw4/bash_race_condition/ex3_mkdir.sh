#!/bin/bash
FILE=race.txt
LOCK=lockdir

if ! test -f $FILE ; then
	echo 1 > $FILE
fi

for i in {1..100}; do
    while test -d $LOCK; do
        :
    done
    mkdir $LOCK
    last=$(tail -n 1 $FILE)
    ((last++))
    echo $last >> $FILE
    rmdir $LOCK
done
