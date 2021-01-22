#!/bin/bash
input="00530_Veto6_A.txt"
tfile="tmpfilerewrite.txt"
output="530_Veto6_A_prep.txt"

if [ -f "$tfile" ] ; then
    rm "$tfile"
fi

tail -n +4 $input >> $tfile

if [ -f "$output" ] ; then
    rm "$output"
fi

#for i in {1..15}
while IFS= read -r line
do
   #read -r line
   echo "$line" | tr '*' ' ' >> $output
done < "$tfile"

rm "$tfile"
