#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int createTree(char* fileName)
{

	FILE* ptr;

	char* inputString;
	char* tempString;

	if(fileName == NULL)
	{

		return(0);

	}

	if(strlen(fileName) < 5)
	{

		return(0);

	}

	if(fileName[strlen(fileName)-4] != '.' && fileName[strlen(fileName)-3] != 'g' && fileName[strlen(fileName)-2] != 'e' && fileName[strlen(fileName)-1] != 'd')
	{

		return(0);

	}

	ptr = fopen(fileName,"r");

	if(ptr == NULL)
	{

		return(0);

	}

	

}