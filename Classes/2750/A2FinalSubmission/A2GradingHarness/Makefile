CC = gcc
CFLAGS = -Wall -g -Iinclude -IstudentInclude
CARD_TEST_FILES = src/CardTest.c src/CardTestCreate.c src/CardTestOther.c src/CardTestUtilities.c src/CardTestWrite.c src/CardTestValidate.c src/CardTestA2Module3.c src/TestHarness2.c

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CCFLAGS += -std=gnu11 
endif
ifeq ($(UNAME), Darwin)
	CCFLAGS += -std=c11
endif

cardTests:  
	$(CC)  $(CFLAGS) $(CARD_TEST_FILES) studentCode/*.c  -o bin/cardTests

funcTest: cardTests
	bin/cardTests

leakTestA1: memTestsA1
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTest 1; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTest 2; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTest 3; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTest 4; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestPrint 1; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestPrint 2; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestPrint 3; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestPrint 4

leakTestA2: memTestsA2
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestWrite 1; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestWrite 2; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestWrite 3; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestWrite 4; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestValidate 1; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestValidate 2; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestValidate 3; \
	valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes bin/memTestValidate 4

memTestsA2:
	$(CC) $(CFLAGS) src/MemTestsWrite.c studentCode/*.c  -o bin/memTestWrite; \
	$(CC) $(CFLAGS) src/MemTestsValidate.c studentCode/*.c  -o bin/memTestValidate

memTestsA1:
	$(CC) $(CFLAGS) src/MemTests.c studentCode/*.c  -o bin/memTest; \
	$(CC) $(CFLAGS) src/MemTestsPrint.c studentCode/*.c  -o bin/memTestPrint

clean:
	rm -rf bin/*