# Testing script for crawler.c
# Author: Temi Prioleau -- Updated from template by Sam Rothschild
# Date: Oct 2021
#
# usage: bash -v testing.sh or 'make test &> testing.out' to redirect into testing.out file

# Define variables
seedURL=http://cs50tse.cs.dartmouth.edu/tse/letters/
externalURL=www.google.com
nonExistentServer=samcs50tsetest.com
vsne=google.com/picture
diffSeedPage1=http://cs50tse.cs.dartmouth.edu/tse/letters/B.html
diffSeedPage2=http://cs50tse.cs.dartmouth.edu/tse/letters/D.html
wikiURL=http://cs50tse.cs.dartmouth.edu/tse/wikipedia/

#####################################
### These tests should fail ###

# 1 argument
echo "Expect incorrect num of args:"
./crawler

# 2 arguments
echo "Expect incorrect num of args:"
./crawler $seedURL

# 3 arguments
echo "Expect incorrect num of args:"
./crawler $seedURL data

# 4 arguments + externalURL
echo "Expect external URL error:"
./crawler $externalURL data 2

# 4 arguments + non-existent server
echo "Expect internal URL error"
./crawler $nonExistentServer data 0

# 4 arguments + valid server + non-existent page
echo "Expect internal URL error"
./crawler vsne data 0

######################################
### These tests should pass ####

# at depth 0
echo "First test that should pass:"
./crawler $seedURL data 0
echo "passed"

# # at depth 2
# echo "Second test that should pass:"
# ./crawler $seedURL data 2
# echo "passed"

# # at depth 4
# echo "Third test that should pass:"
# ./crawler $seedURL data 4
# echo "passed"

# # different seed page in small linked sites:
# echo "Fourth test that should pass:"
# ./crawler $diffSeedPage1 data 3
# echo "Passed"

# # another different seed page in small linked sites:
# ./crawler $diffSeedPage2 data 3
# echo "Passed"

# # Wiki url test with small depth:
# echo "Fifth test that should pass:"
# ./crawler wikiURL data 2
# echo "Passed"

# # Final test of wiki with higher depth:
# echo "Sixth and final test that should pass:"
# ./crawler wikiURL data 4
# echo "Passed. Testing complete."
