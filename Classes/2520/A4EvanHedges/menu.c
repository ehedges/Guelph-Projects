/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 28th
	Assignment: 4
***************************/

#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/********************************************
Purpose: parses file.
In: tree, FILE
Out: tree
*********************************************/

void initializeMenu(head * tree, FILE * ptr)
{

	char * input = malloc(sizeof(char)*10000);
	char * token;

	int countTabs = 0;
	int length = 0;
	int checkTab = 0;
	int increase = 0;

		while(fgets(input,999,ptr)!=NULL)
		{

			token = strtok(input," ");

			while(token !=NULL)
			{

				if(strcmp(token,"\n")!= 0)
				{

					for (int i = 0; i < strlen(token); i++)
					{	

						/* Checks for tabs*/
						if (token[i] == '\t')
						{

							countTabs = 0;

							while(token[countTabs] == '\t')
							{

								countTabs++;

							}

							length = strlen(token)-countTabs;
							
							for (int j = 0; j < length; j++)
							{
								
								token[j] = token[j+countTabs];

							}
							
							token[length] = '\0';

						}

						/*removes new line*/
						if(token[i] == '\n')
						{
							
							token[i] = '\0';
							break;

						}

					}
					
					/*remove tabs*/
					checkTab = 0;

					for (int i = 0; i < strlen(token); i++)
					{

						if(token[i]== '\t')
						{

							checkTab = 1;

						}

					}

					/*adds to tree*/
					if(checkTab == 0 && strlen(token) > 0)
					{

						increase = addTree(tree, token);
						tree->size += increase;

					}


				}				
				
				token = strtok(NULL," ");

			}
			
		}

	free(input);

}

/********************************************
Purpose: input to find in tre.
In: tree
Out: nothing
*********************************************/

void findMenu(head * tree)
{

	char * input = malloc(sizeof(char)*10000);

	printf("\nfind key: ");
	scanf("%s",input);

	findTree(tree->treeNode,input);

	free(input);

}

/********************************************
Purpose: insert 1 thing into find in tre.
In: tree
Out: nothing
*********************************************/

void insertMenu(head * tree)
{

	char * input = malloc(sizeof(char)*10000);

	printf("\ninsert key: ");
	scanf("%s",input);

	if(strlen(input)>0)
	{

		tree->size += addTree(tree,input);

	}
	else
	{

		printf("No input.\n");

	}

	free(input);

}

/********************************************
Purpose: remove 1 thing into find in tree.
In: tree
Out: nothing
*********************************************/

void removeMenu(head * tree)
{

	char * input = malloc(sizeof(char)*10000);

	printf("\nremove key: ");
	scanf("%s",input);
	tree->size +=  removeTree(tree->treeNode,input);
	free(input);

}

/********************************************
Purpose: find height
In: tree
Out: height
*********************************************/

int heightMenu(head * tree)
{

	return(depth(tree->treeNode));

}

/********************************************
Purpose: find size
In: tree
Out: size
*********************************************/


int sizeMenu(head * tree)
{

	return(sizeTree(tree));

}

/********************************************
Purpose: input to find frequencies
Out: nothing
*********************************************/

void freqMenu(head * tree)
{

	char * input = malloc(sizeof(char)*10000);
	char numbers[11] = "1234567890";

	int valid = 0;
	int freq = 0;

	printf("\nFrequency: ");
	scanf("%s",input);

	for (int i = 0; i < 10; i++)
	{

		for (int j = 0; j < strlen(input); j++)
		{
			
			if(numbers[i]==input[j])
			{

				valid = valid + 1;

			}

		}

	}

	if(valid != strlen(input) || tree->size == 0)
	{

		printf("Error.\n");

	}
	else
	{

		freq = atoi(input);
		findFreq(tree->treeNode,freq);

	}

	free(input);

}

