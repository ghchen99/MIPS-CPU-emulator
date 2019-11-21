#!/bin/bash

output="test/output.csv"

run()
{
    metafile="${$1%.*}.meta"
    if [ -f "metafile" ]; then
        metadata=()
        while read -r line  || [[ -n "$line" ]]; do
            metaData+=("${line//#}")
        done < "$metafile"
        
        Instruction=metadata[0]
        Expectedreturn=metadata[1]
        Author=metadata[2]
        
        bin/mips_simulator $1
        
        RETCODE=$?
        if [[ "$RETCODE" == Expectedreturn" ]] ;
                Status="pass"
        else
                Status="fail"
        fi
        outputmessage="$TestId, $Instruction, $Status, $Author"
     fi

}

binfiles="./test/binaries/*.bin"
for file in binfiles
do
    run $file
done
