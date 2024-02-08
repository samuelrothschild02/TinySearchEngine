## CS50 TSE Indexer
# Sam Rothschild, CS50 TSE

# Implementation
As mentioned in DESIGN.md the indexer works by creating a hashtable which maps words to countersets which consist of key item pairs of document ID's mapped to the frequency which words appear in given documents. In indexer.c we get an abstracted look into the process: we build an index, save it to a file and then clean up after ourselves by deleting it.

### index.c
This program found in the common directory does most of the heavy lifting for this part of the lab: it contains all the logic required to build, save, and delete an index with the following functions:
```c
index_t* index_build(char* pageDir, int num_slots);  
void index_save(char* fname, index_t* index);  
void index_delete(index_t* index); 
index_t* index_load(char* fname);
```
More info can be found on these functions in index.h, but essentially `index_build` works by creating the hashtable with countersets and getting and normalising words from crawler files and putting them in the hashtable. The function returns an index struct which is a wrapper for the existing hashtable struct.

`index_save` works by using the existing hashtable_iterate function with our own `printfunc` to print the contents of the hashtable to a file.

`index_delete` passes our own delete function to the existing `hashtable_delete` function. Our own delete function deletes all the counters in the hashtable to avoid memory leaks.

`index_load` synthesises all the words from a file and puts them into our hashtable. It reads over all the lines in a file and creates or sets an existing hashtable if necessary. It then overlays the existing hashtable with the new one with the data synthesised from that file.

### indexer.c
This program is more straightforward, it just contains two functions:
```c
int main(const int argc, char* argv[]);
static void indexer(char* pageDir, char* fname);
```
Main is responsible for parsing the arguments and calling indexer if the arguments provided are valid. Indexer just uses the functions described above to build, save, and delete an index.

### pagedir.c
We leverage two functions from this module for the indexer:
```c
static char* createFname(int id, char* pageDir);
FILE* pageloadtest(char* fname);
```
`createFname` converts the integer id passed to it to a string, allocates appropriate memory and appends the string form of the integer to the filename so it can be used correctly.

`pageloadtest` simply checks that a file can be written to and is not null. If the file isn't null then it returns it.

### word.c
This module simply exists so we can normalise a word (ie putting it all in lowercase) before indexing it:
```c
char* normalize(char* word);
```
`normalize` iterates over a string, using the imported `tolower` function in each individual character. After it has done this, it returns the normalised string.


