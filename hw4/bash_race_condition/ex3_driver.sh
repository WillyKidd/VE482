#!/bin/bash

rm file

for i in {1..10}
do
  # ./ex3.sh; ./ex3.sh&
  ./ex3_mkdir.sh; ./ex3_mkdir.sh &
done
