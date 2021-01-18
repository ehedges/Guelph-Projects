/*****************************
Evan Hedges 0898140
CIS 2750, W18

Professor: Denis Nikitenko
*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GEDCOMparser.h"
#include "GEDCOMutilities.h"
#include "LinkedListAPI.h"
/*****************
Helper Functions
*****************/

void deleteHeader(Header* tobeDeleted)
{

	clearList(&tobeDeleted->otherFields);
	free(tobeDeleted);

}

void destroySubmitter(Submitter* tobeDeleted)
{

	clearList(&tobeDeleted->otherFields);

}
void deleteIndividualGen(void* toBeDeleted)
{

	if(toBeDeleted == NULL)
	{

		return;

	}

	Individual* temp = (Individual*)toBeDeleted;

	if(temp->givenName != NULL)
	{

		free(temp->givenName);

	}

	if(temp->surname != NULL)
	{

		free(temp->surname);
		
	}

	free(temp);

}

void deleteIndividual(void* toBeDeleted)
{

	if(toBeDeleted == NULL)
	{

		return;

	}

	Individual* temp = (Individual*)toBeDeleted;

	if(temp->givenName != NULL)
	{

		free(temp->givenName);

	}

	if(temp->surname != NULL)
	{

		free(temp->surname);
		
	}

	clearList(&temp->otherFields);
	clearList(&temp->families);
	clearList(&temp->events);
	free(temp);

}

int compareIndividuals(const void* first,const void* second)
{

	Individual* firstIndiv = (Individual*) first;

	Individual* secondIndiv = (Individual*) second;

	if(secondIndiv->surname == NULL)
	{

		return(1);

	}

	if(firstIndiv->surname == NULL)
	{

		return(-1);

	}

	if(strcmp(secondIndiv->surname,firstIndiv->surname) != 0)
	{

		return(strcmp(secondIndiv->surname,firstIndiv->surname));

	}

	if(secondIndiv->givenName == NULL)
	{

		return(1);

	}

	if(firstIndiv->givenName == NULL)
	{

		return(-1);

	}

	if(strcmp(secondIndiv->givenName,firstIndiv->givenName) != 0)
	{

		return(strcmp(secondIndiv->givenName,firstIndiv->givenName));

	}

	return(0);

}

void dummyDelete(void* tobeDeleted)
{



}


/********************************************
Gets an individual, prints out all the fields
********************************************/

char* printIndividual(void* toBePrinted)
{

	Individual* temp;

	ListIterator otherIter;
	ListIterator eventIter;

	void* tempElement;

	Field* tempField;

	char* string;
	char* tempString;

	if(toBePrinted == NULL)
	{

		return("NULL");

	}

	temp = (Individual*) toBePrinted;

	string = malloc(sizeof(char)*(strlen(temp->givenName)+15));
	//First name and last name
	strcpy(string,"Name: ");
	strcat(string,temp->givenName);

	if(temp->surname != NULL)
	{

		if(strcmp(temp->surname,"~NULL~") != 0)
		{
			string = realloc(string,sizeof(char)*(strlen(string)+strlen(temp->surname)+5));
			strcat(string," ");
			strcat(string,temp->surname);

		}

	}

	eventIter = createIterator(temp->events);

	tempElement = nextElement(&eventIter);
	//Prints out events
	while(tempElement != NULL)
	{
		
		tempString = printEvent(tempElement);
		string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempString)+5));
		strcat(string,tempString);
		free(tempString);
		tempElement = nextElement(&eventIter);	

	}

	string = realloc(string,sizeof(char)*(strlen(string)+50));
	strcat(string,"\nOtherFields:\n\t");

	otherIter = createIterator(temp->otherFields);

	tempElement = nextElement(&otherIter);
	//Prints out other fields
	if(tempElement != NULL)
	{

		tempField = (Field*) tempElement;

		if(tempField->tag != NULL)
		{

			string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->tag)+5));

			strcat(string,tempField->tag);

			if(strcmp(tempField->value,"~NULL~") != 0)
			{

				string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->value)+10));

				strcat(string,":");
				strcat(string,tempField->value);
				strcat(string,"\n\t");
				tempElement = nextElement(&otherIter);

			}
		}

	
	}

	while(tempElement != NULL)
	{

		tempField = (Field*) tempElement;

		if(tempField->value != NULL && tempField->tag != NULL)
		{

				string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->tag)+strlen(tempField->value)+10));
				strcat(string,tempField->tag);

				if(strcmp(tempField->value,"~NULL~") != 0)
				{

					string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->value)+5));
					strcat(string,":");
					strcat(string,tempField->value);
					strcat(string,"\n\t");

				}
				else
				{

					strcat(string," ");

				}
	
		}		

		tempElement = nextElement(&otherIter);

	}

	return(string);

}

