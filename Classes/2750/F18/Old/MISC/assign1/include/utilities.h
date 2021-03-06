#ifndef _UTILTIES_H
#define _UTILTIES_H

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
char* mergeStrings(char* dest, char* string);
VCardErrorCode readToList(char* fileName,List*list);
VCardErrorCode createDateTime(DateTime** event, char* values);
VCardErrorCode createProperty(char*name, char*group, char*parameters, char*values, Property** prop);

#endif	