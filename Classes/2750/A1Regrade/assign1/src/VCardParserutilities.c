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
Purpose: Checks to maake sure the file extension is in the name and valid
In: Strings for filename  and type (type does not have the dot). Integer for the extension length (length must include dot)
Out: Integer, Valid (0) oor invalid (1-6);
***************************************************************************/
int extensionCheck(char* fileName, char* type, int typeLength)
{

	char* name;
	char* tokenExtension;
	/* Chhecks to ensure that the input into the function is valid*/
	if(type == NULL || fileName == NULL)
	{

		return 1;

	}
	/*Requires an extension of atleast 3 characters.*/
	if(typeLength < 4)
	{

		return 2;

	}
	/*Ensures that length of type and typelength are the same.*/
	if((strlen(type)+1) != typeLength)
	{

		return 3;

	}
	/*Ensures that there iss a file name along with the extension.*/
	if (strlen(fileName) < 5)
	{
		
		return 4;

	}
		/*Copies the string to ensure it's not changed*/
	name = malloc(sizeof(char)*(strlen(fileName)+5));

	strcpy(name,fileName);

	strtok(name,".");
	tokenExtension = strtok(NULL,"");
	/*Checks there is an extension of some sort*/
	if(tokenExtension == NULL)
	{

		free(name);
		return 5;

	}
	/*Ensures that the extension in the file name and the extension in string are the same.*/
	if(strcmp(type,tokenExtension) != 0)
	{

		free(name);
		return 6;

	}

	free(name);

	return 0;

}


/***************************************************************************
Purpose: Combine two strings.
In: A main string, then attachement string.
Out: String.
***************************************************************************/
char* mergeStrings(char* dest, char* string)
{

	char* temp;

	if(string != NULL && dest != NULL)
	{
		
		int length; 

		temp = malloc(sizeof(char)*(strlen(dest)+strlen(string)+5));
		length = strlen(dest);

		for (int i = 0; i < length; i++)
		{
			
			temp[i] = dest[i];
			temp[i+1] = '\0';

		}

		for (int i = 0; i < strlen(string); i++)
		{
			
			temp[i+length] = string[i];
			temp[i+length+1] ='\0';

		}

		free(dest);
		return temp;

	}

	return dest;
	
}

/***************************************************************************
Purpose: Combine two strings.
In: A main string, string for the ending.
Out:  integer, 0 valid, -1 with invalid input, 1 with invalid line ending.
***************************************************************************/
int lineEndingChecker(char* string, char* ending)
{

	/*checks that the strings exist*/
	if(string == NULL || ending == NULL)
	{

		return- 1;

	}

	/*Checks to ensure that there is some value there*/
	if(strlen(string) ==  0 || strlen(ending) == 0 || strlen(string) < strlen(ending))
	{

		return -1;

	}

	for (int i = 0; i < strlen(ending); i++)
	{

		if(string[strlen(string)-strlen(ending)+i] != ending[i])
		{

			return 1;

		}

	}


	return 0;

}

