/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 28th
	Assignment: 4
***************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/********************************************
Purpose: Open file, main menu handling.
In: nothing
Out: nothing
*********************************************/

int main()
{

	FILE * ptr;

	head * tree = NULL;

	char * input = malloc(sizeof(char)*10000);

	int choose = 0;
	int height = 0;
	int size = 0;

	do
	{

		printf("1. Initialization\n");
		printf("2. Find\n");
		printf("3. Insert\n");
		printf("4. Remove\n");
		printf("5. Check Height and Size\n");
		printf("6. Find All (above given frequenecy)\n");
		printf("7. Exit\n");
		printf("avl/> ");
		scanf("%s",input);

		if(strcmp(input,"1")== 0)
		{
			/*Done, may need to do checking for wrong file types*/
			printf("\nfilename: ");	
			free(input);
			input = malloc(sizeof(char)*1000);
			scanf("%s",input);

			if(strlen(input)<=0)
			{

				printf("Invalid input.\n");

			}
			else {

				ptr = fopen(input,"r");

			}

			if(ptr == NULL)
			{

				printf("Error opening file.\n");

			}
			else if(tree == NULL)
			{

				tree = malloc(sizeof(head)*1);
				createTree(tree);
				initializeMenu(tree,ptr);
				fclose(ptr);

			}
			else
			{

				destroyTree(tree->treeNode);
				free(tree);
				tree = malloc(sizeof(head)*1);
				createTree(tree);
				initializeMenu(tree,ptr);
				fclose(ptr);

			}



			

		}
		else if(strcmp(input,"2")== 0)
		{
			/*WIP*/
			if(tree!=NULL && sizeMenu(tree) >0)
			{

				findMenu(tree);	

			}
			else
			{

				printf("Error: Tree does not exist.\n");

			}
				

		}
		else if(strcmp(input,"3")== 0)
		{
			/*WIP*/
			if(tree == NULL)
			{

				tree = malloc(sizeof(head)*1);
				createTree(tree);

			}

			insertMenu(tree);
			
		}
		else if(strcmp(input,"4")== 0 && tree != NULL)
		{

			if(tree!= NULL || sizeMenu(tree) >0)
			{

				removeMenu(tree);

			}
			else
			{

				printf("Error: Tree does not exist.\n");

			}


		}
		else if(strcmp(input,"5")== 0 && tree != NULL)
		{
			
		  	if(tree != NULL)
		  	{

				height = heightMenu(tree);
				size = sizeMenu(tree);
				printf("\nHeight: %d,Size: %d\n",height,size);	

		  	}
		  	else
		  	{

		  		printf("Error: Tree does not exist.\n");

		  	}


		}
		else if(strcmp(input,"6")== 0 && tree != NULL)
		{
								
			freqMenu(tree);

		}
		else if(strcmp(input,"7")== 0)
		{
			
			choose = 7;

		}
		else
		{

			printf("Error: Invalid input or tree does not exist.\n");

		}

	}while(choose !=7);

	if(tree != NULL)
	{

		if(sizeMenu(tree) > 0)
		{

			destroyTree(tree->treeNode);

		}

		free(tree);

	}

	free(input);

	return 0;

}