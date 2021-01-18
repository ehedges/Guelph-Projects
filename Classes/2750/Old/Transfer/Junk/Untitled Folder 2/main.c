#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GEDCOMparser.h"

int main(int argc, char *argv[])
{

	GEDCOMerror temp;

	GEDCOMobject ** obj = NULL;

	char* string;

	temp  = createGEDCOM(argv[1],obj);

	string  = printError(temp);

	printf("%s",string);

	free(string);

	return 0;
}