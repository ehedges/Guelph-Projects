/*
CIS 2750, A1
Evan Hedges 0898140
Current professor is DENIS Nikitenko*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "MainFunctions.h"
#include "CalendarParser.h"

/*Print from the property list*/

char* printProperties(void* data)
{

	Property* value;

	char* tempString;
	//char* storageString;

	value = (Property*)data;

	tempString = malloc(sizeof(char)*(strlen(value->propName)+strlen(value->propDescr)));

	strcpy(tempString,value->propName);

	return(tempString);

}

/*Delete Property*/

void deleteProperties(void * data)
{

	free(data);

}

/*Print error*/

const char* printError(ErrorCode err)
{
	char* errorArray[10];

	errorArray[0] = "Ok.\n";
	errorArray[1] = "Error: Invalid File.\n";
	errorArray[2] = "Error: Invalid Calendar.\n.\n";
	errorArray[3] = "Error: Wrong Version.\n";
	errorArray[4] = "Error: Duplicate Version.\n";
	errorArray[5] = "Error: Invalid Product Id.\n";
	errorArray[6] = "Error: Duplicate Product ID.\n";
	errorArray[7] = "Error: Invalid Event.\n";
	errorArray[8] = "Error: Invalid Creation time.\n";
	errorArray[9] = "Error: Unknown problem.\n";

	return(errorArray[err]);

}

/*Reads the file and puts into a list*/

ErrorCode createCalendar(char* fileName, Calendar** obj)
{

	FILE* ptrFile;

	List inputList;

	ErrorCode parseError;

	char* inputString; 
	char* tempString;

	int offSet = 0;
	/*checks over to make sure the file is valid*/
	if(fileName == NULL)
	{

		return(INV_FILE);

	}

	if(strlen(fileName) <5)
	{

		return(INV_FILE);

	}
	if(fileName[strlen(fileName)-1] != 's' && fileName[strlen(fileName)-2] != 'c' && fileName[strlen(fileName)-3] != 'i' && fileName[strlen(fileName)-4] != '.')
	{

		return(INV_FILE);

	}
	
	ptrFile = fopen(fileName, "r");

	if(ptrFile == NULL)
	{
			
		fclose(ptrFile);

		return(INV_FILE);

	}

	/*Read in the file and put in linkedlist*/

	inputList = initializeList(&printFunction,&deleteFunction,NULL);

	inputString = malloc(sizeof(char)*1000);

	printf("Allocated object \n");

	while(fgets(inputString,100,ptrFile))
	{

		if(inputString[strlen(inputString)-1] == '\n')
		{

			inputString[strlen(inputString)-1] = '\0';

		}

		offSet = 0;

		while(inputString[offSet] == ' ' || inputString[offSet] == '\t')
		{

			offSet++;

		}

		tempString = malloc(sizeof(char) * (strlen(inputString)+1));

		for (int i = 0; i <= strlen(inputString); i++)
		{
			
			tempString[i] = inputString[i+offSet];

		}

		insertBack(&inputList,tempString);

		free(inputString);

		inputString = malloc(sizeof(char)*1000);
		
	}

	

	if(inputList.head == NULL || inputList.tail == NULL)
	{

		fclose(ptrFile);

		return(INV_FILE);

	}

	parseError = parseList(inputList,obj);

	clearList(&inputList);

	free(inputString);

	fclose(ptrFile);

	return(parseError);

}

/* Takes the linked list and turns into a calendar*/

