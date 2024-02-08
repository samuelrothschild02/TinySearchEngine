## CS50 TSE Querier
# Sam Rothschild, CS50 TSE Querier

# Purpose:
Querier is a programme which ranks results for our search engine based on a scoring system that takes into account how many times certain words are featured in documents.

# Assumptions:
No meaningful assumptions beyond are made beyond those outlined in the spec.

# Compile:
In order to compile this usage simply use the keyword: 'make', in order to test use 'make test', and in order to run a memory check use 'make valgrind'.

# Usage: 
The querier is implemented using the following and a local type (see more info in IMPLEMENTATION.md):
```c
void parseArgs(char* directory, char* fname);
void strip(char* line);
void turnIntoWords(query_t* query);
bool testChars(char* line);
bool handleKeywords(query_t* query);
void fetchPages(query_t* query, char* directory, index_t* index);
void printOut(query_t* query);
bool isKeyword(char* word);
void getDocs(index_t* index, char* a, counters_t* b);
void intersect(counters_t* small, counters_t* big);
void intersect_helper(void* arg, const int key, int item);
void printPages(counters_t* counters, char* directory);
void outputLine(void* arg, const int key, int item);
void deleteQuery(query_t* query);
int lesser(int a, int b);
```

*NOTE*: A series of helper functions are used for abstraction and ease of debugging. Please look in the implementation and querier.c files for more details on these.

Arguments: pageDirectory indexFilename  

Example usage: ./querier pageDir indexFname

# Testing note:
Please see TESTING.md for details on testing script. 'make test' to use.

# Attempted implementation of scheme:
Whole thing attempted, all the points outlined in the spec.
