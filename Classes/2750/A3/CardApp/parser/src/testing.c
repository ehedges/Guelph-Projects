#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VCardParser.h"
#include "utilities.h"
#include "LinkedListAPI.h"

int main(int argc, char const *argv[])
{

	char* string;
	//int extenValue;

	string = nameNumJSON();

	if(string == NULL)
	{

		exit(0);

	}
	
	printf("%s\n",string);

	free(string);

	string = openVCard("./uploads/testCard-Ann.vcf");
	
	printf("%s\n",string);

	free(string);

	string = openVCard("./uploads/testCard.vcf");
	
	printf("%s\n",string);

	free(string);
	string = openVCard("./uploads/testCardMin.vcf");
	
	printf("%s\n",string);

	free(string);

	printf("HELLO");
	return 0;
}