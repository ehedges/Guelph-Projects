#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include <unistd.h>

int decrypt(int current,  char* encryptionDic, char* encryptionString,int rank,char* origional);

int main(int argc, char const *argv[])
{

	MPI_Init(NULL, NULL);

	int numUnique = 0;
	int num = 0;
	int firstLetter = 0;
	int diffBool = 0;
	int ranLocate = 0;
	int destLocate = 0;
	int rank = 0;

	char* inputString = malloc(sizeof(char)*500);
	char* encryptString = malloc(sizeof(char)*500);
	char* encryptionDic = malloc(sizeof(char)*500);
	char* unqiueLetters = malloc(sizeof(char)*500);

	char swapChar;

	MPI_Comm_size(MPI_COMM_WORLD,&numUnique);	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == 0)
	{
	
		printf("Please input the string:\n");
		fgets(inputString,499,stdin);
	
		
		
		

		
		for (int i = 0; i < strlen(inputString); i++)
		{
		
			if(inputString[i] == '\n')
			{

				inputString[i] = '\0';

			}

		}


		strcpy(encryptString,inputString);

		while(inputString[firstLetter] == ' ')
		{

			firstLetter++;

		}

		unqiueLetters[0] = inputString[firstLetter];
		num++;

		for (int i = 0; i < strlen(inputString); i++)
		{

			if(inputString[i] != ' ')
			{

				for (int j = 0; j < strlen(unqiueLetters); j++)
				{

					if(unqiueLetters[j] == inputString[i])
					{

						break;

					}
					else if(j == num-1)
					{

						diffBool = 1;

					}

				}


				if(diffBool == 1)
				{

					unqiueLetters[num] = inputString[i];
					num++;

				}

				diffBool = 0;

			}

		}

		//Encryp[ting part
		strcpy(encryptionDic,unqiueLetters);
		for (int i = 0; i < 1337; i++)
		{

			ranLocate = rand() % strlen(encryptionDic);
			destLocate = rand() % strlen(encryptionDic);

			swapChar = encryptionDic[destLocate];
			encryptionDic[destLocate] = encryptionDic[ranLocate];
			encryptionDic[ranLocate] = swapChar;

		}

		for (int i = 0; i < strlen(inputString); i++)
		{
			for (int j = 0; j < strlen(unqiueLetters); j++)
			{
				if(inputString[i] == unqiueLetters[j])
				{

					encryptString[i] = encryptionDic[j];

				}

			}
		}

	MPI_Bcast(encryptString,strlen(encryptString),MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Bcast(encryptionDic,strlen(encryptionDic),MPI_CHAR,0,MPI_COMM_WORLD);

	}
	else
	{

		MPI_Bcast(encryptString,500,MPI_CHAR,0,MPI_COMM_WORLD);
		MPI_Bcast(encryptionDic,500,MPI_CHAR,0,MPI_COMM_WORLD);

	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	swapChar = encryptionDic[rank];
	encryptionDic[rank] = encryptionDic[strlen(encryptionDic)-1];
	encryptionDic[strlen(encryptionDic)-1] = swapChar;

	char* origionalDic = malloc(sizeof(char)*strlen(encryptionDic));

	strcpy(origionalDic,encryptionDic);
	decrypt(numUnique-1,encryptionDic,encryptString,rank,origionalDic);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize(); 

	return 0;
}

int decrypt(int current, char* encryptionDic, char* encryptionString,int rank,char* origional)
{

	char temp;
	char temp2;
	int validBool = 0;

	if(current == 1)
	{

		//printf("P:%d,%s\n",rank,encryptionDic);
		char* decrypt = malloc(sizeof(encryptionDic)+1);
		char* tempString = malloc(sizeof(encryptionString)+1);
		char* token;
		char* finalString = malloc(sizeof(char)*strlen(tempString)+1);
		
		int numtokens = 0;
		int swapFlag = 0;

		strcpy(decrypt,origional);
		//printf("%s\n",encryptionDic);
		strcpy(tempString,encryptionString);

		for (int i = 0; i < strlen(encryptionString); i++)
		{
			
			swapFlag = 0;

			if(encryptionString[i] == ' ')
			{

				tempString[i] = ' ';

			}

			for (int j = 0; j < strlen(encryptionDic); j++)
			{
				
				if(encryptionString[i] == encryptionDic[j]&& swapFlag == 0)
				{

					tempString[i] =  origional[j];
					tempString[i+1] = '\0';
					swapFlag = 1;
					

				}

			}

		}
		printf("%s\n",tempString);
		strcpy(finalString,tempString);

		FILE* ptr = fopen("/usr/share/dict/words","r");
		if(ptr == NULL)
		{

			printf("Error with dictionary.\n");
			return(0);
		}

		validBool = 0;
		token = strtok(tempString," ");
		numtokens = 0;
		while(token != NULL)
		{

			numtokens++;
			ptr = fopen("/usr/share/dict/words","r");

			if(ptr == NULL)
			{

				printf("NOPe\n");
				return(0);

			}

			char* checkWord = malloc(sizeof(char)*1000);

			while(fscanf(ptr,"%s",checkWord)!= EOF)
			{

				if(strcmp(checkWord,token) == 0)
				{

					validBool++;

				}

			}

			fclose(ptr);
			token = strtok(NULL," ");

		}
		//printf("%s\n",tempString);
		if(validBool == numtokens)
		{

			printf("Process %d  found a valid string of: %s\n",rank,finalString);

		}

	}
	else
	{
	
		for (int i = 0; i < current; i++)
		{
			decrypt(current-1,encryptionDic,encryptionString,rank,origional);
			if(current%2 == 0)
			{

				temp = encryptionDic[i];
				temp2 = encryptionDic[current-1];
				encryptionDic[i] = temp2;
				encryptionDic[current-1] = temp;

			}
			else
			{

				temp = encryptionDic[0];
				temp2 = encryptionDic[current-1];
				encryptionDic[0] = temp2;
				encryptionDic[current-1] = temp;

			}
		}
	}
		
	return 0;

}