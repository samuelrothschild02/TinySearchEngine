C = ../common
L = ../libcs50

PROG = querier
OBJS = querier.o
LIBS =
LLIBS = $C/common.a $L/libcs50.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L -I$C
CC = gcc
MAKE = make

VALGRIND = valgrind --leak-check=full

.PHONY: all test valgrind clean

all: $(PROG)

# object files depend on include files
querier.o: $L/hashtable.h $L/memory.h $C/index.h $L/file.h $C/pagedir.h $L/counters.o 

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

valgrind: querier
	$(VALGRIND) bash -v testing.sh

test: querier testing.sh
	bash -v testing.sh

clean:
	rm -f core
	rm -rf *~ *.o *.dSYM
	rm -f $(PROG)
