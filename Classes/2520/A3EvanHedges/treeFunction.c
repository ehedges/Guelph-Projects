/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 7th
	Assignment: 3
***************************/

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/********************************************
Purpose: Intialize head.
In: header node.
Out: Nothing.
*********************************************/

void createTree(treeHead * tree)
{

	node * temp = malloc(sizeof(node));

	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	temp->action = 'E';
	temp->value = 0;
	tree->tree = temp;

	tree->num = 0;

}

/********************************************
Purpose: Creates equation in the form of a tree
In: tree, equation.
Out: Nothing.
*********************************************/

void addTree(treeHead * head, char * array)
{

		node * temp = head->tree;

		char * tempArray = malloc(sizeof(char)*1000);
		char validCharacters[18] ="1234567890*-+/x().";
		char tempChar;

		float value = 0;

		int * validArray = malloc(sizeof(int) *strlen(array));
			
		
		

		/*Makes sure all characters are valid*/
		for(int i = 0; i < strlen(array); i++)
		{

			validArray[i] = 0;

			for(int j = 0; j < strlen(validCharacters); j++)
			{
				if(array[i] == validCharacters[j])
				{

					validArray[i] = 1;

				}
			}

		}

		for(int i = 0; i < strlen(array); i++)
		{
			if(validArray[i] != 1)
			{

				printf("Error with equation.\n");
				exit(0);
			}
		}
			
		/*Creates tree*/
		printf("Intializing tree!\n");
		for(int i = 0; i < strlen(array); i++)
		{

			if(array[i] == '(')
			{

				addLeft(temp);
				temp = temp->left;

			}
			else if(array[i] == '+' || array[i] == '-' || array[i] == '/' || array[i] == '*')
			{
			
				printf("Adding operation \n");
				addRight(temp);
				updateCurrent(temp,array[i], 0);
				temp = temp->right;

			}
			else if(array[i] == ')')
			{

				temp = temp->parent;
		
			}
			else if(array[i] == 'x')
			{
				printf("Adding Variable!\n");
				tempChar = array[i];
				updateCurrent(temp, tempChar, atof(&array[i+1]));
				i = i+1;
				temp = temp->parent;

			}
			else
			{

				printf("Adding Number.\n");
				
                char tempNumArray[4];
				tempNumArray[0] = array[i];
				tempNumArray[1] = array[i+1];
				tempNumArray[2] = array[i+2];
				tempNumArray[3] = array[i+3];
				i = i+3;

				value = atof(tempNumArray);
				updateCurrent(temp, 'N', value);
				temp = temp->parent;
				

			} 	

		}

		free(validArray);
		free(tempArray);

}

/********************************************
Purpose: creates right node
In: tree
Out: nothing
*********************************************/

void addRight(node * tree)
{

	node * temp = malloc(sizeof(node));

	tree->right = temp;
	temp->parent = tree;
	temp->left = NULL;
	temp->right = NULL;
	temp->value = 0;
	temp->action = 'E';

}

/********************************************
Purpose: creates left node
In: tree
Out: nothing
*********************************************/

void addLeft(node * tree)
{

	printf("Adding Node.\n");
	node * temp = malloc(sizeof(node));

	tree->left = temp;
	temp->parent = tree;
	temp->left = NULL;
	temp->right = NULL;
	temp->value = 0;
	temp->action = 'E';
	printf("Adding Done.\n");

}

/********************************************
Purpose: updates value
In: tree, variable number, value, number 
Out: nothing
*********************************************/

void updateCurrent(node * tree, char action, float value)
{


	tree->value = value;
	tree->action = action;

	if(action == 'x')
	{
		tree->unknownNum = value;
		tree->value = 0;
	}


}

/********************************************
Purpose: destroy tree
In: tree, variable.
Out: nothing
*********************************************/

void destroyTree(treeHead * tree)
{
	

	printf("Destroying Tree\n");
	freeTree(tree->tree);
	printf("Gone.\n");


}

/********************************************
Purpose: changes value
In: tree, variable number, value, number 
Out: nothing
*********************************************/

void changeValue(treeHead * tree, int variable, float value)
{

	int done;

	done = searchTree(tree->tree,variable,value, 0);

	if(done != 1)
	{

		printf("Could not find the value\n");

	}


}

/********************************************
Purpose: finds the variable and updates
In: tree, variable number, value, number 
Out: nothing
*********************************************/

