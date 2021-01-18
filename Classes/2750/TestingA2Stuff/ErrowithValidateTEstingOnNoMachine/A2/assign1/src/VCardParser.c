/*	
Evan Hedges. 0898140
CIS 2750, F18
*/
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedListAPI.h"
#include "VCardParser.h"

/***************************************************************************
Purpose: Returns a string value of a node
In: The data
Out: String.
***************************************************************************/
char* returnListFile(void* toBeDeleted)
{

	char* string;
	char* value;

	if(toBeDeleted == NULL)
	{

		return NULL;

	}

	string = (char*)toBeDeleted;

	value = malloc(sizeof(char)*(strlen(string)+5));

	strcpy(value,string);

	return value;

}

/***************************************************************************
Purpose: Delete a node
In: The data
Out: Nothing
***************************************************************************/
void deleteListFile(void* toBeDeleted)
{

	char* string = (char*)toBeDeleted;


	if(string != NULL)
	{

		free(string);

	}	

	return;

}

/***************************************************************************
Purpose: Compare data.
In: The data
Out: Integer comparison. 
***************************************************************************/
int compareListFile(const void* first,const void* second)
{

	char* firstString;
	char* secondString;

	if(first == NULL)
	{

		return -1;

	}

	if(second == NULL)
	{

		return 1;

	}

	firstString = (char*)first;
	secondString = (char*)second;

	return strcmp(firstString,secondString);

}
/**************
Parsing the docuement in 3 loops. One loop to remove the birthday/anniversary.
One loop to parse FN property.
The last loop to parse the remainijng properties. 
Done this way so that when parsing, we do not have to switch from FN to dates
or from FN to another property
****************/
VCardErrorCode createCard(char* fileName, Card** obj)
{

	VCardErrorCode error = OK;

	List* fileList;

	Property* tempProp;
	DateTime* tempEvent;

	ListIterator iter;

	char* string;
	char* tempString;
	char* lineName;
	char* lineValue;
	char* lineGroup;
	char* lineParameters;
	char* token;

	void* element;

	int fnBool;
	int groupBool;

	/* We create a list to store the file and read it in,*/
	fileList = initializeList(&returnListFile,&deleteListFile,&compareListFile);

	error = readToList(fileName,fileList);

	if(error != OK)
	{
		
		clearList(fileList);
		free(fileList);
		(*obj) = NULL;
		return error;

	}

	/*Create the VCARD*/
	(*obj) = malloc(sizeof(Card));
	(*obj)->fn = NULL;
	(*obj)->anniversary = NULL;
	(*obj)->birthday = NULL;
	(*obj)->optionalProperties = initializeList(&printProperty,&deleteProperty,&compareProperties);

	iter = createIterator(fileList);

	element = nextElement(&iter);

	fnBool = 0;
	/*We store each of the types, group, parameter, property, and values in their own strings to send into a function.*/
	while(element != NULL)
	{

		groupBool = 0;

		lineGroup = NULL;
		lineParameters = NULL;

		string = malloc(sizeof(char)*1000);
		strcpy(string,(char*)element);

		//Seperates on the colon, tempString stores the group/parameters/property, lineValue gets the rest

		token = strtok(string,":");

		if(token == NULL)
		{

			error = INV_PROP;

			clearList(fileList);		
			deleteCard((*obj));

			free(fileList);									
			free(string);
			free((*obj));

			(*obj) = NULL;

			return error;

		}

		tempString = malloc(sizeof(char)*(strlen(token)+20));
		strcpy(tempString,token);

		//Here we store the values in lineValue

		token  = strtok(NULL,"");

		if(token == NULL)
		{

			error = INV_PROP;

			clearList(fileList);		
			deleteCard((*obj));

			free(fileList);
			free(tempString);									
			free(string);
			free((*obj));

			(*obj) = NULL;

			return error;

		}

		lineValue = malloc(sizeof(char)*(strlen(token)+20));
		strcpy(lineValue,token);

		//Check for period and seperate the group.

		for (int i = 0; i < strlen(tempString); i++)
		{
			//Found the group

			if(tempString[i] == '.')
			{
				//We seperate the group tag
				if(i == 0 || tempString[strlen(tempString)-1] == ';')
				{
					//There is a period but no group, invalid
					error = INV_PROP;

					clearList(fileList);		
					deleteCard((*obj));

					free(lineValue);
					free(fileList);
					free(tempString);									
					free(string);
					free((*obj));

					(*obj) = NULL;

					return error;

				}

				token = strtok(tempString,".");

				lineGroup = malloc(sizeof(char)*(strlen(token)+20));

				strcpy(lineGroup,token);

				//All that remains is the Property name as well as the parameters, these are seperated by the semicolon. 
				token = strtok(NULL,";");
				lineName = malloc(sizeof(char)*(strlen(token)+20));

				strcpy(lineName,token);
				//Everything that remains, which should be the parameters

				token = strtok(NULL,"");
				groupBool = 1;

				//Check for parameters
				if(token == NULL)
				{

					lineParameters = NULL;

				}
				else
				{

					lineParameters = malloc(sizeof(char)*(strlen(token)+20));

					strcpy(lineParameters,token);

				}				

			}
			else if(tempString[i] == ';')
			{
				//Here is if we find a semi colon before a colon, which means there is no group 
				break;

			}

		}

		//Found no group, so check for parameters.
		if(groupBool == 0)
		{
			
			/*If the last character is a semicolon, we have a blank parameter, I think this is invalid*/
			if(tempString[strlen(tempString)-1] == ';')
			{

				error = INV_PROP;

				clearList(fileList);		
				deleteCard((*obj));

				free(lineValue);
				free(fileList);
				free(tempString);									
				free(string);
				free((*obj));

				(*obj) = NULL;

				return error;

			}

			token = strtok(tempString,";");
			lineName = malloc(sizeof(char)*(strlen(token)+20));

			strcpy(lineName,token);

			token = strtok(NULL,"");

			if(token == NULL)
			{


				lineParameters = NULL;

			}
			else
			{

				lineParameters = malloc(sizeof(char)*(strlen(token)+20));
				strcpy(lineParameters,token);

			}	

		}

		/*Makes it so the lineName is in the same case as the comparisons*/

		for (int i = 0; i < strlen(lineName); i++)
		{

			lineName[i] = toupper(lineName[i]);

		}

		/*Finds if the lines is either B day or anniversary*/
		if(strcmp(lineName,"BDAY") == 0 && (*obj)->birthday == NULL)
		{

			tempEvent = malloc(sizeof(DateTime)+sizeof(char)*(strlen(lineValue)+5));
			error = createDateTime((&tempEvent),lineValue);
			(*obj)->birthday = tempEvent;
			
		}
		else if(strcmp(lineName,"BDAY") == 0 && (*obj)->birthday != NULL)
		{
			//Error if there are two birthdays
			error = INV_PROP;

		}
		else if(strcmp(lineName,"ANNIVERSARY") == 0 && (*obj)->anniversary != NULL)
		{
			//Error if there are two birthdays
			error = INV_PROP;

		}
		else if(strcmp(lineName,"ANNIVERSARY") == 0 && (*obj)->anniversary == NULL)
		{

			tempEvent = malloc(sizeof(DateTime)+sizeof(char)*(strlen(lineValue)+5));
			error = createDateTime((&tempEvent),lineValue);
			(*obj)->anniversary = tempEvent;

		}
		else if(strcmp(lineName,"FN") == 0 && fnBool == 0)
		{

			fnBool = 1;

			tempProp = malloc(sizeof(Property));
			error = createProperty(lineName, lineGroup, lineParameters, lineValue,(&tempProp));
			(*obj)->fn = tempProp;

		}
		else if(strcmp(lineName,"VERSION") == 0)
		{

			error = INV_CARD;

		}
		else
		{

			tempProp = malloc(sizeof(Property));
			error = createProperty(lineName, lineGroup, lineParameters, lineValue,(&tempProp));
			insertBack((*obj)->optionalProperties,(void*)tempProp);

		}

		//Checks if the we created Groups and or Parameters. 
		if(lineGroup != NULL)
		{

			free(lineGroup);

		}

		if(lineParameters != NULL)
		{

			free(lineParameters);

		}

		free(tempString);
		free(string);
		free(lineName);
		free(lineValue);

		if(error != OK)
		{

			clearList(fileList);
			deleteCard((*obj));
			free((*obj));
			free(fileList);
			(*obj) = NULL;
			return error;

		}

		element = nextElement(&iter);
		/*Deletes the data from the list*/

	}

	if((*obj)->fn == NULL)
	{

		deleteCard((*obj));
		error = INV_PROP;
		free((*obj));
		(*obj) = NULL;

	}

	clearList(fileList);
	free(fileList);

	return error;

}

