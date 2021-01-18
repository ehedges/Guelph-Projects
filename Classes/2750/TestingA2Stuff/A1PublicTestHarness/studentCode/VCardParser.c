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

#define SINVALMULTIPROLENGTH 22
#define	SINVALSINGPROPLENGTH 6
#define INVPROPLENGTH 2

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

		if(tempString[0] == ';' || tempString[0] == ':'  || tempString[0] == '.')
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
				if(i == 0 || tempString[strlen(tempString)-1] == ';' || tempString[i+1] == ';')
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
			(*obj) = NULL;
			error = INV_PROP;

		}
		else if(strcmp(lineName,"ANNIVERSARY") == 0 && (*obj)->anniversary != NULL)
		{
			//Error if there are two birthdays
			(*obj) = NULL;
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

			(*obj) = NULL;

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
		error = INV_CARD;
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

	if(obj->optionalProperties != NULL)
	{

		if(getLength(obj->optionalProperties) > 0)
		{

			clearList(obj->optionalProperties);

		}

		free(obj->optionalProperties);


	}

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

	if(temp->values != NULL)
	{

		free(temp->values);

	}

	free(temp->parameters);
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
	else if(err == INV_DT)
	{

		strcpy(stringError,"Invalid DateTime\n");
		
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

	ptr = fopen(fileName,"w+");

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

	free(tempString);

	iter = createIterator(obj->optionalProperties);
	element = nextElement(&iter);

	while(element != NULL)
	{
		tempString = writeProperty((Property*)element);

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

		free(tempString);

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

		free(tempString);
		
	}

	string = mergeStrings(string,"END:VCARD\r\n");
	printf("%s\n",string);
	fprintf(ptr,"%s",string);

	fclose(ptr);

	free(string);

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

	if(strlen(prop->group) >= 1)
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
			tempTime = malloc(sizeof(char)*(strlen(date->time)+5));
			strcpy(tempTime,date->time);
			string = mergeStrings(string,tempTime);
			free(tempTime);

		}

		if(date->UTC == true)
		{

			string = mergeStrings(string,"Z");

		}

	}
             
	string = mergeStrings(string,"\r\n");

	return string;

}



/** Function to writing a Card object into a file in iCard format.
 *@pre Card object exists, and is not NULL.
 *@post Card has not been modified in any way, and a file representing the
        Card contents in vCard format has been created
 *@return the error code indicating success or the error encountered when validating the Card
 *@param obj - a pointer to a Card struct
 **/
