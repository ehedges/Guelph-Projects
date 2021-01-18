/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: September 26th
	Assignment: 1
***************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "a1.h"

/************************************
Purpose: Main control, holds the menu
In: User Input
Out: Prints messages
*************************************/

int main()
{

	FILE *fp; 

	char * values = malloc(sizeof(char)*100); 
	char string[] = "carbon";

	double root = 0;
	double accuracy = 0;
	double square = 0;
	double elapse;

	int loop = 0;
	int first;
	int second;
	int ackvalue;
	int running = 0;
	int i,j;

	struct timeval start;
	struct timeval end;
	
	fp = fopen("carbon.txt","w");

	do
	{

	 	printf("\nOptions:\n A: Carbon \n B: Ackermann's Function\n C: Newton's Divison\n Q: Quit\n\nInput: ");
		fgets(values,99,stdin);
	
		if(strcmp(values,"a\n") == 0 || strcmp(values,"A\n") == 0)
		{
		
			printf("Part A:\n");
			carbon(strlen(string),string,fp);
		
		}
		else if(strcmp(values,"b\n") == 0 || strcmp(values,"B\n") == 0)
		{
		
			printf("Part B:\n M Value: ");			
			fscanf(stdin,"%d",&first);	
			printf(" N Value: ");
			fscanf(stdin,"%d",&second);
			ackvalue = ackermann(first,second);
			printf("Ackerman Value: %d\n",ackvalue );
		
		}
		else if(strcmp(values,"c\n") == 0 || strcmp(values,"C\n") == 0)
		{
		
			printf("Part C:\n Value: ");
			fscanf(stdin,"%lf",&square);
			printf(" Accuracy: ");
			fscanf(stdin,"%lf",&accuracy);
			printf("How many times should this be run?");
			fscanf(stdin,"%d",&running);			
			gettimeofday(&start,NULL);

			for (i = 0; i < running; i++)
			{
				
				root = newtonLoop(square,accuracy);
			
			}

			gettimeofday(&end,NULL);
			/*Converts to milliseconds*/
			elapse = ((end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+end.tv_usec))/1000;
			printf("Non Recursive took: %lfms \n", elapse);
			printf("Root Non Recursive: %f\n",root);
			gettimeofday(&start,NULL);

			for (j = 0; j < running; j++)
			{
				
				root = newtonRec(square,accuracy,square/2);

			}

			gettimeofday(&end,NULL);
			/*Converts to milliseconds*/
			elapse = ((end.tv_sec *1000000 +end.tv_usec)- (start.tv_sec*1000000+start.tv_usec))/1000;
			printf("Recursive took: %lfms \n", elapse);
			printf("Root Recursive: %f\n",root);

		}
		else if(strcmp(values,"quit\n") == 0 || strcmp(values,"Quit\n") == 0|| strcmp(values,"q\n") == 0|| strcmp(values,"Q\n") == 0)
		{
		
			loop = 4;
		
		}
		
		
	} while(loop == 0);

	fclose(fp);
	free(values);

	return(0);
	
}
