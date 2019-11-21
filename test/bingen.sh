#!/bin/bash 

srcPath="tests"
metaFiles="./$srcPath/*.meta"
for meta in $metaFiles
do
    ./parser/bin/parser "$meta" "$srcPath/#"
done

echo -e "Finished.\n"
