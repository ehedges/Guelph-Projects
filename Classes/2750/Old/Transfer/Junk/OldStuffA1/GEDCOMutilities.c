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

GEDCOMerror initIndiv(char* tempRef,List fileList,GEDCOMobject** obj,int line,ListIterator iter)
{

	GEDCOMerror error;

	Individual* tempIndiv;

	Field* tempField;

	char* token;	
	char* string;
	char* getString;

	void* temp;

	int value = 0;
	int validNum = 0;
	int previousValue = 0;
	int personBool = 0;
	int eventValue;

	error.type = OK;

	tempIndiv = malloc(sizeof(Individual));
	tempIndiv->otherFields = initializeList(&printField,&deleteField,&compareFields);
	tempIndiv->surname = NULL;
	tempIndiv->givenName = NULL;
	tempIndiv->events = initializeList(&printEvent,&deleteEvent,&compareEvents);
	tempField = malloc(sizeof(Field));
	tempField->tag = malloc(sizeof(char)*20);
	strcpy(tempField->tag,"REFERENCE");
	tempField->value = malloc(sizeof(char)*strlen(tempRef)+5);
	strcpy(tempField->value,tempRef);

	insertBack(&tempIndiv->otherFields,(void*)tempField);

	temp = nextElement(&iter);

	while(personBool == 0)
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

				personBool = 1;

			}
			else if(strcmp(token,"EVEN") == 0)
			{
					
				error = listEvents(tempIndiv->events,fileList,line,iter,value);
				
				if(error.type != OK)
				{

					return(error);


				}

				ListIterator LUL = createIterator(tempIndiv->events);
				temp = nextElement(&iter);
				line++;
				getString = (char*)temp;
				string = malloc(sizeof(char)*(strlen(getString)+5));
				strcpy(string,getString);
				token = strtok(string," ");
				eventValue = atoi(token);

				while(eventValue > value)
				{
					
					temp = nextElement(&iter);
					line++;
					getString = (char*)temp;
					string = malloc(sizeof(char)*(strlen(getString)+5));
					strcpy(string,getString);
					token = strtok(string," ");
					eventValue = atoi(token);

				}

				void* testingStuffz = nextElement(&LUL);

				if(testingStuffz == NULL)
				{

					printf("ERROR");


				}
				while(testingStuffz != NULL)
				{

					//printf("%s",printEvent(testingStuffz));
					testingStuffz= nextElement(&LUL);


				}	
	
				
				
			}
			
			if(strcmp("NAME",token) == 0)
			{

				token = strtok(NULL," ");

				tempIndiv->givenName = malloc(sizeof(char)*(strlen(token)+5));

				strcpy(tempIndiv->givenName,token);

				token = strtok(NULL," ");

				if(token != NULL)
				{

					tempIndiv->surname = malloc(sizeof(char)*(strlen(token)+5));
					strcpy(tempIndiv->surname,token);			

				}


			}
			else if(strcmp("FAMS",token) == 0)
			{

				

			}
			else if(strcmp("FAMC",token) == 0)
			{

				

			}
			else
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
		else
		{

			error.type = INV_RECORD;
			error.line = line;

		}

		free(string);
		temp = nextElement(&iter);

	}

	insertBack(&(*obj)->individuals,(void*)tempIndiv);

	//printf("%s\n",printIndividual(tempIndiv));

	return(error);

}

GEDCOMerror listIndividuals(GEDCOMobject** obj, List fileList, int line)
{

	GEDCOMerror error;
	ListIterator iter;

	void* temp;

	char* string;
	char* token;
	char* tempRef;
	char* getString;

	int value = 0;
	int validNum = 0;
	int previousValue = 0;

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
					
					error = initIndiv(tempRef,fileList,obj,line,iter);

				}

			}

		}

		free(string);
		temp = nextElement(&iter);
		
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
	char* tempString;

	int checkNum;
	int submitBool = 0;

	fields = initializeList(&printField,&deleteField,&compareFields);

	value = nextElement(&iter);

	error.type = OK;

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

		free(string);

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

	//char* checkSubmit = printSubmitter(tempSub);

	//printf("%s",checkSubmit);

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

	GEDCOMerror error;
	ListIterator iter;

	//Family* tempFam = NULL;

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

	

}

