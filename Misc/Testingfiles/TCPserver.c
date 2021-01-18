#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
 
#define MAXRCVLEN 500
 
int main(int argc, char *argv[])
{

	if(argc != 2)
	{

		printf("Error, incorrect number of arguments.\n");
		exit(0);

	}

	int len;
	int portNumber = 1;

	char buffer[MAXRCVLEN + 1]; // +1 so we can add null terminator
  	char* token;

  	clock_t start;
  	clock_t	end;

  	double timeTaken;

	struct sockaddr_in dest; // socket info about the machine connecting to us
	struct sockaddr_in serv; // socket info about our server
	int mysocket; 
	int total;           // socket used to listen for incoming connections
	socklen_t socksize = sizeof(struct sockaddr_in);

	token = strtok(argv[1],":");

	if(atoi(token) == 0)
	{

		printf("Error with number.\n");
		exit(0);

	}


	if(atoi(token) == 0)
	{

		printf("Error with number.\n");
		exit(0);

	}

	portNumber = atoi(token);

	printf("Port Number:%d\n",portNumber);

	memset(&serv, 0, sizeof(serv));           // zero the struct before filling the fields
	
	serv.sin_family = AF_INET;                // Use the IPv4 address family
	serv.sin_addr.s_addr = htonl(INADDR_ANY); // Set our address to any interface 
	serv.sin_port = htons(portNumber);           // Set the server port number 

	/* Create a socket.
   	   The arguments indicate that this is an IPv4, TCP socket
	*/
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
	// bind serv information to mysocket
	bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

	// start listening, allowing a queue of up to 10 pending connection
	listen(mysocket, 10);
	
	// Create a socket to communicate with the client that just connected
	int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  
	while(consocket)
	{
		printf("Incoming connection from %s \n", inet_ntoa(dest.sin_addr));
		
		// Receive data from the client
		len = 500;
		total = 0;

		start = clock();
		while(len != 0)
		{

			len = recv(consocket, buffer, MAXRCVLEN, 0);
			buffer[len] = '\0';
			printf("%s", buffer);
			total += len;
		
		}
		end = clock();
		printf("\n");
		timeTaken = (double)((end-start));
		printf("All data received.\n");
		printf("Time taken(milliseconds): %f\n",(timeTaken));
		printf("Bytes/seconds: %f\n",(total/(timeTaken/1000)));

		

		//Convert data to upper case
		//Send data to client
		
		//Close current connection
		close(consocket);
		
		//Continue listening for incoming connections
		consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
	}

	close(mysocket);
	return EXIT_SUCCESS;
}