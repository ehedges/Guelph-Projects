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
void clearReferences(List list);
void dummyDelete(void* tobeDeleted);
void descendantList(Individual* indiv, List* masterList, unsigned int maxGen, int depth);
void ancestorsList(Individual* indiv, List* masterList, unsigned int maxGen, int depth);

char* printHeader(Header* head);
char* printSubmitter(Submitter* submit);
char* printFieldList(List list);
//char* writeIndividual(Individual* indiv, int refCount);
//char* writeFamily(Family* fam,List listIndiv,List stringList,int refCount);
//char* writeFamXref(Individual* indiv,List listIndiv,List stringList,char* refString,char* string);
//char* writeEvent(Event* event);

GEDCOMerror createSubmitter(GEDCOMobject** obj,List fileList,char* subRef,int line);
GEDCOMerror listIndividuals(GEDCOMobject** obj, List fileList, int line);
GEDCOMerror listFamily(GEDCOMobject** obj, List fileList,int line);
GEDCOMerror listEvents(List* list, List fileList, int line, ListIterator iter,int* depth);
GEDCOMerror initIndiv(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter);
GEDCOMerror initFam(char* tempRef,List fileList,GEDCOMobject** obj, int line,ListIterator iter);

Individual* getPerson(char* token,GEDCOMobject** obj);
Individual* copyIndividual(Individual* toCopy);

