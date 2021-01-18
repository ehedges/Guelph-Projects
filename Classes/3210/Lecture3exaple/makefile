FLAGS= -std=c11 -Wall
all:
	gcc $(FLAGS) TCPserver.c -o server
	gcc $(FLAGS) TCPclient.c -o client
server:
	gcc $(FLAGS) TCPserver.c -o server
client:
	gcc $(FLAGS) TCPclient.c -o client
clean:
	rm -f client server