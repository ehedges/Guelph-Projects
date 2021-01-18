CFLAGS=-Wall -std=c11 -Iinclude -g
LLFILES=src/LinkedListAPI.c
CALPARSE=src/CalendarParser.c
BINLL = bin/LinkedListAPI.o
BINCP = bin/CalendarParser.o
CFILES = src/A2main.c
EXEC = bin/A2main
TESTM = src/calTest.c
TEST= bin/calTest

all: A2main

list: LinkedListAPI
	-ar cr bin/liblist.a $(BINLL)

parser: CalendarParser
	-ar cr bin/libcparser.a $(BINCP)

CalendarParser: $(CALPARSE)
	gcc $(CFLAGS) -c $(CALPARSE) -o $(BINCP)

LinkedListAPI: $(LLFILES)	
	gcc $(CFLAGS) -c $(LLFILES) -o $(BINLL)

A2calTest: 
	gcc $(CFLAGS) $(TESTM) $(LLFILES) $(CALPARSE) -o $(TEST)

A2solo:
	gcc $(CFLAGS) $(CFILES) -o test

A2main: list parser ./bin/CalendarParser.o ./bin/LinkedListAPI.o
	gcc $(CFLAGS) $(CFILES) -L. bin/libcparser.a bin/liblist.a -o bin/A2main

clean: 
	rm -f bin/*.o bin/*.so bin/*.a bin/A2main test