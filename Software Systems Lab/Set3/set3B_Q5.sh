#!/bin/bash
j=0
re='^[+-]?[0-9]+?$'
# re='^[+-]?[0-9]+([.][0-9]+)?$' for floating values..

for i in $@
do
	if ! [[ $i =~ $re ]]
		then
   			echo "error: Not a number" >&2; exit 1
	fi
	array[$j]=$i
	j=`expr $j + 1`
done


# IFS=$'\n' sorted=($(sort <<<"${array[*]}")); unset IFS
# echo "${sorted[@]}"

echo "no of elemnts: $#"


#logic for sorting--bubble sorting used

for ((i=0;i<$#;i++))
do
	for ((j=$i+1;j<$#;j++))
	do
		if [ ${array[$i]} -gt ${array[$j]} ]
			then
				temp=${array[$j]}
				array[$j]=${array[$i]} 
				array[$i]=$temp
		fi
	done
done

echo ${array[@]}