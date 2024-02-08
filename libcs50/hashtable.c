/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * Sam Rothschlid, CS50 F21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/thayerfs/home/f004pm2/cs50-dev/labs/lab-3-samuelrothschild02/set/set.c"
#include "/thayerfs/home/f004pm2/cs50-dev/labs/lab-3-samuelrothschild02/set/set.h"
#include "/thayerfs/home/f004pm2/cs50-dev/labs/lab-3-samuelrothschild02/lib/mem.h"
#include "/thayerfs/home/f004pm2/cs50-dev/labs/lab-3-samuelrothschild02/hashtable/hashtable.h"
#include "/thayerfs/home/f004pm2/cs50-dev/labs/lab-3-samuelrothschild02/hashtable/hash.h"
#include "/thayerfs/home/f004pm2/cs50-dev/labs/lab-3-samuelrothschild02/hashtable/hash.c"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
/* none */

/**************** global types ****************/
typedef struct hashtable {
  set_t **array;
  int length;  // Initialise length
} hashtable_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see hashtable.h for comments about exported functions */

/**************** hashtable_new() ****************/
hashtable_t* hashtable_new(const int num_slots) {
  if (num_slots > 0) {  // Defensive check that the number of slots is greater than 0
    hashtable_t* new = mem_malloc(sizeof(hashtable_t));  // Allocate memory for new table
    new -> array = mem_calloc(num_slots, sizeof(set_t*));  // Allocate memory for array in table
    new -> length = num_slots;
    for (int i=0; i<num_slots; i++) {
      new -> array[i] = set_new();  // Iterate over each index of the array creating a new set
    }
    return new;  // Return the new table
   }
  return NULL;  // If the number of slots is illegal return null
}

/**************** hashtable_insert() ****************/
bool hashtable_insert(hashtable_t* ht, const char* key, void* item) {
  if (ht == NULL || key == NULL || item == NULL) {  // Defensive check that all the arguments are valid
    return false;
  }
  else {
    if (set_find(ht->array[hash_jenkins(key, ht->length)], key) != NULL) {  // If you can'at successfully insert key should already be in table
      return false;  // So return false
    }
    else if (set_find(ht->array[hash_jenkins(key, ht->length)], key) == NULL) {
      return set_insert(ht->array[hash_jenkins(key, ht->length)], key, item);  // Insert into hashtable
    }
  }
  return false;  // If for any reason insertion can't happen, return false
}

/****************** hashtable_find() *****************/
void *hashtable_find(hashtable_t *ht, const char *key) {
  if (ht == NULL || key == NULL) {  // Defensive check that arguments are legitimate
    return NULL;
  }
  unsigned long i = hash_jenkins(key, ht->length);  // Create new hash
  if (ht->array[i] != NULL) { // If the index of the array is not null
    return set_find(ht->array[i], key);  // return set_find in the set of the hashtable
  }
  else {
    return NULL;
  }
}

/**************** hashtable_print ****************/
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {
  if (fp != NULL) {  // Check the file isn't null
    if (ht != NULL) {  // Check the hashtable isn't null
      fputc('{', fp);  // Start syntax
      for (int i=0; i<ht->length; i++) {  // Iterate over indices of the hashtable
        set_print(ht->array[i], fp, (*itemprint));  // Set print each of the items       
      }
      fputc('}', fp); // Close syntax
    }
    else {
      fputs("(null)", fp);  // If hashtable is null then print warning
    }
  }
}

/**************** hashtable_iterate ****************/
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
  if (ht != NULL && itemfunc != NULL) { // Defensive checks that hashtable and itemfunc are valid
    for (int i=0; i<ht->length; i++) {  // Iterate over the hashtable
      set_iterate(ht->array[i], arg, (*itemfunc));  // Set iterate over each index
    }
  }
}

/**************** hashtable_delete ****************/
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ) {
  if (ht != NULL && itemdelete != NULL) {  // Defensive checks
    for (int i=0; i<ht->length; i++) {  // Iterate over hashtable
      set_delete(ht->array[i], (*itemdelete));  // Delete each set in the table
    }
    free(ht->array);  // Free the array and set to null
    ht->array=NULL;
    free(ht);  // Free the hashtable and set to null
    ht=NULL;
  }
}
