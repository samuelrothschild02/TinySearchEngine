/**
 * indextest.c
 * Program to test indexer
 * Usage ./indexer oldIndexFilename newIndexFilename
 * CS50 Fall 2021 - Lab 5
 * Sam Rothschild -- 10/17/2021
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include"../libcs50/webpage.h"
#include"../libcs50/memory.h"
#include"../common/pagedir.h"
#include"../libcs50/file.h"
#include"../common/index.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage error. Incorrect number of args inputted.");  // Only need to check number of args as per spec
        exit(1);
    }
    char* oldIndFname = argv[1];  // Store first arg
    char* newIndFname = argv[2];  // Store second arg
    
    index_t* index = index_load(oldIndFname);  // Load info from old file into a new index
    index_save(newIndFname, index);  // Save it into new file
    index_delete(index);  // Delete file to clean up
}
