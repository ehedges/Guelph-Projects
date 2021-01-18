CFLAGS = -Wall -std=c11 -g -Iinclude
LLIST = src/LinkedListAPI.c
GEDCOM = src/GEDCOMparser.c
GEDCOMU = src/GEDCOMutilities.c
BINLL = LinkedListAPI.o
BINGED = GEDCOMparser.o 
BINGEDU = GEDCOMutilities.o

all: list parse
	
list: bin/liblist.a

parse: bin/libparse.a


bin/libparse.a: GEDCOMparser.o GEDCOMutilities.o
	ar cr bin/libparse.a $(BINGED) $(BINGEDU)

GEDCOMutilities.o: $(GEDCOMU)
	gcc $(CFLAGS) -c $(GEDCOMU) -o $(BINGEDU) -L./bin/ -llist

bin/liblist.a: LinkedListAPI.o
	-ar cr bin/liblist.a $(BINLL)

LinkedListAPI.o: $(LLIST)	
	gcc $(CFLAGS) -c $(LLIST) -o $(BINLL)

GEDCOMparser.o: $(GEDCOM) $(GEDCOMU)
	gcc $(CFLAGS) -c $(GEDCOM) -o $(BINGED) -L./bin/ -llist

test: list parse
	gcc $(CFLAGS) src/main.c $(LLIST) $(GEDCOMU) $(GEDCOM) -o bin/test -L./bin/ -llist -lparse

clean:
	rm -f *.o bin/*.a bin/test
