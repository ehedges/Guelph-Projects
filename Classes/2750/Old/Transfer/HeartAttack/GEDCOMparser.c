/*****************************
Evan Hedges 0898140
CIS 2750, W18

Professor: Denis Nikitenko
*****************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedListAPI.h"
#include "GEDCOMparser.h"
#include "GEDCOMutilities.h"

#define STARTSIZE 400
#define INPUTREAD 300

void deleteListFile(void* tobeDeleted)
{

	free((char*)tobeDeleted);

}

char* returnListFile(void* tobeDeleted)
{

	return((char*)tobeDeleted);

}

int compareListFile(const void* first,const void* second)
{

	return(0);

}

void deleteEvent(void* toBeDeleted)
{


	

}
int compareEvents(const void* first,const void* second)
{

	return(0);

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

	Field* tempField;

	tempField = (Field*) toBePrinted;

	char* string;

	string = malloc(sizeof(char*)*(strlen(tempField->tag)+strlen(tempField->value)+10));

	strcpy(string,tempField->tag);
	strcat(string,":");
	strcat(string,tempField->value);

	return(string);

}

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

	FILE* ptr = NULL;

	GEDCOMerror error; 

	Header* tempHeader;

	Field* tempField;

	//char** addressList;
	List fileList;

	char* inputString;
	char* tempString; 
	char* token;
	char* tempVersion;
	char* reattachLine;
	char* subRef = NULL;

	int value = 0;
	int headerBool = 0;
	int validNum = 0;
	int previousValue = 0;
	int sourBool = 0;
	int findCont = 0;
	int line = 1;

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

	tempString = malloc(sizeof(char)*STARTSIZE);

	fgets(tempString,INPUTREAD,ptr);

	cleanseNewline(tempString);

	token = strtok(tempString," ");

	if(strcmp(token,"0") != 0)
	{

		error.type = INV_HEADER;

		free(tempString);
		fclose(ptr);

		return(error);

	}

	token = strtok(NULL," ");

	if(strcmp(token,"HEAD") != 0)
	{

		error.type = INV_HEADER;

		free(tempString);
		fclose(ptr);

		return(error);

	}

	tempHeader = malloc(sizeof(Header)*1);
	tempHeader->gedcVersion = 1.0;
	strcpy(tempHeader->source,"\0");
    tempHeader->encoding = ASCII;
    tempHeader->submitter = NULL;
    List list = initializeList(&printField,&deleteField,&compareFields);
    //tempHeader->otherFields 

	while(headerBool == 0)
	{

		line++;

		fgets(tempString,INPUTREAD,ptr);

		if(tempString == NULL)
		{

				error.type = INV_HEADER;
				free(tempString);
				fclose(ptr);

				return(error);

		}

		cleanseNewline(tempString);

		token = strtok(tempString," ");
		validNum = checkNums(token);

		if(validNum == 0)
		{

			value = atoi(token);

			if(value-previousValue > 1)
			{

				error.type = INV_HEADER;
				free(tempString);
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
		if(value == 0)
		{

			headerBool = 1;
			reattachLine = malloc(sizeof(char)*(strlen(tempString)+5));

			strcpy(reattachLine,"0");

			while(token != NULL)
			{
				
				reattachLine = realloc(reattachLine,(sizeof(char)*(strlen(reattachLine) + strlen(token)+5)));
				strcat(reattachLine," ");
				strcat(reattachLine,token);
				token = strtok(NULL,"");

			}

		}
		else if(strcmp(token,"SOUR") == 0)
		{

			sourBool = value;
			token = strtok(NULL,"");
			strcpy(tempHeader->source,token);

		}
		else if(strcmp(token,"NAME") == 0 && sourBool != 0)
		{

			token = strtok(NULL,"");
			strcpy(tempHeader->source,token);

		}
		else if(strcmp(token,"SUBM") == 0)
		{

			token = strtok(NULL,"");
			subRef = malloc((sizeof(char)*(strlen(token)+5)));
			strcpy(subRef,token);

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

				if(value-previousValue > 1)
				{

					error.type = INV_HEADER;
					free(tempString);
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

				if(tempHeader->gedcVersion == 1.0)
				{

					token = strtok(NULL,".");					

					if(token == NULL)
					{

						error.type = INV_HEADER;
						free(tempString);
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
						fclose(ptr);

						return(error);

					}

					tempVersion = realloc(tempVersion,sizeof(char)*(strlen(tempVersion)+strlen(token)+5));

					strcat(tempVersion,".");
					strcat(tempVersion,token);

					tempHeader->gedcVersion = atof(tempVersion);
					free(tempVersion);

				}
				else
				{
				
					error.type = INV_HEADER;
					free(tempString);
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
		else
		{

			tempField = malloc(sizeof(Field));
			tempField->tag = malloc(sizeof(token)*(strlen(token)+5));

			strcpy(tempField->tag,token);
			token = strtok(NULL,"");

			tempField->value = malloc(sizeof(token)*(strlen(token)+5));

			strcpy(tempField->value,token);
			insertBack(&list,(void*)tempField);

		}

	}

	if(subRef == NULL)
	{

		error.type = INV_HEADER;
		free(tempString);
		fclose(ptr);

		return(error);

	}

	tempHeader->otherFields = list;

	//char* checking;

	fileList = initializeList(&returnListFile,&deleteListFile,&compareListFile);
	inputString = malloc(sizeof(char)*STARTSIZE);
	strcpy(inputString,reattachLine);
	insertBack(&fileList,(void*)inputString);

	while(fgets(tempString,INPUTREAD,ptr))
	{

		cleanseNewline(tempString);

		while(tempString[findCont] != ' ')
		{

			findCont++;

		}
/*
		if(tempString[findCont+1] == 'C' && tempString[findCont+2] == 'O' && tempString[findCont+3] == 'N' && tempString[findCont+4] == 'T')
		{

			inputString = realloc(inputString,sizeof(char)*(strlen(inputString)+strlen(tempString)+5));

			checkCont = malloc(sizeof(char)*(strlen(tempString)+5));

			strcpy(checkCont,tempString);

			token = strtok(checkCont," ");

			token = strtok(NULL," ");

			token = strtok(NULL,"");

			strcat(inputString,token);

		}
		else if(tempString[findCont+1] == 'C' && tempString[findCont+2] == 'O' && tempString[findCont+3] == 'N' && tempString[findCont+4] == 'C')
		{

			inputString = realloc(inputString,sizeof(char)*(strlen(inputString)+strlen(tempString)+5));

			checkCont = malloc(sizeof(char)*(strlen(tempString)));

			strcat(inputString,"\r");
			strcat(inputString,checkCont);

		}
		else 
		{
*/
			inputString = malloc(sizeof(char)*STARTSIZE);
			strcpy(inputString,tempString);
			insertBack(&fileList,(void*)inputString);

		//}

	}

	(*obj)->header = tempHeader;

	//checking = printHeader((*obj)->header);
	error = listIndividuals(obj,fileList,line);
	error = createSubmitter(obj,fileList,subRef,line);
	error = listFamily(obj,fileList,line);

	char* checking;

	ListIterator checkFams;

	void* stuff;

	checkFams = createIterator((*obj)->families);


	stuff = nextElement(&checkFams);

	while(stuff != NULL)
	{

		checking = printFamily((Family*)stuff);

		printf("%s",checking);
		stuff = nextElement(&checkFams);

	}

	free(tempString);
	free(inputString);
	free(reattachLine);
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

	deleteHeader(obj->header);

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


	ListIterator iter;

	iter =  createIterator(familyRecord->individuals);

	void* temp;

	bool value;

	value = false;

	temp = nextElement(&iter);
	value = (*compare)(temp,person);

	while(temp != NULL || value == false)
	{

		temp = nextElement(&iter);
		value = (*compare)(temp,person);
		
	}

	if(temp == NULL)
	{

		return(NULL);

	}

	return((Individual*)temp);

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