/******************
Removes \n and \r 
*****************/

void cleanseNewline(char* string)
{

	int offset = 0;
	char* tempString = malloc(sizeof(char)*strlen(string)+5);

	for(int i = 0; i < strlen(string); i++)
	{

		if(string[i] == '\n' || string[i] == '\r')
		{

			string[i] = '\0';

		}

	}

	while(string[offset] == ' ' || string[offset] == '\t')
	{

		offset++;

	}

	for (int i = 0; i <= strlen(string); i++)
	{

		tempString[i] = string[i+offset];

	}

	strcpy(string,tempString);

	free(tempString);

}

/**********************************
Checks string if it is only numbers
**********************************/

int checkNums(char* string)
{

	char numArray[10] = "1234567890";

	for (int i = 0; i < strlen(string); i++)
	{
			
		for (int j = 0; j < 10; j++)
		{

			if(string[i] == numArray[j])
			{

				break;

			}
			else if(j == 10)
			{

				return(1);

			}

		}
			
	}

	return(0);

}

/**********************************************
Creates a single individual, adds it to the list

***********************************************/

GEDCOMerror initIndiv(char* tempRef,List fileList,GEDCOMobject** obj,int line,ListIterator iter)
{

	GEDCOMerror error;

	Individual* tempIndiv;

	Field* tempField;

	char* token;	
	char* string;
	char* getString;
	char* storeString;

	void* temp;

	int* depth;

	int value;
	int validNum;
	int previousValue;
	int personBool;
	int misc;

	value = 0;
	validNum = 0;
	previousValue = 0;
	personBool = 0;

	depth = malloc(sizeof(int));

	error.type = OK;

	tempIndiv = malloc(sizeof(Individual));
	tempIndiv->otherFields = initializeList(&printField,&deleteField,&compareFields);
	tempIndiv->events = initializeList(&printEvent,&deleteEvent,&compareEvents);
	tempIndiv->families = initializeList(&printFamily,&dummyDelete,&compareFamilies);
	tempIndiv->surname = NULL;
	tempIndiv->givenName = NULL;
	tempField = malloc(sizeof(Field));
	tempField->tag = malloc(sizeof(char)*20);
	strcpy(tempField->tag,"REFERENCE");
	tempField->value = malloc(sizeof(char)*strlen(tempRef)+5);
	strcpy(tempField->value,tempRef);

	insertBack(&tempIndiv->otherFields,(void*)tempField);

	temp = nextElement(&iter);
	//Loops until not a person
	while(personBool == 0)
	{

		line++;

		getString = (char*)temp;

		string = malloc(sizeof(char)*(strlen(getString)+5));
		strcpy(string,getString);

		token = strtok(string," ");
		validNum = checkNums(token);
		//Checks valid num
		if(validNum == 0)
		{

			value = atoi(token);
			token = strtok(NULL," ");

			if(value-previousValue > 1)
			{

				error.type = INV_GEDCOM;
				error.line = line;
				free(string);

				return(error);

			}
			else
			{

				previousValue = value;

			}
			//Fills the fields
			if(value == 0)
			{

				personBool = 1;

			}
			else if(strcmp(token,"EVEN") == 0)
			{
				//Creates an event
				depth[0] = value;
				error = listEvents(&(tempIndiv)->events,fileList,line,iter,depth);
				
				if(error.type != OK)
				{

					return(error);

				}

				for(int i = 0; i < (depth[0]-line); i++)
				{

					temp = nextElement(&iter);

				}
			
				
			}
			else if(strcmp("NAME",token) == 0)
			{

				token = strtok(NULL," ");

				tempIndiv->surname = NULL;

				tempIndiv->givenName = malloc(sizeof(char)*(strlen(token)+5));

				if(token[0] == '/' && token[strlen(token)-1] == '/')
				{

					storeString = malloc(sizeof(char)*(strlen(token)+5));

					strcpy(storeString,token);

					for (int i = 0; i < strlen(storeString)-1; i++)
					{
							
						storeString[i] = storeString[i+1];

					}

					storeString[strlen(storeString)-2] = '\0';
					strcpy(tempIndiv->givenName,storeString);

					free(storeString);
				}
				else
				{

					strcpy(tempIndiv->givenName,token);

				}
				
				token = strtok(NULL," ");

				if(token != NULL)
				{

					if(token[0] == '/' && token[strlen(token)-1] == '/')
					{

						storeString = malloc(sizeof(char)*(strlen(token)+5));

						strcpy(storeString,token);

						for (int i = 0; i < strlen(storeString)-1; i++)
						{
							
							storeString[i] = storeString[i+1];

						}

						storeString[strlen(storeString)-2] = '\0';

						tempIndiv->surname = malloc(sizeof(char)*(strlen(storeString)+5));
						strcpy(tempIndiv->surname,storeString);		

						free(storeString);

					}
					else
					{

						tempIndiv->surname = malloc(sizeof(char)*(strlen(token)+5));
						strcpy(tempIndiv->surname,"~NULL~");	

					}

				}


			}
			else if(strcmp("FAMS",token) == 0)
			{
				//Does nothing
				misc = 0;

			}
			else if(strcmp("FAMC",token) == 0)
			{
				//Does nothing
				misc++;

			}
			else
			{
				//Other fields
				tempField = malloc(sizeof(Field));
				tempField->tag = malloc(sizeof(token)*(strlen(token)+5));

				strcpy(tempField->tag,token);

				token = strtok(NULL,"");
				if(token != NULL)
				{

					tempField->value = malloc(sizeof(token)*(strlen(token)+5));
					strcpy(tempField->value,token);

				}
				else
				{

					tempField->value = malloc(sizeof(token)*(strlen("~NULL~")+5));
					strcpy(tempField->value,"~NULL~");

				}

				insertBack(&tempIndiv->otherFields,(void*)tempField);

			}

		}	
		else
		{

			error.type = INV_RECORD;
			error.line = line;

		}

		free(string);

		temp = nextElement(&iter);

	}

	free(depth);

	insertBack(&(*obj)->individuals,(void*)tempIndiv);

	return(error);

}

