## CS50 TSE Indexer TESTING.md
# Sam Rothschild, CS50 TSE Indexer

# How to test + presentation of testing:
Attached in the indexer directory is a ./testing.sh file. Use 'make test' in order to run this. Use make valgrind to check for memory leaks, and make clean to tidy up afterwards. Use either test A or test B depending on what you would like to test.

# testing.sh
Initially this testing script uses invalid arguments in order to check that the defensive coding is working properly. After this, it runs indexer and indextest creating output files for several different depths. It also cleans up from previous uses of the testing command. The results can be found in the generated directories but are also concatenated in the testing.out file for grader's ease.

# unit testing:
There is also unittesting in the appropriate modules: can be found in the appropriate files.

# valgrind testing:
use 'make valgrind' to check for memory leakage etc.