/****************************************************************************
Purpose: Print data.
In: Card.
Out: String.
***************************************************************************/
char* printCard(const Card* obj)
{

	char* string;
	char* tempString;

	if(obj == NULL)
	{

		string = malloc(sizeof(char)*1000);

		strcpy(string,"NULL");

		return string;

	}

	if(obj->fn == NULL)
	{

		string = malloc(sizeof(char)*1000);

		strcpy(string,"NULL");

		return string;

	}

	//Creaste the card string

	string = malloc(sizeof(char)*1000);

	strcpy(string,"VCARD:\n");

	tempString = printProperty((void*)obj->fn);
	string = mergeStrings(string,tempString);
	free(tempString);

	//Get a string representating a birthday.

	if(obj->birthday != NULL)
	{

		tempString = printDate(obj->birthday);
		string = mergeStrings(string,"\nBDay: ");
		string = mergeStrings(string,tempString);
		strcat(string,"\n");
		free(tempString);

	}

	//Get a string representating a anniversary.

	if(obj->anniversary != NULL)
	{


		tempString = printDate(obj->anniversary);
		string = mergeStrings(string,"\nANNIVERSARY: ");
		string = mergeStrings(string,tempString);
		strcat(string,"\n");
		free(tempString);

	}

	tempString = toString(obj->optionalProperties);
	string = mergeStrings(string,tempString);
	free(tempString);

	return (string);

}

