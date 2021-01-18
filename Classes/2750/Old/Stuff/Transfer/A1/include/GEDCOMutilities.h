#include "GEDCOMparser.h"

void cleanseNewline(char* string);
int checkNums(char* string);
void deleteHeader(Header* tobeDeleted);
void destroyList(List tempList);

char* printHeader(Header* head);
char* printSubmitter(Submitter* submit);
char* printFieldList(List list);

GEDCOMerror createSubmitter(GEDCOMobject** obj,List fileList,char* subRef,int line);
GEDCOMerror listIndividuals(GEDCOMobject** obj, List fileList, int line);
GEDCOMerror listFamily(GEDCOMobject** obj, List fileList,int line);
GEDCOMerror listEvents(GEDCOMobject** obj, List fileList,int line);
GEDCOMerror initIndiv(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter);
GEDCOMerror initFam(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter);

Individual* getPerson(char* token,GEDCOMobject** obj); 
/*
GEDCOMerror printField(List list);
GEDCOMerror deleteField(List list, void* tobeDeleted);
GEDCOMerror compareFields(List list, void* tobeDeleted);*/
