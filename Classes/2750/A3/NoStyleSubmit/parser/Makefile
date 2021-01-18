CFLAGS = -Wall -std=c11 -g -Iinclude
CUTIL = src/VCardParserutilities.c
CLL = src/LinkedListAPI.c
CVCARD = src/VCardParser.c
LL = LinkedListAPI.o
VCARD = VCard.o
VUTIL = Vutil.o

all: dynamic

dynamic:  parser list
	gcc -shared -o ../VCardlib.so $(LL) $(VCARD) $(VUTIL)

list:
	gcc $(CFLAGS) -c -fpic $(CLL) -o $(LL)

parser:
	gcc $(CFLAGS) -c -fpic $(CVCARD) -o $(VCARD)
	gcc $(CFLAGS) -c -fpic $(CUTIL) -o $(VUTIL)

testing:
	gcc $(CFLAGS) $(CVCARD) $(CLL) $(CUTIL) src/testing.c -o testing

clean:
	rm -f bin/*.o bin/*.a bin/testing bin/*.so bin/testingDynamic ./*.so ./*.o
