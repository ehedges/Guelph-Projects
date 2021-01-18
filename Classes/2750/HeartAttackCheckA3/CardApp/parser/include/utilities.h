#ifndef _UTILTIES_H
#define _UTILTIES_H
/*
Evan Hedges 0898140
CIS 2750, F18
*/
#include "VCardParser.h"
#include "LinkedListAPI.h"
/***************************************************************************
Purpose: Checks to maake sure the file extension is in the name and valid
In: Strings for filename  and type (type does not have the dot). Integer for the extension length (length must include dot)
Out: NInteger, Valid (0) oor invalid (1)
***************************************************************************/
int extensionCheck(char* fileName, char* type, int typeLength);
int lineEndingChecker(char* string, char* ending);
char* cleanseNewline(char* string);
char* mergeStrings(char* dest, const char* string);
VCardErrorCode readToList(char* fileName,List*list);
VCardErrorCode createDateTime(DateTime** event, char* values);
VCardErrorCode createProperty(char*name, char*group, char*parameters, char*values, Property** prop);
char* writeProperty(const Property* prop);
char* writeDate(const DateTime* date);
VCardErrorCode checkParameters(const Property* prop);
VCardErrorCode validDate(DateTime* date);
VCardErrorCode validateProperty(const Property* prop);
char* nameNumJSON();
char* openVCard(char* fileName);
char* VCardtoJSON(Card* card);

#endif	