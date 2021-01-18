
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListAPI.h"

/*
CIS 2750, A0
Evan Hedges 0898140
This file contains a general linked list API.
I looked at some of the in class examples to understand
how the program should function. I took 2520 in 2016.
Used https://stackoverflow.com/questions/2859703/how-to-test-is-a-string-is-initialized-in-c
to check if the List is initialized.*/

/** Function to initialize the list metadata head with the appropriate function pointers.
*@return the list struct
*@param printFunction function pointer to print a single node of the list
*@param deleteFunction function pointer to delete a single piece of data from the list
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
**/
List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{

	List newList;

	newList.head = NULL;
	newList.tail = NULL;
	newList.deleteData = *deleteFunction;
	newList.compare = *compareFunction;
	newList.printData = *printFunction;

	return(newList);

}

/**Function for creating a node for the linked list. 
* This node contains abstracted (void *) data as well as previous and next
* pointers to connect to other nodes in the list
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a void * pointer to any data type.  Data must be allocated on the heap.
**/
Node *initializeNode(void *data)
{

	Node * newNode = malloc(sizeof(Node)*1);

	newNode->data = data;

	return(newNode);

}

/**Inserts a Node at the front of a linked list.  List metadata is updated
* so that head and tail pointers are correct.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded)
{

	Node *newNode = initializeNode(toBeAdded);

	newNode->next = list->head;
	newNode->previous = NULL;
	if(list)
	{

		if (list->head != NULL)
		{

			list->head->previous = newNode;

		}

		/*checks to see if only element*/
		list->head = newNode;

		if(list->tail == NULL)
		{

			list->tail = newNode;

		}

	}
	else
	{

		printf("Error with list.\n");

	}

}

/**Inserts a Node at the back of a linked list. 
*List metadata is updated so that head and tail pointers are correct.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded)
{

	Node *newNode; 

	
	
	if(list)
	{

		newNode = initializeNode(toBeAdded);
		newNode->next = NULL;
		newNode->previous = list->tail;

		if(list->tail != NULL)
		{

			list->tail->next = newNode;

		}	

		/*checks to see if only element*/
		list->tail = newNode;

		if(list->head == NULL)
		{

			list->head = newNode;
			
		}

	}
	else
	{

		printf("Error with the list\n");

	}



}

/** Clears the contents linked list, freeing all memory asspociated with these contents.
* uses the supplied function pointer to release allocated memory for the data
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void clearList(List *list)
{

	Node* temp;
	Node* current; 
	if(list)
	{

		current= list->head;

		while(current != NULL)
		{

			list->deleteData(current->data);

			temp = current;
			current = current->next;

			free(temp);

		}

		list->head = NULL;
		list->tail = NULL;

	}
	else
	{

		printf("Error with the list\n");

	}


}

/** Uses the comparison function pointer to place the element from lowest to highest in the 
* appropriate position in the list.
* should be used as the only insert function if a sorted list is required.  
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well 
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *toBeAdded)
{

	Node* newNode; 
	Node* current; 

	if(list)
	{

		newNode = initializeNode(toBeAdded);
		current = list->head;
		newNode->next = NULL;
		newNode->previous = NULL;

		/*Checks to see if the list has members*/
		if(list->head != NULL)
		{

			/*checks lowest*/
			while(list->compare(current->data, toBeAdded) < 0 && current->next != NULL)
			{

				current = current->next;

			}

			/* checks to see if it is in the middle, then if there is 1 element, at the end, at the start*/
			if(current->next != NULL && current->previous != NULL)
			{

				newNode->next = current;
				newNode->previous =current->previous;
				newNode->previous->next = newNode;
				current->previous = newNode;

			}
			else if(current->next == NULL && current->previous == NULL)
			{
				
				if(list->compare(current->data, toBeAdded) < 0)
				{

					insertBack(list,toBeAdded);

				}
				else
				{

					insertFront(list,toBeAdded);

				}

			}
			else if(current->next == NULL)
			{

				if(list->compare(current->data, toBeAdded) < 0)
				{

					insertBack(list,toBeAdded);

				}
				else
				{

					/* smaller than last but larger than the 2nd last*/
					newNode->next = current;
					newNode->previous = current->previous;
					newNode->previous->next = newNode;
					current->previous = newNode;

				}

			}
			else if(current->previous == NULL)
			{

				insertFront(list,toBeAdded);

			}

		}
		else
		{

			insertFront(list, toBeAdded);

		}

	}
	else
	{

		printf("Error with the list\n");

	}

}