int searchTree(node * tree,int variable, float value, int done)
{

	if(tree->left!=NULL)
	{

		searchTree(tree->left,variable, value, done);

	}

	if(tree->action == 'x' && tree->unknownNum == variable)

	{

		tree->value = value;

		printf("X%d = %f",tree->unknownNum, tree->value);


	}

	printf("\n");

	if(tree->right!=NULL)
	{

		searchTree(tree->right,variable,value,done);

	}

	return 1;

}

/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

void inorderPrint(treeHead * tree)
{

	inorder(tree->tree);

}
/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/


void postorderPrint(treeHead * tree)
{

	postorder(tree->tree);

}

/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

void preorderPrint(treeHead * tree)
{

	preorder(tree->tree);

}

/********************************************
Purpose: Prints in inorder
In: tree, 
Out: Prints
*********************************************/

void inorder(node * tree)
{

	if(tree->left!=NULL)
	{

		inorder(tree->left);

	}

	printf("%c",tree->action);

	if(tree->action == 'x')

	{

		printf("%d = %f",tree->unknownNum, tree->value);


	}
	else if(tree->action == 'N')
	{

		printf(" = %f",tree->value );

	}

	printf("\n");

	if(tree->right!=NULL)
	{

		inorder(tree->right);

	}

	

}
/********************************************
Purpose: Prints in preorder
In: tree, 
Out: Prints
*********************************************/

void preorder(node * tree)
{

	printf("%c",tree->action);

	if(tree->action == 'x')
	{

		printf("%d = %f",tree->unknownNum, tree->value);

	}
	else if(tree->action == 'N')
	{

		printf(" = %f",tree->value );

	}
	printf("\n");

	if(tree->left!=NULL)
	{

		preorder(tree->left);

	}



	if(tree->right!=NULL)
	{

		preorder(tree->right);

	}

	

}
/********************************************
Purpose: Prints in postorder
In: tree, 
Out: Prints
*********************************************/

void postorder(node * tree)
{


	if(tree->left!=NULL)
	{

		postorder(tree->left);

	}



	if(tree->right!=NULL)
	{

		postorder(tree->right);

	}

	printf("%c",tree->action);

	if(tree->action == 'x')
	{

		printf("%d = %f",tree->unknownNum, tree->value);

	}
	else if(tree->action == 'N')
	{

		printf(" = %f",tree->value );

	}

	printf("\n");


}

/********************************************
Purpose: Destroy
In: tree, 
Out: nothing.
*********************************************/

void freeTree(node * tree)
{

	if(tree->left!=NULL)
	{

		freeTree(tree->left);

	}



	if(tree->right!=NULL)
	{

		freeTree(tree->right);

	}

	free(tree);
}

/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

void calculateTree(treeHead * tree)
{
	float answer;
	answer = calculate(tree->tree);
	printf("Answer : %f\n",answer);

}

/********************************************
Purpose: Calculates the tree.
In: tree.
Out: Float.
*********************************************/

float calculate(node *tree)
{

	float tempOne;
	float tempTwo;

	if(tree->action == '+')
	{

		tempOne = calculate(tree->left);
		tempTwo = calculate(tree->right);
		tree->value = tempOne + tempTwo;
		printf("Value %f\n", tree->value);
		return(tree->value);

	}
	else if(tree->action == '-')
	{

		tempOne = calculate(tree->left);
		tempTwo = calculate(tree->right);
		tree->value = tempOne - tempTwo;

		return(tree->value);

	}
	else if(tree->action == '*')
	{
		
		tempOne = calculate(tree->left);
		tempTwo = calculate(tree->right);
		tree->value = tempOne * tempTwo;

		return(tree->value);

	}
	else if(tree->action == '/')
	{
		
		tempOne = calculate(tree->left);
		tempTwo = calculate(tree->right);

		if(tempTwo == 0)
		{

			printf("Dividing by 0. Exiting\n");
			exit(0);

		}

		tree->value = tempOne/tempTwo;

		return(tree->value);

	}
	else
	{

		return(tree->value);

	}
	return(-999999);
	
}

void display(node * tree)
{

	printf(" %c ", tree->action);
	if(tree -> left != NULL)
	{
		display(tree->left);
		printf(" ");
		
	}

	if(tree -> right != NULL)
	{
		display(tree->right);
		printf("\n");
		
	}

	if(tree->left == NULL && tree->right == NULL)
	{
		
		printf(" ");

	}
	else if(tree->right == NULL)
	{
		
		printf("_");

	}
	else if(tree->left == NULL)
	{

		printf("_");

	}


}