/****************************************************************************
Purpose: Delete all data,, set to null.
In: Card
Out: Empty card.
***************************************************************************/
void deleteCard(Card* obj)
{

	if(obj == NULL)
	{

		return;

	}

	if(getLength(obj->optionalProperties) > 0)
	{

		clearList(obj->optionalProperties);

	}

	free(obj->optionalProperties);

	if(obj->birthday != NULL)
	{

		deleteDate(obj->birthday);

	}

	if(obj->anniversary != NULL)
	{
			
		deleteDate(obj->anniversary);

	}

	deleteProperty((void*)obj->fn);
	obj->fn = NULL;
	obj->birthday = NULL;
	obj->anniversary = NULL;
	obj->optionalProperties = NULL;

}

/****************************************************************************
Purpose: Delete a property
In: Aproperty
Out: Nothing, free data.
***************************************************************************/
void deleteProperty(void* toBeDeleted)
{

	Property* temp;

	temp = (Property*)toBeDeleted;

	if(temp == NULL)
	{

		return;

	}

	if(temp->name != NULL)
	{

		free(temp->name);

	}

	if(temp->group != NULL)
	{

		free(temp->group);

	}	

	if(getLength(temp->parameters) > 0)
	{

		clearList(temp->parameters);

	}

	if(getLength(temp->values) > 0)
	{

		clearList(temp->values);

	}

	free(temp->parameters);
	free(temp->values);
	free(temp);

}

