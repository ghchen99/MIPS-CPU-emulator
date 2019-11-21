output="test/output.csv"


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
