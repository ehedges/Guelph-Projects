CC = gcc
CFLAGS = -g -Wall -Iinclude -std=c11 -pthread

CLIENT = TCPclient
SERVER = TCPserver

all: ./bin/$(CLIENT) ./bin/$(SERVER)
client: ./bin/$(CLIENT)
server: ./bin/$(SERVER)

./bin/$(CLIENT): ./bin/$(CLIENT).o
	$(CC) $(CFLAGS) -o ./bin/client ./bin/$(CLIENT).o

./bin/$(CLIENT).o: ./src/$(CLIENT).c ./include/$(CLIENT).h
	$(CC) $(CFLAGS) -c ./src/$(CLIENT).c -o ./bin/$(CLIENT).o

./bin/$(SERVER): ./bin/$(SERVER).o
	$(CC) $(CFLAGS) -o ./bin/server ./bin/$(SERVER).o

./bin/$(SERVER).o: ./src/$(SERVER).c ./include/$(SERVER).h
	$(CC) $(CFLAGS) -c ./src/$(SERVER).c -o ./bin/$(SERVER).o

clean:
	$(RM) ./bin/server ./bin/client ./bin/*.o
