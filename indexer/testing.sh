#!/bin/bash
# Testing script for indexer.c
# Author: Sam Rothschild -- based heavily on crawler test script provided for last lab
# Date: Oct 2021
#
# usage: bash -v testing.sh or 'make test &> testing.out' to redirect into testing.out file

# If directories are left over from previous test runs then delete them:
if [ -d illegible ]
then
    rmdir illegible
fi

if [ -d output ]
then
    rmdir output
fi

# Now remake target directories, and specify preferences
mkdir illegible
chmod o-r illegible

mkdir output

## Test invalid indexer arguments

# Illegible directory
echo "Illegible crawler directory -- using premade illegible directory called 'illegible'"
./indexer illegible indexfile

# Non-crawler directory
echo "Non-crawler directory"
./indexer ../libcs50 indexfile

## Test successful indexer 

# Test at depth 0
echo "Test at depth 0"
./indexer /thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/letters-depth-0 output/indexfile0
echo "Output:"
cat output/indexfile0

# Use index test 
echo "Now indextest"
./indextest output/indexfile0 output/testresult0
echo "Output:"
cat output/testresult0

# Now compare the two
echo""
echo "Now to sort and compare:"
gawk -f indexsort.awk output/indexfile0 > output/indexfile0.sorted
gawk -f indexsort.awk output/testresult0 > output/testresult0.sorted

# See if there is any difference:
diff -q output/indexfile0.sorted output/testresult0.sorted

if [ $? -ne 0 ]
    then
    echo "Difference in the files"
else
    echo "Success -- no difference in the files"
fi

# Test at depth 3
echo "Test at depth 3"
./indexer /thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/letters-depth-3 output/indexfile3
echo "Output:"
cat output/indexfile3

# Use indextest
echo "Now indextest"
./indextest output/indexfile3 output/testresult3
echo "Output:"
cat output/testresult3

# Now compare them
echo "Now to sort and compare:"
gawk -f indexsort.awk output/indexfile3 > output/indexfile3.sorted
gawk -f indexsort.awk output/testresult3 > output/testresult3.sorted

if [ $? -ne 0 ]
    then
    echo "Difference in the files"
else
    echo "Success -- no difference in the files"
fi

exit 0
