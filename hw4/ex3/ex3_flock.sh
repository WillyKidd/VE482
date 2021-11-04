#!/bin/bash

FILE=./file

if ! [ -s $FILE ]; then
  echo 1 > $FILE
fi

for i in {1..20}
do
  (
    flock -n 33
    last=$(tail -n 1 $FILE)
    ((last+=1))
    echo $last >> $FILE
  )
  33>>$FILE
done
