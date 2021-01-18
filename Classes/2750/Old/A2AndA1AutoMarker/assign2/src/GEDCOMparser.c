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


	void* temp;

	if(familyRecord == NULL || person == NULL || (*compare) == NULL)
	{

		return (NULL);

	}

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

/** Function for validating an existing GEDCOM object
 *@pre GEDCOM object exists and is not null
 *@post GEDCOM object has not been modified in any way
 *@return the error code indicating success or the error encountered when validating the GEDCOM
 *@param obj - a pointer to a GEDCOMobject struct
 **/
ErrorCode validateGEDCOM(const GEDCOMobject* obj)
{

	ErrorCode temp;

	temp = OK;

	if(obj == NULL)
	{

		temp = INV_GEDCOM;
		return(temp);

	}

	if(obj->header == NULL)
	{

		temp = INV_GEDCOM;
		return(temp);

	}

	if(obj->header->source == NULL)
	{
		//printf("HERE\n");
		temp = INV_HEADER;
		return(temp);

	}

	if(strlen(obj->header->source ) > 200)
	{

		temp = INV_RECORD;
		return(temp);

	}

	if(obj->header->submitter == NULL)
	{

		temp = INV_HEADER;
		return(temp);

	}

	if(obj->header->gedcVersion < 0.0)
	{

		temp = INV_HEADER;
		return(temp);
		
	}

	if(obj->submitter == NULL)
	{

		temp = INV_GEDCOM;
		return(temp);

	}
/*
	if(obj->submitter->address == NULL)
	{

		temp = INV_RECORD;
		return(temp);

	}*/
/*
	if(strlen(obj->submitter->address) > 200)
	{

		temp = INV_RECORD;
		return(temp);
		
	}
*/
	if(obj->submitter->submitterName == NULL)
	{
		
		temp = INV_RECORD;
		return(temp);

	}

	if(strlen(obj->submitter->submitterName) > 200)
	{

		temp = INV_RECORD;
		return(temp);
		
	}

	if(obj->header->encoding == ANSEL || obj->header->encoding == UTF8 || obj->header->encoding == UNICODE || obj->header->encoding == ASCII)
	{

		return(temp);

	} 
	else
	{
		
		temp = INV_HEADER;
		return(temp);
		
	}
	
	return(temp);

}

/** Function to writing a GEDCOMobject into a file in GEDCOM format.
 *@pre GEDCOMobject object exists, is not null, and is valid
 *@post GEDCOMobject has not been modified in any way, and a file representing the
 GEDCOMobject contents in GEDCOM format has been created
 *@return the error code indicating success or the error encountered when parsing the calendar
 *@param obj - a pointer to a GEDCOMobject struct
 **/