VCardErrorCode validateCard(const Card* obj)
{

	Property* prop;

	ListIterator iter;

	VCardErrorCode error;

	void* element;

	/* The arrays store the different names of properties*/

	char singleValueMultiProp[SINVALMULTIPROLENGTH][50] = {"CALURI","CALADRURI","FBURL","KEY","URL","SOUND","NOTE","RELATED","LOGO","ROLE","TITLE","GEO","TZ","LANG","IMPP","EMAIL","TEL","PHOTO","MEMBER","FN","XML","SOURCE"};
	char singleValueSingleProp[SINVALSINGPROPLENGTH][10] = {"KIND","PRODID","REV","NICKNAME","CATEGORIES","UID"};
	char invalidProp[INVPROPLENGTH][20] = {"VERSION","CLIENTPIDMAP"};

	int validProp;
	int length;
	int existCounter;
	int genderCounter;
	int NCounter;

	if(obj == NULL)
	{
		printf("NULLCARD\n");
		return INV_CARD;

	}

	if(obj->fn == NULL)
	{
		printf("NULL FN\n");
		return INV_CARD;
                                                                        
	}

	error = validateProperty(obj->fn);

	if(error != OK)
	{
		printf("FN Validate Error");
		return error;

	}
				
	length = getLength(obj->fn->values);

	if(length != 1)
	{
		printf("HERE\n");
		return INV_PROP;

	}

	if(obj->optionalProperties == NULL)
	{
		printf("HERER\n");
		return INV_CARD;

	}

	if(obj->birthday != NULL)
	{

		error = validDate(obj->birthday);

		if(error != OK)
		{

			return INV_DT;

		}

	}

	if(obj->anniversary != NULL)
	{

		error = validDate(obj->anniversary);

		if(error != OK)
		{

			return INV_DT;

		}
			
	}

	existCounter = 0;

	iter = createIterator(obj->optionalProperties);

	element = nextElement(&iter);

	/* This loop checks for properties that can appear many times*/

	while(element != NULL)
	{

		prop = (Property*) element;

		for (int i = 0; i < INVPROPLENGTH; i++)
		{
			
			if(strcmp(invalidProp[i],prop->name) == 0)
			{

				return INV_PROP;

			}

		}


		for (int i = 0; i < SINVALMULTIPROLENGTH; i++)
		{
			
			if(strcmp(singleValueMultiProp[i],prop->name) == 0)
			{

				existCounter++;

				error = validateProperty(prop);

				if(error != OK)
				{

					return error;

				}
				
				length = getLength(prop->values);

				if(length != 1)
				{

					return INV_PROP;

				}

				break;

			}

		}

		element = nextElement(&iter);

	}

	for (int i = 0; i < SINVALSINGPROPLENGTH; i++)
	{
		
		iter = createIterator(obj->optionalProperties);

		element = nextElement(&iter);

		validProp = 0;

		while(element != NULL)
		{

			prop = (Property*) element;

			if(strcmp(singleValueSingleProp[i],prop->name) == 0)
			{

				if(validProp > 0)
				{

					return INV_PROP;

				}

				error = validateProperty(prop);

				if(error != OK)
				{

					return error;

				}
				
				length = getLength(prop->values);

				if(length != 1)
				{

					return INV_PROP;

				}

				existCounter++;

				validProp++;

			}

			element = nextElement(&iter);

		}

	}

	genderCounter = 0;
	NCounter = 0;

	iter = createIterator(obj->optionalProperties);

	element = nextElement(&iter);

	while(element != NULL)
	{

		prop = (Property*) element;

		if(strcmp("N",prop->name) == 0)
		{

			if(getLength(prop->values) != 5)
			{

				return INV_PROP;

			}

			NCounter++;
			existCounter++;

		}
		else if(strcmp("GENDER",prop->name) == 0)
		{

			if(getLength(prop->values) != 1 && getLength(prop->values) != 2)
			{

				return INV_PROP;

			}

			genderCounter++;
			existCounter++;

		}
		else if(strcmp("ADR",prop->name) == 0)
		{

			if(getLength(prop->values) != 7)
			{

				return INV_PROP;

			}


			existCounter++;

		}
		else if(strcmp("ORG",prop->name) == 0)
		{

			if(getLength(prop->values) == 0)
			{

				return INV_PROP;

			}

			existCounter++;

		}

		if(NCounter >= 2 || genderCounter >= 2)
		{

			return INV_PROP;

		}

		element = nextElement(&iter);

	}

	length = getLength(obj->optionalProperties);

	if(existCounter != length)
	{

		return INV_PROP;

	}

	return OK;

}

VCardErrorCode validDate(DateTime* date)
{

	if(date == NULL)
	{

		return OK;

	}

	if(date->date == NULL || date->time == NULL || date->text == NULL)
	{
		printf("SOMETHINGNULL");
		return INV_DT;

	}

	if(date->isText == true)
	{

		if(date->UTC == true)
		{

			return INV_DT;

		}
		else if((strlen(date->date) > 0) || (strlen(date->time) > 0) || (strlen(date->time) == 0) )
		{
			printf("HERERRSRSRS\n");
			return INV_DT;

		}

	}
	else if(date->isText == false)
	{

		if(strlen(date->date) == 0 && strlen(date->time) == 0)
		{
			printf("NOT TEXT BUT FAILS\n");
			return INV_DT;

		}

	}

	return OK;

}

VCardErrorCode validateProperty(const Property* prop)
{

	VCardErrorCode error;

	if(prop->name == NULL || prop->group == NULL)
	{

		return INV_PROP;

	}

	if(prop->parameters == NULL || prop->values == NULL)
	{

		return INV_PROP;

	}

	if(strlen(prop->name) == 0)
	{

		return INV_PROP;

	}

	error = checkParameters(prop);

	if(error != OK)
	{

		return INV_PROP;

	}

	return OK;

}

/**
Checks for parameters not being null or empty
*/
VCardErrorCode checkParameters(const Property* prop)
{

	Parameter* tempParam;

	ListIterator iter;

	void* element;

	if(prop->parameters == NULL)
	{

		return INV_PROP;

	}

	iter = createIterator(prop->parameters);

	element = nextElement(&iter);

	while(element != NULL)
	{

		tempParam= (Parameter*) element;

		if(tempParam->name == NULL || tempParam->value == NULL)
		{

			return INV_PROP;

		}

		if(strlen(tempParam->name) == 0 || strlen(tempParam->value) == 0)
		{

			return INV_PROP;

		}

		element = nextElement(&iter);

	}

	return OK;

}


