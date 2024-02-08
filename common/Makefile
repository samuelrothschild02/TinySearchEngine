## Makefile for Common Directory of TSE CS50
# Based heavily on Makefiles provided by David Kotz in other labs

L = ../libcs50
OBJS = pagedir.o word.o index.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L
CC = gcc
MAKE = make

.PHONY: clean all

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

pagedir.o: pagedir.h $L/file.h $L/memory.h $L/webpage.h
word.o: word.h $L/memory.h
index.o: index.h pagedir.h word.h $L/counters.h $L/hashtable.h $L/webpage.h $L/set.h $L/memory.h $L/file.h

clean:
	rm -f $(LIB) *~ *.o *_unittest