/****************************************************************************
Purpose: See if two properties are the same.
In: 2 properties.
Out: Integer.
***************************************************************************/
int compareProperties(const void* first, const void* second)
{

	Property* tempOne;
	Property* tempTwo;

	char* oneString;
	char* twoString;

	int value;

	if(first == NULL)
	{

		return -1;

	}

	if(second == NULL)
	{

		return 1;

	}

	value = 0;

	tempOne = (Property*)first;
	tempTwo = (Property*)second;

	oneString = printProperty(tempOne);
	twoString = printProperty(tempTwo);

	value = strcmp(oneString,twoString);

	free(oneString);
	free(twoString);

	return value;

}

/****************************************************************************
Purpose: Print a property.
In: A property.
Out: Human readable string.
***************************************************************************/
char* printProperty(void* toBePrinted)
{

	Property* tempProp;

	char* string;
	char* tempString;

	tempProp = (Property*)toBePrinted;

	string = malloc(sizeof(char)*(strlen(tempProp->name)+10));
	strcpy(string,tempProp->name);
	//Checks for group and adds it to the string
	if(tempProp->group != NULL)
	{

		string = mergeStrings(string,"\nGroup:");
		string = mergeStrings(string,tempProp->group);

	}
	//Checks for parameters and adds it.
	if(getLength(tempProp->parameters) > 0)
	{

		tempString = toString(tempProp->parameters);
		string = mergeStrings(string,tempString);
		free(tempString);

	}
	//Checks for values ( (which should be there but if not) then adds it to a string.
	if(getLength(tempProp->values) > 0)
	{

		string = mergeStrings(string,"\nvalues:");
		tempString = toString(tempProp->values);
		string = mergeStrings(string,tempString);
		free(tempString);

	}	

	return (string);

}

/****************************************************************************
Purpose: Deletea a parameter.
In: A parameter.
Out: Nothing, free data.
***************************************************************************/
void deleteParameter(void* toBeDeleted)
{

	Parameter* temp;

	if(toBeDeleted == NULL)
	{

		return;

	}

	temp = (Parameter*)toBeDeleted;

	free(temp);

}

/****************************************************************************
Purpose: Print a property.
In: A property.
Out: Human readable string.
***************************************************************************/
int compareParameters(const void* first, const void* second)
{

	if(first == NULL)
	{

		return -1;

	}

	if(second == NULL)
	{

		return 1;

	}

	return 0;

}

/****************************************************************************
Purpose: Print a parameter.
In: A parameter.
Out: Human readable string.
***************************************************************************/
char* printParameter(void* toBePrinted)
{

	Parameter* temp;

	char* string;

	if(toBePrinted == NULL)
	{

		return NULL;

	}

	temp = (Parameter*)toBePrinted;
	//Print the parameter.
	string = malloc(sizeof(char)*(strlen(temp->value)+strlen(temp->name)+100));
	strcpy(string,"Parameter: ");
	string = mergeStrings(string,temp->name);
	string = mergeStrings(string," ");
	string = mergeStrings(string,temp->value);
	strcat(string,"\n");

	return string;

}

/****************************************************************************
Purpose: Free a value.
In: A values.
Out: Nothing.
***************************************************************************/
void deleteValue(void* toBeDeleted)
{

	free((char*)toBeDeleted);

}

/****************************************************************************
Purpose: Compare values.
In: two values.
Out: integer, representation comparison.
***************************************************************************/
int compareValues(const void* first,const void* second)
{

	if(first == NULL)
	{

		return -1;

	}

	if(second == NULL)
	{

		return 1;

	}

	return strcmp((char*)first,(char*)second);

}

/****************************************************************************
Purpose: Human readable string representation of a value.
In: Value.
Out: Human readable string.
***************************************************************************/
char* printValue(void* toBePrinted)
{

	char* string;
	char* tempString;

	if(toBePrinted == NULL)
	{

		return NULL;

	}

	tempString = (char*)toBePrinted;

	string = malloc(sizeof(char)*(strlen(tempString)+10));

	strcpy(string,(char*)tempString);

	return (string);

}

/****************************************************************************
Purpose: Free a date.
In: Date
Out: Nothing, free date.
***************************************************************************/
void deleteDate(void* toBeDeleted)
{

	DateTime* temp;

	if(toBeDeleted == NULL)
	{

		return;

	}

	temp = (DateTime*)toBeDeleted;

	free(temp);

}

