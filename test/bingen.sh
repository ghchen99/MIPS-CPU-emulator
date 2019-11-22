#!/bin/bash 

metafiles="./test/testcases/*.meta"
for meta in $metafiles
do
    ./test/parser/bin/parser $meta "test/binaries/#"
done

echo -e "Binaries created.\n"
