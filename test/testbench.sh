bin/simulator testcase/addu.bin
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
