#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAXRCVLEN 500
#define PORTNUM 2300
 
int main(int argc, char *argv[])
{

	FILE* ptr;

	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	char* msg = malloc(sizeof(char)*1000);
	int len, mysocket;
	struct sockaddr_in dest; // socket info about the machine connecting to us
 
	int inputBool = 0;
	char* inputFile = malloc(sizeof(char)*1000);

	while(inputBool == 0)
	{

		printf("Please input your file: \n");
		scanf("%s",inputFile);

		if(inputFile != NULL)
		{

			ptr = fopen(inputFile, "r");

			if(ptr != NULL)
			{

				inputBool = 1;
				printf("Opened file.\n");

			}
			else
			{

				printf("Error.\n");

			}

		}

	}

	/* Create a socket.
	   The arguments indicate that this is an IPv4, TCP socket
	*/
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
	memset(&dest, 0, sizeof(dest));                // zero the struct
	
	//Initialize the destination socket information
	dest.sin_family = AF_INET;					   // Use the IPv4 address family
	dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Set destination IP number - localhost, 127.0.0.1
	dest.sin_port = htons(PORTNUM);                // Set destination port number
 	
	// Connect to the server
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
  
  	while(fgets(msg,MAXRCVLEN,ptr))
  	{
  		printf("%s\n",msg);
  		send(mysocket, msg, strlen(msg), 0); 
		len = recv(mysocket, buffer, MAXRCVLEN, 0);

  	}

 
	/* We have to null terminate the received data ourselves */
	buffer[len] = '\0';
 
	printf("Received %s (%d bytes).\n", buffer, len);
 
	free(inputFile);

	close(mysocket);
	return EXIT_SUCCESS;
}