/***************************************************************************
Purpose: Remove the newline and a space.
In: A main string.
Out:  Same string with no ending and the first tab or space removed.
***************************************************************************/
char* cleanseNewline(char* string)
{

	int offset = 0;

	char* tempString = malloc(sizeof(char)*strlen(string)+200);
	//Finds new line, replaces with terminator
	for(int i = 0; i < strlen(string); i++)
	{

		if(string[i] == '\n' || string[i] == '\r')
		{

			break;

		}
		else
		{

			tempString[i] = string[i];
			tempString[i+1]= '\0';

		}

	}
	//Removes the spaces
	if(string[offset] == ' ' || string[offset] == '\t')
	{

		for (int i = 0; i < strlen(string)+1; i++)
		{

			tempString[i] = tempString[i+1];

		}


	}
	
	strcat(tempString,"\0");

	free(string);
	return(tempString);

}
/***************************************************************************
Purpose: Take in a file. Turn it into a list.
In: A main string, string for the ending.
Out:  List, either empty if there is nothing there or with lines or characters.
***************************************************************************/
VCardErrorCode readToList(char* fileName,List* list)
{

	FILE* ptr;

	char* inputString;
	char* multiString;
	char* endCheck;
	char* token;

	void* input;

	int breakBool;
	int lineEndingCheck;
	/*Checks to ensure that the extension is of either type*/
	if(extensionCheck(fileName,"vcf",4) != 0) 
	{

		if(extensionCheck(fileName,"vcard",6) != 0)
		{

			return INV_FILE;

		}

	}
	/*Opens, checks for valid file*/
	ptr = fopen(fileName,"r");

	if(ptr == NULL)
	{

		return INV_FILE;

	}
	/*Starts parsing*/
	inputString = malloc(sizeof(char)*1000);
	fgets(inputString,750,ptr);
	/*If there is nothing*/
	if(inputString == NULL)
	{
		fclose(ptr);
		free(inputString);
		return INV_FILE;

	}

	breakBool = 0;
	/*Checks for begin and version*/
	for(int i = 0; i < strlen(inputString)+1; i++)
	{

		inputString[i] = toupper(inputString[i]);

	}

	inputString = cleanseNewline(inputString);

	if(strcmp("BEGIN:VCARD",inputString) != 0)
	{

		fclose(ptr);
		free(inputString);
		return INV_CARD;

	}

	fgets(inputString,750,ptr);

	if(inputString == NULL)
	{

		fclose(ptr);
		free(inputString);
		return INV_CARD;

	}

	inputString = cleanseNewline(inputString);

	for(int i = 0; i < strlen(inputString)+1; i++)
	{

		inputString[i] = toupper(inputString[i]);

	}

	if(strcmp("VERSION:4.0",inputString) != 0)
	{

		fclose(ptr);
		free(inputString);
		return INV_CARD;

	}

	endCheck = malloc(sizeof(char)*1000);
	/*Loop to read in the file,. End of file condition is the line END:VCARD*/
	while(fgets(inputString,750,ptr) != NULL)
	{

		lineEndingCheck = lineEndingChecker(inputString,"\r\n");

		if(lineEndingCheck != 0)
		{

			fclose(ptr);
			free(inputString);
			free(endCheck);
			return INV_CARD;

		}

		/*Error with fgets or reaches EOF before END*/
		if(inputString == NULL)
		{

			fclose(ptr);
			free(endCheck);
			return INV_CARD;

		}
		/*Checking for end with case insensitive. */
		strcpy(endCheck,inputString);

		for(int i = 0; i < strlen(endCheck); i++)
		{

			endCheck[i] = toupper(endCheck[i]);

		}

		if(strlen(endCheck) < 4)
		{

			fclose(ptr);
			free(inputString);
			free(endCheck);
			return INV_CARD;

		}

		endCheck = cleanseNewline(endCheck);

		token = strtok(endCheck,":");
		if(token == NULL)
		{

			fclose(ptr);
			free(inputString);
			free(endCheck);
			return INV_CARD;

		}
		/*End  of file condition*/
		if(strcmp("END",token) == 0)
		{

			token = strtok(NULL,"");

			if(strcmp("VCARD",token) == 0)
			{

				breakBool = 1;

			}

		}
		else if(strcmp("VERSION",token)==0)
		{

			fclose(ptr);
			free(inputString);
			free(endCheck);
			return INV_CARD;

		}
		else
		{
						
			/*If the string is folded, remove the incomplete string from the back, and add the next line to it. Otherwise, add it*/ 
			if(inputString[0] == ' '|| inputString[0] == '\t')
			{

				inputString = cleanseNewline(inputString);
				input = deleteDataFromList(list,getFromBack(list));
				multiString = (char*)input;
				multiString = mergeStrings(multiString,inputString);
				insertBack(list,multiString);

			}
			else
			{

				inputString = cleanseNewline(inputString);
				insertBack(list,(void*)inputString);
				inputString = malloc(sizeof(char)*1000);

			}

		}

	}

	if(breakBool != 1)
	{

		fclose(ptr);
		free(inputString);
		free(endCheck);
		return INV_CARD;

	}

	/*Cleaning*/
	free(inputString);
	free(endCheck);
	fclose(ptr);

	return OK;

}

