#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "task.h"
#include "ncurses.h"
#include <pthread.h>

pthread_mutex_t Queues;
pthread_cond_t startQueues = PTHREAD_COND_INITIALIZER;
pthread_t* threads;

int ** boardOne;
int ** boardTwo;

int boardSize;
int boardBool;
int numThreads;	
int* liveQueue;
int* deadQueue;
int liveEnd;
int deadEnd;
int doneLength;
//fix the life part. 

int main(int argc, char *argv[])
{

	int iterations = 0;
	int displayBool = 0;

	long xCoord = 0;

	if(argc < 3 || argc > 4)
	{

		printf("Error, with arguments.\n");
		exit(0);

	}

	if(argc == 4)
	{

		if(strcmp("-d",argv[3]) == 0)
		{

			displayBool = 1;	

		}	

	}

	pthread_mutex_init(&Queues,NULL);

	boardBool = 0;
	doneLength = 1;
	threads = malloc(sizeof(pthread_t)* 3);
	boardSize = atoi(argv[1]);
	iterations = atoi(argv[2]);
	liveQueue = malloc(sizeof(int)*(boardSize+1));
	deadQueue = malloc(sizeof(int)*(boardSize+1));
	liveEnd = 0;
	deadEnd = 0;

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
		for (int x = 0; x < boardSize; x++)
		{
			
			xCoord = x;

			if(pthread_create(&threads[0],NULL,&neighborsCheck,(void*)xCoord) != 0)
			{

				printf("Error with thread 1.\n");
				exit(0);

			}


			if(pthread_create(&threads[1],NULL,&createLife,(void*)xCoord) != 0)
			{

				printf("Error with thread 1.\n");
				exit(0);

			}

			if(pthread_create(&threads[2],NULL,&spreadDeath,(void*)xCoord) != 0)
			{

				printf("Error with thread 1.\n");
				exit(0);

			}

			pthread_join(threads[0],NULL);
			pthread_join(threads[1],NULL);
			pthread_join(threads[2],NULL);

			liveEnd = 0;
			deadEnd = 0;

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
void* createLife(void* X)
{

	int j = 0;

	long i = (long)X;

	for (int q = 0; q < liveEnd; q++)
	{

		j = liveQueue[q];
	
		if (boardBool == 1)
		{

			boardOne[j][i] = 1;

		}
		else
		{

			boardTwo[j][i] = 1;

		}

	}

	return(0);

}

void* spreadDeath(void* X)
{

	int j = 0;

	long i = (long)X;

	for (int q = 0; q < deadEnd; q++)
	{

		j = deadQueue[q];
	
		if (boardBool == 1)
		{

			boardOne[j][i] = 0;

		}
		else
		{

			boardTwo[j][i] = 0;

		}

	}

	return(0);

}

void* neighborsCheck(void* X)
{

	long i = (long)X;

	int neighbors = 0;

	pthread_mutex_lock(&Queues);

	doneLength = 1;

	for (int j = 0; j < boardSize; j++)
	{
		
		if(boardBool == 0)
		{
			//printf("%d %ld %d\n",j,i,boardOne[j][i+1]);

			if(i+1 < boardSize)
			{

				if(boardOne[j][i+1] ==1)
				{
					
					neighbors++;

				}

			}
			if(i-1 > 0)
			{

				if(boardOne[j][i-1] == 1)
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

		if(neighbors == 3)
		{

			liveQueue[liveEnd] = j;
			liveEnd++;

		}
		else if(neighbors < 2 || neighbors > 3 )
		{

			deadQueue[deadEnd] = j;
			deadQueue++;

		}

		while(doneLength == 1)
		{

			pthread_cond_wait(&startQueues,&Queues);

		}


	}

	pthread_mutex_unlock(&Queues);

	doneLength = 0;

	return(0);

}