int compareFamilies(const void* first,const void* second)
{

	return(0);

}

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

	strcpy(string,"Family:\nHusband: \n");

	if(fam->husband != NULL)
	{

		tempString = printIndividual(fam->husband);
		string = realloc(string,sizeof(char)*(strlen(tempString)+strlen(string)+50));
		strcat(string,tempString);

	}
	else
	{
		string = realloc(string,sizeof(char)*(strlen(string)+50));
		strcat(string,"NONE\n");	

	}

	strcat(string,"\nWife: \n");
	
	if(fam->wife != NULL)
	{

		tempString = printIndividual(fam->wife);
		string = realloc(string,sizeof(char)*(strlen(tempString)+strlen(string)+50));
		strcat(string,tempString);

	}
	else
	{

		string = realloc(string,sizeof(char)*(strlen(string)+50));
		strcat(string,"NONE\n");	

	}

	
	strcat(string,"\nChildren:\n");

	childIter = createIterator(fam->children);

	children = nextElement(&childIter);

	if(children == NULL)
	{

		string = realloc(string,sizeof(char)*(strlen(string)+50));
		strcat(string,"NONE\n");

	}

	while(children != NULL)
	{

		tempIndiv = (Individual*) children;

		tempString = printIndividual(tempIndiv);

		string = realloc(string,sizeof(char)*(strlen(tempString)+strlen(string)+15));
		strcat(string,tempString);
		strcat(string,"\n");
		children = nextElement(&childIter);

	}

	strcat(string,"\n\n");

	return(string);

}

GEDCOMerror initFam(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter)
{

	GEDCOMerror error;

	Family* tempFam;

	Field* tempField;

	char* token;	
	char* string;
	char* getString;

	void* temp;

	int value = 0;
	int validNum = 0;
	int previousValue = 0;
	int famBool = 0;

	tempFam = malloc(sizeof(Family)*1);

	tempFam->husband = NULL;
	tempFam->wife = NULL;
	tempFam->children = initializeList(&printIndividual,&deleteIndividual,&compareFields);

	tempFam->otherFields = initializeList(&printField,&deleteField,&compareFields);

	error.type = OK;

	temp = nextElement(&iter);

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

			if(value == 0)
			{

				famBool = 1;

			}
			else if(strcmp("WIFE",token) == 0)
			{

				token = strtok(NULL," ");

				tempFam->wife = getPerson(token,obj);

			}
			else if(strcmp("HUSB",token) == 0)
			{

				token = strtok(NULL," ");

				tempFam->husband = getPerson(token,obj);

			}
			else if(strcmp("CHIL",token) == 0)
			{

				token = strtok(NULL," ");
				insertBack(&tempFam->children,getPerson(token,obj));


			}
			else
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

	printf("%s\n",printFamily(tempFam));

	insertBack(&(*obj)->families,tempFam);

	return(error);


}

Individual* getPerson(char* token,GEDCOMobject** obj)
{

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

GEDCOMerror listEvents(List events, List fileList, int line, ListIterator iter,int depth)
{

	GEDCOMerror error;

	Event* tempEvent;

	Field* tempField;

	void* temp;

	char* string;
	char* token;
	char* getString;

	int value = 0;
	int validNum = depth;
	int previousValue = depth;

	tempEvent = malloc(sizeof(Event));
	tempEvent->otherFields = initializeList(&printEvent,&deleteEvent,&compareEvents);

	error.type = OK;
	error.line = 0;

	temp = nextElement(&iter);

	string = (char*)temp;

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

			if(value < depth)
			{
				//printf("%s",printEvent((void*)tempEvent));
				insertBack(&events,(void*)tempEvent);
				free(string);
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

	insertBack(&events,(void*)tempEvent);

	/*ListIterator checking;

	void* lul;*/

	return(error);

}

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
		strcat(string,"\n");

	}

	if(tempEvent->date != NULL)
	{

		strcat(string,"Date: ");
		string = realloc(string,(strlen(string)+strlen(tempEvent->date)+10));
		strcat(string,tempEvent->date);
		strcat(string,"\n");

	}

	if(tempEvent->place != NULL)
	{

		strcat(string,"Place: ");
		string = realloc(string,(strlen(string)+strlen(tempEvent->place)+10));
		strcat(string,tempEvent->place);
		strcat(string,"\n");

	}

	tempElement = nextElement(&iter);

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

		tempElement = nextElement(&iter);

	}

	return(string);

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

void deleteHeader(Header* tobeDeleted)
{

	destroyList(tobeDeleted->otherFields);

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