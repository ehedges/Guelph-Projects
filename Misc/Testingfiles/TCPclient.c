#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
 
int main(int argc, char *argv[])
{

	if(argc < 2 || argc > 3)
	{

		printf("Error, incorrect number of srguments.\n");
		exit(0);

	}

	FILE* ptr;

	char* buffer; /* +1 so we can add null terminator */
	char* token;
	char* inputFile = malloc(sizeof(char)*1000);
	char* serverAddress;

	int mysocket;
	int portNumber = 1;
	int lengthBuffer;

	struct sockaddr_in dest; // socket info about the machine connecting to us

	token = strtok(argv[1],":");

	strcpy(inputFile,"\0");

	if(atoi(token) == 0)
	{

		printf("Error with number.\n");
		exit(0);

	}

	serverAddress = malloc(sizeof(char)*(strlen(token)+1));
	strcpy(serverAddress,token);
	printf("Server Address is %s. Port is: %d\n", serverAddress,portNumber);
	token = strtok(NULL,":");

	if(atoi(token) == 0)
	{

		printf("Error with number.\n");
		exit(0);

	}

	if(argc != 3)
	{

		strcpy(inputFile,"Alice");

	}
	else
	{

		strcpy(inputFile,argv[2]);

	}

	portNumber = atoi(token);

	ptr = fopen(inputFile, "r");

	if(ptr == NULL)
	{

		printf("Error.\n");
		exit(0);

	}


	if(argc == 3)
	{

		lengthBuffer = atoi(argv[2]);

		if(lengthBuffer <= 0)
		{

			lengthBuffer = 500;

		}

	}

	/* Create a socket.
	   The arguments indicate that this is an IPv4, TCP socket
	*/
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
	memset(&dest, 0, sizeof(dest));                // zero the struct
	
	//Initialize the destination socket information
	dest.sin_family = AF_INET;					   // Use the IPv4 address family
	dest.sin_addr.s_addr = inet_pton(AF_INET,serverAddress,&dest.sin_addr);
	inet_pton(AF_INET,serverAddress,&dest.sin_addr.s_addr); // Set destination IP number - localhost, 127.0.0.1
	//dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	dest.sin_port = htons(portNumber);                // Set destination port number
 	
	// Connect to the server
	while(connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in)) == -1)
	{

		printf("Waiting for a free socket.\n");
		sleep(1);

	}
  
	buffer = malloc(sizeof(char)*lengthBuffer+1);

	//int tempValue =1; 

	//tempValue = fread(buffer,sizeof(char),lengthBuffer,ptr);

	//start = clock();

    while(fgets(buffer,lengthBuffer,ptr))
  	{

 		printf("Sending: %s\n", buffer);
 		//printf("%d\n",tempValue );
  		send(mysocket, buffer, strlen(buffer), 0); 
  		free(buffer);
  		buffer = malloc(sizeof(char)*lengthBuffer+1);
  		//tempValue = fread(buffer,sizeof(char),lengthBuffer,ptr);

  	}

  	//end = clock();

  	//differ = end - start;
	/* We have to null terminate the received data ourselves */
 
	fclose(ptr);

	close(mysocket);

	free(buffer);
	free(inputFile);
	free(serverAddress);

	return EXIT_SUCCESS;
}