/****************************************************************************
Purpose: compare Dates.
In: two dates.
Out: Integer representation of a comparison of two dates.
***************************************************************************/
int compareDates(const void* first, const void* second)
{

	DateTime* tempOne;
	DateTime* tempTwo;

	char* oneString;
	char* twoString;

	int tempValue;

	if(first == NULL)
	{

		return -1;

	}

	if(second == NULL)
	{

		return 1;

	}

	tempOne = (DateTime*)first;
	tempTwo = (DateTime*)second;

	if(tempOne->isText != tempTwo->isText)
	{

		return -1;

	}

	if(tempOne->UTC != tempTwo->UTC)
	{

		return -2;

	}

	if(tempOne->UTC != tempTwo->UTC)
	{

		return -2;

	}

	if(tempOne->isText == true)
	{

		return(strcmp(tempOne->text,tempTwo->text));

	}
	else
	{

		oneString = printDate(tempOne);
		twoString = printDate(tempTwo);

		tempValue = strcmp(oneString,twoString);

		free(oneString);
		free(twoString);

		return tempValue;

	}


	return 0;

}

/****************************************************************************
Purpose: Print a human readble date.
In: A date.
Out: Human readable string.
***************************************************************************/
char* printDate(void* toBePrinted)
{

	DateTime* temp;

	char* string;

	temp = (DateTime*)toBePrinted;

	if(toBePrinted == NULL)
	{

		return NULL;

	}

	if(temp->isText == true)
	{
		//Copies the string representation
		string = malloc(sizeof(char)*(strlen(temp->text)+5));
		strcpy(string,temp->text);

	}
	else
	{
		//Copies the string date and time if not a string
		string = malloc(sizeof(char)*(250));
		strcpy(string,"Date/Time:-");

		if(strlen(temp->date) > 0)
		{

			strcat(string,temp->date);

		}

		strcat(string,"/-");

		if(strlen(temp->time) > 0)
		{

			strcat(string,temp->time);
			strcat(string,"\n");

		}

		if(temp->UTC == true)
		{

			strcat(string,"Z");

		}
		
	}

	return (string);

}

/****************************************************************************
Purpose: Turn error code into 
In: Error code
Out: Human readable error code. 
***************************************************************************/
char* printError(VCardErrorCode err)
{

	char* stringError;

	stringError = malloc(sizeof(char)*1000);

	if(err == OK)
	{

		strcpy(stringError,"OK\n");
		
	}
	else if(err == INV_FILE)
	{

		strcpy(stringError,"Invalid File\n");
		
	}
	else if(err == INV_CARD)
	{

		strcpy(stringError,"Invalid Card\n");
		
	}
	else if(err == INV_PROP)
	{

		strcpy(stringError,"Invalid Property\n");
		
	}
	else if(err == WRITE_ERROR)
	{

		strcpy(stringError,"Invalid Writing\n");
		
	}
	else if(err == OTHER_ERROR)
	{

		strcpy(stringError,"Unknown Error\n");
		
	}
	else
	{

		strcpy(stringError,"Invalid error code\n");

	}

	return stringError;

}