ErrorCode parseList(List list, Calendar** obj)
{
	
	ListIterator current;

	ErrorCode error = OK;

	char* tempString;
	char* getData;
	char* token;
	char* tempTrack;

	int calendarBool = 0;
	int eventBool = 0;
	int exitBool = 0;

	current = createIterator(list);

	getData = (char*)nextElement(&current);

	if(getData == NULL)
	{

		return(INV_FILE);

	}

	/*checks the different types*/
	while(getData!= NULL && error == 0)
	{

		tempString = malloc(sizeof(char)*(strlen(getData)+1));
		strcpy(tempString,getData);

		if(tempString[0] == ';')
		{

			free(tempString);

		}
		else
		{

			token = strtok(tempString,":;");

			if(strcmp(token,"BEGIN") == 0)
			{

				token = strtok(NULL,":;");

				for (int i = 0; i < strlen(token); i++)
				{

					if(token[i] == '\r')
					{

						token[i] = '\0';

					}

				}

				if(strcmp(token,"VCALENDAR") == 0)
				{

					if(calendarBool == 0)
					{

						

						*obj = malloc(sizeof(Calendar)*1);

						(*obj)->event = NULL;
						calendarBool = 1;

						(*obj)->prodID[0] = '\0';
						(*obj)->version = -1.0;

					}
					else
					{

						deleteCalendar(*obj);
						return(INV_CAL);

					}

				}
				else if(strcmp(token,"VEVENT") == 0)
				{

					if(calendarBool == 1 && eventBool == 0)
					{

						eventBool = 1;
						(*obj)->event = malloc(sizeof(Event*)*1);

						error = createEvent((*obj)->event,current);
						printf("HERE\n");
						if(error == 0)
						{

							while(exitBool == 0)
							{

								tempTrack = (char*)nextElement(&current);

								for (int i = 0; i < strlen(tempTrack); i++)
								{

									if(tempTrack[i] == '\r')
									{

										tempTrack[i] = '\0';

									}

								}

								if(strcmp(tempTrack,"END:VEVENT") != 0)
								{

									exitBool = 1;

								}

							}
							

						}

					}
					else if(calendarBool == 0)
					{	
						printf("TestHERE\n");
						deleteCalendar(*obj);

						return(INV_CAL);

					}
					else if(eventBool == 1)
					{

						deleteCalendar(*obj);

						return(INV_EVENT);

					}

				}
				else if(strcmp(token,"VALARM") == 0)
				{
					printf("Parse Alarm\n");
					if(calendarBool == 1 && eventBool == 1)
					{

						printf("Parse Alarm\n");
						(*obj)->event->alarms = initializeList(&printAlarm,&deleteAlarm,NULL);

					}
					else if(calendarBool == 0)
					{
						printf("Error Alarm\n");
						deleteCalendar(*obj);

						return(INV_CAL);

					}
					else if(eventBool == 1)
					{

						printf("Error Event\n");
						deleteCalendar(*obj);
						return(INV_EVENT);

					}

				}

			}
			else if(strcmp(token,"VERSION") == 0)
			{

				token = strtok(NULL,":;");

				if((*obj)->version == -1.0)
				{

					if(atof(token) < 2.00)
					{

						free(tempString);

						return(INV_VER);

					}
					(*obj)->version = atof(token);


				}
				else
				{

					free(tempString);

					return(DUP_VER);

				}

			}
			else if(strcmp(token,"PRODID") == 0)
			{

				if((*obj)->prodID == NULL)
				{

					free(tempString);
					deleteCalendar(*obj);

					return(DUP_PRODID);

				}
				else
				{

					token = strtok(NULL,":;");

					strcpy((*obj)->prodID,token);

				}


			}			
			else if(strcmp(token,"END") == 0)
			{

				token = strtok(NULL,":;");

				for (int i = 0; i < strlen(token); i++)
				{

					if(token[i] == '\r')
					{

						token[i] = '\0';

					}

				}

				if(strcmp(token,"VCALENDAR") == 0)
				{

					if(calendarBool == 0)
					{

						deleteCalendar(*obj);
						return(INV_CAL);

					}
					else
					{

						calendarBool = 0;

					}

				}
				
			}

		}

		if(tempString != NULL)
		{

			free(tempString);

		}

		getData = (char*)nextElement(&current);

	}

	if(calendarBool != 0)
	{
		printf("Error with Cal BOol\n");
		deleteCalendar(*obj);

		return(INV_CAL);

	}

	if(error != 0)
	{

		deleteCalendar(*obj);

	}

	printf("File parsed successfully.\n");

	return(OK);

}

