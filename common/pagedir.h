/**
 * pagedir.h - header file for the pagedir module - TSE Lab (crawler)
 * 
 * Save pages to crawler output directory
 * 
 * Sam Rothschild, TSE Lab CS50
 **/

#include "../libcs50/webpage.h"

/** FUNCTIONS **/

// Check crawler directory is created and valid
bool isValidDir(char* dir);  

// Save pages in crawler output dir
void pagesaver(webpage_t* page, int id, char* pageDir);

// Create filename for indexer
char* createFname(int id, char* pageDir);

// Load a file for indexer
FILE* pageloadtest(char* fname);