GEDCOMerror writeGEDCOM(char* fileName, const GEDCOMobject* obj)
{

	GEDCOMerror error;

	FILE * ptr;

	ListIterator indivIter;
	ListIterator famIter;
	ListIterator stringIndivIter;
	ListIterator stringFamIter;

	List indivList;
	List famList;

	void* element;

	char* string;
	char* tempString;
	char* stringIndiv;
	char* stringFam;
	char* fileNameExt;

	int refIndiv;
	int refFams;

	error.type = OK;
	error.line = 0;

	refIndiv = 0;
	refFams = 0;

	error.type = validateGEDCOM(obj);

	if(error.type != OK)
	{

		error.type = WRITE_ERROR;

		return(error);

	}

	if(fileName == NULL)
	{

		error.type = WRITE_ERROR;

		return(error);

	}

	fileNameExt = malloc(sizeof(char)*(strlen(fileName)+15));

	strcpy(fileNameExt,fileName);

	if(fileName[strlen(fileName)-4] != '.' || fileName[strlen(fileName)-3] != 'g' || fileName[strlen(fileName)-2] != 'e' || fileName[strlen(fileName)-1] != 'd')
	{

		strcat(fileNameExt,".ged");

	}



	string = malloc(sizeof(char)*500);

	/* Dealing with the head*/
	strcpy(string,"0 HEAD\n");
	/*Source related things*/
	string = realloc(string,sizeof(char)*(strlen(string)+(strlen(obj->header->source)*2)+50));
	strcat(string,"1 SOUR ");
	strcat(string,obj->header->source);
	strcat(string,"\n2 NAME ");
	strcat(string,obj->header->source);
	strcat(string,"\n");

	/*GEDC RElated things*/
	string = realloc(string,sizeof(char)*(strlen(string)+50));
	tempString = malloc(sizeof(char)*20);
	strcat(string,"1 GEDC\n2 FORM LINEAGE-LINKED\n2 VERS ");
	snprintf(tempString,10,"%f",obj->header->gedcVersion);
	strcat(string,tempString);
	strcat(string,"\n");
	free(tempString);

	/*Character set*/
	string = realloc(string,sizeof(char)*(strlen(string)+50));
	strcat(string,"1 CHAR ");
	if(obj->header->encoding == ANSEL)
	{

		strcat(string,"ANSEL\n");

	} 
	else if(obj->header->encoding == UTF8)
	{

		strcat(string,"UTF-8\n");

	}
	else if(obj->header->encoding == UNICODE)
	{

		strcat(string,"UNICODE\n");

	}
	else if(obj->header->encoding == ASCII)
	{

		strcat(string,"ASCII\n");

	}
	/*Done with Header*/

	/*Dealing with submitter*/
	strcat(string,"1 SUBM @SUB1@\n0 @SUB1@ SUBM\n1 NAME ");

	string = realloc(string,sizeof(char)*(strlen(string)+(strlen(obj->submitter->submitterName))+65));

	strcat(string,obj->submitter->submitterName);
	strcat(string,"\n");

	if(obj->submitter->address != NULL)
	{

		string = realloc(string,sizeof(char)*(strlen(string)+(strlen(obj->submitter->address))+65));
		strcat(string,"1 ADDR ");
		strcat(string,obj->submitter->address);
		strcat(string,"\n");

	}
	/*Done with Submitter*/

	indivIter = createIterator(obj->individuals);
	element = nextElement(&indivIter);

	indivList = initializeList(&returnListFile,&deleteListFile,&compareListFile);

	while(element != NULL)
	{

		refIndiv++;

		stringIndiv = writeIndividual((Individual*)element,refIndiv);

		insertBack(&indivList,stringIndiv);

		element = nextElement(&indivIter);

	}

	

	famList = initializeList(&returnListFile,&deleteListFile,&compareListFile); 
	famIter = createIterator(obj->families);
	element = nextElement(&famIter);

	while(element != NULL)
	{

		refFams++;
		stringFam = writeFamily((Family*)element,obj->individuals,indivList,refFams);
		insertBack(&famList,stringFam);
		element = nextElement(&famIter);

	}

	stringIndivIter = createIterator(indivList);
	stringFamIter = createIterator(famList);

	element = nextElement(&stringIndivIter);

	while(element != NULL)
	{

		tempString = (char*)element;

		string = realloc(string,sizeof(char)*(strlen(string)+(strlen(tempString)+50)));
		strcat(string,tempString);
		element = nextElement(&stringIndivIter);

	}

	element = nextElement(&stringFamIter);

	while(element != NULL)
	{

		tempString = (char*)element;

		string = realloc(string,sizeof(char)*(strlen(string)+(strlen(tempString)+50)));
		strcat(string,tempString);
		element = nextElement(&stringFamIter);

	}

	strcat(string,"0 TRLR\n");


	
	clearList(&indivList);
	clearList(&famList);

	ptr =  fopen(fileNameExt,"w");

	if(ptr != NULL)
	{

		fputs(string,ptr);

	}
	else
	{

		error.type = WRITE_ERROR;

	}

	free(string);

	free(fileNameExt);

	fclose(ptr);

	return(error);

}

