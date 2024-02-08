#!/bin/bash
# Testing script for querier.c
# Author: Sam Rothschild -- based heavily on crawler test script provided for last lab
# Date: Oct 2021
#
# usage: bash -v testing.sh or 'make test &> testing.out' to redirect into testing.out file

# Variables:
pageDir=/thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/toscrape-depth-2
indexFile=/thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/wikipedia-index-1.s

# Defensive tests:
echo "Test 1: invalid crawler dir:"
./querier ../libcs50 $indexFile

echo "Test 2: illegible crawler dir:"
./querier ../indexer/illegible $indexFile

echo "Test 3: valid parameters with invalid and/or syntax (defined in lab spec):"
./querier $pageDir $indexFile < invalid.txt

echo "Erroneous test cases passed: now to test valid queries"

echo "Test 4: valid parameters with valid queries:"
./querier $pageDir $indexFile < valid.txt
