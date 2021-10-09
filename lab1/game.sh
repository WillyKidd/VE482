#!/bin/bash
number=$((($RANDOM)%100))
guess=333
count=0
while [ $number -ne $guess ] ; do
	echo guess a number please:
	read guess
	count=$(($count+1))
	if [ $number -lt $guess ] ; then
		echo Smaller
	elif [ $number -gt $guess ] ; then
		echo Larger
	else
		echo "That is correct!"
		echo "You've guessed "$count" times!"
		break
	fi
done
