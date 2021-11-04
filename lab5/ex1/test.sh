#!/bin/bash
echo "removing all *.txt and make files"
make clean
make all
echo "Please enter the data type: (int, double, char*):"
echo -n "> "
read dtype
echo "Please enter the order to sort the list: (inc, dec, rand)"
echo -n "> "
read order
echo "Thanks. A list of 10 items with random order will be randomly generated."
echo "The file name is rand_$dtype.txt"
echo "Choose the command line interface or the menu interface: (cmd, menu)"
echo -n "> "
read interface

touch "rand_$dtype.txt"
for i in {1..10}
do
    rand_key=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w 5 | head -n 1)
    if [ "$dtype" = "int" ]; then
        rand_val=$(( ( RANDOM % 100 )  + 1 ))
    elif [ "$dtype" = "double" ]; then
        rand_val=$(( ( RANDOM % 100 )  + 1 ))
        rand_helper=$(cat /dev/urandom | tr -dc '0-9' | fold -w 6 | head -n 1)
        rand_val="${rand_val}.${rand_helper}"
    elif [ "$dtype" = "char*" ]; then
        rand_val=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w 10 | head -n 1)
    else
        echo "error: the data type specified is not supported."
        exit -1
    fi
    echo "${rand_key}=${rand_val}" >> "rand_$dtype.txt"
done

if [ "$interface" = "cmd" ]; then
    ./cmd "rand_$dtype.txt" $order
elif [ "$interface" = "menu" ]; then
    ./menu
else
    echo "error: the interface specified is not supported."
fi
