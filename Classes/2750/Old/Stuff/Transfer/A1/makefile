CFLAGS = -Wall -std=c11 -g -Iinclude
LLIST = src/LinkedListAPI.c
GEDCOM = src/GEDCOMparser.c
GEDCOMU = src/GEDCOMutilities.c
BINLL = bin/LinkedListAPI.o
BINGED = bin/GEDCOMparser.o 
BINGEDU = bin/GEDCOMutilities.o

all: list parser 
	
parser: GEDCOMparser
	-ar cr bin/libGEDCOMparser.a $(BINGED) $(BINGEDU)

list: LinkedListAPI
	-ar cr bin/liblist.a $(BINLL)

LinkedListAPI: $(LLIST)	
	gcc $(CFLAGS) -c $(LLIST) -o $(BINLL)

GEDCOMparser: $(GEDCOM) $(GEDCOMU)
	gcc $(CFLAGS) -c $(GEDCOMU) -o $(BINGEDU)
	gcc $(CFLAGS) -c $(GEDCOM) -o $(BINGED)

test: list parser 
	gcc $(CFLAGS) src/main.c $(LLIST) $(GEDCOMU) $(GEDCOM) -o bin/test

clean:
	rm -f bin/*.o bin/*.so bin/*.a bin/test
