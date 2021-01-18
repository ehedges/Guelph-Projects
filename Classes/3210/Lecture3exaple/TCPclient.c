#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 500

 
int main(int argc, char *argv[])
{
	if(argc < 2 || argc > 3)
	{

		printf("Error with arguments.\n");
		exit(0);

	}

	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	char* msg = "Hello Worlds!\n";
	int len, mysocket;
	struct sockaddr_in dest; // socket info about the machine connecting to us
 	int portNum = 1203;
	/* Create a socket.
	   The arguments indicate that this is an IPv4, TCP socket
	*/
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
	memset(&dest, 0, sizeof(dest));                // zero the struct
	
	//Initialize the destination socket information
	dest.sin_family = AF_INET;					   // Use the IPv4 address family
	dest.sin_addr.s_addr = inet_pton(AF_INET,"127.0.0.1",&dest.sin_addr.s_addr); // Set destination IP number - localhost, 127.0.0.1
	dest.sin_port = htons(portNum);                // Set destination port number
 	
	// Connect to the server
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
  
	send(mysocket, msg, strlen(msg), 0); 
	len = recv(mysocket, buffer, MAXRCVLEN, 0);
 
	/* We have to null terminate the received data ourselves */
	buffer[len] = '\0';
 
	printf("Received %s (%d bytes).\n", buffer, len);
 
	close(mysocket);
	return EXIT_SUCCESS;
}
