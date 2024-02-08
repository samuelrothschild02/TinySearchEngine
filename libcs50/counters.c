/* 
* counters.c - CS50 'counters' module
*
* see counters.h for more information
*
* Sam Rothschild F21
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "../libcs50/memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct counternode {
	int key;  // Initialise integer key
	int data;  // Initialise integer data (ie the count)
	struct counternode *next;  // Pointer to next node
} counternode_t;

/**************** global types ****************/
typedef struct counters {
  struct counternode *head;       // head of the list of items in counter
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see counters.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static counternode_t* counternode_new(int key, int data);  // Function to create a new node in linked list

/**************** counters_new() ****************/
/* see counters.h for description */
counters_t* counters_new(void) {
  counters_t* counter = malloc(sizeof(counters_t));  // Allocate required memory for counter

  if (counter == NULL) {
    return NULL;  // Return null if there was an error allocating memory
  } else {
    // initialize contents of counter structure
    counter->head = NULL;
    return counter;  // Return new counter
  }
}

/**************** counters_add() ****************/
/* see counters.h for description */
int counters_add(counters_t* ctrs, const int key) {
  if (ctrs != NULL && key >= 0) {  // Check args are legitimate
    int count = counters_get(ctrs, key);  // Check current data field of the counter passed in
    if (count >=0) {  // If it is more than 0 ie already existing:
      count += 1; // Increment count
      counters_set(ctrs, key, count);  // Set the new value
      return count;  // Return the new count value
    }
    else if (count == 0) {  // If count is 0 ie doesn't already exist
      counters_set(ctrs, key, 1);  // Set a new counter to 1
      return 1;  // Return 1 as this must be the value 
    }
  }
  return 0;  // Return 0 for error
}

/**************** counters_get() ****************/
/* see counters.h for description */
int counters_get(counters_t* ctrs, const int key) {
  if (ctrs != NULL && key >= 0) {
		for (counternode_t *node = ctrs -> head; node != NULL; node = node -> next) {  // Iterate over all nodes
			if (node -> key == key) {  // If current node node's key matches the one we're searching for
				return node -> data;  // Return the data field for that node
			}
		}
	}
  else {
    return 0;
  }
  return 0;
}

/**************** counters_set() ****************/
/* see counters.h for description */
bool counters_set(counters_t* ctrs, const int key, const int count) {
  int counter = counters_get(ctrs, key);
  if (count < 0 || key < 0 || ctrs == NULL) {  // Check args are legitimate as per counters.h
    return false;  // If they aren't return false
  }
  if (counter == 0) {  // If the counter isn't already existing
    counternode_t *new = counternode_new(key, count);  // Make a new counter node
    if (new != NULL) {  // If new is made without problem
      new -> next = ctrs -> head;  // Reshuffle counters
      ctrs -> head = new;
      return true;  // Return true
    }
    return false;  // Return false for error
  }
  for (counternode_t *node = ctrs -> head; node != NULL; node = node -> next) {  // If counter is already existing iterate over nodes
    if (node -> key == key) {  // If the key matches that of the current node
      node -> data = count;  // Reassign count value
      return true;  // Return true
    }
  }
  return false;  // Return false for error
}

/**************** counters_print() ****************/
/* see counters.h for description */
void counters_print(counters_t* ctrs, FILE* fp) {
  if (ctrs == NULL) {  // Check if the counter provided is null
    fputs("(null)\n", fp);  // Notify user if so
  }
  if (fp != NULL && ctrs != NULL) {   // Defensive check that the file provided isn't null and pointer isn't null
    fputc('{', fp);  // Print syntax given in spec
    for (counternode_t *node = ctrs -> head; node != NULL; node = node -> next) {  // Iterate over nodes 
      fprintf(fp, "%d=%d,", node -> key, node ->data);  // Print values
    }
    fputc('}', fp);
    fputc('\n', fp);
  }
}

/**************** counters_iterate() ****************/
/* see counters.h for description */
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count)) {
  if (ctrs != NULL && itemfunc != NULL) {  // Defensive check  that the counter and function provided aren't null
    for (counternode_t *node = ctrs -> head; node != NULL; node = node -> next) {  // Iterate over nodes
      (*itemfunc) (node, node -> key, node -> data);  // Pass key and data into the function
    }
  }
}

/**************** counters_delete() ****************/
/* see counters.h for description */
void counters_delete(counters_t* ctrs) {
  if (ctrs != NULL) {  // Defensive check of args
    for (counternode_t *node = ctrs -> head; node != NULL;) {  // Iterate over nodes
      counternode_t *next = node -> next;  // Set next node
      free(node);  // Free node
      node = next;
    }
    free(ctrs);  // Free counter after freeing all nodes
  }
}

/**************** counternode_new() ****************/
/* local function */
static counternode_t*  counternode_new(int key, int data) {
  counternode_t* node = malloc(sizeof(counternode_t));

  if (node == NULL) {
    return NULL;  // If there was an error allocating memory return null
  } else {
    node->data = data;  // Otherwise set values and return new
    node->key = key;
    node->next = NULL;
    return node;
  }
}
