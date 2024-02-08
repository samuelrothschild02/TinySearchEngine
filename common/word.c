/**
 * word.c
 * Implementation of word.h file to normalize a word for the tiny search engine. 
 * CS50 Fall 2021 - Lab 5
 * Sam Rothschild -- 10/19/2021
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"word.h"
#include"memory.h"

// Function to normalise a word, see word.h for more information
char* normalize(char* word) {
    size_t len = strlen(word);  // Get the length of the word
    char* normalized = malloc(sizeof(char*) * len + 1);  // Allocate sufficient memory for length of normalized string and null terminator (to be free by user)
    for (int curr=0; curr<len; curr++) {  // Iterate over each character in the string
        normalized[curr] = tolower(word[curr]);  // Use function to ensure each character is lower case
    }
    normalized[len] = '\0';  // Add null terminator
    return normalized;  // Return normalized string for use in program
}

// UNCOMMENT LINE BELOW TO USE UNIT TEST:
// Use 'make clean' to clean up when finished
// Ensure you have made common before the test, and comment the #define WORD_UNIT_TEST line back out before trying to make again
//#define WORD_UNIT_TEST
// Once line above is uncommented use these commands to compile:
// mygcc -I ../libcs50 ../libcs50/libcs50-given.a -o word_unittest
// ./word_unittest

#ifdef WORD_UNIT_TEST
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"word.h"
#include"../memory.h"
int main(int argc, const char* argv[]) {
    printf("Test normalise:\n");
    char* comp = "hello";
    char* result = normalize("HELLO");
    if (strcmp(comp, result) != 0) {
        exit(1);
    }
    printf("Result is: %s\n", result);
    printf("Normalised successfully\n");
}
#endif