/********************************
Finds individual records.
********************************/

GEDCOMerror listIndividuals(GEDCOMobject** obj, List fileList, int line)
{

	GEDCOMerror error;
	ListIterator iter;

	void* temp;

	char* string;
	char* token;
	char* tempRef;
	char* getString;

	int value;
	int validNum;
	int previousValue;

	value = 0;
	validNum = 0;
	previousValue = 0;

	iter = createIterator(fileList);
	error.type = OK;
	error.line = 0;

	temp = nextElement(&iter);

	string = (char*)temp;

	if(temp == NULL)
	{
		
		error.type = INV_GEDCOM;

		return(error);

	}

	(*obj)->individuals  = initializeList(&printIndividual,&deleteIndividual,&compareIndividuals);
	//Loops through the file list finding the individuals
	while(temp != NULL)
	{

		line++;

		getString = (char*)temp;

		string = malloc(sizeof(char)*(strlen(getString)+5));
		strcpy(string,getString);

		token = strtok(string," ");
		validNum = checkNums(token);

		if(validNum == 0)
		{

			value = atoi(token);
			token = strtok(NULL," ");

			if(value-previousValue > 1)
			{

				error.type = INV_GEDCOM;
				error.line = line;
				free(string);

				return(error);

			}
			else
			{

				previousValue = value;

			}
			//Ensure it is a valid num, then checks to see if it is an individual. 
			if(value == 0)
			{

				if(token[0] == '@'&& token[strlen(token)-1] == '@')
				{

					tempRef = token;
					token = strtok(NULL," ");

				}

				if(strcmp(token,"INDI") == 0)
				{
					
					error = initIndiv(tempRef,fileList,obj,line,iter);

				}

			}

		}

		free(string);
		temp = nextElement(&iter);
		
	}

	return(error);

}

