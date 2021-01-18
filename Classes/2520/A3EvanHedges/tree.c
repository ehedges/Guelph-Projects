/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 7th
	Assignment: 3
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/********************************************
Purpose: Controls the program, gets an equation basic error checking.
In: Commandline, options
Out: Prints information.
*********************************************/

int main(int argc, char * argv[])
{

	treeHead * tree = malloc(sizeof(treeHead));

	char * input = malloc(sizeof(char)*1000);

	float updateValue = 0;

	int updateVarible = 0;
	int unknowns = 0;
	int choose = 0;

	/*Ensures an equation is entered*/
	if(argc !=2)
	{

		printf("Error with in: Incorrect number of arguments\n");
		exit(0);

	}

	/*Finds the number of unknowns in the array*/
	for(int i = 0; i < strlen(argv[1]); i++)
	{
		if(argv[1][i] == 'x')
		{

			unknowns++;

		}
	}

	createTree(tree);
	printf("%s\n",argv[1]);
	addTree(tree,argv[1]);

	/*Main menu*/
	do
	{

		printf("\n\n%s\n",argv[1]);
		printf("Enter a number to the corresponding option.\n");
		printf("1. Display\n");
		printf("2. Preorder\n");
		printf("3. Inorder\n");
		printf("4. Postorder\n");
		printf("5. Update\n");
		printf("6. Calculate\n");
		printf("7. Exit\n");
		scanf("%s",input);

		if(strcmp(input,"1")== 0)
		{
			/*Print tree*/
			display(tree->tree);


		}
		else if(strcmp(input,"2")== 0)
		{
			/*Print Preorder*/
			printf("Printing in Preorder\n");
			preorderPrint(tree);


		}
		else if(strcmp(input,"3")== 0)
		{
			/*Print Inorder*/
			printf("Printing in Inorder\n");
			inorderPrint(tree);

		}
		else if(strcmp(input,"4")== 0)
		{
			/*Print Postorder*/
			printf("Printing in Postorder\n");
			postorderPrint(tree);

		}
		else if(strcmp(input,"5")== 0)
		{
				/*Update variable*/
				printf("Input a varible number.\n");	
				scanf("%d",&updateVarible);
				printf("Input a value.\n");		
				scanf("%f",&updateValue);
				
				if(updateVarible != 0 && updateVarible <= unknowns)
				{

					changeValue(tree,updateVarible,updateValue);
					printf("x%d = %f\n",updateVarible, updateValue);
					updateVarible = 0;
					updateValue = 0;

				}
				else
				{

					printf("Invalid input.\n");

				}

		}
		else if(strcmp(input,"6")== 0)
		{
			/*Calculate*/
			printf("Calculating:\n");
			calculateTree(tree);


		}
		else if(strcmp(input,"7")== 0)
		{

			printf("Exiting\n");
			choose = 7;

		}
		else
		{

			printf("Invalid input.\n");

		}

	}while(choose !=7);

	destroyTree(tree);
	free(input);

	return 0;

}