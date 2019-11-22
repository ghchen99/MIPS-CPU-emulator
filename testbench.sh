#!/bin/bash

output="test/output.csv"
outputmessage="TestId, Instruction, Status, Author, Message\n"
binfiles="./test/binaries/*.bin"


for file in $binfiles
do
    filename=$(basename -- "$file")
    metafile="./test/testcases/${filename%.*}.meta"
    if [ -f "$metafile" ]; then
       metadata=()
       count=0
       while read -r line || [[ -n "$line" ]] && ((count < 10)); do
           metadata+=("${line//#}")
           count+=1
       done < "$metafile"
       
       TestId=$filename
       Instruction=${metadata[0]}
       Expectedreturn=${metadata[1]}
       Author=${metadata[2]}
    
       bin/mips_simulator $file
       
       RETCODE=$?
       #echo $RETCODE
       if [[ "$RETCODE" == "$Expectedreturn" ]] ; then
          Status="pass"
       else
          Status="fail"
       fi
       Message="expected $Expectedreturn and obtained $RETCODE"
       outputmessage+="$TestId, $Instruction, $Status, $Author, $Message\n"
    fi
done

printf "$outputmessage" > test/output.csv
