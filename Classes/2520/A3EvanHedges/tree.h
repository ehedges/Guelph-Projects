/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 7th
	Assignment: 3
***************************/


typedef struct treeNode{

	char action;

	float value;
	int unknownNum;

	struct treeNode * left;
	struct treeNode * right;
	struct treeNode * parent;

} node;

typedef struct headNode{

	int num;
	node * tree;

} treeHead;


void createTree(treeHead * tree);
/********************************************
Purpose: Intialize head.
In: header node.
Out: Nothing.
*********************************************/

void addTree(treeHead * tree, char * input);
/********************************************
Purpose: Creates equation in the form of a tree
In: tree, equation.
Out: Nothing.
*********************************************/

void addRight(node * tree);
/********************************************
Purpose: creates right node
In: tree
Out: nothing
*********************************************/

void addLeft(node * tree);
/********************************************
Purpose: creates left node
In: tree
Out: nothing
*********************************************/

void updateCurrent(node * tree, char action, float value);
/********************************************
Purpose: updates value
In: tree, variable number, value, number 
Out: nothing
*********************************************/

void destroyTree(treeHead * tree);
/********************************************
Purpose: destroy tree
In: tree, variable.
Out: nothing
*********************************************/

void changeValue(treeHead * tree,int variable, float value);
/********************************************
Purpose: changes value
In: tree, variable number, value, number 
Out: nothing
*********************************************/

int searchTree(node * tree,int variable, float value, int done);
/********************************************
Purpose: finds the variable and updates
In: tree, variable number, value, number 
Out: nothing
*********************************************/

void inorderPrint(treeHead * tree);
/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

void postorderPrint(treeHead * tree);
/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

void preorderPrint(treeHead * tree);
/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

void preorder(node * tree);
/********************************************
Purpose: Prints in preorder
In: tree, 
Out: Prints
*********************************************/

void postorder(node * tree);
/********************************************
Purpose: Prints in postorder
In: tree, 
Out: Prints
*********************************************/


void inorder(node * tree);
/********************************************
Purpose: Prints in inorder
In: tree, 
Out: Prints
*********************************************/


void freeTree(node*tree);
/********************************************
Purpose: Destroy
In: tree, 
Out: nothing.
*********************************************/

void calculateTree(treeHead * tree);
/********************************************
Purpose: Remove head.
In: tree, 
Out: tree
*********************************************/

float calculate(node *tree);
/********************************************
Purpose: Calculates the tree.
In: tree.
Out: Float.
*********************************************/

void display(node * tree);
/********************************************
Purpose: Prints an approximate tree.
In: tree.
Out: Nothing..
*********************************************/