#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VCardParser.h"
#include "utilities.h"
#include "LinkedListAPI.h"

int main(int argc, char const *argv[])
{

	VCardErrorCode error;

	Card* obj;

	char* first;
	char* second;
	char* third;
	char* fileName;

	//int extenValue;

	first = malloc(sizeof(char)*100);
	second = malloc(sizeof(char)*100);
	third = malloc(sizeof(char)*100);


	first = strcpy(first,"!test!");
	second = strcpy(second,"|TESTED|");

/*
	printf("%s\n",first);

	extenValue = -1;

	extenValue = extensionCheck("file.ged","ged",4);
	printf("Test1: Valid: %d expected: 0\n,",extenValue);
	extenValue = extensionCheck("","ged",4);
	printf("Test2: No inpit file: %d expected: 4\n",extenValue);
	extenValue = extensionCheck(NULL,"ged",4);
	printf("Test3: NUll input file: %d expected:1\n",extenValue);
	extenValue = extensionCheck("file.ged","gef",4);
	printf("Test4: Invalid extension: %d expected: \n",extenValue);
	extenValue = extensionCheck("fileged","ged",4);
	printf("Test5: No dot for extension: %d expected: \n",extenValue);
	extenValue = extensionCheck("file.ged","",4);
	printf("Test6: No extension given: %d expected: \n",extenValue);
	extenValue = extensionCheck("file.ged","ged",2);
	printf("Test7: Extension longer than type length: %d expected: 3\n",extenValue);
	extenValue = extensionCheck("file.gedas","gedas",6);
	printf("Test8: Extension longer than type length: %d expected: \n",extenValue);

	strcpy(third,"ABCD");
	extenValue = lineEndingChecker(third,"D");
	printf("Test1: Vaild: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(NULL,"C");
	printf("Test2: NULL input: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,NULL);
	printf("Test3: NULL ending %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,"\r");
	printf("Test4: Wrong ending: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,"ABCD");
	printf("Test5: Multiple characters: %d expected: 0\n",extenValue);
	extenValue = lineEndingChecker(third,"ABCDABCD");
	printf("Test6: Double characters: %d expected: 0\n",extenValue);
*/
	//(*obj) = malloc(sizeof(Card));

	error = OK;
	//printf("Error:%d\n",error);
	fileName = malloc(sizeof(char)*1000);
	strcpy(fileName, "testCardN-compVal.vcf");
	error = createCard(fileName,(&obj));
	char* stuff = printError(error);
	printf("%s\n",stuff);
	free(stuff);

	if(obj == NULL)
	{

		printf("HERER\n");

	}

	char* string = printCard(obj);
	printf("Main:%s\n",string);
	free(string);
	deleteCard(obj);
	deleteCard(NULL);
	string = printCard(NULL);
	free(string);
	free(obj);
	free(fileName);
	free(third);
	free(first);
	free(second);

	error = createCard(NULL,(&obj));
	printf("Null Error:%d\n",error);

	error = createCard("",(&obj));
	printf("Empty Error:%d\n",error);

	error = createCard("Nocard.vcf",(&obj));
	printf("No existant Card Error:%d\n",error);

	error = createCard("utilities.c",(&obj));
	printf("Exist file wrong extension Error:%d\n",error);

	error = createCard("",(&obj));
	printf("Wrong extensions Error:%d\n",error);

	error = createCard("",(&obj));
	printf("Empty Error:%d\n",error);

/*
	for (error = OK ; error < 6; error++)
	{
		string = printError(error);
		printf("%s\n",string);
		free(string);
	}
*/
	return 0;
}