/** Function to return a list of up to N generations of descendants of an individual in a GEDCOM
 *@pre GEDCOM object exists, is not null, and is valid
 *@post GEDCOM object has not been modified in any way, and a list of descendants has been created
 *@return a list of descendants.  The list may be empty.  All list members must be of type List.    *@param familyRecord - a pointer to a GEDCOMobject struct
 *@param person - the Individual record whose descendants we want
 *@param maxGen - maximum number of generations to examine (must be >= 1)
 **/
List getDescendantListN(const GEDCOMobject* familyRecord, const Individual* person, unsigned int maxGen)
{

	List temp;

	ListIterator iterPerson;

	Individual* tempPerson;

	void* element;

	int exitBool; 

	iterPerson = createIterator(familyRecord->individuals);

	element = nextElement(&iterPerson);

	exitBool = 0;

	if(familyRecord == NULL)
	{

		return(temp);

	}

	if(person == NULL)
	{

		return(temp);

	}

	if(person->surname == NULL )
	{

		return(temp);

	}

	if(person->givenName == NULL )
	{
		return(temp);

	}

	if(maxGen < 0)
	{

		return(temp);

	}	
	if(maxGen == 0)
	{

		maxGen = getLength(familyRecord->individuals);
		
	}

	temp = initializeList(&printGeneration,&deleteGeneration,&compareGenerations);

	while(element != NULL && exitBool == 0)
	{

		tempPerson = (Individual*)element;

		if(tempPerson->surname != NULL && tempPerson->givenName != NULL)
		{

			if(strcmp(tempPerson->surname,person->surname) == 0 && strcmp(tempPerson->givenName,person->givenName) == 0)
			{

				exitBool = 1;

			}

		}

		element = nextElement(&iterPerson);

	}

	if(exitBool == 1)
	{

		descendantList(tempPerson,&temp,maxGen,0);

	}

	return(temp);

}

/** Function to return a list of up to N generations of ancestors of an individual in a GEDCOM
 *@pre GEDCOM object exists, is not null, and is valid
 *@post GEDCOM object has not been modified in any way, and a list of ancestors has been created
 *@return a list of ancestors.  The list may be empty.
 *@param familyRecord - a pointer to a GEDCOMobject struct
 *@param person - the Individual record whose descendants we want
 *@param maxGen - maximum number of generations to examine (must be >= 1)
 **/
List getAncestorListN(const GEDCOMobject* familyRecord, const Individual* person, int maxGen)
{


	List temp;

	ListIterator iterPerson;

	Individual* tempPerson;

	void* element;

	int exitBool; 

	iterPerson = createIterator(familyRecord->individuals);

	element = nextElement(&iterPerson);

	exitBool = 0;

	if(familyRecord == NULL)
	{

		return(temp);

	}

	if(person == NULL)
	{

		return(temp);

	}

	if(person->surname == NULL )
	{

		return(temp);

	}

	if(person->givenName == NULL )
	{
		return(temp);

	}

	if(maxGen < 0)
	{

		return(temp);

	}	
	if(maxGen == 0)
	{

		maxGen = getLength(familyRecord->individuals);
		
	}

	temp = initializeList(&printGeneration,&deleteGeneration,&compareGenerations);

	while(element != NULL && exitBool == 0)
	{

		tempPerson = (Individual*)element;

		if(tempPerson->surname != NULL && tempPerson->givenName != NULL)
		{

			if(strcmp(tempPerson->surname,person->surname) == 0 && strcmp(tempPerson->givenName,person->givenName) == 0)
			{

				exitBool = 1;

			}

		}

		element = nextElement(&iterPerson);

	}

	if(exitBool == 1)
	{

		ancestorsList(tempPerson,&temp,maxGen,0);

	}

	return(temp);

}

/** Function for converting an Individual struct into a JSON string
 *@pre Individual exists, is not null, and is valid
 *@post Individual has not been modified in any way, and a JSON string has been created
 *@return newly allocated JSON string.  May be NULL.
 *@param ind - a pointer to an Individual struct
 **/
