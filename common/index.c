/**
 * index.c - implementation of index.h (please see for more information)
 * 
 * Sam Rothschild CS50 F21
 **/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"index.h"
#include"pagedir.h"
#include"counters.h"
#include"hashtable.h"
#include"set.h"
#include"webpage.h"
#include"memory.h"
#include"file.h"
#include"word.h"

/*** GLOBAL TYPES ***/
typedef struct index {
    hashtable_t* ht;
} index_t;

/*** LOCAL FUNCTIONS ***/
static void indexword(char* word, hashtable_t* ht, int id);
static void printfunc(void* arg, const char* key, void* item);
static void countersprintfunc(void* arg, const int key, int count);
static void delete(void* item);

index_t* index_build(char* pageDir, int num_slots) {
    FILE* fp;  // Initialise file
    int id = 1;  // Initialise id
    hashtable_t* ht = hashtable_new(num_slots);  // Create a new hashtable
    char* fname = createFname(id, pageDir);  // Create filename
    while ((fp = pageloadtest(fname)) != NULL) {  // while file can be loaded
        char* url = freadlinep(fp);  // Read in URL
        char* depth = freadlinep(fp);  // Read in depth
        char* html = freadfilep(fp);  // Read in HTML
        int depthAsInt = atoi(depth);  // Convert to integer
        char* norm;  // Initialise word to store normalised word in
        int pos = 0;  // Initialise pos to 0
        char* notNorm;  // Initialise not normalised and normalised versions
        webpage_t* page = webpage_new(url, depthAsInt, html);  // Create new webpage
        while ((notNorm = webpage_getNextWord(page, &pos)) != NULL) {  // While you can get more words
        if (strlen(notNorm) >= 3) {  // If the length is ok
            norm = normalize(notNorm);  // Normalise
            indexword(norm, ht, id);  // Add word to index
            count_free(norm); // Clean up
        }
        free(notNorm);
        }
        count_free(depth);
        webpage_delete(page);
        count_free(fname);  // Clean up
        fclose(fp);
        id++;  // Increment id
        fname = createFname(id, pageDir);  // Create new filename with new id
    }
    count_free(fname); 
    
    index_t* index = count_malloc(sizeof(index_t));  // Allocate memory for index
    if (index == NULL) {
        return NULL;
    } else {
        index->ht = ht;  // Overlay new hashtable
    }
    return index;  // Return the index built
}

index_t* index_load(char* fname) {
  	FILE* fp;  // Initialise new file
    if ((fp = pageloadtest(fname)) != NULL) {  // If  page loader is null ie if it can't be loaded
        int num_slots = lines_in_file(fp);          // Initialise one slot for each line in the file
        char *result;                               // Initialise word        
        hashtable_t *ht = hashtable_new(num_slots); // Make a new hashtable
        while ((result = freadwordp(fp)) != NULL)
        {                                         // While there are still words to read
            counters_t *counter = counters_new(); // Initialise a new counter for each word
            int count;                            // Initialise docID and a count
            int ID;
            while (fscanf(fp, "%d", &count) == 1 && fscanf(fp, "%d", &ID)==1) {  // While both can be scanned                               
                counters_add(counter, ID); // Add to the counter and set new value
                counters_set(counter, ID, count);
            }
            hashtable_insert(ht, result, counter); // Delete hashtable and free word
            free(result);
        }
        fclose(fp);                                     // Close the file
        index_t *index = count_malloc(sizeof(index_t)); // Allocate memory for the index
        if (index != NULL) {  // If the index isn't null overlay the hashtable
            index->ht = ht;
        }
        else {
            return NULL; // Else return null
        }
        return index; // Return index
    }
    else {
        return NULL;
    }
}

void index_save(char* fname, index_t* index) {
    FILE *fp;  // Initialise new file
    fp = fopen(fname, "w");  // Open new file for overwriting (overwrite if existing)
    if (fp == NULL) {
        exit(5);  // Exit if file is null
    }
    hashtable_iterate(index->ht, fp, printfunc);  // Iterate over hashtable while printing
    fclose(fp);  // Close the file
}

static void indexword(char* word, hashtable_t* ht, int id) {
    counters_t* count = counters_new();  // Create new counter
    if (hashtable_insert(ht, word, count) == false) {  // If it doesn't insert
        free(count);  // Free count
        count = hashtable_find(ht, word);  // Hashtable find
    }
    counters_add(count, id);  // Counter add if not existing
}

static void printfunc(void* arg, const char* key, void* item) {
    fprintf(arg, "%s", key);  // Print the keys
    counters_iterate(item, arg, countersprintfunc);  // Iterate over the counters using countersprint func
    fprintf(arg, "\n");  // Print new line for
}

static void countersprintfunc(void* arg, const int key, int count) {
    fprintf(arg, " %d %d", key, count);  // Print the key and its count
}

static void delete(void* item) {
    counters_delete(item);  // Delete counters
}

void index_delete(index_t* index) {
    hashtable_delete(index->ht, delete);  // Hashtable delete
    count_free(index);  // Free the index
}

// Helper function used in querier
/* Returns the item associated with word
 */
void* index_get(index_t* index, char* word) {
  return hashtable_find(index->ht, word);
}

// UNCOMMENT LINE BELOW TO USE UNIT TEST:
// Use 'make clean' to clean up when finished
// Ensure you have made commmon before the test, and comment the #define INDEX_UNIT_TEST line back out before trying to make again
//#define INDEX_UNIT_TEST
// Once line above is uncommented use these commands to compile:
// mygcc -I ../libcs50 index.c pagedir.c word.c ../libcs50/libcs50-given.a -o index_unittest
// ./index_unittest

#ifdef INDEX_UNIT_TEST
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"index.h"
#include"pagedir.h"
#include"counters.h"
#include"hashtable.h"
#include"set.h"
#include"webpage.h"
#include"memory.h"
#include"file.h"
#include"word.h"
int main(int argc, const char* argv[]) {
    FILE* fp = fopen("test", "w");
	printf("Testing index build\n");
	index_t* index = index_build("/thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/letters-depth-0", 5);
	printf("Index built successfully, now to test index save:\n");
	index_save("test", index);
	printf("Index saved successfully, now to test index load:\n");
	index_load("output/indexloadunittest");
	printf("Index loaded successfully, not to test deletion\n");
	index_delete(index);
	printf("Index succesfully deleted. Use 'make valgrind to test'\n");
    fclose(fp);
	return 0;
}
#endif