/** Function for converting a list of strings into a JSON string
 *@pre List exists, is not null, and is valid
 *@post List has not been modified in any way, and a JSON string has been created
 *@return newly allocated JSON string.  May be NULL.
 *@param strList - a pointer to an Individual struct
 **/
char* strListToJSON(const List* strList)
{

	ListIterator iter;

	void* temp;

	char* JSON;

	if(strList == NULL)
	{

		return NULL;

	}

	if(getLength(strList) == 0)
	{

		JSON = malloc(sizeof(char)*100);

		strcpy(JSON,"[\"\"]");

		return JSON;

	}

	JSON = malloc(sizeof(char)*100);


	strcpy(JSON,"[");

	iter = createIterator(strList);

	temp = nextElement(&iter);

	while(temp != NULL)
	{

		JSON = mergeStrings(JSON,"\"");
		JSON = mergeStrings(JSON,(char*)temp);
		JSON = mergeStrings(JSON,"\"");

		temp = nextElement(&iter);

		if(temp ==  NULL)
		{

			JSON = mergeStrings(JSON,"]");

		}
		else
		{

			JSON = mergeStrings(JSON,",");

		}

	}

	return JSON;

}


/** Function for creating an List of strings from an JSON string
 *@pre String is not null, and is valid
 *@post String has not been modified in any way, and a List has been created
 *@return a newly allocated List.  May be NULL.
 *@param str - a pointer to a JSON string
 **/
List* JSONtoStrList(const char* str)
{

	List* list;

	char* tempValue;

	int stringLength;
	int valueBool;

	if(str == NULL)
	{

		return NULL;

	}

	if(str[0] != '[' || str[strlen(str)-1] != ']')
	{

		return NULL;

	}

	list = initializeList(&printValue,&deleteValue,&compareValues);
	tempValue = malloc(sizeof(char)*105);
	strcpy(tempValue,"");

	valueBool = 0;
	stringLength = 0;

	for (int i = 0; i < strlen(str); i++)
	{


		if(str[i] == '\"' && valueBool == 1)
		{

			valueBool = 0;
			insertBack(list,tempValue);

			tempValue = malloc(sizeof(char)*105);
			strcpy(tempValue,"");
			stringLength = 0;

		}
		else if(str[i] == '\"' && valueBool == 0)
		{

			valueBool = 1;

		}
		else if(valueBool == 1)
		{

			if(stringLength == (strlen(tempValue)-10))
			{

				tempValue = realloc(tempValue,sizeof(char)*(stringLength+100));

			}

			tempValue[stringLength] = str[i];
			tempValue[stringLength+1] = '\0';
			stringLength++;

		}

	}

	return list;

}


/** Function for converting a Property struct into a JSON string
 *@pre Property exists, is not null, and is valid
 *@post Property has not been modified in any way, and a JSON string has been created
 *@return newly allocated JSON string.  May be NULL.
 *@param strList - a pointer to a Property struct
 **/
char* propToJSON(const Property* prop)
{

	char* JSON;
	char* tempString;

	if(prop == NULL)
	{

		return NULL;

	}

	if(prop->name == NULL || prop->group == NULL || prop->values == NULL || prop->parameters == NULL)
	{

		return NULL;

	}


	JSON = malloc(sizeof(char)*100);

	strcpy(JSON,"{\"group\":\"");

	if(strlen(prop->group) > 0)
	{

		JSON = mergeStrings(JSON,prop->group);

	}

	JSON = mergeStrings(JSON,"\",\"name\":");

	if(strlen(prop->name) > 0)
	{

		JSON = mergeStrings(JSON,prop->name);

	}
	else
	{

		free(JSON);

		return NULL;

	}

	JSON = mergeStrings(JSON,"\",\"values\":");

	tempString = strListToJSON(prop->values);

	if(tempString == NULL)
	{

		free(JSON);

		return NULL;

	}

	JSON = mergeStrings(JSON,"}");

	free(tempString);

	return JSON;

}


/** Function for creating a Property struct from an JSON string
 *@pre String is not null, and is valid
 *@post String has not been modified in any way, and a Property struct has been created
 *@return a newly allocated Property.  May be NULL.
 *@param str - a pointer to a JSON string
 **/