char* indToJSON(const Individual* ind)
{

	char* string = malloc(sizeof(char)*500);

	if (ind == NULL)
	{

		strcpy(string,"\"");
		strcat(string,"\"");

		return(string);

	}

	strcpy(string,"{\"givenName\":\"");

	if(ind->givenName != NULL)
	{

		string = realloc(string,sizeof(char)*(strlen(string)+strlen(ind->givenName)+50));
		strcat(string,ind->givenName);

	}

	strcat(string,"\",\"surname\":\"");
	if(ind->surname != NULL)
	{

		string = realloc(string,sizeof(char)*(strlen(string)+strlen(ind->surname)+50));
		strcat(string,ind->surname);
		
	}

	strcat(string,"\"}");

	return(string);

}

/** Function for creating an Individual struct from an JSON string
 *@pre String is not null, and is valid
 *@post String has not been modified in any way, and an Individual struct has been created
 *@return a newly allocated Individual struct.  May be NULL.
 *@param str - a pointer to a JSON string
 **/
Individual* JSONtoInd(const char* str)
{

	char* tempString;
	char* token;
	char* storeString;

	Individual* tempIndiv;

	if(str == NULL)
	{

		return(NULL);

	}

	tempString = malloc(sizeof(char)*(strlen(str)+5));
	strcpy(tempString,str);

	if(tempString[0] != '{' || tempString[strlen(tempString)-1] != '}')
	{

		free(tempString);
		return(NULL);

	}

	if(tempString[1] != '"' || tempString[strlen(tempString)-2] != '"')
	{

		free(tempString);
		return(NULL);

	}

	tempIndiv = malloc(sizeof(Individual));
	tempIndiv->otherFields = initializeList(&printField,&deleteField,&compareFields);
	tempIndiv->events = initializeList(&printEvent,&deleteEvent,&compareEvents);
	tempIndiv->families = initializeList(&printFamily,&dummyDelete,&compareFamilies);
	tempIndiv->surname = NULL;
	tempIndiv->givenName = NULL;

	token = strtok(tempString,":");

	if(strcmp("{\"givenName\"",token) != 0 || token == NULL)
	{

		deleteIndividual((void*)tempIndiv);
		free(tempString);
		return(NULL);

	}

	token = strtok(NULL,",");

	if(token[0] != '"' || token[strlen(token)-1] != '"' || token == NULL)
	{

		deleteIndividual((void*)tempIndiv);
		free(tempString);

		return(NULL);

	}

	storeString = malloc(sizeof(char)*(strlen(token)+5));

	strcpy(storeString,token);

	for (int i = 0; i < strlen(storeString)-1; i++)
	{
		
		storeString[i] = storeString[i+1];

	}

	storeString[strlen(storeString)-2] = '\0';

	tempIndiv->givenName = malloc(sizeof(char)*(strlen(token)+5));

	strcpy(tempIndiv->givenName,storeString);

	free(storeString);

	token = strtok(NULL,":");

	if(strcmp("\"surname\"",token) != 0 || token == NULL)
	{

		deleteIndividual((void*)tempIndiv);
		free(tempString);
		return(NULL);

	}

	token = strtok(NULL,"}");

	if(token[0] != '"' || token[strlen(token)-1] != '"' || token == NULL)
	{

		deleteIndividual((void*)tempIndiv);
		free(tempString);
		return(NULL);

	}

	storeString = malloc(sizeof(char)*(strlen(token)+5));

	strcpy(storeString,token);

	for (int i = 0; i < strlen(storeString)-1; i++)
	{
		
		storeString[i] = storeString[i+1];

	}

	storeString[strlen(storeString)-2] = '\0';

	tempIndiv->surname = malloc(sizeof(char)*(strlen(token)+5));

	strcpy(tempIndiv->surname,storeString);

	free(storeString);

	free(tempString);

	return(tempIndiv);

}

