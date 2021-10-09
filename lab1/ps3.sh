#!/bin/bash
PS3='Enter a digit: '
select i in a b c d e
do
	case $i in
		a) echo "alpha";;
		b) echo "beta";;
		c) echo "charlie";;
		d) echo "delta";;
		e) echo "exit"; exit;;
	esac
done