/*****************************
Creates and allocates subitter
*****************************/

GEDCOMerror createSubmitter(GEDCOMobject** obj, List fileList,char* subRef,int line)
{

	Submitter* tempSub;

	GEDCOMerror error;

	Field* tempField;

	ListIterator iter;

	List fields;

	iter = createIterator(fileList);

	void* value;

	char* string;
	char* token;
	char* numString;
	char* tempName;
	char* tempAddress;
	char* lastField;
	char* tempString;

	int checkNum;
	int submitBool;

	submitBool = 0;

	tempAddress = NULL;
	tempName = NULL;

	fields = initializeList(&printField,&deleteField,&compareFields);

	value = nextElement(&iter);

	error.type = OK;
	//Loops through and finds the submitter
	while(value != NULL)
	{

		line++;

		tempString = (char*) value;

		string = malloc(sizeof(char)*(strlen(tempString)+5));	
		strcpy(string,tempString);

		numString = strtok(string," ");
		token = strtok(NULL," ");
		checkNum = checkNums(numString);

		if(checkNum == 0)
		{

			checkNum = atoi(numString);
			//Creates the submitter and puts in the fields
			if(checkNum == 0 && submitBool == 0 && strcmp(subRef,token) == 0)
			{
				
				lastField = strtok(NULL,"");
				if(strcmp(lastField,"SUBM") == 0)
				{

					submitBool = 1;

				}
				
			}
			else if(checkNum == 0 && submitBool == 1)
			{

				submitBool = 0;

			}
			else if(strcmp(token,"ADDR") == 0 && submitBool == 1)
			{

				token = strtok(NULL,"");
				tempAddress = malloc(sizeof(char)*strlen(token)+5);
				strcpy(tempAddress,token);
					

			}
			else if(strcmp(token,"NAME") == 0 && submitBool == 1)
			{

				token = strtok(NULL,"");
				if(strlen(token) < 61)
				{

					tempName = malloc(sizeof(char)*strlen(token)+5);
					strcpy(tempName,token);

				}
				else
				{

					error.type =  INV_RECORD;
					error.line = line;

				}
				
			}
			else if(submitBool == 1)
			{
				//Other Fields
				tempField = malloc(sizeof(Field));
				tempField->tag = malloc(sizeof(token)*(strlen(token)+5));
				strcpy(tempField->tag,token);
				token = strtok(NULL,"");
				tempField->value = malloc(sizeof(token)*(strlen(token)+5));
				strcpy(tempField->value,token);
				insertBack(&fields,(void*)tempField);

			}

		}

		free(string);

		value = nextElement(&iter);

	}


	if(tempAddress != NULL)
	{

		tempSub = malloc(sizeof(Submitter)+sizeof(char)*(strlen(tempAddress)+5));
		strcpy(tempSub->address,tempAddress);
		free(tempAddress);

	}
	else
	{

		tempSub = malloc(sizeof(Submitter)+sizeof(char)*50);
		strcpy(tempSub->address,"EMPTY");

	}


	if(tempName != NULL)
	{

		strcpy(tempSub->submitterName,tempName);

		free(tempName);

	}

	tempSub->otherFields = fields;
	(*obj)->submitter = tempSub;
	(*obj)->header->submitter = tempSub;

	return(error);

}

/***********************
Prints out submitter fields	
***********************/

