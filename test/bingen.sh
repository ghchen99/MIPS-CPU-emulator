#!/bin/bash 

srcPath="tests"
parserPath="./parser/bin/parser"
metaFiles="./$srcPath/*.meta"
for meta in $metaFiles
do
    $parserPath "$meta" "$srcPath/#"
done

echo -e "Finished.\n"






#!/bin/bash

FILES="text_files/*"

for F in $FILES
do
    bin/parser $F "binaries/#"
done

echo -e "Finished.\n"