VCardErrorCode createDateTime(DateTime** event, char* values)
{

	char numbers[12] = "1234567890-";

	int timeBool;
	int numberBool;
	int counter;

	strcpy((*event)->date,"");
	strcpy((*event)->time,"");
	strcpy((*event)->text,"");
	(*event)->UTC = false;
	(*event)->isText = false;

	timeBool = 0;

	/*Checks for text*/	
	numberBool = 0;

	for (int i = 0; i < 12; i++)
	{
		
		if(values[0] == numbers[i])
		{

			numberBool = 1;

		}

	}
	

	if(numberBool == 1)
	{
		counter = 0;

		for (int i = 0; i < strlen(values); i++)
		{

			if(values[i] == 'T')
			{

				timeBool = 1;

			}
			else if(values[i] == 'Z')
			{

				if(i != (strlen(values)-1))
				{

					return INV_PROP;

				}

				(*event)->UTC = true;

			}
			else if(timeBool == 0)
			{

				if(strlen((*event)->date) == 8)
				{

					return INV_PROP;

				}

				(*event)->date[i] = values[i];
				(*event)->date[i+1] = '\0';

			}
			else if(timeBool == 1)
			{
				
				if(counter == 6)
				{

					break;

				}

				numberBool = 0;

				for (int k = 0; k < 12; k++)
				{
					
					if(values[i] == numbers[k])
					{

						numberBool = 1;

					}

				}

				if(numberBool == 0)
				{

					return INV_PROP;

				}

				(*event)->time[counter] = values[i];
				(*event)->time[counter+1] = '\0';
				counter++;

			}			
			
		}

		if(timeBool == 1)
		{

			if(strlen((*event)->time) < 1)
			{

				return INV_PROP;
				
			}

		}

	}
	else
	{

		(*event)->isText = true;
		strcpy((*event)->text,values);

	}

	return OK;

}