Property* JSONtoProp(const char* str)
{

	Property* prop;

	char* string;

	int quoteBool;
	int backSlashBool;
	int groupBool;
	int nameBool;
	int valuesBool;
 
	int stringCounter;

	if(str == NULL)
	{

		return NULL;

	}

	if(str[0] != '{' || str[strlen(str)-1] != '}')
	{

		return NULL;

	}

	prop = malloc(sizeof(Property*));
	prop->name = NULL;
	prop->group = NULL;
	prop->parameters = initializeList(&printParameter,&deleteParameter,&compareParameters);
	prop->values = NULL;

	string = malloc(sizeof(char)*(strlen(str)+10));
	stringCounter = 0;
	quoteBool = 0;

	for (int i = 1; i < (strlen(str)-1); i++)
	{
	
		if(str[i] == '\"' && backSlashBool != 0)
		{

			quoteBool++;

		}
		if(str[i] == '\\' && backSlashBool == 0)
		{

			string[stringCounter] = str[i];
			string[stringCounter+1] = '\0';
			stringCounter++;

			backSlashBool++;

		}
		else
		{

			string[stringCounter] = str[i];
			string[stringCounter+1] = '\0';
			stringCounter++;

			backSlashBool = 0;

		}

		if(quoteBool == 2)
		{

			if(strcmp(string,"group") == 0)
			{

				groupBool++;
				stringCounter = 0;

			}

			if(strcmp(string,"name") == 0)
			{

				nameBool++;
				stringCounter = 0;
				
			}

			if(strcmp(string,"values") == 0)
			{

				valuesBool++;
				stringCounter = 0;
				
			}


		}

		if(quoteBool == 4)
		{

			quoteBool = 0;

			if(groupBool == 1)
			{

				groupBool = 0;

				prop->group = malloc(sizeof(char)*(strlen(string)+5));

				strcpy(prop->group,string);


			}
			else if(nameBool == 1)
			{
				
				nameBool = 0;
				prop->name = malloc(sizeof(char)*(strlen(string)+5));

				strcpy(prop->name,string);


			}
			else if(valuesBool == 1)
			{
				
				valuesBool = 0;

				prop->values = JSONtoStrList(string);

			}

		}
		
	}

	if(prop->group == NULL)
	{

		prop->group = malloc(sizeof(char)*5);
		strcpy(prop->group,"");

	}

	if(prop->values == NULL)
	{

		deleteProperty(prop);

		return NULL;
	}


	free(string);

	return prop;

}


/** Function for converting a DateTime struct into a JSON string
 *@pre DateTime exists, is not null, and is valid
 *@post DateTime has not been modified in any way, and a JSON string has been created
 *@return newly allocated JSON string.  May be NULL.
 *@param strList - a pointer to a DateTime struct
 **/
char* dtToJSON(const DateTime* prop)
{

	char* JSON;

	if(prop == NULL)
	{

		return NULL;

	}

	if(prop->isText == true)
	{

		if(strlen(prop->text) == 0)
		{

			return NULL;

		}

		JSON = malloc(sizeof(char)*(strlen(prop->text)+100));

		strcpy(JSON,"{\"isText\":true,\"date\":\"\",\"time\":\"\",\"text\":");


		JSON = mergeStrings(JSON,prop->text);

		JSON = mergeStrings(JSON,"\"\",\"isUTC\":false}");

		return JSON;

	}

	JSON = malloc(sizeof(char)*1000);

	strcpy(JSON,"{\"isText\":false,\"date\":");

	JSON = mergeStrings(JSON,prop->date);

	JSON = mergeStrings(JSON,"\",\"time\":\"");

	strcat(JSON,prop->time);

	JSON = mergeStrings(JSON,"\",\"text\":\"\",\"isUTC\":");

	if(prop->UTC == true)
	{

		JSON = mergeStrings(JSON,"true}");

	}
	else
	{

		JSON = mergeStrings(JSON,"false}");

	}

	return JSON;

}


/** Function for creating a DateTime struct from an JSON string
 *@pre String is not null, and is valid
 *@post String has not been modified in any way, and a DateTime struct has been created
 *@return a newly allocated DateTime.  May be NULL.
 *@param str - a pointer to a JSON string
 {"isText":false,"date":"19540203","time":"123012","text":"","isUTC":true} 
 {"isText":true,"date":"","time":"","text":"circa 1960","isUTC":false} 
 **/