/** Function for creating a GEDCOMobject struct from an JSON string
 *@pre String is not null, and is valid
 *@post String has not been modified in any way, and a GEDCOMobject struct has been created
 *@return a newly allocated GEDCOMobject struct.  May be NULL.
 *@param str - a pointer to a JSON string
 **/
GEDCOMobject* JSONtoGEDCOM(const char* str)
{

	GEDCOMobject* obj; 

	Header* tempHeader;
	Submitter* tempSubmit;

	char* tempString;
	char* token;
	char* submitterName;
	char* storeString;

	if(str == NULL)
	{

		return(NULL);

	}

	tempString = malloc(sizeof(char)*(strlen(str)+5));
	strcpy(tempString,str);
	/* Checks to ensure that there is quotes and stuff*/
	if(tempString[0] != '{' || tempString[strlen(tempString)-1] != '}')
	{

		free(tempString);
		return(NULL);

	}

	if(tempString[1] != '"' || tempString[strlen(tempString)-2] != '"')
	{

		free(tempString);
		return(NULL);

	}
	/*Seperates and looks at the sources*/

	token = strtok(tempString,":");

	if(strcmp("{\"source\"",token) != 0 || token == NULL)
	{

		free(tempString);
		return(NULL);

	}

	token = strtok(NULL,",");

	tempHeader = malloc(sizeof(Header));
	

	tempHeader->otherFields = initializeList(&printField,&deleteField,&compareFields);
	storeString = malloc(sizeof(char)*(strlen(token)+5));
	strcpy(storeString,token);

	for (int i = 0; i < strlen(storeString)-1; i++)
	{
		
		storeString[i] = storeString[i+1];

	}

	storeString[strlen(storeString)-2] = '\0';

	strcpy(tempHeader->source,storeString);
	free(storeString);
	/*Gets the next field, Version*/

	token = strtok(NULL,":");
	if(strcmp("\"gedcVersion\"",token) != 0 || token == NULL)
	{

		free(tempString);
		free(tempHeader);

		return(NULL);

	}

	token = strtok(NULL,",");
	/*Storesin a string with is converted to a float*/
	storeString = malloc(sizeof(char)*(strlen(token)+5));

	strcpy(storeString,token);

	for (int i = 0; i < strlen(storeString)-1; i++)
	{
		
		storeString[i] = storeString[i+1];

	}

	storeString[strlen(storeString)-2] = '\0';
	tempHeader->gedcVersion = atof(storeString);

	free(storeString);

	/*Looks at the encoding*/
	token = strtok(NULL,":");

	if(strcmp("\"encoding\"",token) != 0 || token == NULL)
	{

		free(tempString);
		free(tempHeader);

		return(NULL);

	}

	token = strtok(NULL,",");

	/*Finds the encoding type*/

	if(strcmp(token,"\"ANSEL\"") == 0)
	{

		tempHeader->encoding = ANSEL;

	}
	else if(strcmp(token,"\"UTF-8\"") == 0)
	{

		tempHeader->encoding = UTF8;

	}
	else if(strcmp(token,"\"UNICODE\"") == 0)
	{

		tempHeader->encoding = UNICODE;

	}
	else if(strcmp(token,"\"ASCII\"") == 0)
	{

		tempHeader->encoding = ASCII;
				
	}

	/*Get the submitter Name*/

	token = strtok(NULL,":");

	if(strcmp("\"submitterName\"",token) != 0 || token == NULL)
	{

		free(tempString);
		free(tempHeader);

		return(NULL);

	}

	token = strtok(NULL,",");

	submitterName = malloc(sizeof(char)*(strlen(token)+5));

	strcpy(submitterName,token);

	/*Gets the submitter address*/

	token = strtok(NULL,":");

	if(strcmp("\"submitterAddress\"",token) != 0 || token == NULL)
	{

		free(submitterName);
		free(tempString);
		free(tempHeader);

		return(NULL);

	}

	token = strtok(NULL,",");

	tempSubmit = malloc(sizeof(Submitter)+sizeof(char)*(strlen(token)+5));

	storeString = malloc(sizeof(char)*(strlen(token)+5));
	strcpy(storeString,token);

	for (int i = 0; i < strlen(storeString)-1; i++)
	{
		
		storeString[i] = storeString[i+1];

	}

	storeString[strlen(storeString)-3] = '\0';

	/*Throw the values in the submitter fields*/

	strcpy(tempSubmit->submitterName,submitterName);

	strcpy(tempSubmit->address,storeString);

	free(storeString);

	tempSubmit->otherFields = initializeList(&printField,&deleteField,&compareFields); 

	obj = malloc(sizeof(GEDCOMobject));

	obj->header = tempHeader;
	obj->submitter = tempSubmit;

	obj->families = initializeList(&printFamily,&deleteFamily,&compareFamilies); 
	obj->individuals = initializeList(&printField,&deleteField,&compareFields);

	tempHeader->submitter = tempSubmit;

	free(submitterName);
	free(tempString);

	return(obj);

}

