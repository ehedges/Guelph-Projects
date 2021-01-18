#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GEDCOMparser.h"
#include "GEDCOMutilities.h"
#include "LinkedListAPI.h"

void deleteIndividual(void* toBeDeleted)
{

	Individual* temp = (Individual*)toBeDeleted;

	if(temp->givenName == NULL)
	{

		free(temp->givenName);

	}

	if(temp->surname == NULL)
	{

		free(temp->surname);
		
	}

	destroyList(temp ->otherFields);
	destroyList(temp ->families);
	destroyList(temp ->events);

}
int compareIndividuals(const void* first,const void* second)
{

	return(0);

}
char* printIndividual(void* toBePrinted)
{

	Individual* temp;

	ListIterator otherIter;

	void* tempElement;

	Field* tempField;

	char* string;

	if(toBePrinted == NULL)
	{

		return("NULL");

	}

	temp = (Individual*) toBePrinted;

	string = malloc(sizeof(char)*(strlen(temp->givenName)+15));

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
	
	strcat(string,"\n");

	otherIter = createIterator(temp->otherFields);

	tempElement = nextElement(&otherIter);
	tempElement = nextElement(&otherIter);

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

Individual* initIndiv(char* tempRef)
{

	Individual* tempIndiv;

	Field* tempField;

	tempIndiv = malloc(sizeof(Individual));
	tempIndiv->otherFields = initializeList(&printField,&deleteField,&compareFields);
	tempIndiv->surname = NULL;
	tempIndiv->givenName = NULL;
	tempField = malloc(sizeof(Field));
	tempField->tag = malloc(sizeof(char)*20);
	strcpy(tempField->tag,"REFERENCE");
	tempField->value = malloc(sizeof(char)*strlen(tempRef)+5);
	strcpy(tempField->value,tempRef);
	insertBack(&tempIndiv->otherFields,(void*)tempField);

	return(tempIndiv);

}

GEDCOMerror listIndividuals(GEDCOMobject** obj, List fileList, int line)
{

	GEDCOMerror error;
	ListIterator iter;
	ListIterator testing;

	Individual* tempIndiv;

	Field* tempField;

	void* temp;
	void* checking;

	char* string;
	char* token;
	char* tempRef;
	char* getString;

	int value = 0;
	int validNum = 0;
	int previousValue = 0;
	int personBool = 0;

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

	tempIndiv = NULL;

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

			if(value == 0)
			{

				if(token[0] == '@'&& token[strlen(token)-1] == '@')
				{

					tempRef = token;
					token = strtok(NULL," ");

				}

				if(strcmp(token,"INDI") == 0)
				{

					if(tempIndiv != NULL)
					{

						insertBack(&(*obj)->individuals ,tempIndiv);

					}
					
					tempIndiv = initIndiv(tempRef);

					personBool = 1;

				}
				else if(personBool != 0)
				{


					insertBack(&(*obj)->individuals ,tempIndiv);

					personBool = 0;

				}

			} 
			else if(strcmp("NAME",token) == 0 && personBool == 1)
			{

				token = strtok(NULL," ");
				//Token is NULL after this.
				tempIndiv->givenName = malloc(sizeof(char)*(strlen(token)+5));

				strcpy(tempIndiv->givenName,token);

				token = strtok(NULL," ");

				if(token != NULL)
				{

					tempIndiv->surname = malloc(sizeof(char)*(strlen(token)+5));
					strcpy(tempIndiv->surname,token);			

				}


			}
			else if(strcmp("FAMS",token) == 0 && personBool == 1)
			{



			}
			else if(strcmp("FAMC",token) == 0 && personBool == 1)
			{



			}
			else if(personBool == 1 && personBool == 1)
			{

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

		free(string);
		temp = nextElement(&iter);
		
	}

	testing = createIterator((*obj)->individuals );

	checking = nextElement(&testing);

	while(checking != NULL)
	{

		printf("%s\n",printIndividual((void*)tempIndiv));

		checking = nextElement(&testing);

	}

	return(error);

}

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
	char* tempName = NULL;
	char* tempAddress = NULL;
	char* lastField;

	int checkNum;
	int submitBool = 0;

	fields = initializeList(&printField,&deleteField,&compareFields);

	value = nextElement(&iter);

	error.type = OK;

	while(value != NULL)
	{

		line++;

		string = (char*) value;
		numString = strtok(string," ");
		token = strtok(NULL," ");
		checkNum = checkNums(numString);

		if(checkNum == 0)
		{

			checkNum = atoi(numString);

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

				tempField = malloc(sizeof(Field));
				tempField->tag = malloc(sizeof(token)*(strlen(token)+5));
				strcpy(tempField->tag,token);
				token = strtok(NULL,"");
				tempField->value = malloc(sizeof(token)*(strlen(token)+5));
				strcpy(tempField->value,token);
				insertBack(&fields,(void*)tempField);

			}

		}

		value = nextElement(&iter);

	}


	if(tempAddress != NULL)
	{

		tempSub = malloc(sizeof(Submitter)+sizeof(char)*(strlen(tempAddress)+5));
		strcpy(tempSub->address,tempAddress);

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

	char* checkSubmit = printSubmitter(tempSub);

	printf("%s",checkSubmit);

	(*obj)->submitter = tempSub;

	return(error);

}

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