char* printSubmitter(Submitter* submit)
{

	ListIterator otherIter;

	void* tempElement;

	Field* tempField;

	char* string;

	if(submit == NULL)
	{

		return("NULL");

	}

	string = malloc(sizeof(char)*(strlen(submit->submitterName)+15));

	strcpy(string,"Submitter: ");
	strcat(string,submit->submitterName);
	strcat(string,"\n");

	if(strcmp("EMPTY",submit->address) != 0)
	{

		string = realloc(string,sizeof(char)*(strlen(string)+strlen(submit->address)+15));
		strcat(string,"Address: ");
		strcat(string,submit->address);
		strcat(string,"\n");

	}

	otherIter = createIterator(submit->otherFields);

	tempElement = nextElement(&otherIter);
	//Prints other fields
	if(tempElement != NULL)
	{

		tempField = (Field*) tempElement;

		if(tempField->tag != NULL)
		{

			string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->tag)+5));

			strcat(string,tempField->tag);

			if(strcmp(tempField->value,"~NULL~") != 0)
			{

				string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->value)+10));

				strcat(string,":");
				strcat(string,tempField->value);
				strcat(string,"\n");
				tempElement = nextElement(&otherIter);

			}
		}

	
	}

	while(tempElement != NULL)
	{

		tempField = (Field*) tempElement;

		if(tempField->value != NULL && tempField->tag != NULL)
		{

				string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->tag)+strlen(tempField->value)+10));
				strcat(string,tempField->tag);

				if(strcmp(tempField->value,"~NULL~") != 0)
				{

					string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->value)+5));
					strcat(string,":");
					strcat(string,tempField->value);
					strcat(string,"\n");

				}
				else
				{

					strcat(string," ");

				}
	
		}		

		tempElement = nextElement(&otherIter);

	}

	return(string);

}

/***********************
Finds the family records
***********************/

GEDCOMerror listFamily(GEDCOMobject** obj, List fileList,int line)
{

	GEDCOMerror error;
	ListIterator iter;

	void* temp;

	char* string;
	char* token;
	char* tempRef;

	int validNum;
	int value;
	int previousValue;

	iter = createIterator(fileList);
	error.type = OK;
	error.line = 0;

	temp = nextElement(&iter);

	(*obj)->families = initializeList(&printFamily,&deleteFamily,&compareFamilies);

	previousValue = 0;

	if(temp == NULL)
	{

		/*Double checkl error codes*/
		error.type = INV_GEDCOM;
		error.line = line;
		return(error);

	}
	//Finds the family 
	while(temp != NULL)
	{

		line++;

		string = (char*)temp;		
		token = strtok(string," ");
			
		validNum = checkNums(token);

		if(validNum == 0)
		{

			value = atoi(token);
			token = strtok(NULL," ");
			
			if(value-previousValue > 1)
			{

				error.type = INV_GEDCOM;
				error.line = line;
				free(string);

				return(error);

			}
			else
			{

				previousValue = value;

			}

			if(value == 0)
			{				
				
				if(token[0] == '@'&& token[strlen(token)-1] == '@')
				{

					tempRef = token;
					token = strtok(NULL," ");

				}

				if(strcmp(token,"FAM") == 0)
				{

					error = initFam(tempRef,fileList,obj,line,iter);			

				}


			}

		}

		temp = nextElement(&iter);
		
	}

/*

*/
	return(error);



}

void deleteFamily(void* toBeDeleted)
{

	Family* temp = (Family*)toBeDeleted;
	clearList(&temp->otherFields);
	clearList(&temp->children);
	clearList(&temp->events);
	free(temp);

}

