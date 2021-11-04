#!/bin/bash

FILE=./file

if ! test -f $FILE ; then
  echo 1 > $FILE
fi

for i in {1..20}
do
  last=$(tail -n 1 $FILE)
  ((last+=1))
  echo $last >> $FILE
done