/** Function for adding an Individual to a GEDCCOMobject
 *@pre both arguments are not NULL and valid
 *@post Individual has not been modified in any way, and its address had been added to GEDCOMobject's individuals list
 *@return void
 *@param obj - a pointer to a GEDCOMobject struct
 *@param toBeAdded - a pointer to an Individual struct
**/
void addIndividual(GEDCOMobject* obj, const Individual* toBeAdded)
{

	if(obj == NULL || toBeAdded == NULL)
	{

		return;

	}

	insertBack(&obj->individuals,(void*)toBeAdded);

}

/** Function for converting a list of Individual structs into a JSON string
 *@pre List exists, is not null, and has been initialized
 *@post List has not been modified in any way, and a JSON string has been created
 *@return newly allocated JSON string.  May be NULL.
 *@param iList - a pointer to a list of Individual structs
 **/
char* iListToJSON(List iList)
{

	char* string;
	char* tempString;

	ListIterator iter;

	void* element;

	string = malloc(sizeof(char)*10);

	strcpy(string,"[");

	iter = createIterator(iList);

	element = nextElement(&iter);

	if(element == NULL)
	{

		strcat(string,"]");

		return(string);

	}

	tempString = indToJSON((Individual*)element);

	string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempString)+5));

	strcat(string,tempString);

	element = nextElement(&iter);

	free(tempString);

	while(element != NULL)
	{

		strcat(string,",");
		tempString = indToJSON((Individual*)element);

		string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempString)+5));

		strcat(string,tempString);

		element = nextElement(&iter);

		free(tempString);

	}

	string = realloc(string,sizeof(char)*(strlen(string)+5));

	strcat(string,"]");

	return(string);

}

/** Function for converting a list of lists of Individual structs into a JSON string
 *@pre List exists, is not null, and has been initialized
 *@post List has not been modified in any way, and a JSON string has been created
 *@return newly allocated JSON string.  May be NULL.
 *@param gList - a pointer to a list of lists of Individual structs
 **/
char* gListToJSON(List gList)
{

	ListIterator listIter;

	List* tmp;

	List tempList;

	char* string;
	char* tempString;

	void* element;

	string = malloc(sizeof(char)*100);

	strcpy(string,"[");

	listIter = createIterator(gList);

	element = nextElement(&listIter);

	while(element != NULL)
	{

		tmp = (List*)element;
		tempList = *tmp;

		tempString = iListToJSON((tempList));

		string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempString)+5));
		strcat(string,tempString);
		element = nextElement(&listIter);

	}

	strcat(string,"]");

	return(string);

}


//****************************************** List helper functions added for A2 *******************************************
void deleteGeneration(void* toBeDeleted)
{

	List* tmp;
	List tempList;

	tmp = (List*)toBeDeleted;
	tempList = *tmp;

	clearList(&tempList);

}

int compareGenerations(const void* first,const void* second)
{

	return(0);

}

char* printGeneration(void* toBePrinted)
{

	return("NULL");

}

