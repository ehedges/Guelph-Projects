/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 5th
	Assignment: 3
***************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************
Purpose: Generate keys.
In: the heap and a row
Out: returns the key (int).
*********************************************/

int generateKey (int heap[21][11], int row)
{

	int key = 0;;

	if(row == 0)
	{

		printf("Error, trying to acces row 0, which is always empty\n");

		return 1;

	}

	key = heap[row][0];
	key += heap[row][1]+heap[row][2];

	return(key);

}

/********************************************
Purpose: Print the heap.
In: the heap.
Out: Prints the heap to the screen.
*********************************************/

void printHeap(int heap[21][11])
{

	int key = 0;

	for (int i = 1; i < 21; i++)
	{
		
		key = generateKey(heap,i);
		printf("Key: %d Row: ", key);
		for (int j = 0; j < 10; j++)
		{
			printf("%d ",heap[i][j]);
		}

		printf("\n");

	}

}