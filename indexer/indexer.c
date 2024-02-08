/**
 * indexer.c
 * Program to index webpages gathered by crawler, second part in the tse series of labs. 
 * Usage ./indexer pageDir indexFilename
 * CS50 Fall 2021 - Lab 5
 * Sam Rothschild -- 10/17/2021
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"webpage.h"
#include"memory.h"
#include"pagedir.h"
#include"file.h"
#include"index.h"
#include"hashtable.h"	

#define NUM_SLOTS 200

/** Function prototypes **/
static void indexer(char* pageDir, char* fname);
static bool parseArgs(char* name, char* pageDir, char* indexFname);

int main(const int argc, char* argv[]) {
	// Check that the right number of args are passed in
	if (argc != 3) {
		fprintf(stderr, "Incorrect usage - wrong number of arguments. Correct usage: ./indexer pageDir indexFilename\n");
		exit(1);
	}
	char* name = argv[0];  // Store prog name from command line
    char* pageDir = argv[1];  // Store page name from command line
    char* fname = argv[2];  // Store target filename from command line

	if (parseArgs(name, pageDir, fname) == true) {  // If arguments are legitimate
		indexer(pageDir, fname);  // Call indexer
	}
}

static bool parseArgs(char* name, char* pageDir, char* indexFname) {
	if (isValidDir(pageDir)) {  // Test validity of directory passed in
		fprintf(stderr, "Incorrect usage - invalid directory. Correct usage: ./indexer pageDir indexFilename\n");
		exit(2);
	}
	FILE* fp;  // Initialise file
	fp = fopen(indexFname, "w+");  // Use special w+ token to truncate file if already existing and then write (ie to overwrite as according to spec)
	if (fp == NULL) {  // If the file is null, exit
		fprintf(stderr, "Incorrect usage - file given is not writeable. Correct usage: ./indexer pageDir indexFilename\n");
		exit(3);
	}
	fclose(fp);  // Close the file and return true if args are valid
	return true;
}

static void indexer(char* pageDir, char* fname) {
	index_t* index = index_build(pageDir, NUM_SLOTS);  // Build index
	fprintf(stdout, "Index Built\n");
	index_save(fname, index);  // Save the index to the filename
	fprintf(stdout, "Saved\n");
	index_delete(index);  // Delete for memory
	fprintf(stdout, "Deleted\n");
}