int compareFamilies(const void* first,const void* second)
{

	return(0);

}
/***********************************************
Returns string of family, includes individuals
***********************************************/
char* printFamily(void* toBePrinted)
{

	ListIterator childIter;

	Family* fam;

	Individual* tempIndiv;

	char* string;
	char* tempString;

	void* children;

	fam = (Family*) toBePrinted;

	string = malloc(sizeof(char)*100);

	strcpy(string,"Family:\nHusband \n");
	//See if the husband exist and prints
	if(fam->husband != NULL)
	{

		tempString = printIndividual(fam->husband);
		string = realloc(string,sizeof(char)*(strlen(tempString)+strlen(string)+50));
		strcat(string,tempString);

		free(tempString);

	}
	else
	{
		string = realloc(string,sizeof(char)*(strlen(string)+50));
		strcat(string,"NONE\n");	

	}

	strcat(string,"\nWife \n");
	//See if the husband exist and prints
	if(fam->wife != NULL)
	{

		tempString = printIndividual(fam->wife);
		string = realloc(string,sizeof(char)*(strlen(tempString)+strlen(string)+50));
		strcat(string,tempString);
		free(tempString);

	}
	else
	{

		string = realloc(string,sizeof(char)*(strlen(string)+50));
		strcat(string,"NONE\n");	

	}

	
	strcat(string,"\nChildren:\n");

	childIter = createIterator(fam->children);

	children = nextElement(&childIter);
	//See if the children exist and prints
	if(children == NULL)
	{

		string = realloc(string,sizeof(char)*(strlen(string)+50));
		strcat(string,"NONE\n");

	}

	while(children != NULL)
	{

		tempIndiv = (Individual*)children;

		tempString = printIndividual(tempIndiv);

		string = realloc(string,sizeof(char)*(strlen(tempString)+strlen(string)+15));
		strcat(string,tempString);
		strcat(string,"\n");

		free(tempString);

		children = nextElement(&childIter);

	}

	strcat(string,"\n\n");

	return(string);

}

/*******************************************
Creates the family, links individuals as well
*******************************************/

GEDCOMerror initFam(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter)
{

	GEDCOMerror error;

	Family* tempFam;

	Field* tempField;

	Individual* indiv;

	char* token;	
	char* string;
	char* getString;

	int* depth;

	void* temp;

	int value = 0;
	int validNum = 0;
	int previousValue = 0;
	int famBool = 0;

	depth = malloc(sizeof(int));

	tempFam = malloc(sizeof(Family)*1);

	tempFam->husband = NULL;
	tempFam->wife = NULL;
	tempFam->children = initializeList(&printIndividual,&dummyDelete,&compareFields);
	tempFam->events = initializeList(&printEvent,&deleteEvent,&compareEvents);
	tempFam->otherFields = initializeList(&printField,&deleteField,&compareFields);

	error.type = OK;

	temp = nextElement(&iter);
	//Loops through creates a family
	while(famBool == 0)
	{

		line++;

		getString = (char*)temp;		
		string = malloc(sizeof(char)*(strlen(getString)+5));
		strcpy(string,getString);
		token = strtok(string," ");
		validNum = checkNums(token);

		if(validNum == 0)
		{

			value = atoi(token);
			token = strtok(NULL," ");

			if(value-previousValue > 1)
			{

				error.type = INV_GEDCOM;
				error.line = line;
				free(string);

				return(error);

			}
			else
			{

				previousValue = value;

			}
			//Finds the members, wife, husband or child and links the family to the person
			if(value == 0)
			{

				famBool = 1;

			}
			else if(strcmp("WIFE",token) == 0)
			{

				token = strtok(NULL," ");
				tempFam->wife = getPerson(token,obj);
				insertBack(&tempFam->wife->families,(void*)tempFam);

			}
			else if(strcmp("HUSB",token) == 0)
			{

				token = strtok(NULL," ");
				tempFam->husband = getPerson(token,obj);
				insertBack(&tempFam->husband->families,(void*)tempFam);

			}
			else if(strcmp("CHIL",token) == 0)
			{

				token = strtok(NULL," ");

				indiv = (Individual*)getPerson(token,obj);
				insertBack(&indiv->families,(void*)tempFam);
				insertBack(&tempFam->children,indiv);				

			}
			else if(strcmp(token,"EVEN") == 0)
			{
				//Creates an event
				depth[0] = value;
				error = listEvents(&(tempFam)->events,fileList,line,iter,depth);
				
				if(error.type != OK)
				{

					return(error);

				}

				for(int i = 0; i < (depth[0]-line); i++)
				{

					temp = nextElement(&iter);

				}
			
				
			}
			else
			{
				//Other Fields
				tempField = malloc(sizeof(Field));
				tempField->tag = malloc(sizeof(token)*(strlen(token)+5));

				strcpy(tempField->tag,token);

				token = strtok(NULL,"");
				if(token != NULL)
				{

					tempField->value = malloc(sizeof(token)*(strlen(token)+5));
					strcpy(tempField->value,token);

				}
				else
				{

					tempField->value = malloc(sizeof(token)*(strlen("~NULL~")+5));
					strcpy(tempField->value,"~NULL~");

				}

				insertBack(&tempFam->otherFields,(void*)tempField);

			}

		}	
		else
		{

			error.type = INV_RECORD;
			error.line = line;

		}

		free(string);

		temp = nextElement(&iter);

	}

	insertBack(&(*obj)->families,tempFam);
	free(depth);
	return(error);


}

