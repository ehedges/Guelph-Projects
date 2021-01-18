/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 28th
	Assignment: 4
***************************/

typedef struct treeNode{

	char * key;

	int freq;
	int balance;
	int height;

	struct treeNode * left;
	struct treeNode * right;
	struct treeNode * parent;

} node;

typedef struct headNode{

	int height;
	int size;
	node *treeNode;

} head;


void createTree(head * tree);
/********************************************
Purpose: Intialize head.
In: header node.
Out: header
*********************************************/

int addTree(head * tree, char * input);
/********************************************
Purpose: add to tree.
In: header node.
Out: tree
*********************************************/

int addNode(node * tree, char * input);
/********************************************
Purpose: add to tree.
In:  tree
Out: tree
*********************************************/

void addNodeLeft(node * tree, char * input);
/********************************************
Purpose: add to tree.
In:  node.
Out: tree
*********************************************/

void addNodeRight(node * tree, char * input);
/********************************************
Purpose: add to tree.
In:  node.
Out: tree
*********************************************/

int removeTree(node * tree, char * input);
/********************************************
Purpose: remove from tree.
In:  tree
Out: int
*********************************************/

void findTree(node * tree, char * input);
/********************************************
Purpose: find string in tree.
In:  tree
Out: int
*********************************************/

int heightTree(head * tree);
/********************************************
Purpose: find height.
In:  tree
Out: int
*********************************************/

int sizeTree(head * tree);
/********************************************
Purpose: find size.
In:  tree
Out: int
*********************************************/

void findFreq(node * tree, int freq);
/********************************************
Purpose: find nodes above a frequency
In:  tree
Out: nothing
*********************************************/

node *  rightRotate(node * tree);
/********************************************
Purpose: balance tree.
In:  node
Out: node
*********************************************/

node *  leftRotate(node * tree);
/********************************************
Purpose: balance tree.
In:  node
Out: node
*********************************************/

node * leftRightRotate(node * tree);
/********************************************
Purpose: balance tree.
In:  node
Out: node
*********************************************/

node * rightLeftRotate(node * tree);
/********************************************
Purpose: balance tree.
In:  node
Out: node
*********************************************/

node * balance(node * tree);
/********************************************
Purpose: balance the entire tree.
In:  tree
Out: tree
*********************************************/

void destroyTree(node * tree);
/********************************************
Purpose: kill tree.
In:  tree
Out: nothing
*********************************************/

int depth(node* tree);
/********************************************
Purpose: size of tree.
In:  tree
Out: int
*********************************************/






