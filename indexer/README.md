## CS50 TSE Indexer
# Sam Rothschild, CS50 TSE Indexer

# Purpose:
Indexer is a program which tracks words, which documents those words appear in, and how frequently they appear. This frequency count will be useful for querier later.

# Assumptions:
No meaningful assumptions beyond are made beyond those outlined in the spec.

# Compile:
In order to compile this usage simply use the keyword: 'make', in order to test use 'make test', and in order to run a memory check use 'make valgrind'.

# Usage: 
The indexer is implemented using the following:
```c
int main(const int argc, char* argv[]) 
static void indexer(char* pageDir, char* fname);
```

Arguments: pageDirectory indexFilename  

Example usage: ./indexer pageDir indexFname
