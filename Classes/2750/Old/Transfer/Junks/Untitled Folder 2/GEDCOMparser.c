#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedListAPI.h"
#include "GEDCOMparser.h"
#include "GEDCOMutilities.h"

#define STARTSIZE 400
#define INPUTREAD 300


void deleteEvent(void* toBeDeleted)
{


}
int compareEvents(const void* first,const void* second)
{

	return(0);

}
char* printEvent(void* toBePrinted)
{

	return("TBF");

}

void deleteIndividual(void* toBeDeleted)
{


}

int compareIndividuals(const void* first,const void* second)
{

	return(0);

}

char* printIndividual(void* toBePrinted)
{

	return("TBF");

}

void deleteFamily(void* toBeDeleted)
{

	

}

int compareFamilies(const void* first,const void* second)
{

	return(0);

}

char* printFamily(void* toBePrinted)
{

	return("TBF");

}

void deleteField(void* toBeDeleted)
{

	Field* tempField = (Field*) toBeDeleted;

	free(tempField->tag);
	free(tempField->value);

	free(tempField);

}

int compareFields(const void* first,const void* second)
{

	return(0);

}

char* printField(void* toBePrinted)
{

	return("TBF");

}

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

	FILE* ptr = NULL;

	GEDCOMerror error; 

	Header* tempHeader;

	Field* tempField;

	Submitter* tempSub = NULL;

	List fileList =  initializeList(NULL,NULL,NULL);
	List list =  initializeList(NULL,NULL,NULL);

	char* inputString;
	char* tempString; 
	char* token;
	char* tempVersion;

	int value = 0;
	int headerBool = 0;
	int validNum = 0;
	int previousValue = 0;
	int sourBool = 0;

	error.line = 0;
	error.type = OK;

	if(fileName == NULL)
	{

		error.type =  INV_FILE;

		return(error);

	}

	if(strlen(fileName) < 5)
	{

		error.type =  INV_FILE;

		return(error);

	}

	if(fileName[strlen(fileName)-4] != '.' || fileName[strlen(fileName)-3] != 'g' || fileName[strlen(fileName)-2] != 'e' || fileName[strlen(fileName)-1] != 'd')
	{

		error.type =  INV_FILE;

		return(error);

	}

	ptr = fopen(fileName,"r");

	if(ptr == NULL)
	{

		error.type =  INV_FILE;

		return(error);

	}

	inputString = malloc(sizeof(char)*STARTSIZE);
	tempString = malloc(sizeof(char)*STARTSIZE);

	fgets(tempString,INPUTREAD,ptr);

	cleanseNewline(tempString);

	token = strtok(tempString," ");

	if(strcmp(token,"0") != 0)
	{

		error.type = INV_HEADER;

		free(tempString);
		free(inputString);
		fclose(ptr);

		return(error);

	}

	token = strtok(NULL," ");

	if(strcmp(token,"HEAD") != 0)
	{

		error.type = INV_HEADER;

		free(tempString);
		free(inputString);
		fclose(ptr);

		return(error);

	}

	tempHeader = malloc(sizeof(Header)*1);
	tempHeader->gedcVersion = -2;
	strcpy(tempHeader->source,"\0");
    tempHeader->encoding = ASCII;
    tempHeader->submitter = NULL;
    //tempHeader->otherFields 

	while(headerBool == 0)
	{

		fgets(tempString,INPUTREAD,ptr);

		if(tempString == NULL)
		{

				error.type = INV_HEADER;
				free(tempString);
				free(inputString);
				fclose(ptr);

				return(error);

		}

		cleanseNewline(tempString);

		token = strtok(tempString," ");
		validNum = checkNums(token);

		if(validNum == 0)
		{

			value = atoi(token);

			if(value-previousValue < -1 || value-previousValue > 1)
			{

				error.type = INV_HEADER;
				free(tempString);
				free(inputString);
				fclose(ptr);

				return(error);

			}
			else
			{

				previousValue = value;

			}

		}

		token = strtok(NULL," ");

		if(sourBool > value)
		{

			sourBool = 0;

		}

		if(strcmp(token,"SOUR") == 0)
		{

			sourBool = value;

		}
		else if(strcmp(token,"NAME") == 0 && sourBool != 0)
		{

			token = strtok(NULL,"");
			strcpy(tempHeader->source,token);

		}
		else if(strcmp(token,"SUBM") == 0)
		{

			token = strtok(NULL,"");

			tempSub = malloc(sizeof(Submitter)*1+(sizeof(char)*(strlen(token)+5)));

			strcpy(tempSub->address,token);

			tempHeader->submitter = tempSub;

			printf("%s",tempHeader->submitter->address);


		}
		else if(strcmp(token,"GEDC") == 0)
		{

			fgets(tempString,INPUTREAD,ptr);

			cleanseNewline(tempString);

			token = strtok(tempString," ");
			validNum = checkNums(token);

			if(validNum == 0)
			{

				value = atoi(token);

				if(value-previousValue > 1 || value-previousValue == 0 )
				{

					error.type = INV_HEADER;
					free(tempString);
					free(inputString);
					fclose(ptr);

					return(error);

				}
				else
				{

					previousValue = value;

				}

			}

			token = strtok(NULL," ");

			if(strcmp(token,"VERS") == 0)
			{

				if(tempHeader->gedcVersion == -2)
				{

					token = strtok(NULL,".");					

					if(token == NULL)
					{

						error.type = INV_HEADER;
						free(tempString);
						free(inputString);
						fclose(ptr);

						return(error);

					}

					tempVersion = malloc(sizeof(char)*(strlen(token)+5));

					strcpy(tempVersion,token);

					token = strtok(NULL,".");

					if(token == NULL)
					{
						
						error.type = INV_HEADER;
						free(tempString);
						free(inputString);
						fclose(ptr);

						return(error);

					}

					tempVersion = realloc(tempVersion,sizeof(char)*(strlen(tempVersion)+strlen(token)+5));

					strcat(tempVersion,".");
					strcat(tempVersion,token);

					tempHeader->gedcVersion = atof(tempVersion);
					printf("%f",tempHeader->gedcVersion);
					free(tempVersion);

				}
				else
				{
				
					error.type = INV_HEADER;
					free(tempString);
					free(inputString);
					fclose(ptr);

					return(error);

				}

			}
			else if(strcmp(token,"FORM") == 0)
			{
				
				tempField = malloc(sizeof(Field));

				tempField->tag = malloc(sizeof(token)*(strlen(token)+5));

				strcpy(tempField->tag,token);

				token = strtok(NULL,"");

				tempField->value = malloc(sizeof(token)*(strlen(token)+5));

				strcpy(tempField->value,token);

				insertBack(&list,(void*)tempField);

			}
			else
			{
				
					error.type = INV_HEADER;
					free(tempString);
					free(inputString);
					fclose(ptr);

					return(error);

			}
			
		}
		else if(strcmp(token,"CHAR") == 0)
		{

			token = strtok(NULL,"");

			if(strcmp(token,"ANSEL") == 0)
			{

				tempHeader->encoding = ANSEL;

			}
			else if(strcmp(token,"UTF-8") == 0)
			{

				tempHeader->encoding = UTF8;

			}
			else if(strcmp(token,"UNICODE") == 0)
			{

				tempHeader->encoding = UNICODE;

			}
			else if(strcmp(token,"ASCII") == 0)
			{

				tempHeader->encoding = ASCII;
				
			}
			
		}
		else if(value == 0)
		{
			printf("%s\n",tempString);
			headerBool = 1;

		}
		else
		{

			printf("E");

			tempField = malloc(sizeof(Field));

			tempField->tag = malloc(sizeof(token)*(strlen(token)+5));

			strcpy(tempField->tag,token);

			token = strtok(NULL,"");

			tempField->value = malloc(sizeof(token)*(strlen(token)+5));

			strcpy(tempField->value,token);

			insertBack(&list,(void*)tempField);

		}

		printf("\n");


	}

	tempHeader->otherFields = list;

	fileList = initializeList(NULL,NULL,NULL);

	while(fgets(tempString,INPUTREAD,ptr))
	{

		cleanseNewline(tempString);

		insertBack(&fileList,(void*)tempString);

	}

	free(tempString);
	free(inputString);
	fclose(ptr);

	return(error);

}