GEDCOMerror listFamily(GEDCOMobject** obj, List fileList,int line)
{


	GEDCOMerror codes;
	ListIterator iter;

	//Family* tempFam = NULL;

	void* temp;

	//char* string;

	iter = createIterator(fileList);
	codes.type = OK;
	codes.line = 0;

	temp = nextElement(&iter);

	if(temp == NULL)
	{

		/*Double checkl error codes*/
		codes.type = INV_GEDCOM;

		return(codes);

	}
/*
	while(temp != NULL)
	{

		string = (char*)temp;

		if(validNum == 0)
		{

			value = atoi(token);
			token = strtok(string," ");
			if(value-previousValue < -1 || value-previousValue > 1)
			{

				error.type = INV_HEADER;

				free(string);

				return(error);

			}
			else if(value == 0)
			{

				if(tempFam != NULL)
				{

					insertBack(&list,tempFam);

				}
				else
				{

					list = initializeList(&printIndividual,&deleteIndividual,&compareIndividuals);

				}

				tempFam = malloc(sizeof(Family));

			} 
			else
			{

				error.type = INV_GEDCOM;
				error.line = line;
				deleteIndividual(tempIndiv);
				return(error);

			}

		}
		printf("%s",string);
		temp = nextElement(&iter);
		
	}
*/
	return(codes);



}

GEDCOMerror listEvents(GEDCOMobject** obj, List fileList,int line)
{

	
	GEDCOMerror codes;
	ListIterator iter;

	void* temp;

	char* string;

	iter = createIterator(fileList);
	codes.type = OK;
	codes.line = 0;

	temp = nextElement(&iter);

	if(temp == NULL)
	{

		/*Double checkl error codes*/
		codes.type = INV_GEDCOM;

		return(codes);

	}	

	while(temp != NULL)
	{

		string = (char*)temp;
		temp = nextElement(&iter);
		
	}

	return(codes);

}

void deleteHeader(Header* tobeDeleted)
{

	//destroyList(tobeDeleted->otherFields);

}

void destroyList(List tempList)
{

	ListIterator element = createIterator(tempList);
	void* tempThing;

	tempThing = nextElement(&element);

	while(tempThing != NULL)
	{
	
		deleteDataFromList(&tempList,tempThing);
		tempThing = nextElement(&element);

	}	

}

void destroySubmitter(Submitter* tobeDeleted)
{

	destroyList(tobeDeleted->otherFields);

}

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


