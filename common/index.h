/**
 * Header file for index module of TSE
 * 
 * Provides function prototypes to make, save, and delete index files/data structure.
 * 
 * Sam Rothschild CS50 F21
 **/

#include<stdio.h>
#include<stdbool.h>
#include"../libcs50/hashtable.h"

/*** GLOBAL TYPE ***/
typedef struct index index_t;

/*** FUNCTIONS ***/
index_t* index_build(char* pageDir, int num_slots);  // Build index data structure

void index_save(char* fname, index_t* index);  // Save index data structure by writing it to a file

void index_delete(index_t* index);  // Delete index data structure

index_t* index_load(char* fname);  // Populate index data structure with contents of index file

void* index_get(index_t* index, char* word);  // Helper function for querier -- returns item associated with a word 