/* Takes the list and creates the alarm list and the properties for the event*/

ErrorCode createEvent(Event* event, ListIterator current)
{

	ErrorCode error = OK;

	Property* tempProp;

	DateTime tempDate;

	List tempList;
	List alarmList;

	char* getData;
	char* token;
	char* tempString;
	char* propString;	

	int endBool = 0;
	int counter = 0;

	getData = (char*)nextElement(&current);

	tempList = initializeList(&printProperties,&deleteProperties,NULL); 
	alarmList = initializeList(&printAlarm,&deleteAlarm,NULL);

	if(getData == NULL)
	{

		return(INV_FILE);

	}	

	/*Parse the remaining sections and put into an event*/
	printf("Creating Event.\n");
	while(endBool == 0 && error == 0 && getData != NULL)
	{

		tempString = malloc(sizeof(char)*(strlen(getData)+2));
		strcpy(tempString,getData);
		printf("%s\n",tempString);
		if(tempString[0] == ';')
		{

			free(tempString);

		}
		else 
		{

			token = strtok(tempString,":;");

			if(strcmp(token,"BEGIN") == 0)
			{

				token = strtok(NULL,":;");

				for (int i = 0; i < strlen(token); i++)
				{

					if(token[i] == '\r')
					{

						token[i] = '\0';

					}

				}
				printf("%s\n",token);
				if(strcmp(token,"VALARM") == 0)
				{
					printf("Entering Event ALarms\n");
					error = createAlarm(alarmList,current);

				}
				else if(strcmp(token,"VCALENDAR") == 0)
				{

					error = INV_CAL;
					endBool = 1;

				}
				else if(strcmp(token,"VEVENT") == 0)
				{

					error = INV_EVENT;
					endBool = 1;
				}

			}
			else if(strcmp(token,"DTSTAMP") == 0)
			{

				token = strtok(NULL,":;");

				for (int i = 0; i < strlen(token); i++)
				{

					if(token[i] == '\r')
					{

						token[i] = '\0';

					}

				}

				if(token[(strlen(token)-1)] == 'Z')
				{

					tempDate.UTC = true;					

					for (int i = 0; i < 8; i++)
					{
						
						tempDate.date[i] = token[i];

						counter = i;

						
					}

					while(token[counter]!='T')
					{

						counter++;

					}

					for (int i = 0; i < 6; i++)
					{
						
						tempDate.time[i] = token[counter+i+1];

					}

				}

				event->creationDateTime = tempDate;
				
			}
			else if(strcmp(token,"UID") == 0)
			{

				token = strtok(NULL,":;");
				strcpy(event->UID,token);

				
			}
			else if(strcmp(token,"END") == 0)
			{

				token = strtok(NULL,":;");

				if(strcmp(token,"VCALENDAR") == 0)
				{

					error = INV_EVENT;

				}

				event->properties = tempList;
				event->alarms = alarmList;
				printf("Made Event.\n");
				return(error);
				
			}
			else
			{

				if(token != NULL)
				{
					
					tempProp = malloc(sizeof(Property) + (sizeof(char)*(strlen(token)+5)));	
						
					strcpy(tempProp->propName,token);
					token = strtok(NULL,":");

					propString = malloc(sizeof(char)*(strlen(token)+5));

					for (int i = 0; i < strlen(token); i++)
					{

						if(token[i] == '\r')
						{

							token[i] = '\0';

						}

					}

					strcpy(propString,token);
					token = strtok(NULL,":");

					while(token != NULL)
					{

						strcat(propString,":");
						propString = realloc(propString,sizeof(char)*(strlen(propString)+strlen(token)+5));
						strcat(propString,token);
						token = strtok(NULL,":");

					}	
					
					propString[strlen(propString)] = '\0';

					strcpy(tempProp->propDescr,propString);					
					insertBack(&tempList, (void*)tempProp);

				}

			}

		}

		free(tempString);

		getData = (char*)nextElement(&current);


	}

	return(error);

}