VCardErrorCode writeCard(const char* fileName, const Card* obj)
{

	FILE* ptr;

	ListIterator iter;

	void* element;

	char* string;
	char* tempString;
	char* tempFileName;

	tempFileName = malloc(sizeof(char)*(strlen(fileName)+20));

	strcpy(tempFileName,fileName);

	if(extensionCheck(tempFileName,"vcf",4) != 0 && extensionCheck(tempFileName,"vcard",4) != 0)
	{
		free(tempFileName);
		return INV_FILE;

	}

	free(tempFileName);

	ptr = fopen(fileName,"r");

	if(ptr != NULL)
	{

		fclose(ptr);
		return INV_FILE;

	}

	ptr = fopen(fileName,"w");

	if(ptr == NULL)
	{

		return INV_FILE;

	}

	string = malloc(sizeof(char)*1000);

	strcpy(string,"BEGIN:VCARD\r\nVERSION:4.0\r\n");

	tempString = writeProperty(obj->fn);

	if(tempString == NULL)
	{

		return WRITE_ERROR;

	}

	string = mergeStrings(string,tempString);

	free(string);

	iter = createIterator(obj->optionalProperties);
	element = nextElement(&iter);

	while(element != NULL)
	{
		tempString = writeProperty(obj->fn);

		if(tempString == NULL)
		{

			return WRITE_ERROR;

		}

		string = mergeStrings(string,tempString);
		element = nextElement(&iter);

		free(tempString);

	}

	if(obj->birthday != NULL)
	{

		tempString = writeDate(obj->birthday);
		string = mergeStrings(string,"BDAY");
		string = mergeStrings(string,tempString);
		if(tempString == NULL)
		{

			return WRITE_ERROR;

		}

	}

	if(obj->anniversary != NULL)
	{

		tempString = writeDate(obj->anniversary);
		string = mergeStrings(string,"anniversary");
		string = mergeStrings(string,tempString);

		if(tempString == NULL)
		{

			return WRITE_ERROR;

		}
		
	}

	string = mergeStrings(string,"END:VCARD\r\n");

	fprintf(ptr,"%s",string);

	fclose(ptr);

	return OK;

}

char* writeProperty(const Property* prop)
{

	ListIterator iter;

	Parameter* tempPara;

	void* element;

	char* string;
	char* group;

	if(prop == NULL)
	{

		return NULL;

	}

	/*Copy the property name here*/

	string = malloc(sizeof(char)*(strlen(prop->name)+20));

	strcpy(string,prop->name);

	/*Check for parameters*/

	iter = createIterator(prop->parameters);

	element = nextElement(&iter);

	if(element != NULL)
	{

		strcat(string,";");

	}

	while(element != NULL)
	{

		tempPara = (Parameter*) element;

		string = mergeStrings(string,tempPara->name);

		strcat(string,"=");

		string = mergeStrings(string,tempPara->value);

		element = nextElement(&iter);

		if(element != NULL)
		{

			strcat(string,";");

		}

	}

	/*Check for values*/

	strcat(string,":");

	iter = createIterator(prop->values);

	element = nextElement(&iter);

	if(element == NULL)
	{

		free(string);

		return NULL;

	}

	while(element != NULL)
	{

		string = mergeStrings(string,(char*)element);

		element = nextElement(&iter);

		if(element != NULL)
		{

			strcat(string,";");

		}

	}

	/*Groups if there is any*/

	string = mergeStrings(string,"\r\n");

	if(prop->group != NULL)
	{

		group = malloc(sizeof(char)*(strlen(prop->group)+20));
		strcpy(group,prop->group);
		strcat(group,".");
		group = mergeStrings(group,string);

		free(string);

		return group;

	}
	

	return string;

}

char* writeDate(const DateTime* date)
{

	char* string;
	char* tempDate;
	char* tempTime;

	if(date->isText == true)
	{

		string = malloc(sizeof(char)*(strlen(date->text)+100));
		strcpy(string,":");
		string = strcat(string,date->text);
		string = mergeStrings(string,"\r\n");

	}
	else 
	{

		string = malloc(sizeof(char)*100);
		strcpy(string,":");

		if(strlen(date->date) >= 1)
		{

			tempDate = malloc(sizeof(char)*(strlen(date->date)));
			strcpy(tempDate,date->date);
			string = mergeStrings(string,tempDate);
			free(tempDate);

		}

		if(strlen(date->time) >= 1)
		{

			string = mergeStrings(string,"T");
			tempTime = malloc(sizeof(char)*(strlen(date->time)));
			strcpy(tempDate,tempTime);
			string = mergeStrings(string,tempTime);
			free(tempDate);

		}

		if(date->UTC == true)
		{

			string = mergeStrings(string,"Z");

		}

	}


	return string;

}