/**
 * pagedir.c - TSE pagedir module implementation
 * 
 * Refer to pagedir.h for more info
 * 
 * Sam Rothschild, TSE Lab CS50
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/memory.h"
#include "pagedir.h"
#include "../libcs50/webpage.h"

bool isValidDir(char* dir) {
	FILE* fp;  // Initialise file 'fp'
	char* fname;  // Initialise filename
	char* fending;  // Initialise file ending

	fending = "/.crawler";  // Set the ending to ./crawler 
	size_t length = strlen(fending) + strlen(dir) + 1;  // Store the length of the file name and ending
	fname = count_malloc(sizeof(char*) * length + 1);  // Allocate memory for the whole file name (17 to allocate for extra './')
	strcat(fname, dir);  // Concatenate dir to fname
	strcat(fname, fending);  // Concatenate ending to name
	fp = fopen(fname, "w");  // Open for reading
	if (fp == NULL) {  // If null, then open for reading
		count_free(fname);  // Free and return false to indicate failure
		return false;
	}
	else {
		count_free(fname);  // If not null then still free and close but return true to indicate success: the directory is valid
		fclose(fp);
		return true;
	}
}

void pagesaver(webpage_t* page, int id, char* pageDir) {
	char* idString = count_malloc(sizeof(char *));  // Initialise idString passed in
	sprintf(idString, "%d", id);  // Convert to integer
	size_t length = (strlen(idString) + strlen(pageDir) + 1);  // Set length for new file
	char* new_file = count_malloc(sizeof(char*) * length + 1);	// Allocate memory for length of new file
	strcpy(new_file, pageDir);  // Copy in the pagedirectory as new file
	strcat(new_file, idString);	 // Concatenate idString to end of new file

	FILE *fp;  // Initialise File
	fp = fopen(new_file, "w");  // Open file
	fprintf(fp, "%s\n %d\n", webpage_getURL(page), webpage_getDepth(page));  // Print URL and depth
	fprintf(fp, "%s", webpage_getHTML(page));  // Print html 
	fclose(fp);  // Close
	count_free(new_file);  // Free memory allocated
	count_free(idString);
}

char* createFname(int id, char* pageDir) {
    char* stringId = count_malloc(sizeof(char*));  // Allocate memory for id in string form
    sprintf(stringId, "/%d", id);  // Convert integer id to string
    size_t len = strlen(stringId) + strlen(pageDir) + 1;  // Allocate length of file suffix
    char* fname = count_malloc(sizeof(char*) * len + 1);  // Allocate memory for filename
    strcpy(fname, pageDir);  // Copy page directory to filename
    strcat(fname, stringId);  // Concatenate string ID onto filename string
    count_free(stringId);  // Free string ID
    return fname;  // Don't forget to free fname when used
}

FILE* pageloadtest(char* fname) {
    FILE* fp = fopen(fname, "r");  // Open a file for writing
    if (fp != NULL) {  // If the file is null then return null
        return fp;
    } else {
        return NULL;  // Otherwise return the file
    }
}

// UNCOMMENT LINE BELOW TO USE UNIT TEST:
// Use 'make clean' to clean up when finished
// Ensure you have made common before the test, and comment the #define PAGEDIR_UNIT_TEST line back out before trying to make again
//#define PAGEDIR_UNIT_TEST
// Once line above is uncommented use these commands to compile:
// mygcc -I ../libcs50 index.c pagedir.c word.c ../libcs50/libcs50-given.a -o pagedir_unittest
// ./pagedir_unittest

#ifdef PAGEDIR_UNIT_TEST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/memory.h"
#include "pagedir.h"
#include "../libcs50/webpage.h"
int main(int argc, const char* argv[]) {
	printf("Test `isValidDir`\n");
	if (isValidDir("/thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/letters-depth-0")) {
		exit(1);
	}

	printf("Directory valid. \nNow to test `createFname`:\n");
	char* result = createFname(1, "/thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/letters-depth-0");
	if (result == NULL) {
		exit(2);
	}
	printf("Name created. \nNow to test `pageloadtest`:\n");
	FILE* fp = fopen("test", "w");
	if (pageloadtest("test") == NULL) {
		exit(3);
	}
	printf("Page loaded correctly\n");
	fclose(fp);
	return 0;
}
#endif
