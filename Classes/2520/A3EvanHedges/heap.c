/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 5th
	Assignment: 3
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/********************************************
Purpose: Controls the program, reads in a file and min heaps it.
In: A file.
Out: Nothing.
*********************************************/

int main()
{

	FILE * ptr;

	char * input = malloc(sizeof(char)*1000);
	char * token;
	
	int heap[21][11];
	int row = 1;
	int swap;
	int temp;
	int tempKey;
	int firstKey;
	int secondKey;
	int thirdKey;

	

	ptr = fopen("f.dat","r");

	/*Read in*/
	while(fgets(input,999,ptr)!=NULL)
	{

		token = strtok(input," ");
		temp = atoi(token);
		heap[row][0] = temp;

		for (int i = 1; i < 10; i++)
		{

			token = strtok(NULL," ");
			temp = atoi(token);
			heap[row][i] = temp;

		}

		row++;
			
	}

	printf("Origional File Input:\n");
	printHeap(heap);

	/*Heaping*/
	for(int i = 0; i < 10; i++)
	{		
		for(int j = 1; j < 11; j++)
		{
		
			firstKey = generateKey(heap,j);
			
			/* Ensures that we are not going out of bounds*/
			if(j*2 <= 20)
			{
				
				secondKey = generateKey(heap,2*j);

			}
			else
			{

				secondKey = -1;

			}

			/* Ensures that we are not going out of bounds*/
			if(j*2+1 <= 20)
			{

				thirdKey = generateKey(heap, 2*j+1);

			}
			else
			{

				thirdKey = -1;

			}

			/* Check the keys*/
			if (firstKey > secondKey && secondKey != -1)
			{

				/*Swap*/
				for (int i = 0; i < 10; i++)
				{
			
					swap = heap[j][i];
					heap[j][i] = heap[2*j][i];
					heap[2*j][i] = swap;

				}

				/*Ensures that the keys still correspond*/
				tempKey = firstKey;
				firstKey = secondKey;
				secondKey = tempKey; 

			}

			if (firstKey > thirdKey && thirdKey != -1)
			{
				
				for (int i = 0; i < 10; i++)
				{
			
					swap = heap[j][i];
					heap[j][i] = heap[2*j+1][i];
					heap[2*j+1][i] = swap;

				}

				/*Ensures that the keys still correspond, even if it is not needed*/
				tempKey = firstKey;
				firstKey = thirdKey;
				thirdKey = tempKey; 

			}

		}

	}
	

	printf("\n\nHeaped:\n");
	printHeap(heap);

	free(input);
	fclose(ptr);	

	return 0;

}