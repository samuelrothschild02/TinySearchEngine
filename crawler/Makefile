# Makefile for crawler TSE
# CS50 F21

C = ../common
L = ../libcs50
LLIBS = $C/pagedir.h $C/pagedir.c $L/libcs50-given.a 

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all test valgrind clean

all: crawler

crawler: crawler.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


crawler.o: $C/pagedir.h $L/bag.h $L/hashtable.h $L/memory.h $L/webpage.h 

valgrind: testing.sh
	$(VALGRIND) ./testing.sh 

test: crawler testing.sh
	bash -v testing.sh

clean:
	rm -f core
	rm -rf *~ *.o *.dSYM
	rm -f crawler