/***************************
Finds a person
***************************/

Individual* getPerson(char* token,GEDCOMobject** obj)
{
	//Finds a person
	ListIterator indivIter;

	Field* frontField;

	Individual* tempIndiv;

	void* findIndiv;
	void* getField;

	char* indivRef;

	indivIter = createIterator((*obj)->individuals);

	findIndiv = nextElement(&indivIter);

	while(findIndiv  != NULL)
	{
					
		tempIndiv = (Individual*)findIndiv;
		getField = getFromFront(tempIndiv->otherFields);

		frontField = (Field*) getField;

		indivRef = frontField->value;

		if(strcmp(indivRef,token) == 0)
		{

			return(tempIndiv);

		}

			findIndiv = nextElement(&indivIter);

		}

	return(NULL);

}

/***************************************************
Finds and creates events, puts it in individual list
***************************************************/

GEDCOMerror listEvents(List* list, List fileList, int line, ListIterator iter,int* depth)
{

	GEDCOMerror error;

	Event* tempEvent;

	Field* tempField;

	void* temp;

	char* string;
	char* token;
	char* getString;

	int value;
	int validNum;
	int previousValue;

	value = 0;
	validNum = depth[0];
	previousValue = depth[0];

	tempEvent = malloc(sizeof(Event));
	tempEvent->otherFields = initializeList(&printField,&deleteField,&compareFields);
	tempEvent->date = NULL;
	tempEvent->place = NULL;

	error.type = OK;
	error.line = 0;

	temp = nextElement(&iter);

	string = (char*)temp;
	//Loops through creates an event
	while(temp != NULL)
	{

		line++;
		
		getString = (char*)temp;

		string = malloc(sizeof(char)*(strlen(getString)+5));
		strcpy(string,getString);
		token = strtok(string," ");
		validNum = checkNums(token);
		
		if(validNum == 0)
		{

			value = atoi(token);
			token = strtok(NULL," ");

			if(value-previousValue > 1)
			{

				error.type = INV_GEDCOM;
				error.line = line;
				free(string);

				return(error);

			}

			if(value <= depth[0])
			{
				
				insertBack(list,(void*)tempEvent);
				free(string);
				depth[0] = line-1;

				return(error);

			}
			else
			{

				previousValue = value;

			}
			if(strcmp(token,"TYPE") == 0)
			{
		
				token = strtok(NULL,"");
				if(strlen(token) > 5)
				{

					error.type = INV_RECORD;
					error.line = line;

				}
				strcpy(tempEvent->type,token);
		
			}
			else if(strcmp(token,"DATE") == 0)
			{

				token = strtok(NULL,"");
				tempEvent->date = malloc(sizeof(char)*(strlen(token)+5));
				strcpy(tempEvent->date,token);

			}
			else if(strcmp(token,"PLAC") == 0)
			{

				token = strtok(NULL,"");
				tempEvent->place = malloc(sizeof(char)*(strlen(token)+5));
				strcpy(tempEvent->place,token);

			}
			else
			{
				//Otherfields
				tempField = malloc(sizeof(Field));
				tempField->tag = malloc(sizeof(token)*(strlen(token)+5));
				strcpy(tempField->tag,token);
				token = strtok(NULL,"");

				if(token != NULL)
				{

					tempField->value = malloc(sizeof(token)*(strlen(token)+5));
					strcpy(tempField->value,token);

				}
				else
				{

					tempField->value = malloc(sizeof(token)*(strlen("~NULL~")+5));
					strcpy(tempField->value,"~NULL~");

				}

				insertBack(&tempEvent->otherFields,(void*)tempField);	

			}	

		}
		else
		{

			free(string);
			return(error);

		}

		free(string);
		temp = nextElement(&iter);
		
	}

	depth[0] = line-1;
	insertBack(list,(void*)tempEvent);

	return(error);

}
/**************************************
Prints events
**************************************/

