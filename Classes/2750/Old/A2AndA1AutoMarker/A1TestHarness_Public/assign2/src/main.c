#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GEDCOMparser.h"

int main(int argc, char *argv[])
{

	GEDCOMerror temp;

	GEDCOMerror error;

	GEDCOMobject* obj = NULL;
	GEDCOMobject* tempGED = NULL;

	Individual* tempIndiv;

	char* string;
	char* errorString;

	temp  = createGEDCOM(argv[1],&obj);

	errorString = printError(temp);

	printf("%s\n",errorString);
	free(errorString);
	if(temp.type == OK)
	{	
		char* LUL = malloc(sizeof(char)*1000);

		strcpy(LUL,"{\"givenName\":\"William\",\"surname\":\"Shakespeare\"}");

		tempIndiv = JSONtoInd(LUL);

		string = indToJSON(tempIndiv);

		free(string);

		free(LUL);

		LUL = malloc(sizeof(char)*1000);

		strcpy(LUL,"{\"source\":\"Blah\",\"gedcVersion\":\"5.5\",\"encoding\":\"ANSEL\",\"submitterName\":\"Some dude\",\"submitterAddress\":\"nowhere\"}");

		tempGED = JSONtoGEDCOM(LUL);

		free(LUL);

		if(tempGED != NULL)
		{

			addIndividual(tempGED,tempIndiv);

			LUL = printGEDCOM(obj);
			//printf(":%s\n",LUL);
			free(LUL);			

			LUL = iListToJSON(obj->individuals);

			writeGEDCOM("TESTWRITE",obj);

			free(LUL);

			//printf("LUL:%s\n",LUL);
			//free(LUL);	

			error.type = validateGEDCOM(tempGED);

			

			LUL = printError(error);
			//printf("%s\n",LUL);			
			free(LUL);

			List genList;
			genList = getAncestorListN(obj,tempIndiv,0);

			//printf("%s\n",iListToJSON(obj->individuals));
			//printf("%d\n",getLength(genList));
			LUL = gListToJSON(genList);
			printf("%s\n",LUL);
			free(LUL);
			//clearList(&genList);
			//clearList(&genList);

			genList = getDescendantListN(obj,tempIndiv,0);
			LUL = gListToJSON(genList);
			//printf("%d\n",getLength(genList));
			printf("%s\n",LUL );

			free(LUL);
			deleteGEDCOM(tempGED);

			//clearList(&genList);
		}

		deleteGEDCOM(obj);

	}

	
	return 0;
}