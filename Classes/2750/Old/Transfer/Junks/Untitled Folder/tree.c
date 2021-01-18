
int compareValues()
{

	return (0);

}

int initialTree()
{

	headNode * tree = malloc(sizeof(headNode));
	tree->head = NULL;
	tree->numNodes = 0;

	return (0);

}

void findValue()
{

	return (0);

}

int createNodeLeft(int data, nodeTree branch)
{

	nodeTree * leaf = malloc(sizeof(nodeTree));

	leaf->data = data;
	leaf->parent = branch;
	left->right = NULL;
	branch->left = leaf;

	return (0);

}

int createNodeRight(int data, nodeTree branch)
{

	nodeTree * leaf = malloc(sizeof(nodeTree));

	leaf->data = data;
	leaf->parent = branch;
	leaf->left = NULL;
	branch->right = leaf;

	return (0);

}

int insertNodeT(headNode * tree, int data)
{
	
	nodeTree * current;

	current = tree->head;

	if(current = NULL)
	{

		current = malloc(sizeof(nodeTree));

		current->left = NULL;
		current->right = NULL;
		current->data = data;

	}

	return (0);

}

int deleteNodeT()
{

	return (0);

}

int deleteTree(headNode * tree)
{

	current = tree->head;

	if(tree->head == NULL)
	{

		if(tree->numNodes != 0)
		{

			return(1);

		}
		else
		{

			return(0);

		}

	}

	while(numNodes != 0)
	{



	}

	return (0);

}
