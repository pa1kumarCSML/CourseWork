#!/bin/bash

echo "Enter the list of strings:"
index=0
#enter strings separated by space
read list

for str in ${list[@]}
do
    reversed_string=""
    # finding the length of string
    len=${#str}
    # traverse the string in reverse order.
    for (( i=$len-1; i>=0; i-- ))
        do
            reversed_string="$reversed_string${str:$i:1}" #concatenation
        done
    listA[$index]=$reversed_string
    index=`expr $index + 1`
done
for ((i=0;i<$index;i++))
do
listRev[$i]=${listA[$index - $i -1]}
done    
echo "${listA[@]}"
echo "After reverse"
echo "${listRev[@]}"
