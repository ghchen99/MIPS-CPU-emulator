#!/bin/bash

output="test/output.csv"

run()
{
    if [ -f "tests/testcases" ]
        #metadata=()
        #while read
        
        #testinstruction=metadata[0]
        #expectedreturn=metadata[1]
        #author=metadata[2]
        
        bin/simulator $1
        
        RETCODE=$?
        if [[ "$RETCODE" == expectedreturn" ]] ;
                echo "You pass" ;
        else
                echo "You fail" ;

}

binfiles="./tests/*.bin"
for file in binfiles
do
    run file
done

#bin/simulator tests/addu.bin
