#!/bin/bash
if [ $# -eq 0 ] ; then
    echo "Please specify input file!"
    exit -1
fi

file=$1
count=$(wc -l < $file)

if [ $count -gt 0 ] ; then 
	for((i=($count); i>0; i--)) ; do
		head -n $i $file | tail -n 1 | xargs echo >> $file
	done
	sed -i '1,'$count'd' $file
fi

