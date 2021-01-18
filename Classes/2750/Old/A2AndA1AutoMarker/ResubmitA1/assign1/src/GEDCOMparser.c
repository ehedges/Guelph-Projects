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

#define STARTSIZE 500
#define INPUTREAD 300

/******
Generic Helper Functions
*****/

void deleteListFile(void* tobeDeleted)
{

	if(tobeDeleted != NULL)
	{

		free((char*)tobeDeleted);

	}
	
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

	Event* temp;

	temp = (Event*)toBeDeleted;

	free(temp->date);
	free(temp->place);	
	clearList(&temp->otherFields);
	free(temp);

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

	Field* field = (Field*)second;

	char* string = (char*)first;

	return(strcmp(string,field->tag));

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

//***************************************** GEDCOOM object functions *****************************************

/** Function to create a GEDCOM object based on the contents of an GEDCOM file.
 *@pre File name cannot be an empty string or NULL.  File name must have the .ged extension.
 File represented by this name must exist and must be readable.
 *@post Either:
 A valid GEDCOM has been created, its address was stored in the variable obj, and OK was returned
 or
 An error occurred, the GEDCOM was not created, all temporary memory was freed, obj was set to NULL, and the
 appropriate error code was returned
 *@return the error code indicating success or the error encountered when parsing the GEDCOM
 *@param fileName - a string containing the name of the GEDCOM file
 *@param a double pointer to a GEDCOMobject struct that needs to be allocated
 **/

GEDCOMerror createGEDCOM(char* fileName, GEDCOMobject** obj)
{

	FILE* ptr = NULL;

	GEDCOMerror error; 

	Header* tempHeader = NULL;

	Field* tempField;

	List fileList;

	char* inputString;
	char* tempString; 
	char* token;
	char* tempVersion;
	char* reattachLine;
	char* subRef = NULL;
	char* insertString;

	int value = 0;
	int headerBool = 0;
	int validNum = 0;
	int previousValue = 0;
	int sourBool = 0;
	int line = 1;

	error.line = 0;
	error.type = OK;

	/*File error checking*/
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
	//Checking file type
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
	//Valid file, beging to make the header;
	/*Checking if there is a header*/
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
    tempHeader->otherFields = initializeList(&printField,&deleteField,&compareFields);
    /*Parsing for the header*/
	while(headerBool == 0)
	{

		line++;

		fgets(tempString,INPUTREAD,ptr);

		if(tempString == NULL)
		{

				error.type = INV_HEADER;
				free(tempString);
				fclose(ptr);
				deleteHeader(tempHeader);
				return(error);

		}

		cleanseNewline(tempString);

		token = strtok(tempString," ");
		validNum = checkNums(token);
		/*Checking to see if it geins with a number*/
		if(validNum == 0)
		{

			value = atoi(token);

			if(value-previousValue > 1)
			{

				error.type = INV_HEADER;
				free(tempString);
				fclose(ptr);
				deleteHeader(tempHeader);
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
		/*This one checks if the header has ended thus exiting the loop*/
		/*Everything after is individual fields to check*/
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
			/*Checks the verson and other things*/
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
					deleteHeader(tempHeader);
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
						deleteHeader(tempHeader);
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
						free(tempVersion);
						deleteHeader(tempHeader);
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
					deleteHeader(tempHeader);
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
				insertBack(&tempHeader->otherFields,(void*)tempField);

			}
			else
			{
				
					error.type = INV_HEADER;
					free(tempString);
					fclose(ptr);
					deleteHeader(tempHeader);
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
			//Other fields
			tempField = malloc(sizeof(Field));
			tempField->tag = malloc(sizeof(token)*(strlen(token)+5));

			strcpy(tempField->tag,token);
			token = strtok(NULL,"");

			tempField->value = malloc(sizeof(token)*(strlen(token)+5));

			strcpy(tempField->value,token);
			insertBack(&tempHeader->otherFields,(void*)tempField);

		}

	}
	//Checks if there is a link to a submitter
	if(subRef == NULL)
	{

		error.type = INV_HEADER;
		free(tempString);
		fclose(ptr);
		deleteHeader(tempHeader);
		return(error);

	}

	fileList = initializeList(&returnListFile,&deleteListFile,&compareListFile);
	insertString = malloc(sizeof(char)*STARTSIZE);
	insertBack(&fileList,(void*)reattachLine);

	error.line = line;
	//Reads in the rest of the file as a linked list
	while(fgets(tempString,INPUTREAD,ptr))
	{

		error.line++;

		cleanseNewline(tempString);
		strcpy(insertString,tempString);

		token = strtok(insertString," ");

		validNum = checkNums(token);

		if(validNum != 0)
		{

			error.type = INV_RECORD;

			free(tempString);
			free(inputString);
			free(insertString);
			free(reattachLine);
			fclose(ptr);

			clearList(&fileList);
			deleteHeader(tempHeader);
			return(error);

		}

		token = strtok(NULL," ");

		inputString = malloc(sizeof(char)*STARTSIZE);
		strcpy(inputString,tempString);
		insertBack(&fileList,(void*)inputString);	

	}
	//Creates the object then parses the file
	(*obj) = malloc(sizeof(GEDCOMobject));

	(*obj)->header = NULL;
	(*obj)->submitter = NULL;

	(*obj)->header = tempHeader;

	error = listIndividuals(obj,fileList,line);
	error = createSubmitter(obj,fileList,subRef,line);
	error = listFamily(obj,fileList,line);

	clearReferences((*obj)->individuals);

	clearList(&fileList);

	free(insertString);
	free(tempString);
	free(subRef);

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

	ListIterator checkFams;

	char* string;
	char* temp;

	void* stuff;

	string = printHeader(obj->header);
	temp = printSubmitter(obj->submitter);

	string = realloc(string,sizeof(char*)*(strlen(string)+strlen(temp)+5));
	strcat(string,temp);

	strcat(string,"\n");

	if(temp != NULL)
	{

		free(temp);

	}


	checkFams = createIterator(obj->families);

	stuff = nextElement(&checkFams);
	
	while(stuff != NULL)
	{

		temp = printFamily(stuff);
		string = realloc(string,sizeof(char*)*(strlen(string)+strlen(temp)+5));
		strcat(string,temp);
		strcat(string,"\n");
		free(temp);
		stuff = nextElement(&checkFams);

	}
 
	strcat(string,"\0");

	return(string);

}


/** Function to delete all GEDCOM object content and free all the memory.
 *@pre GEDCOM object exists, is not null, and has not been freed
 *@post GEDCOM object had been freed
 *@return none
 *@param obj - a pointer to a GEDCOMobject struct
 **/
void deleteGEDCOM(GEDCOMobject* obj)
{

	if((obj->submitter) != NULL)
	{

		destroySubmitter(obj->submitter);		
		free(obj->submitter);

	}

	if((obj->header) != NULL)
	{

		deleteHeader(obj->header);		

	}

	if(&obj->individuals != NULL)
	{

		clearList(&obj->individuals);

	}

	if(&obj->families != NULL)
	{

		clearList(&obj->families);

	}

	free(obj);

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

	if(familyRecord == NULL || person == NULL || (*compare) == NULL)
	{

		return (NULL);

	}

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

	temp = findElement(familyRecord->individuals,(*compare), person);

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
 **/
List getDescendants(const GEDCOMobject* familyRecord, const Individual* person)
{

	List tempList; 

	ListIterator iterPerson;

	Individual* tempPerson;

	void* element;

	int exitBool = 0;

	tempList = initializeList(&printIndividual,&deleteIndividual,&compareIndividuals);

	iterPerson = createIterator(familyRecord->individuals);

	element = nextElement(&iterPerson);

	while(element != NULL && exitBool == 0)
	{

		tempPerson = (Individual*)element;

		if(strcmp(tempPerson->surname,person->surname) == 0 && strcmp(tempPerson->givenName,person->givenName) == 0)
		{

			exitBool = 1;

		}

		element = nextElement(&iterPerson);

	}

	return(tempList);

}


