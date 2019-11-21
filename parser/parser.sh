#!/bin/bash

FILES="textfiles/*"

for F in $FILES
do
    bin/parser $F "binaries/#"
done

echo -e "Finished.\n"
