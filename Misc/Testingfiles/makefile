FLAGS= -std=c11 -Wall
all: server client

server:
	gcc $(FLAGS) TCPserver.c -o server
client:
	gcc $(FLAGS) TCPclient.c -o client
clean:
	rm -f client server