#!/bin/bash 

metafiles="./tests/*.meta"
for meta in $metafiles
do
    ./parser/bin/parser $meta "tests/#"
done

echo -e "Finished.\n"
