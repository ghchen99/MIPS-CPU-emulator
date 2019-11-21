#!/bin/bash 

metafiles="./testcases/*.meta"
for meta in $metafiles
do
    ./parser/bin/parser $meta "binaries/#"
done

echo -e "Finished.\n"