char* printEvent(void* toBePrinted)
{
	
	ListIterator iter;
 
	Field* tempField;

	Event* tempEvent;

	char* string;

	void* tempElement;

	tempEvent = (Event*) toBePrinted;

	iter = createIterator(tempEvent->otherFields);

	tempEvent = (Event*) toBePrinted;

	string = malloc(sizeof(char)*(50));

	strcpy(string,"\nEvent: ");

	if(tempEvent->type != NULL)
	{

		strcat(string,"TYPE: ");
		string = realloc(string,(strlen(string)+strlen(tempEvent->type)+10));
		strcat(string,tempEvent->type);
		strcat(string,"\n\t");

	}

	if(tempEvent->date != NULL)
	{

		strcat(string,"Date: ");
		string = realloc(string,(strlen(string)+strlen(tempEvent->date)+10));
		strcat(string,tempEvent->date);
		strcat(string,"\n\t");

	}

	if(tempEvent->place != NULL)
	{

		strcat(string,"Place: ");
		string = realloc(string,(strlen(string)+strlen(tempEvent->place)+10));
		strcat(string,tempEvent->place);
		strcat(string,"\n\t");

	}

	tempElement = nextElement(&iter);
	//Prints otherfields
	while(tempElement != NULL)
	{

		tempField = (Field*) tempElement;

		if(tempField->value != NULL && tempField->tag != NULL)
		{

				string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->tag)+strlen(tempField->value)+10));
				strcat(string,tempField->tag);

				if(strcmp(tempField->value,"~NULL~") != 0)
				{

					string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->value)+5));
					strcat(string,":");
					strcat(string,tempField->value);
					strcat(string,"\n\t");

				}
				else
				{

					strcat(string," ");

				}
	
		}		

		tempElement = nextElement(&iter);

	}

	return(string);

}
/*************************
Prints header
*************************/

char* printHeader(Header* head)
{

	char* string;

	char version[11];

	Field* tempField; 

	ListIterator otherIter;

	void* item;

	string = malloc(sizeof(char)*(strlen(head->source)+100));

	strcpy(string,"Source: ");

	strcat(string,head->source);

	snprintf(version,10,"%f",head->gedcVersion);

	strcat(string,"\n\tVersion: ");
	strcat(string,version);
	strcat(string,"\n\tCharacter Set: ");

	if(head->encoding == ANSEL)
	{

		strcat(string,"ANSEL \n\t");

	}
	else if(head->encoding == UNICODE)
	{

		strcat(string,"UNICODE \n\t");

	}
	else if(head->encoding == UTF8)
	{

		strcat(string,"UTF8 \n\t");

	}
	else if(head->encoding == ASCII)
	{

		strcat(string,"ASCII \n\t");

	}

	strcat(string,"Other Fields:\n\t\t");

	otherIter = createIterator(head->otherFields);

	item = nextElement(&otherIter);

	while(item != NULL)
	{

		tempField = (Field*)item;

		string = realloc(string,sizeof(char)*(strlen(string)+strlen(tempField->tag)+strlen(tempField->value)+10));
		strcat(string,tempField->tag);
		strcat(string,":");
		strcat(string,tempField->value);
		strcat(string,"\n\t\t");
		item = nextElement(&otherIter);

	}

	strcat(string,"\n");

	return(string);

}

void clearReferences(List list)
{

	ListIterator iter;

	Individual* indiv;

	void* item;
	void* delete;

	char* reference;

	reference = malloc(sizeof(char)*15);

	strcpy(reference,"REFERENCE");

	iter = createIterator(list);

	item = nextElement(&iter);

	while(item != NULL)
	{

		indiv = (Individual*)item;

		delete = deleteDataFromList(&(indiv)->otherFields,(void*)reference);

		deleteField(delete);

		item = nextElement(&iter);

	}

	free(reference);

}
