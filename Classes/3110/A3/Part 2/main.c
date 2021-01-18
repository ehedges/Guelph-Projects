#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128

typedef struct thing
{

	int count; 
	int size;
	int done;
	char * name;

} process;

int main(int argc, char * argv[])
{

	FILE * fp;

	char ** memory = malloc(sizeof(char*)*SIZE);
	char ** inputs = malloc(sizeof(char*)*SIZE);
	char * token;
	process ** array = malloc(sizeof(process*)*SIZE);

	int processTotal = 0;
	int tempNum = 0;
	int start = 0;
	int slots =  0;
	int processCount = 0;
	int holes = 0;
	int memUsage = 0;
	int cumulative = 0;
	int boolCheck = 0;
	int reset = 0;
	int endReached = 0;
	int done = 0;
	float averageProcess = 0;



	/*Open file*/
	if (argc < 1)
	{
		printf("Error, not enough arguments.\n");
	}

	fp = fopen(argv[1],"r");

	for (int i = 0; i < SIZE; i++)
	{
		inputs[i]= malloc(sizeof(char)*25);
	}
	/*Get input*/
	while (fgets(inputs[processTotal],1000,fp))
	{

		//printf("%s\n",inputs[processTotal]);
		processTotal++;

	}
	/*Loads all the information into an array*/
	for (int i = 0; i < processTotal; i++)
	{
	
		array[i] = malloc(sizeof(process));
		array[i]->name = malloc(sizeof(char*));
		token = strtok(inputs[i]," "); 
		strcpy(array[i]->name,token);
		token = strtok(NULL," ");
		tempNum= atoi(token); 
		array[i]->size = tempNum;
		array[i]->count = 0;
		array[i]->done = 0;
		printf("%s %d\n",array[i]->name, array[i]->size);

	}
	/*Makes the memory blank*/
	for (int i = 0; i < SIZE; i++)
	{
		memory[i] = malloc(sizeof(char)*3);
		strcpy(memory[i],"!");
	
	}

	//printf("HERE\n");
	//printf("Process Total%d\n",processTotal);
	/*First come*/
while(done < processTotal)
{
	done++;
	for (int i = 0; i < processTotal; i++)
	{		
		
		slots = array[i]->size;
		//printf("%s\n",array[i]->name);

		for (int j = 0; j < slots; j++)
		{
			
			if ((start +j) >= SIZE)
			{

				start = 0;

			}

			//printf("Start:%d\n",start);

//			if (strcmp(memory[j+start],"!"))
				//printf("%d\n",start);
				//printf("%d\n",slots);
				/*
				for (int A = 0; A < SIZE; A++)
				{
					printf("%s",memory[A]);
				}
*/
				for (int k = 0; k < processTotal; k++)
				{
					//printf("Checking for which program it is\n");
					//printf("%d\n",k);
					if (strcmp(memory[j+start],array[k]->name) == 0 && array[k]->count != 3)
					{
						processCount--;
						if (array[k]->size > slots && boolCheck == 0)
						{

							holes++;
							boolCheck = 1;
							
						}

						for (int q = 0; q < array[k]->size; q++)
						{
							//printf("HERE\n");
							if((j+start+q) <SIZE )
							{
								strcpy(memory[j+start+q],"!");
							}
							else if(endReached == 0)
							{
								endReached = 1;
								reset = j+start+q;
								strcpy(memory[0],"!");


							}
							else
							{

								strcpy(memory[j+start+q-reset],"!");

							}
							
							
						}

						endReached = 0;

						array[k] ->count += 1;

							
						if (array[k]->count == 3)
						{
								
							array[k]->done = 1;
							
						}

					}
				

				}

			strcpy(memory[j+start],array[i]->name);

		}
		processCount++;
		printf("pid loaded #processes:%d, #holes:%d, %%memUsage:%d cumulative %%mem:%d \n", processCount, holes, memUsage, cumulative);
		boolCheck = 0;
		start += slots;		
		//printf("%d\n",z);
		
	}
	averageProcess+=processCount;
	for (int i = 0; i < processTotal; i++)
	{
			if (array[i]->done == 1)
			{
				done++;
			}
	}	
}	
	averageProcess = averageProcess/processTotal;
	printf("Total loads:%d , average #processes:%f, average #holes:. cumulative %%mem:\n",processTotal,averageProcess);

	fclose(fp);

	return 0;

}