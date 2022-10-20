#!/bin/bash

arr_csv=() 
while IFS= read -r line 
do
    arr_csv+=("$line")
done < Student_marks.csv

index=0
noofcol=0
noofdeformedrows=0
noofrows=0
for record in "${arr_csv[@]}"
do
   IFS=','
   # no of columns
   read -ra arr <<< "$record"

   if [ $noofcol == 0 ]
   then
      noofcol=${#arr[@]}
      continue
   fi


   if [ $noofcol -ne 0 -a $noofrows -eq 0 -a $index -eq `expr ${#arr_csv[@]} - 2` ]
   then
      if [ $index == ${arr[1]} ]
      then
         noofrows=$index
         continue
      fi   
   fi

   if [ ${#arr[@]} != $noofcol ]
   then
      noofdeformedrows=`expr $noofdeformedrows + 1`
      echo `expr $index + 1`
   fi

   ((index++))
done

echo $noofcol
echo $noofdeformedrows
echo $noofrows