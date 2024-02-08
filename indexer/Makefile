# Makefile for 'indexer' module
# Based heavily on versions provided in the course already
# CS50 F21

C = ../common
L = ../libcs50

PROGS = indexer indextest
LIBS =
LLIBS = $C/common.a $L/libcs50-given.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
CC = gcc
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all test valgrind clean

all: $(PROGS)

indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indexer.o: $C/index.h $C/pagedir.h $C/word.h
indexer.o: $L/webpage.h $L/file.h $L/memory.h $L/counters.h $L/hashtable.h

indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest.o: $C/index.h
indextest.o: $L/hashtable.h

test: indexer indextest testing.sh
	bash -v testing.sh

valgrind: testing.sh
	$(VALGRIND) ./indexer /thayerfs/courses/21fall/cosc050.02/workspace/cs50tse/tse-output/letters-depth-0 output/indexfile3

clean:
	rm -f core
	rm -rf *~ *.o *.dSYM
	rm -f $(PROGS)
