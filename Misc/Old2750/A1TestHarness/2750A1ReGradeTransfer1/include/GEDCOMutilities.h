/*****************************
Evan Hedges 0898140
CIS 2750, W18

Professor: Denis Nikitenko
*****************************/

#include "GEDCOMparser.h"

int checkNums(char* string);

void cleanseNewline(char* string);
void deleteHeader(Header* tobeDeleted);
void destroyList(List tempList);
void destroySubmitter(Submitter* tobeDeleted);

char* printHeader(Header* head);
char* printSubmitter(Submitter* submit);
char* printFieldList(List list);

GEDCOMerror createSubmitter(GEDCOMobject** obj,List fileList,char* subRef,int line);
GEDCOMerror listIndividuals(GEDCOMobject** obj, List fileList, int line);
GEDCOMerror listFamily(GEDCOMobject** obj, List fileList,int line);
GEDCOMerror listEvents(Individual* indiv, List fileList, int line, ListIterator iter,int* depth);
GEDCOMerror initIndiv(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter);
GEDCOMerror initFam(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter);

Individual* getPerson(char* token,GEDCOMobject** obj); 