/*create the alarm, store teh properties*/

ErrorCode createAlarm(List list, ListIterator current)
{

	printf("Creating an Alarm\n");

	ErrorCode error = OK;

	Alarm* tempAlarm = malloc(sizeof(Alarm)*1);

	Property* tempProp = malloc(sizeof(Property));

	List tempList;

	char* getData;
	char* token;
	char* tempString;

	int endBool = 0;


	getData = (char*)nextElement(&current);

	tempList = initializeList(&printProperties,&deleteProperties,NULL); 

	if(getData == NULL)
	{

		return(INV_FILE);

	}

	tempString = malloc(sizeof(char)*(300));

	while(endBool == 0 && error == 0 && getData != NULL)
	{

		
		strcpy(tempString,getData);

		for (int i = 0; i < strlen(token); i++)
		{

			if(token[i] == '\r')
			{

				token[i] = '\0';

			}

		}

		printf("%s\n",token);
		if(tempString[0] == ';')
		{

			free(tempString);

		}
		else 
		{

			token = strtok(tempString,":;");
			printf("%s\n",token);
			for (int i = 0; i < strlen(token); i++)
			{

				if(token[i] == '\r')
				{

					token[i] = '\0';

				}

			}


			if(strcmp(token,"BEGIN") == 0)
			{

				token = strtok(NULL,":;");

				if(strcmp(token,"VALARM") == 0)
				{

					error = INV_EVENT;

				}
				else if(strcmp(token,"VCALENDAR") == 0)
				{

					error = INV_CAL;
					endBool = 1;

				}
				else if(strcmp(token,"VEVENT") == 0)
				{

					error = INV_EVENT;
					endBool = 1;

				}				

			}
			else if(strcmp(token,"TRIGGER") == 0)
			{

				token = strtok(NULL,":;");
				printf("%s\n",token);
				strcpy(tempAlarm->action,token);

			}
			else
			{

				if(token != NULL)
				{

					tempProp = malloc(sizeof(Property) + sizeof(char)*strlen(token));			
					strcpy(tempProp->propName,token);
					token = strtok(NULL,":;");
					strcpy(tempProp->propDescr,token);
					insertBack(&tempList, (void*)tempProp);

				}

			}

		}

		getData = (char*)nextElement(&current);
	}

	tempAlarm->properties = tempList;

	insertBack(&list,(void*)tempAlarm);
	printf("Return\n");
	free(tempString);

	return(error);

}

/*Print out the calendar*/

char* printCalendar(const Calendar* obj)
{


	Event* tempEvent;

	char* calendarString = NULL;
	char* tempFloat;
	char* eventReturn;

	char inputString[20];
 
	int offSet = 0;
	int endString = 0;

	if(obj != NULL)
	{

		calendarString = malloc(sizeof(char)*(strlen(obj->prodID)+50));
		strcpy(calendarString,"Calendar: ");

		tempFloat = malloc(sizeof(char)*11);

		snprintf(tempFloat,10,"%f",obj->version);

		offSet = (strlen(calendarString)-1);

		if(calendarString)

		for (int i = 0; i < 8; i++)
		{
		
			calendarString[i+offSet] = tempFloat[i];
			endString = i+offSet;

		}

		offSet = (strlen(calendarString)-1);

		calendarString = realloc(calendarString,(sizeof(char)*(20+strlen(calendarString)+strlen(obj->prodID))));

		calendarString[endString] = ',';

		endString++;

		strcpy(inputString," prodID = ");

		for (int i = 0; i < strlen(inputString); i++)
		{
		
			calendarString[endString] = inputString[i];
			endString++;

		}

		for (int i = 0; i < strlen(obj->prodID); i++)
		{
		
			calendarString[endString] = obj->prodID[i];
			endString++;

		}

		calendarString[endString] = '\n';
		endString++;

	}

	tempEvent = obj->event;

	eventReturn = printEvent(tempEvent);
	calendarString = realloc(calendarString,(sizeof(char)*(strlen(calendarString)+strlen(eventReturn)+1)));

	for (int i = 0; i < strlen(eventReturn); i++)
	{
		
		calendarString[endString] = eventReturn[i];
		endString++;

	}

	calendarString[endString+1] = '\0';

	free(tempFloat);

	return(calendarString);

}

