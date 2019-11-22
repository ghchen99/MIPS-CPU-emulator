#!/bin/bash

output="test/output.csv"
outputmessage="TestId, Instruction, Status, Author, Message\n"
TestId="testId"
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
       
       Instruction=${metadata[0]}
       TestId=$Instruction
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
       echo $outputmessage
    fi
done

printf "$outputmessage" > test/output.csv