/** Removes data from from the list, deletes the node and frees the memory,
 * changes pointer values of surrounding nodes to maintain list structure.
 * returns the data 
 * You can assume that the list contains no duplicates
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return on success: void * pointer to data  on failure: NULL
 **/
void* deleteDataFromList(List *list, void *toBeDeleted)
{

	void* temp = NULL;

	Node* current;

	if(list)
	{

		current = list->head;

		while(list->compare(current->data, toBeDeleted) != 0 && current != NULL)
		{

			current = current->next;

		}

		/* checks to see if the element is found, then deletes based upon position*/
		if(current != NULL)
		{

			/*Checks to see if only element, last, first, or middle*/
			if(current->previous == NULL && current->next == NULL)
			{

				list->head = NULL;
				list->tail = NULL;

			}
			else if(current->previous == NULL)
			{

				list->head = current->next;
				list->head->previous = NULL;

			}
			else if(current->next == NULL)
			{

				list->tail = current->previous;
				list->tail->next = NULL;

			}
			else
			{

				current->previous->next = current->next;
				current->next->previous = current->previous;

			}

			temp = current->data;

			free(current);

		}

	}
	else
	{

		printf("Error with list.\n");
		return(NULL);

	}

	return(temp);	

}

/**Returns a pointer to the data at the front of the list. Does not alter list structure.
 *@pre The list exists and has memory allocated to it
 *@param the list struct
 *@return pointer to the data located at the head of the list
 **/
void* getFromFront(List list)
{

	return(list.head->data);

}

/**Returns a pointer to the data at the back of the list. Does not alter list structure.
 *@pre The list exists and has memory allocated to it
 *@param the list struct
 *@return pointer to the data located at the tail of the list
 **/
void* getFromBack(List list)
{

	return(list.tail->data);

}

/**Returns a string that contains a string representation of
the list traversed from  head to tail. Utilize the list's printData function pointer to create the string.
returned string must be freed by the calling function. Uses \n to denote different strings
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 *@return on success: char * to string representation of list (must be freed after use).  on failure: NULL
 **/
char* toString(List list)
{

	Node* temp = list.head;

	char* string = malloc(sizeof(char));
	char* tempString;

	int counter = 0;
	int i = 0;

	/*Make an empty string, fill with characters from each node*/
	while(temp!=NULL)
	{

		tempString = list.printData(temp->data);

		if((counter + strlen(tempString)-1) > strlen(string)-1)
		{

			string = realloc(string,(strlen(string)+strlen(tempString)+10));

		}

		for (i = 0; i < strlen(tempString); i++)
		{

			string[i+counter] =	tempString[i];

		}

		string[i+counter] = '\n';
		counter += i+1;

		temp = temp->next;

	}

	return(string);

}

/** Function for creating an iterator for the linked list. 
 * This node contains abstracted (void *) data as well as previous and next
 * pointers to connect to other nodes in the list
 *@pre List exists and is valid
 *@post List remains unchanged.  The iterator has been allocated and points to the head of the list.
 *@return The newly created iterator object.
 *@param list - a pointer to the list to iterate over.
**/
ListIterator createIterator(List list)
{

	ListIterator move;

	move.current = list.head;

	return(move);

}

/** Function that returns the next element of the list through the iterator. 
* This function returns the head of the list the first time it is called after.
* the iterator was created. Every subsequent call returns the next element.
*@pre List exists and is valid.  Iterator exists and is valid.
*@post List remains unchanged.  The iterator points to the next element on the list.
*@return The data associated with the list element that the iterator pointed to when the function was called.
*@param iter - an iterator to a list.
**/
void* nextElement(ListIterator* iter)
{

	void* temp;

	if(iter)
	{

		if (iter->current == NULL)
		{
			
			return(NULL);

		}

		temp = iter->current->data;
		iter->current = iter->current->next;
	}
	else
	{

		printf("Error with the iterator.\n");

	}


	return(temp);

}
