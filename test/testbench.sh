#!/bin/bash

output="test/output.csv"

run()
{
    if [ -f "tests/testcases" ];
        metadata=()
        while read line ; do
            metadata
        
        testinstruction=metadata[0]
        expectedreturn=metadata[1]
        author=metadata[2]
        
        bin/simulator $1
        
        RETCODE=$?
        if [[ "$RETCODE" == expectedreturn" ]] ;
                result="pass"
        else
                result="fail"
        fi
        outputmessage="$testid, $testinstruction, 
     else
     fi

}

binfiles="./tests/*.bin"
for file in binfiles
do
    run file
done

bin/simulator tests/addu.bin
metadata()
