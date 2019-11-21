#!/bin/bash

output="test/output.csv"

run()
{
    if [ -f "tests/testcases" ]
        metadata=()
        while read
        
        testinstruction=metadata[0]
        expectedreturn=metadata[1]
        author=metadata[2]
        
        bin/simulator tests/.bin
        
        RETCODE=$?
        if [[ "$RETCODE" == expectedreturn" ]] ;
                echo "You pass" ;
        else
                echo "You fail" ;
        
bin/simulator tests/addu.bin
RETCODE=$?

if [[ "$RETCODE" == "9" ]] ;
        echo "Success" ;
else
        echo "Failure" ; 
        
bin/simulator testcase/subu.bin
RETCODE=$?

if [[ "$RETCODE" == "6" ]] ;
        echo "Success" ;
else
        echo "Failure" ;
        
        how do i comment all of this
