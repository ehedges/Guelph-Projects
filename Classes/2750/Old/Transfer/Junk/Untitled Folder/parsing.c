#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkedListAPI.h"
#include "parsing.h"

#define STARTSIZE 400
#define INPUTREAD 300

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj);
{

	FILE* ptr = NULL;

	char* inputString;
	char* tempString; 
	char* token;

	char numArray[10] = "1234567890";

	int lengthInput;
	int firstBool = 0;
	int depth = 0;
	int validNum = 0;
	int value = 0;
	int previousValue = 0;

	if(fileName == NULL)
	{

		printf("ErrorNULL\n");
		return(0);

	}

	if(strlen(fileName) < 5)
	{

		printf("ErrorEXT\n");
		return(0);

	}

	if(fileName[strlen(fileName)-4] != '.' || fileName[strlen(fileName)-3] != 'g' || fileName[strlen(fileName)-2] != 'e' || fileName[strlen(fileName)-1] != 'd')
	{

		printf("ErrorIMPEXT\n");
		return(0);

	}

	ptr = fopen(fileName,"r");

	if(ptr == NULL)
	{

		printf("ErrorDNE\n");
		return(0);

	}

	inputString = malloc(sizeof(char)*STARTSIZE);
	tempString = malloc(sizeof(char)*STARTSIZE);

	while(fgets(tempString,INPUTREAD,ptr))
	{

		//printf("%s",tempString);
		//Checks to see if the first value is a number
		token = strtok(tempString," ");

		for (int i = 0; i < strlen(token); i++)
		{
			
			for (int j = 0; j < strlen(numArray); j++)
			{

				if(token[i] == numArray[j])
				{

					validNum++;

				}

			}
			
		}

		if(validNum != strlen(token))
		{

			printf("Error with num: %s\n",token);
			printf("%d\n",validNum);

		}
		else
		{

			value = atoi(token);

			if(value + 1 == previousValue || value - 1 == previousValue || value == previousValue)
			{

				printf("SOMETHINGHERE\n");

			}
			else
			{

				printf("Error with value\n");

			}

		}

		token = strtok(NULL,"");

		if(token != NULL)
		{

			while(token != NULL)
			{

				printf("%s",token);
				token = strtok(NULL,"");
				
			}

		}
		else
		{

			printf("Something about nothing else in this line. \n");

		}



		strcpy(inputString,tempString);

		validNum = 0;

	}

	//printf("Done: %s\n",inputString);

	free(tempString);
	free(inputString);
	fclose(ptr);

	return(0);

}
/** Function to create a string representation of a GEDCOMobject.
 *@pre GEDCOMobject object exists, is not null, and is valid
 *@post GEDCOMobject has not been modified in any way, and a string representing the GEDCOM contents has been created
 *@return a string contaning a humanly readable representation of a GEDCOMobject
 *@param obj - a pointer to a GEDCOMobject struct
 **/
char* printGEDCOM(const GEDCOMobject* obj);


/** Function to delete all GEDCOM object content and free all the memory.
 *@pre GEDCOM object exists, is not null, and has not been freed
 *@post GEDCOM object had been freed
 *@return none
 *@param obj - a pointer to a GEDCOMobject struct
 **/
void deleteGEDCOM(GEDCOMobject* obj);


/** Function to "convert" the GEDCOMerror into a humanly redabale string.
 *@return a string contaning a humanly readable representation of the error code
 *@param err - an error struct
 **/
char* printError(GEDCOMerror err);

/** Function that searches for an individual in the list using a comparator function.
 * If an individual is found, a pointer to the Individual record
 * Returns NULL if the individual is not found.
 *@pre GEDCOM object exists,is not NULL, and is valid.  Comparator function has been provided.
 *@post GEDCOM object remains unchanged.
 *@return The Individual record associated with the person that matches the search criteria.  If the Individual record is not found, return NULL.
 *If multiple records match the search criteria, return the first one.
 *@param familyRecord - a pointer to a GEDCOMobject struct
 *@param compare - a pointer to comparator fuction for customizing the search
 *@param person - a pointer to search data, which contains seach criteria
 *Note: while the arguments of compare() and person are all void, it is assumed that records they point to are
 *      all of the same type - just like arguments to the compare() function in the List struct
 **/
Individual* findPerson(const GEDCOMobject* familyRecord, bool (*compare)(const void* first, const void* second), const void* person);


/** Function to return a list of all descendants of an individual in a GEDCOM
 *@pre GEDCOM object exists, is not null, and is valid
 *@post GEDCOM object has not been modified in any way, and a list of descendants has been created
 *@return a list of descendants.  The list may be empty.  All list members must be of type Individual, and can appear in any order.
 *All list members must be COPIES of the Individual records in the GEDCOM file.  If the returned list is freed, the original GEDCOM
 *must remain unaffected.
 *@param familyRecord - a pointer to a GEDCOMobject struct
 *@param person - the Individual record whose descendants we want
 **/
List getDescendants(const GEDCOMobject* familyRecord, const Individual* person);


//************************************************************************************************************

//****************************************** List helper functions *******************************************
void deleteEvent(void* toBeDeleted);
int compareEvents(const void* first,const void* second);
char* printEvent(void* toBePrinted);

void deleteIndividual(void* toBeDeleted);
int compareIndividuals(const void* first,const void* second);
char* printIndividual(void* toBePrinted);

void deleteFamily(void* toBeDeleted);
int compareFamilies(const void* first,const void* second);
char* printFamily(void* toBePrinted);

void deleteField(void* toBeDeleted);
int compareFields(const void* first,const void* second);
char* printField(void* toBePrinted);