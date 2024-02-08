## CS50 TSE Querier
# Sam Rothschild, CS50 TSE

# Implementation
The querier parses arguments from the commandline and then loads the file into the index data structure made from last lab. After this it tokenizes the input, splitting it into individual words in an array. It then searches the documents trying to match the words and ranks them based on their score (see the lab spec for details on scoring). After this, it prints out the results. If a blank line is inputted it doesn't stop, but if a non-space or non-character char is put in then it does.

# Types:
A local type was made for the querier module: this struct contains a 'line' for what the user enters, an array of words which we get from that line with which we query, an integer for the number of words we get and a number of and sequences.

### querier.c
This program found in the querier directory contains all the logic for the implementation described above:
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

```c
static bool parseArgs(char* pageDir, char* indexFname);
```
Parse args checks the arguments passed in at the command line. It checks that the first argument is a crawler directory and that the second line is readable, as well as that the correct number of args have been passed in.

```c
void strip(char* line);
```
Helper function that strips all the white space from an input line. Useful for taking input into array.

```c
void turnIntoWords(query_t* query);
```
Function iterating over words in order to create a list of words that we can use in other functions.

```c
bool testChars(char* line);
```
Helper function to check if a line of input contians any invalid characters, and so if we should report any sort of error.

```c
bool handleKeywords(query_t* query);
```
Check through the query in order to check that the order of the special keywords is valid. As specified keywords cannot be first or last word in query or adjacent to one another.

```c
void fetchPages(query_t* query, char* directory, index_t* index);
```
Function which prints all results associated with a given query. Essentially it iterates over all the pertinent pages, calculating and printing the relevant information.

```c
void printOut(query_t* query);
```
Print clean version of the query after we have manipulated for the user before printing the results.

```c
bool isKeyword(char* word);
```
Simple function to check if a given word is one of the special keywords 'and' or 'or'.

```c
void getDocs(index_t* index, char* a, counters_t* b);
```
Function which gets all the documents associated with a given word and intersects them for the 'and' keyword

```c
void intersect(counters_t* small, counters_t* big);
void intersect_helper(void* arg, const int key, int item);
```
Functions using counters iterate which takes in two counters and reduces them to one 'overall' counter which contains the INTERSECTION of the two counters passed in.

```c
void printPages(counters_t* counters, char* directory);
void outputLine(void* arg, const int key, int item);
```
Iterate over the relevant counters printing out the results, ie the bit the user sees after they have queried. List is the helper function here which gets the URL of the relevant result and prints the output information.

```c
void deleteQuery(query_t* query);
```
Frees words in a query and query itself, useful for cleaning up memory usage neatly.

```c
int lesser(int a, int b);
```
Simple function, returns the less of two integers. Useful for intersection.