VCardErrorCode createProperty(char*name, char*group, char*parameters, char*values, Property** prop)
{

	VCardErrorCode error;

	Parameter* tempParameter;

	char* insertString;
	char* tempParameterName;
	char* tempParameterValue;

	int backlashBool;
	int counter;
	int parameterBool;
	int storeBool; 
	int parameterInsertBool;

	error = OK;

	if(parameters != NULL)
	{

		if(strlen(parameters) == 0)
		{

			error = INV_PROP;

			return error;

		}

	}

	/*Misc property creation*/
	(*prop)->name = NULL;
	(*prop)->group = NULL;
	(*prop)->parameters = initializeList(&printParameter,&deleteParameter,&compareParameters);
	(*prop)->values = initializeList(&printValue,&deleteValue,&compareValues);

	/*Storing property name*/
	(*prop)->name = malloc(sizeof(char)*(strlen(name)+10));
	strcpy((*prop)->name,name);

	/*In name we seperated by the first period. If there is multiple groups, they will be attached to the rest of the name, check for that here.*/
	for (int i = 0; i < strlen((*prop)->name); i++)
	{
		
		if((*prop)->name[i] == '.')
		{

			error = INV_PROP;

			return error;

		}

	}

	counter = 0;
	backlashBool = 0;

	if(group != NULL)
	{

		(*prop)->group = malloc(sizeof(char)*(strlen(group)+5));
		strcpy((*prop)->group,group);

	}
	else
	{

		(*prop)->group = malloc(sizeof(char)*(5));
		strcpy((*prop)->group,"");
	

	}

	
	
	/*If there is parameters*/
	parameterInsertBool = 0;

	if(parameters != NULL)
	{

		if(strlen(parameters) < 3)
		{

			error = INV_PROP;

			return error;

		}

		tempParameterName = malloc(sizeof(char)*(205));
		tempParameterValue = malloc(sizeof(char)*(strlen(parameters)+5));

		strcpy(tempParameterValue,"");
		strcpy(tempParameterName,"");

		parameterBool = 0;
		parameterInsertBool = 0;

		/*Go through the string*/

		for (int i = 0; i < strlen(parameters)+1; i++)
		{

			if(parameters[i] == ';')
			{
				/*Semi colon means we have a new parameter*/
				if(strcmp(tempParameterName,"") == 0)
				{

					free(tempParameterName);
					free(tempParameterValue);

					return INV_PROP;

				}

				parameterBool = 0;
				counter = 0;
				tempParameter = malloc(sizeof(Parameter)+sizeof(char)*(strlen(tempParameterValue)+5));
				strcpy(tempParameter->name,tempParameterName);
				strcpy(tempParameter->value,tempParameterValue);

				insertBack((*prop)->parameters,tempParameter);

				free(tempParameterName);
				free(tempParameterValue);

				tempParameterName = malloc(sizeof(char)*(205));
				tempParameterValue = malloc(sizeof(char)*(strlen(parameters)+5));

				strcpy(tempParameterValue,"");
				strcpy(tempParameterName,"");
				parameterInsertBool = 0;				

			}
			else if(parameters[i] == '=')
			{
				/*Equal means we have a paramtere value*/
				parameterBool = 1;
				counter = 0;
				parameterInsertBool = 1;

			}
			else if(parameterBool == 0)
			{
				/*Stores the name*/
				tempParameterName[counter] = parameters[i];
				counter++;
				tempParameterName[counter] = '\0';
				parameterInsertBool = 1;

			}
			else
			{
				/*Stores the value*/
				tempParameterValue[counter] = parameters[i];
				counter++;
				tempParameterValue[counter] = '\0';
				parameterInsertBool = 1;

			}

		}

	}
	/*Incase the last value has not been put in*/
	if(parameterInsertBool == 1)
	{

		parameterBool = 0;
		counter = 0;
		tempParameter = malloc(sizeof(Parameter)+sizeof(char)*(strlen(tempParameterValue)+5));
		strcpy(tempParameter->name,tempParameterName);
		strcpy(tempParameter->value,tempParameterValue);
		insertBack((*prop)->parameters,tempParameter);
		parameterInsertBool = 0;

		free(tempParameterName);
		free(tempParameterValue);

	}

	/*This copies and stores the values*/
	insertString = malloc(sizeof(char)*(strlen(values)+10));
	strcpy(insertString,"");
	storeBool = 0;
	for (int i = 0; i < strlen(values)+1; i++)
	{
		/*Checks to see if there is a blackslash, if there is a backslash before a comma, means we want to keep the comma, triggers the bool*/
		if(values[i] == '\\' && backlashBool == 0)
		{

			backlashBool = 1;

		}
		else if((values[i] == ';') && backlashBool == 0)
		{
			/*Comma is the seperator, new value*/
			counter = 0;
			insertBack((*prop)->values,(void*)insertString);
			insertString = malloc(sizeof(char)*(strlen(values)+10));
			strcpy(insertString,"");
			storeBool = 0;

		}
		else
		{
			/*Stores the values*/
			backlashBool = 0;
			insertString[counter] = values[i];
			counter++;
			insertString[counter] = '\0';
			storeBool = 1;

		}

	}

	/*If there is only one value, may not have a comma, and may not insert the last element, checks for this*/
	if(storeBool == 1)
	{

		insertBack((*prop)->values,(void*)insertString);

	}	

	return error;

}