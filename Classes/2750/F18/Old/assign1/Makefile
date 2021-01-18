CFLAGS = -Wall -std=c11 -g -Iinclude
LIBFLAGS = -L./bin
LIB = -lcparse -lllist
CUTIL = src/VCardParserutilities.c
CLL = src/LinkedListAPI.c
CVCARD = src/VCardParser.c
BINLL = bin/LinkedListAPI.o
BINVCARD = bin/VCard.o
BINVUTIL = bin/Vutil.o

all: list parser

testing: list parser
	gcc $(CFLAGS) $(LIBFLAGS) src/testing.c $(LIB) -o bin/testing

parser:	VCARDparser
	ar crs bin/libcparse.a $(BINVCARD) $(BINVUTIL)

list: ListAPI
	ar crs bin/libllist.a $(BINLL)

VCARDparser:
	gcc $(CFLAGS) -c $(CVCARD) -o $(BINVCARD)
	gcc $(CFLAGS) -c $(CUTIL) -o $(BINVUTIL)

ListAPI:
	gcc $(CFLAGS) -c $(CLL) -o $(BINLL)

clean:
	rm -f bin/*.o bin/*.a

cleant:
	rm -f bin/*.o bin/*.a bin/testing
