## CS50 TSE Crawler
# Sam Rothschild, CS50 TSE crawler

# Purpose:
Crawler is a programme which crawls the crawls the web (like a spider) and retreives webpages from a seedURL. It goes through each of those pages grabbing URLS and saving data,up until a maxdepth specified by the user.

# Assumptions:
*It is necessary for the subdirectory you want to print to be existing in the crawler directory.* No meaningful assumptions beyond are made beyond those outlined in the spec.

# Compile:
In order to compile this usage simply use the keyword: 'make'.

# Usage: 
The crawler is implemented using the following:
```c
bool crawler(char *seedURL, char *pageDirectory, int maxDepth);
bool page_fetcher(webpage_t* page);
void page_saver(webpage_t* page, char* pageDirectory, int id);
void pagescanner(webpage_t* page, hashtable_t* ht, bag_t* bag);
```

Arguments: ./crawler SeedURL PageDir Depth

Example usage: ./crawler http://cs50tse.cs.dartmouth.edu/tse/ data 2

# Issue acknowledgement:
I acknowledge the existence of a memory leak from running my crawler.c, however it compiles without issue and the test cases work well.