/*Delete the calendar*/

void deleteCalendar(Calendar* obj)
{

	Event* tempEvent;

	if(obj != NULL)
	{

		tempEvent = obj->event;

		if(tempEvent != NULL)
		{

			deleteEvent(tempEvent);

		}

	}
	
}

/*print out the event*/

char* printEvent(const Event* event)
{

	ListIterator current;

	char* eventString = malloc(sizeof(char)*(strlen(event->UID) + 20));
	char* tempDate = malloc(sizeof(char)*10);
	char* tempTime = malloc(sizeof(char)*8);
	char* allProps;
	Property* getProp;
	char* listProp;

	int length = strlen(event->UID);

	strcpy(eventString,event->UID);
	strcpy(tempDate,event->creationDateTime.date);
	strcpy(tempTime,event->creationDateTime.time);

	for (int i = 0; i < strlen(tempDate); i++)
	{
		
		eventString[length+i-1] = tempDate[i]; 

	}

	length = strlen(eventString);

	for (int i = 0; i < strlen(tempTime); i++)
	{
		
		eventString[length+i-1] = tempTime[i]; 

	}

	current = createIterator(event->properties);

	getProp = (Property*)nextElement(&current);
	listProp = malloc(sizeof(char)*(strlen(getProp->propDescr)+strlen(getProp->propName)));
	strcpy(listProp,getProp->propDescr);

	while(getProp != NULL)
	{

		listProp = realloc(listProp,sizeof(char)*(strlen(getProp->propDescr)+strlen(getProp->propName)+strlen(listProp)+10));
		strcat(listProp,"\n\t\t- ");
		strcat(listProp,getProp->propName);
		strcat(listProp," : ");
		strcat(listProp,getProp->propDescr);
		//listProp[strlen(listProp)-1] = '\n';


		printf("Desc:%s",getProp->propDescr);
		printf("Name:%s\n",getProp->propName);

		if(strcmp("\r",getProp->propDescr) == 0)
		{

			printf("Error with return.\n");

		}

		getProp = (Property*)nextElement(&current);

	}
	
	printf("HERE\n");
	allProps = malloc(sizeof(char)*(strlen(listProp)+20));
	strcpy(allProps,("\n\tOther properties:\n\t\t- "));

	strcat(allProps,listProp);

	return(allProps);

}

/*Delete all of the event and properties.*/

void deleteEvent(Event* event)
{

	if(&event->properties != NULL)
	{

		//clearList(&event->properties);

	}

	if(&event->alarms != NULL)
	{

		//clearList(&event->alarms);

	}

	free(event);

}

/*Print Alarm and properties*/

char* printAlarm(void* voidAlarm)
{

	Alarm* alarm = (Alarm*)voidAlarm;

	char* tempString = malloc(sizeof(char)*(strlen(alarm->trigger)+strlen(alarm->action)));

	int length = strlen(tempString);

	strcpy(tempString,alarm->trigger);

	for (int i = 0; i < strlen(alarm->action); i++)
	{
		
		tempString[length+i] = alarm->action[i]; 

	}

	return(tempString);

}

void deleteAlarm(void* alarm)
{

	/*Alarm* temp = (Alarm*)alarm;

	clearList(&temp->properties);

	if(temp->trigger != NULL)
	{

		free(temp->trigger);

	}

	free(temp);*/

}

char* printFunction(void* data)
{

	return((char*) data);

}

void deleteFunction(void* data)
{

	free(data);

}
