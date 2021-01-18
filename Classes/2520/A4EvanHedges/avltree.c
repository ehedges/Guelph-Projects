/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 28th
	Assignment: 4
***************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "menu.h"

/********************************************
Purpose: Create tree.
In: header node;
Out: XCreates the header.
*********************************************/

void createTree(head * tree)
{

	tree->height = 0;
	tree->size = 0;
	tree->treeNode = NULL;

}

/********************************************
Purpose: Add to the avl tree.
In: tree, key
Out: tree.
*********************************************/

int addTree(head * tree, char * input)
{

	int value = 0;

	if(tree->treeNode == NULL)
	{

		tree->treeNode = malloc(sizeof(node)*1);
		tree->treeNode->key = malloc(sizeof(char)*1000);
		strcpy(tree->treeNode->key,input);
		tree->treeNode ->freq = 1;
		tree->treeNode ->balance = 0;
		tree->treeNode ->height = 0;
		tree->treeNode ->left = NULL;
		tree->treeNode ->right = NULL;

		return (1);

	}
	else
	{

		value = addNode(tree->treeNode,input);

	}

	tree->height = depth(tree->treeNode);

	return (value);
	
}

/********************************************
Purpose: Creates and adds a node to the tre.
In: tree, input
Out: tree, int for succes.
*********************************************/

int addNode(node * tree, char * input)
{

	int value = 0;

	/*printf("Compare: %d Key: %s\n",strcmp(tree->key,input),input);*/
	if(strcmp(tree->key,input) == 0)
	{

		tree->freq += 1;
		return(0);

	}
	else if(strcmp(tree->key,input) > 0)
	{
		
		if(tree->left == NULL)
		{
			printf("Left%s\n",tree->key );
			addNodeLeft(tree,input);

			return (1);

		}
		else
		{

			value = addNode(tree->left,input);

		}
		
	}
	else if(strcmp(tree->key,input) < 0)
	{

		if(tree->right == NULL)
		{
			printf("Right:%s\n",tree->key );
			addNodeRight(tree,input);
		
			return (1);

		}
		else
		{

			value = addNode(tree->right,input);

		}

	}

	tree->height = depth(tree);
	tree = balance(tree);
	tree->height = depth(tree);

	return(value);
}

/********************************************
Purpose: adds a node.
In: tree, input
Out: tree
*********************************************/

void addNodeLeft(node * tree, char * input)
{

	node * temp = malloc(sizeof(node)*1);
	temp->key = malloc(sizeof(char)*1000);
	strcpy(temp->key,input);
	temp->freq = 1;
	temp->balance = 0;
	temp->height = 0;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = tree;
	tree->left = temp;

}

/********************************************
Purpose: adds a node.
In: tree, input
Out: tree
*********************************************/

void addNodeRight(node * tree, char * input)
{

	node * temp = malloc(sizeof(node)*1);
	temp->key = malloc(sizeof(char)*1000);
	strcpy(temp->key,input);
	temp->freq = 1;
	temp->balance = 0;
	temp->height = 0;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = tree;
	tree->right = temp;

}

/********************************************
Purpose: remove one frequency, or destroy a node
In: tree, input
Out: tree, int of succes.
*********************************************/

int removeTree(node * tree, char * input)
{

	int value = 0;

	if(tree->left == NULL && tree->right == NULL)
	{

		printf("no_such_key\n");
		return(0);

	}
	else if(tree->left !=NULL)
	{

		/*compares nodes*/
		if(strcmp(tree->left->key,input) == 0)
		{

			tree->left->freq-=1;

			if(tree->left->freq == 0)
			{

				node * temp = tree->left;
				/* checking for all possible nodes removed*/
				if(tree->left->left == NULL && tree->left->right == NULL)
				{
					/*leaf*/
					tree->left = NULL;
					free(temp->key);
					free(temp);

				}
				else if(tree->left->left == NULL && tree->left->right != NULL)
				{
					/*one child*/
					tree->left = tree->left->right;
					free(temp->key);
					free(temp);

				}
				else if(tree->left->left != NULL && tree->left->right == NULL)
				{
					/*one child*/
					tree->left = tree->left->left;
					free(temp->key);
					free(temp);

				}
				else
				{
					/*two children*/
					node * move = temp->right;
					node * temp2;
					node * temp3 = move->left;

					while(temp3->left != NULL)
					{

						move = move->left;
						temp3 = temp3->left;

					}

					temp2 = move;
					move = move->left;
					strcpy(temp->key,move->key);			
					temp->freq = move->freq;
					move->freq = 1;
					strcpy(move->key,"KILLNODE");
					value = removeTree(tree, "KILLNODE");
					temp2->left = NULL;
					free(move->key);
					free(move);
					
				}

				return(-1);
			}
			else
			{

				printf("Error. when removing.\n");

			}

		}

	}
	else if(tree->right != NULL)
	{

		if(tree->right->freq == 0)
		{

			node * temp = tree->right;
			/* checking for all possible nodes removed*/
			if(tree->right->left == NULL && tree->right->right == NULL)
			{

				/*leaf*/
				tree->right = NULL;
				free(temp->key);
				free(temp);

			}
			else if(tree->right->left == NULL && tree->right->right != NULL)
			{

				/*one child*/
				tree->right = tree->right->right;
				free(temp->key);
				free(temp);

			}
			else if(tree->right->left != NULL && tree->right->right == NULL)
			{

				/*one child*/
				tree->right = tree->right->left;
				free(temp->key);
				free(temp);

			}
			else
			{

				/*two children*/
				node * move = temp->left;
				node * temp2;
				node * temp3 = move->right;

				while(temp3->right != NULL)
				{

					move = move->right;
					temp3 = temp3->right;

				}

				temp2 = move;
				move = move->right;
				strcpy(temp->key,move->key);			
				temp->freq = move->freq;
				move->freq = 1;
				strcpy(move->key,"KILLNODE");
				value = removeTree(tree, "KILLNODE");
				temp2->right = NULL;
				free(move->key);
				free(move);
					
			}

			return(-1);
			
		}
	
	}
	else if(strcmp(tree->key,input) > 0)
	{

		value = removeTree(tree->left,input);

	}
	else if(strcmp(tree->key,input) < 0)
	{

		value = removeTree(tree->right,input);

	}
	else
	{

		printf("no_such_key\n");
		return(0);

	}

	if(value == -1)
	{

		tree = balance(tree);

	}

	return(value);

}

