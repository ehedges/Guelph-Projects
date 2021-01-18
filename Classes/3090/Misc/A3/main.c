#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

void printMatrix(float** matrix, float* vector, float* finalVector,int sizeMatrix);

void calcuMatrix(float** matrix, float* vector, float* finalVector,int sizeMatrix,int numThreads,int flagBool);

float* finalVector;

clock_t begin;
clock_t end;

int main(int argc, char const *argv[])
{

	float** matrix;
	float* vector;

	//float timeArray[4][3];
	float time;
	int numThreads = 0;
	int sizeMatrix = 0;
	int flagBool = 0;

	if(argc == 2)
	{

		if(strcmp(argv[1],"-g") == 0)
		{

			numThreads = 1;
			sizeMatrix = 100;
			flagBool = 1;

			vector = malloc(sizeof(float)*20000);
			finalVector = malloc(sizeof(float)*20000);
			matrix = malloc(sizeof(float*)*20000);

			for (int i = 0; i < 20000; i++)
			{

				matrix[i]= malloc(sizeof(float)*20000);

			}

			printf("Size\t\tthreads\n");
			printf("\t1\t2\t4\n");
			printf("100");

			for (int i = 0; i < sizeMatrix; i++)
			{

				vector[i] = rand()%10;
				if(vector[i] == 0)
				{
	
					vector[i] = 1;

				}

				finalVector[i] = 0;

			}

			for (int i = 0; i < sizeMatrix; i++)
			{

				for (int j = 0; j < sizeMatrix; j++)
				{
			
					matrix[i][j] = rand()%10;
					if(matrix[i][j] == 0)
					{

						matrix[i][j] = 1;

					}
	
				}

			}

			while(numThreads < 5)
			{
							
				calcuMatrix(matrix,vector,finalVector,sizeMatrix,numThreads,flagBool);
				
				time = (float)(end - begin)/numThreads;
				time = time/CLOCKS_PER_SEC;
				printf("\t%.3f",time);
				numThreads = numThreads*2;
				if(numThreads == 8 && sizeMatrix != 20000)
				{
					
					numThreads = 1;

					sizeMatrix = sizeMatrix*10;
					if(sizeMatrix == 100000)
					{

						sizeMatrix = 20000;

					}
					printf("\n%d",sizeMatrix);

				}

			}	

			printf("\n");

		}
		else
		{

			printf("Error with flag.\n");

		}

	}
	else if(argc == 3)
	{

		numThreads = atoi(argv[1]);
		sizeMatrix = atoi(argv[2]);

		vector = malloc(sizeof(float)*sizeMatrix);
		finalVector = malloc(sizeof(float)*sizeMatrix);
		matrix = malloc(sizeof(float*)*sizeMatrix);

		for (int i = 0; i < sizeMatrix; i++)
		{

			matrix[i]= malloc(sizeof(float)*sizeMatrix);

		}


		calcuMatrix(matrix,vector,finalVector,sizeMatrix,numThreads,flagBool);
		time = (float)(end - begin)/numThreads;
		time = time/CLOCKS_PER_SEC;
		printf("Time:%.3f s\n",time);

	}

	return 0;
}

void calcuMatrix(float** matrix, float* vector, float* finalVector,int sizeMatrix,int numThreads,int flagBool)
{

	//printMatrix(matrix,vector,finalVector,sizeMatrix);
	if(flagBool == 0)
	{

		for (int i = 0; i < sizeMatrix; i++)
		{

			vector[i] = rand()%10;

			if(vector[i] == 0)
			{

				vector[i] = 1;

			}
			
			finalVector[i] = 0;

		}

		for (int i = 0; i < sizeMatrix; i++)
		{

			for (int j = 0; j < sizeMatrix; j++)
			{
			
				matrix[i][j] = rand()%10;
				if(matrix[i][j] == 0)
				{

					matrix[i][j] = 1;

				}

			}

		}

	}
	begin = clock();
	# pragma omp parallel for schedule(dynamic)num_threads(numThreads) reduction(+:finalVector[:sizeMatrix])

		for (int i = 0; i < sizeMatrix; i++)
		{
			for (int j = 0; j < sizeMatrix; j++)
			{

				finalVector[i] += matrix[j][i]*vector[j];

			}
		
		}

	end = clock();
	if(flagBool == 0)
	{

		//printMatrix(matrix,vector,finalVector,sizeMatrix);

	}

}

void printMatrix(float** matrix, float* vector, float* finalVector,int sizeMatrix)
{


	int spacing = 9;
	int alignVector = 0;
	int row = 0;
	int vectorTrack = 0;

	printf("AXB = [");
	//Prints out the vector
	for (int i = 0; i < sizeMatrix; i++)
	{

		printf("%.2f ",vector[i]);

		if(vector[i] > 99)
		{

			spacing += 7;

		}
		else if(vector[i] > 9)			
		{

			spacing += 6;

		}
		else			
		{

			spacing+= 5;

		}

	}
	//Aligns everything to the right
	printf("] |");
	alignVector = 0;
	for (int i = 0; i < sizeMatrix; i++)
	{

		printf("%.2f ",matrix[row][i]);

		if(matrix[row][i] < 9)
		{

			alignVector += 5;

		}
		else if(matrix[row][i] < 99)			
		{

			alignVector += 4;

		}

	}

	row++;
	//Print the result.
	printf("| ");
	printf("%.2f = C\n",finalVector[vectorTrack]);
	vectorTrack++;
	for (int i = 0; i < (sizeMatrix-1); i++)
	{
		
		for (int k = 0; k < spacing; k++)
		{
			
			printf(" ");

		}

		printf("|");

		alignVector = 0;
		//Prints the containment
		for (int i = 0; i < sizeMatrix; i++)
		{

			printf("%.2f ",matrix[row][i]);
			if(matrix[row][i] < 9)
			{

				alignVector += 5;

			}
			else if(matrix[row][i] < 99)			
			{

				alignVector += 4;

			}

		}
/*
		for (int i = 0; i < alignVector; i++)
		{
			
			printf(" ");

		}
*/
		printf("|");
		row++;
		printf(" %.2f\n", finalVector[vectorTrack]);
		vectorTrack++;

	}

}