#!/bin/bash

output="test/output.csv"

run()
{
    if [ -f "test/testcase" ];
        metadata=()
        while read line ; do
            metadata
        
        Instruction=metadata[0]
        Expectedreturn=metadata[1]
        Author=metadata[2]
        
        bin/simulator $1
        
        RETCODE=$?
        if [[ "$RETCODE" == Expectedreturn" ]] ;
                Status="pass"
        else
                Status="fail"
        fi
        outputmessage="$TestId, $Instruction, $Status, $Author"
     else
     fi

}

binfiles="./tests/*.bin"
for file in binfiles
do
    run file
done
