#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "ncurses.h"
#include <pthread.h>

int ** boardOne;
int ** boardTwo;

int boardSize;
int boardBool;
int sections;
int numThreads;	
//fix the life part. 

int main(int argc, char *argv[])
{

	pthread_t* threads;

	int iterations = 0;
	int displayBool = 0;
	
	long threadID;

	threadID = 0;
	numThreads = 0;

	if(argc < 4 || argc > 5)
	{

		printf("Error, with arguments.\n");
		exit(0);

	}

	if(argc == 5)
	{

		if(strcmp("-d",argv[4]) == 0)
		{

			displayBool = 1;	

		}	

	}

	boardBool = 0;

	numThreads = atoi(argv[1]);

	threads = malloc(sizeof(pthread_t)* numThreads);
	boardSize = atoi(argv[2]);
	iterations = atoi(argv[3]);

	sections = boardSize/numThreads;

	if(numThreads > boardSize)
	{

		sections = 1;

	}

	printf("Creating Board...\n");

	createBoard();

	printf("The board starts as:\n");

	for (int i = 0; i < boardSize; i++)
	{
				
		printf("-");

	}

	printBoard();

	for (int i = 0; i < iterations; i++)
	{

		for (int j = 0; j < numThreads; j++)
		{

			threadID = j;
			if(pthread_create(&threads[j],NULL,&gameLife,(void*)threadID) != 0)
			{

				printf("Error with thread 1.\n");
				exit(0);

			}

		}

		for (int i = 0; i < numThreads; i++)
		{
			
			pthread_join(threads[i],NULL);
		
		}

		if(boardBool == 1)
		{

			boardBool = 0;

		}
		else if(boardBool == 0)
		{

			boardBool = 1;

		}

		if(displayBool == 1)
		{

			for (int i = 0; i < boardSize; i++)
			{
				
				printf("-");

			}

			printBoard();

		}

	}

	for (int i = 0; i < boardSize; i++)
	{
		
		free(boardOne[i]); 
		free(boardTwo[i]);

	}

	free(boardOne);
	free(boardTwo);

	return 0;
}

void* gameLife(void* num)
{

	long id = (long) num;

	spreadDeath(id);
	createLife(id);

	return(0);

}

void createBoard()
{

	int startPop;
	int randomX;
	int randomY;

	boardOne = malloc(sizeof(int*)*(boardSize));
	boardTwo = malloc(sizeof(int*)*(boardSize));

	for (int i = 0; i < boardSize; i++)
	{

		boardOne[i] = malloc(sizeof(int)*(boardSize));
		boardTwo[i] = malloc(sizeof(int)*(boardSize));

		for (int j = 0; j < boardSize; j++)
		{			

			boardOne[i][j] = 0;
			boardTwo[i][j] = 0;

		}	

	}

	startPop = boardSize*boardSize*0.3;

	for (int i = 0; i < startPop; i++)
	{
		do 
		{

			randomY = rand() % boardSize;
			randomX = rand() % boardSize;

		} while(boardOne[randomY][randomX] == 1);

		boardOne[randomY][randomX] = 1;

	}

}

void printBoard()
{

	printf("\n");

	for (int i = 0; i < boardSize; i++)
	{
		
		for (int j = 0; j < boardSize; j++)
		{
			if(boardBool == 0)
			{

				if(boardOne[i][j] == 0)
				{

					printf(" ");

				}
				else
				{

					printf("X");

				}

			}
			else if(boardBool == 1)
			{

				if(boardTwo[i][j] == 0)
				{

					printf(" ");

				}
				else
				{

					printf("X");

				}
				
			}
					
		}

		printf("\n");
	}

}
//Switched i and j around
void createLife(long id)
{

	int neighbors;

	int i = 0;
	int j = 0;

	for (i = id; i < boardSize; i+= numThreads)
	{

		for (j = 0; j < boardSize; j++)
		{

			neighbors = neighborsCheck(i,j);	

			if(neighbors == 3)
			{

				if (boardBool == 1)
				{

					boardOne[j][i] = 1;

				}
				else
				{

					boardTwo[j][i] = 1;

				}

			}

			neighbors = 0;

		}

	}

}
void spreadDeath(long id)
{

	int neighbors = 0;
	int i = 0;
	int j = 0;

	for (i = 0; i < boardSize; i+= numThreads)
	{

		neighbors = 0;

		for (j = 0; j < boardSize; j++)
		{
			
			neighbors = neighborsCheck(i,j);	

			if(neighbors < 2 || neighbors > 3 )
			{

				if (boardBool == 1)
				{

					boardOne[j][i] = 0;

				}
				else
				{

					boardTwo[j][i] = 0;

				}

			}

			neighbors = 0;

		}

	}

}

int neighborsCheck(int i,int j)
{

	int neighbors = 0;

	if(boardBool == 0)
	{

		if(i-1 > 0)
		{

			if(boardOne[j][i-1] ==1)
			{

				neighbors++;

			}

		}
		if(i+1 < boardSize)
		{

			if(boardOne[j][i+1] ==1)
			{
				
				neighbors++;

			}

		}
		if(j-1 > 0)
		{

			if(boardOne[j-1][i] ==1)
			{

				neighbors++;

			}

		}
		if(j+1 < boardSize)
		{

			if(boardOne[j+1][i] ==1)
			{
				
				neighbors++;

			}

		}
		if(i+1 < boardSize && j+1 < boardSize)
		{

			if(boardOne[j+1][i+1] ==1)
			{
				
				neighbors++;

			}

		}
		if(i-1 > 0 && j-1 > 0)
		{

			if(boardOne[j-1][i-1] == 1)
			{
				
				neighbors++;

			}

		}
		if(i+1 <boardSize && j-1 > 0)
		{

			if(boardOne[j-1][i+1] == 1)
			{
				
				neighbors++;

			}

		}
		if(i-1 > 0 && j+1 < boardSize)
		{

			if(boardOne[j+1][i-1] == 1)
			{
				
				neighbors++;

			}

		}

	}
	else
	{


		if(i-1 > 0)
		{

			if(boardTwo[j][i-1] ==1)
			{

				neighbors++;

			}

		}
		if(i+1 < boardSize)
		{

			if(boardTwo[j][i+1] ==1)
			{
				
				neighbors++;

			}

		}
		if(j-1 > 0)
		{

			if(boardTwo[j-1][i] ==1)
			{

				neighbors++;

			}

		}
		if(j+1 < boardSize)
		{

			if(boardTwo[j+1][i] ==1)
			{
				
				neighbors++;

			}

		}
		if(i+1 < boardSize && j+1 < boardSize)
		{

			if(boardTwo[j+1][i+1] ==1)
			{
				
				neighbors++;

			}

		}
		if(i-1 > 0 && j-1 > 0)
		{

			if(boardTwo[j-1][i-1] == 1)
			{
				
				neighbors++;

			}

		}
		if(i+1 <boardSize && j-1 > 0)
		{

			if(boardTwo[j-1][i+1] == 1)
			{
				
				neighbors++;

			}

		}
		if(i-1 > 0 && j+1 < boardSize)
		{

			if(boardTwo[j+1][i-1] == 1)
			{
				
				neighbors++;

			}

		}

	}

	return(neighbors);

}