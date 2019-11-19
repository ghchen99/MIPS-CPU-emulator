bin/simulator testcase/addu.bin
RETCODE=$?

if [[ "$RETCODE" == "246" ]] ;
        echo "Success" ;
else
        echo "Failure" ;
        
