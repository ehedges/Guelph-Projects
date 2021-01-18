
typedef struct treeNode {

	treeNode * left;
	treeNode * right;
	treeNode * parent;

	int data;

} nodeTree;

typedef struct treeHead {

	treeNode * head;
	int numNodes;

} headNode;

int compareValues();

int initialTree();

void findValue();

int createNodeLeft();

int createNodeRight();

int insertNodeT();

int deleteNodeT();

int deleteTree();