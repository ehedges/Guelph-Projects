/*Evan Hedges, 0898140, 2750*/
#include "LinkedListAPI.h"
#include "CalendarParser.h"

#ifndef _MAIN_FUNCTIONS_
#define _MAIN_FUNCTIONS_

/*Generic functions for the main Parsing list*/
char* printFunction(void* data);
int compareFunction(const void* data,const void* value);
void deleteFunction(void* data);

void deleteEvent(Event* data);
void deleteAlarm(void* alarm);
char* printProperties(void* prop);
char* printAlarm(void* alarm);
char* printEvent(const Event* event);

ErrorCode parseList(List list, Calendar** obj);
ErrorCode createEvent(Event* event, ListIterator current);
ErrorCode createAlarm(List list, ListIterator current);

#endif