/** Function to create a string representation of a GEDCOMobject.
 *@pre GEDCOMobject object exists, is not null, and is valid
 *@post GEDCOMobject has not been modified in any way, and a string representing the GEDCOM contents has been created
 *@return a string contaning a humanly readable representation of a GEDCOMobject
 *@param obj - a pointer to a GEDCOMobject struct
 **/
char* printGEDCOM(const GEDCOMobject* obj)
{

	return("SoonTM");

}


/** Function to delete all GEDCOM object content and free all the memory.
 *@pre GEDCOM object exists, is not null, and has not been freed
 *@post GEDCOM object had been freed
 *@return none
 *@param obj - a pointer to a GEDCOMobject struct
 **/
void deleteGEDCOM(GEDCOMobject* obj)
{


}


/** Function to "convert" the GEDCOMerror into a humanly redabale string.
 *@return a string contaning a humanly readable representation of the error code
 *@param err - an error struct
 **/

char* printError(GEDCOMerror err)
{

	char* errorString;
	char* lineString;

	int length = 0;

	

	if(err.type == OK)
	{

		errorString = malloc(sizeof(char)*5);
		strcpy(errorString,"OK");

	} 
	else if(err.type == INV_FILE)
	{

		errorString = malloc(sizeof(char)*20);
		strcpy(errorString,"invalid file");

	} 
	else if(err.type == INV_GEDCOM)
	{

		length = snprintf(NULL,0,"%d",err.line);

		errorString = malloc(sizeof(char)*40);
		lineString = malloc(sizeof(char)*(length+1));

		snprintf(lineString,length+2,"%d",err.line); 

		strcpy(errorString,"invalid record (line ");

		strcat(errorString,lineString);
		strcat(errorString,")\0");

	} 
	else if(err.type == INV_HEADER)
	{

		errorString = malloc(sizeof(char)*20);
		strcpy(errorString,"invalid header");

	} 
	else if(err.type == INV_RECORD)
	{

		errorString = malloc(sizeof(char)*20);
		strcpy(errorString,"invalid record");

	} 
	else
	{

		errorString = malloc(sizeof(char)*10);
		strcpy(errorString,"other");

	}

	return(errorString);

}

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
Individual* findPerson(const GEDCOMobject* familyRecord, bool (*compare)(const void* first, const void* second), const void* person)
{


	return(NULL);

}


/** Function to return a list of all descendants of an individual in a GEDCOM
 *@pre GEDCOM object exists, is not null, and is valid
 *@post GEDCOM object has not been modified in any way, and a list of descendants has been created
 *@return a list of descendants.  The list may be empty.  All list members must be of type Individual, and can appear in any order.
 *All list members must be COPIES of the Individual records in the GEDCOM file.  If the returned list is freed, the original GEDCOM
 *must remain unaffected.
 *@param familyRecord - a pointer to a GEDCOMobject struct
 *@param person - the Individual record whose descendants we want
 **//*
List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{

	List tempList; 

	tempList = initalizeList(&printIndividual,&compareIndividuals,&deleteIndividual);

	return(tempList);

}*/
