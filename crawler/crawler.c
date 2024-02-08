/**
 * cralwer.c
 * Program to crawl the web like a spider and retrieve webpages starting from a seedURL, first part in the tse series of labs. 
 * Usage ./crawler seedURL pageDirectory maxDepth
 * CS50 Fall 2021 - Lab 3
 * Sam Rothschild -- 10/10/2021
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"../libcs50/webpage.h"
#include"../libcs50/bag.h"
#include"../libcs50/hashtable.h"
#include"../libcs50/memory.h"
#include"../common/pagedir.h"

/** Function prototypes **/
void crawler(char *seedURL, char *pageDirectory, int maxDepth);
bool page_fetcher(webpage_t* page);
void pagescanner(webpage_t* page, hashtable_t* ht, bag_t* bag);
void page_saver(webpage_t* page, int id, char* pageDirectory);

int main(int argc, char *argv[]) {
  if (argc != 4) {  // Check that the correct number of arguments has been passed in
		fprintf(stderr, "Usage error - incorrect number of arguments. Usage instructions: ./crawler seedURL pageDirectory maxDepth\n");
		exit(1);
  }
	// Check seedURL is valid
	char* URL = argv[1];
	if (IsInternalURL(URL)==false) {	// If the URL isn't internal
		fprintf(stderr, "Usage error - incorrect URL input. Usage instructions: URL must be internal\n");
		exit(2);
	}

	// Check pageDirectory is valid
	char* pageDir = argv[2];
	if (!isValidDir(pageDir)) {
		fprintf(stderr, "Usage error - incorrect page directory input. Usage instructions: Page directory must be valid\n");
		exit(3);
	}

	// Assign depth value from args
	int maxDepthint;
	char* maxDepth = argv[3];
	int digitTest = sscanf(maxDepth, "%d", &maxDepthint);
	if (digitTest != 1 || maxDepthint < 0) {	 // Check maxDepth is valid (ie a positive integer)
		fprintf(stderr, "Usage error - incorrect maxDepth. Usage instructions: maxDepth must be a positive integer\n");
    exit(4);
	}
	// If all arguments are checked and valid then run
	crawler(URL, pageDir, maxDepthint);
	return 0;  // Return 0 on success
}

void crawler(char *seedURL, char *pageDirectory, int maxDepth) {
	bag_t* toVisit = bag_new();  // Initialise bag of pages to visit
	webpage_t* seedPage = webpage_new(seedURL, 0, NULL);  // Initialise new 'seed' webpage
	hashtable_t* visited = hashtable_new((maxDepth + 1) * 100);	 // Initialise hashtable of visited pages
	bag_insert(toVisit, seedPage);	// Insert start webpage into the bag
	hashtable_insert(visited, webpage_getURL(seedPage), "");	// Insert the URL into the hashtable of visited URLs
	int id = 0;  // Intialise id for printing as 1
	webpage_t* currentPage;
	while ((currentPage = bag_extract(toVisit)) != NULL) {
		// Pause for at least 1 second as per spec -- is taken care of in the webpage_fetch function
		if (page_fetcher(currentPage)) {  // If it is possible to fetch the current webpage
			id++;	// Increment page save id
			page_saver(currentPage, id, pageDirectory);
		}
		if (webpage_getDepth(currentPage) <= maxDepth) {  // If the current depth is below the maxDepth (ie if we want to do more)
			pagescanner(currentPage, visited, toVisit);
		}
		//webpage_delete(currentPage);
	}
	bag_delete(toVisit, webpage_delete);  // Delete bag to free memory
	hashtable_delete(visited, NULL);	// Delete hashtable to free memory
}


bool page_fetcher(webpage_t* page) {
	return webpage_fetch(page);  // Abstracted function which leverages webpage fetch
}

void pagescanner(webpage_t* page, hashtable_t* ht, bag_t* bag) {
	int depth = webpage_getDepth(page);	 // Get current depth of webpage
	depth++;  // Increment depth
	int currPos = 0;  // Current position in html
	char* result;  // Initialise result
	while ((result = webpage_getNextURL(page, &currPos)) != NULL) {	 // While there are more URLS to go through
		if (NormalizeURL(result) == true) {  // If it is normalized
			if (IsInternalURL(result)) {	// If it is internal
				if (hashtable_insert(ht, result, "") == true) {  // If not already in the hashtable (ie can be inserted)
					webpage_t* newPage;  // Initialise new page
					newPage = webpage_new(result, depth, NULL);  // Create new webpage with resulting URL and depth
					bag_insert(bag, newPage);  // Insert into bag to visit
				}
			}
		}
		//count_free(result);  // Free result
	}
}

void page_saver(webpage_t* page, int id, char* pageDirectory) {
	FILE *fp;  // Initialise file pointer to print webpage info
	char* idAsString = count_malloc(sizeof(char*));  // Allocate memory for string version of id
	sprintf(idAsString, "%d", id);  // Convert id name to string
	size_t length = strlen(idAsString) + strlen(pageDirectory) + 1;  // Initialise length
	char* newFile = count_malloc(sizeof(char*) * length + 2);  // Allocate memory for new file name holder
	strcpy(newFile, pageDirectory);  // Copy page directory to new file
	strcat(newFile, "/");  // Add the slash for directory syntax
	strcat(newFile, idAsString);  // Concartenate id name in string form (so we know what file number we're on)
	fp = fopen(newFile, "w");  // Open teh new file
    fprintf(fp, "%s\n %d\n", webpage_getURL(page), webpage_getDepth(page));  // Print the URL and depth at top
	printf("in page saver, url is %s\n", webpage_getURL(page));  // Print url is: so you can track progress of crawler on command line
    fprintf(fp, "%s", webpage_getHTML(page));  // Print the html (body of the webiste)
	fclose(fp);  // Close opened file
	count_free(idAsString);  // Free idasstring and newfile
	count_free(newFile);
}