DateTime* JSONtoDT(const char* str)
{

	DateTime* date;

	char* string;

	int quoteBool;
	int backSlashBool;
	int isTextBool;
	int dateBool;
	int timeBool;
	int textBool;
	int isUTCBool;
 
	int stringCounter;

	if(str == NULL)
	{

		return NULL;

	}

	if(str[0] != '{' || str[strlen(str)-1] != '}')
	{

		return NULL;

	}

	date = malloc(sizeof(DateTime*)+sizeof(char)*strlen(str)+10);
	date->UTC = false;
	date->isText = false;  
	strcpy(date->date,""); 
	strcpy(date->time,""); 
	strcpy(date->text,"");


	string = malloc(sizeof(char)*(strlen(str)+10));
	stringCounter = 0;
	quoteBool = 0;

	for (int i = 1; i < (strlen(str)-1); i++)
	{
	
		if(str[i] == '\"' && backSlashBool != 0)
		{

			quoteBool++;

		}
		if(str[i] == '\\' && backSlashBool == 0)
		{

			string[stringCounter] = str[i];
			string[stringCounter+1] = '\0';
			stringCounter++;

			backSlashBool++;

		}
		else
		{

			string[stringCounter] = str[i];
			string[stringCounter+1] = '\0';
			stringCounter++;

			backSlashBool = 0;

		}

		if(quoteBool == 2)
		{

			if(strcmp(string,"isText") == 0)
			{

				isTextBool++;
				stringCounter = 0;

			}

			if(strcmp(string,"date") == 0)
			{

				dateBool++;
				stringCounter = 0;
				
			}
			if(strcmp(string,"time") == 0)
			{

				timeBool++;
				stringCounter = 0;
				
			}
			if(strcmp(string,"text") == 0)
			{

				textBool++;
				stringCounter = 0;
				
			}
			if(strcmp(string,"isUTC") == 0)
			{

				isUTCBool++;
				stringCounter = 0;
				
			}

		}

		if(quoteBool == 4)
		{

			quoteBool = 0;

			if(isTextBool == 1)
			{

				isTextBool = 0;

				if(strcmp(string,"true") == 0)
				{

					date->isText = true;

				}

			}
			else if(dateBool == 1)
			{
				
				dateBool = 0;

				strcpy(date->date,string);


			}
			else if(timeBool == 1)
			{
				
				timeBool = 0;

				strcpy(date->time,string);

			}
			else if(textBool == 1)
			{
				
				textBool = 0;

				strcpy(date->text,string);

			}
			else if(isUTCBool == 1)
			{
				
				isUTCBool = 0;

				date->UTC = true;

			}

		}
		
	}

	free(string);

	return date;

}


/** Function for creating a Card struct from an JSON string
 *@pre String is not null, and is valid
 *@post String has not been modified in any way, and a Card struct has been created
 *@return a newly allocated Card.  May be NULL.
 *@param str - a pointer to a JSON string
 **/
Card* JSONtoCard(const char* str)
{

	
	Card* obj;

	Property* fn;

	char* token;
	char* string;

	int nameLength;

	if(str == NULL)
	{

		return NULL;

	}

	string = malloc(sizeof(char)*(strlen(str)+10));

	strcpy(string,str);

	token = strtok(string,":");

	if(token == NULL)
	{

		return NULL;

	}

	if(strcmp("{\"FN\"",token)!= 0)
	{

		return NULL;

	}

	token = strtok(NULL,"");

	fn = malloc(sizeof(Property));

	fn->name = malloc(sizeof(char)*(strlen(token)+5));

	nameLength = 0;

	for (int i = 0; i < strlen(token); i++)
	{
		
		if(token[i] != '\"' ||token[i] != '}')
		{

			fn->name[nameLength] = token[i];
			nameLength++;

			fn->name[nameLength] = '\0';

		}

	}

	obj = malloc(sizeof(Card));
	obj->fn = NULL;
	obj->anniversary = NULL;
	obj->birthday = NULL;
	obj->optionalProperties = initializeList(&printProperty,&deleteProperty,&compareProperties);

	obj->fn = fn;

	free(string);

	return obj;

}


/** Function for adding an optional Property to a Card object
 *@pre both arguments are not NULL and valid
 *@post Property has not been modified in any way, and its address had been added to 
 *      Card's optionalProperties list
 *@return void
 *@param obj - a pointer to a Card struct
 *@param toBeAdded - a pointer to an Property struct
**/
void addProperty(Card* card, const Property* toBeAdded)
{

	if(card == NULL || toBeAdded == NULL)
	{

		return;

	}

	if(card->optionalProperties== NULL)
	{

		return;

	}

	insertBack(card->optionalProperties,(void*)toBeAdded);

}

// *************************************************************************
