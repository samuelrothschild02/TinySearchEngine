## CS50 TSE Indexer TESTING.md
# Sam Rothschild, CS50 TSE Indexer

# How to test + presentation of testing:
Attached in the querier directory is a testing.sh file. Use 'make test' in order to run this. Use make valgrind to check for memory leaks, and make clean to tidy up afterwards. In addition there is glass box unit testing which can be used following the instructions provided in the file.

# testing.sh
Initially this testing script uses invalid arguments in order to check that the defensive coding is working properly. After this, it runs the querier correctly. It also cleans up from previous uses of the testing command. The outputs are printed to stdout normally, but are redirected to a file 'testing.out' for the grader's ease. Please note, I have put the test cases which are faulty in "" quote marks to avoid a segfault when the grader runs.

# unit testing:
There is also glass box unittesting in querier.c: please see instructions on how best to use commented at the bottom of that file.

# valgrind testing:
use 'make valgrind' to check for memory leakage etc.