/********************************************
Purpose: Finds a node, and it' frequency.
In: tree, input
Out: nothing.
*********************************************/

void findTree(node * tree, char * input)
{

	if(strcmp(tree->key,input) == 0)
	{

		printf("key: %s, frequency: %d\n",tree->key,tree->freq );

	}
	else if(strcmp(tree->key,input) > 0)
	{
		
		if(tree->left != NULL)
		{

			findTree(tree->left,input);

		}
		else
		{

			printf("no_such_key\n");

		}

		
	}
	else if(strcmp(tree->key,input) < 0)
	{

		if(tree->right != NULL)
		{

			findTree(tree->right,input);

		}
		else
		{

			printf("no_such_key\n");

		}

	}

}

/********************************************
Purpose: finds height.
In: tree
Out: height
*********************************************/

int heightTree(head * tree)
{

	return(tree->height);

}

/********************************************
Purpose: finds size.
In: tree
Out: size.
*********************************************/

int sizeTree(head * tree)
{

	return(tree->size);

}

/********************************************
Purpose: finds all nodes above a requency.
In: tree, int.
Out: nothing
*********************************************/

void findFreq(node * tree, int freq)
{

	if(tree->left!=NULL)
	{

		findFreq(tree->left,freq);

	}

	if(tree->freq >= freq && tree !=NULL)
	{

		printf("Key: %s Frequency: %d\n",tree->key,tree->freq);

	}

	if(tree->right!=NULL)
	{

		findFreq(tree->right,freq);

	}

}

/********************************************
Purpose: rotates left
In: tree
Out: tree
*********************************************/

node * leftRotate(node * tree)
{

	node * temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;

	tree->height = depth(tree);
	temp->height = depth(tree);


	return(temp);
}

/********************************************
Purpose: rotates right
In: tree
Out: tree
*********************************************/


node * rightRotate(node * tree)
{

	node * temp = tree->right;
	tree->right = temp->left;
	temp->left = tree;

	tree->height = depth(tree);
	temp->height = depth(tree);

	return(temp);

}

/********************************************
Purpose: rotates right, but the 
input is the left Node.
In: tree
Out: tree
*********************************************/

node * leftRightRotate(node * tree)
{

	node * temp = tree->right;
	tree->right = temp->left;
	temp->left = tree;

	tree->height = depth(tree);
	temp->height = depth(tree);

	return(temp);
}

/********************************************
Purpose: rotates left, but the 
input is the right Node.
In: tree
Out: tree
*********************************************/

node * rightLeftRotate(node * tree)
{
	
	node * temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;

	tree->height = depth(tree);
	temp->height = depth(tree);

	return(temp);

}

/********************************************
Purpose: balances the tree.
In: tree
Out: tree
*********************************************/

node * balance(node * tree)
{

	tree->height = depth(tree);

	int left; 
	int right; 
	int balance;

	if(tree->right != NULL)
	{

		right = tree->height;

	}
	else
	{

		right = 0;

	}

	if(tree->left != NULL)
	{

		left = tree->height;

	}
	else
	{

		left = 0;

	}

	right = depth(tree->right);
	left = depth(tree->left);
	balance = right - left;

	if(balance == -2)
	{

		if(tree->left->left != NULL)
		{

			tree->left = leftRotate(tree->left);

		}
		else if(tree->left->right !=NULL)
		{

			tree->left = leftRightRotate(tree->left);

		}

	}
	else if(balance == 2)
	{

		if(tree->right->right != NULL)
		{

			tree->right = rightRotate(tree->right);

		}
		else if(tree->right->left !=NULL)
		{

			tree->right = rightLeftRotate(tree->right);

		}
		else
		{

			printf("Error when rotating.\n");

		}


	}

	tree->height = depth(tree);

	return(tree);

}

/********************************************
Purpose: destroys the tree.
In: tree
Out: nothing
*********************************************/

void destroyTree(node * tree)
{

	if(tree != NULL)
	{

		if(tree->left!=NULL)
		{

			destroyTree(tree->left);

		}

		if(tree->right!=NULL)
		{

			destroyTree(tree->right);

		}

		free(tree->key);
		free(tree);

	}
	
}

/********************************************
Purpose: finds the depth, or height.
Out: int
*********************************************/

int depth(node * tree)
{

	if(tree == NULL)
	{

		return (0);

	}

	int left = depth(tree->left);
	int right = depth(tree->right);

	if(left > right)
	{

		return(left+1);

	}	

	return(right+1);	

}
