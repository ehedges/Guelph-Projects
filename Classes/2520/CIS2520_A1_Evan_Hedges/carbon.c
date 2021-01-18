/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: September 26th
	Assignment: 1
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a1.h"

/********************************************
Purpose: Rearrange carbon for all variations.
In: Nothing
Out: Prints all variations, outputs a file.
*********************************************/

int carbon(int length, char string[], FILE *fp)
{

	char temp;
	char temp2;

	if(length == 1)
	{

		printf("%s\n",string);
		fputs(string,fp);
		fputs("\n",fp);

	}
	else
	{
		for(int i = 0; i < length; i++)
		{
			carbon(length-1,string,fp);

			if(length%2 == 0)
			{

				temp = string[i];
				temp2 = string[length-1];
				string[i] = temp2;
				string[length-1] = temp;

			}
			else
			{

				temp = string[0];
				temp2 = string[length-1];
				string[0] = temp2;
				string[length-1] = temp;

			}
		}
	}
		
	return(-42);

}