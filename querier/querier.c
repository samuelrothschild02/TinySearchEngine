/**
 * querier.c - implementation of querier module
 * 
 * Please see design, implementation and readme.md for more info.
 * 
 * Usage: ./querier pagedir indexfile
 * 
 * Sam Rothschild CS50 F21
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../common/index.h"
#include "../common/pagedir.h"
#include "../libcs50/counters.h"
#include"../common/word.h"
#include"../libcs50/file.h"

typedef struct query {
  char* line;   // what the user enter
  char** words; // the line as an array of words
  int numWords; // the number of words in the array
  int numSeqs; // number of andsequences
} query_t;

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

int main(int argc, char const *argv[])
{
  char* progName = (char*)argv[0];  // Store name of program entered
  if(argc != 3)  // If incorrect number of arguments entered, print error message and exit
  {
    printf("Usage error -- correct usage: ./%s pageDirectory indexfilename\n", progName);
    exit(1);
  }
  char* directory = malloc(strlen(argv[1]) + 1);  // Now we have validated enough args entered, allocate memory and store them
  strcpy(directory, argv[1]);
  char* fname = malloc(strlen(argv[2]) + 1);
  strcpy(fname, argv[2]);
  parseArgs(directory, fname);  // Call abstracted function to ensure the arguments entered are valid
  index_t* index = index_build(fname, 200);  // build index to hold data on frequency of words
  index = index_load(fname);  // Load in the index from file given
  char* line;  // Initialise line of a query
  query_t* query;  // Initialise query
  while(true) {
    printf("Query: ");  // Print query as per lab instructions
    line = freadlinep(stdin);  // Read from stdin
    if(line == NULL) break;  // If line is null then break
    strip(line);  // Remove white space and normalise
    normalize(line);
    if(testChars(line))  // Check that input isn't empty or that there aren't invalid characers entered
    {
      query = malloc(sizeof(query_t));  // Allocate memory for query
      query->line = line;  // Set the query line to what the user put in
      turnIntoWords(query);  // break the query into an array of words and get the number of words

      if(handleKeywords(query))  // Check that there are no invalid keyword inputs as per spec
      {
        printf("Query: ");  // Print query
        printOut(query);  // Print the new 'clean' version of the query that adheres to our guidelines
        fetchPages(query, directory, index);  // Grab the pages associated with the word(s) used
      }
      deleteQuery(query);  // Clean up
    }
    free(line);  // Free line
  }

  printf("\n");
  free(fname);  // Clean up
  free(directory);
  // deleteQuery(query);
  index_delete(index);

  return 0;  // On success, return 0
}


// Function which gets all the documents associated with a given word and intersects them for the 'and' keyword
void getDocs(index_t* index, char* word, counters_t* allPages)
{
  counters_t* relevantDocs = index_get(index, word);  // Get counters associated with a given word
  intersect(relevantDocs, allPages);  // Intersect the documents with the word with all the pages to get pertinent results
}

// Set counter to only have the documents which the smaller of the two counters has
void intersect(counters_t* small, counters_t* big)
{
  counters_iterate(small, big, intersect_helper);  // Iterate with helper
}

// Helper function used in the iterator above to help find the intersection between to counters
void intersect_helper(void* arg, const int key, int item)
{
  counters_t* big = arg;  // Bigger of two counters is arg
  int i = counters_get(big, key);   // 0 if doc not found in big

  if(i != 0)   // if the document satisfies both
  {
    counters_set(big, key, lesser(item, i));  // Set with the less of the item or count
  }
  else    // doc satisfies only one
  {
    counters_set(big, key, 0);  // Set to 0
  }
}

// Print resulting pages which satisfy query
void fetchPages(query_t* query, char* directory, index_t* index)
{
  counters_t* allPages = index_get(index, query->words[0]);  // Get all relevant pages 
  for(int i = 1; i < query->numWords; i++)  // Iterate over them
  {
    getDocs(index, query->words[i], allPages);
  }
  printPages(allPages, directory);  // Print results
}

// Print resulting 'websites'
void printPages(counters_t* result, char* directory)
{
  counters_iterate(result, directory, outputLine);  // Iterate over them printing website and score using helper function
}

// Function which prints a 'website' and its associated score
void outputLine(void *arg, const int key, int count)
{
  if(count == 0)  // If given count arg is 0 just return
  {
    return;
  }
  char* directory = arg;  // Store directory
  char* file = malloc(strlen(directory) + sizeof(int) + 2);  // Allocate memory for file
  sprintf(file, "%s/%d", directory, key);  // Convert
  FILE* fp = fopen(file, "r");  // Open file
  char* URL = freadlinep(fp);  // Read out URL
  printf("Score: %d Document: %d URL: %s\n", count, key, URL);  // Print number of documents, document id and URL associated
  free(URL);  // Clean up
  free(file);
  fclose(fp);
}

// Function to check if a word is one of the keywords given in the spec
bool isKeyword(char* word)
{
  if(strcmp(word, "and") == 0)  // If the word is and or or return true, otherwise return false
  {
    return true;
  }
  if(strcmp(word, "or") == 0)
  {
    return true;
  }
  return false;
}

// Print the clean version of the query after we have manipulated it 
void printOut(query_t* query)
{
  query->numSeqs = 0;  // Set number of sequences to 0
  for(int i = 0; i < query->numWords; i++)  // Iterate over words in query
  {
    printf("%s ", query->words[i]);   // print current word
    if(i != query->numWords - 1)  // if we aren't on the last word
    {
      if(strcmp(query->words[i], "or") == 0)  // if we find an or 
      {
        query->numSeqs++;  // Increment number of sequences
      }
    }
  }
  printf("\n");
}

// Remove white space from a line
void strip(char* line)
{
  if(line == NULL)  // If a line is null then return
  {
    return;
  }
  int i;  // Initialise count
  int x=0;  // Initialise comparison 
  for(i = 0; line[i]; i++)  // Iterate over line
  {
    if(!isspace(line[i]) || (i > 0 && !isspace(line[i - 1])))  // If character is not a space and if previous character wasn't a space
    {
      line[x] = line[i];  // Set end of word
      x++;  // Increment x
    }
  }
  line[x] = '\0';   // End a word with the null terminator
}

// Ensure that the input is valid
bool testChars(char* line)
{
  if(line == NULL || strcmp(line, "") == 0)  // If line is null or empty, return false
  {
    return false;
  }

  for(char* p = line; *p != '\0'; p++)   // iterate over string
  {
    if(!isalpha(*p) && !isspace(*p)) // if the current character is non-alphabetical or non-space
    {
      printf("Usage error -- invalid character: '%c' in query.\n", *p);  // Print error message and return false
      return false;
    }
  }
  return true;  // Otherwise all is fine and return true
}

// Turn a query into an array of words and get the number of words in the array
void turnIntoWords(query_t* query)
{
  if(query->line != NULL)  // If null then return
  {
    query->numWords = 0;  // Set number of words to 0
    char* line = query->line;  // store line
    bool midWord = false;  // Initialise in a word to false
    char* word;  // Initialise word string
    char* end;  // Initialise end of word
    int len = strlen(line) + 1;  // Get size of line
    query->words = malloc(0);  // mallocate
    for(int i = 0; i < len; i++)  // Iterate over line
    {
      if(!isspace(line[i]) && !midWord)  // if first character of a word
      {
        midWord = true;  // Set in a word to true
        word = &line[i];  // Store in word
      }
      else if(!isalpha(line[i]) && midWord)  // If not a letter and in a word, ie end of a word
      {
        end = &line[i];  // Store end
        *end = '\0';  // set end to null teroutputLineator
        midWord = false;  // Set in a word back to false for the next word
        // Add to the array
        query->words = realloc(query->words, sizeof(char*) * (query->numWords + 1));  // allocate room for new pointer
        query->words[query->numWords] = malloc(strlen(word)*sizeof(char)+1); // allocate memory for length of word
        query->words[query->numWords++] = word;   // store this word
      }
    }
  } 
}

// Ensure that a query is valid in terms of how the special keywords are ordered
bool handleKeywords(query_t* query)
{
  int numWords = query->numWords;
  int end = numWords-1;  // Get end, so we can test to see if a keyword is at end of input
  for (int i=0; i<numWords; i++) {  // Iterate through all words
      if (strcmp(query->words[i], "and")==0 || strcmp(query->words[i], "or")==0) {
          if (i == 0) {  // Check that one of the key words isn't first or last
              fprintf(stderr, "Error! %s cannot be first\n", query->words[0]);
              return false;
          }
          if (strcmp(query->words[i-1], "and")==0 || strcmp(query->words[i-1], "or")==0) {  // Check that thhere aren't adjacent keywords 
              fprintf(stderr, "Error! %s %s cannot be adjcent\n", query->words[i-1], query->words[i]);
              return false;
          }
          if (i == end) {  // Check that a keyword isn't the final word in a query
              fprintf(stderr, "Error! %s cannot be last\n", query->words[end]);
              return false;
          }
      }
  }
  return true;
}

// Parse args function to ensure that user input is valid for our program
void parseArgs(char* directory, char* fname)
{
    if (isValidDir(directory)) {  // Test validity of directory passed in
		fprintf(stderr, "Incorrect usage - invalid directory. Correct usage: ./indexer pageDir indexFilename\n");
		exit(2);
	}
	FILE* fp;  // Initialise file
	fp = fopen(fname, "r");  // Open file for reading
	if (fp == NULL) {  // If the file is null, exit
		fprintf(stderr, "Incorrect usage - file given is not writeable. Correct usage: ./indexer pageDir indexFilename\n");
		exit(3);
	}
	fclose(fp);  // Close the file and return true if args are valid
}

// Function to help clean up and delete a query
void deleteQuery(query_t* query)
{
  free(query->words);  // Free all the words
  free(query);  // Free query itself
}

// Helper function to return the smaller of two integers
int lesser(int a, int b) 
{
  if(a < b) // If a is less than b then return it, else, the opposite
  {
    return a;
  }
  return b;
}

// Use 'make clean' to clean up when finished
// Ensure you have made common before the test, and comment the #define QUERIER_UNIT_TEST line back out before trying to make again
// UNCOMMENT LINE BELOW TO USE UNIT TEST:
//#define QUERIER_UNIT_TEST
// Once line above is uncommented use these commands to compile:
// mygcc -I ../libcs50 ../common/index.c ../common/pagedir.c ../common/word.c ../libcs50/libcs50-given.a -o querier_unittest
// ./querier_unittest
// Here we test the smaller functions that make up the bigger ones to ensure that they are working, that aren't obviously covered by the black box testing

#ifdef QUERIER_UNIT_TEST
#include<stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../common/index.h"
#include "../common/pagedir.h"
#include "../libcs50/counters.h"
#include"../common/word.h"
#include"../libcs50/file.h"
int main(int argc, const char* argv[]) {
  printf("Begin unit testing:\n");
  printf("Test `strip(char*)`\n");
  char* test = "test test ";
  strip(test);
  printf("%s", test);
  printf("Test `testChars(char*)`\n");
  char* testF = "test!";
  char* testS = "test";
  bool acidTest;
  acidTest = testChars(testF);
  printf("%B", acidTest);
  acidTest = testChars(testS);
  printf("%B", acidTest);
  printf("Test `isKeyword`\n");
  char* testY = "and";
  char* testN = "notAnd";
  acidTest = isKeyword(testN);
  printf("%B", acidTest);
  acidTest = isKeyword(testY);
  printf("%B", acidTest);
  printf("Finally, test `lesser(int a, int b)`\n");
  int lower = 1;
  int higher = 2;
  int result = lesser(lower, higher);
  printf("%s", result);
  printf("This concludes unit testing of smaller functions. Please look at blackbox testing script for testing of overall functionality");
}
#endif
