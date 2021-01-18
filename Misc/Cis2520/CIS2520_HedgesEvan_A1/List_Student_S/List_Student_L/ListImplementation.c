#include "ListInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* some code here (e.g., #include directives, static functions) */

void Initialize (List *L) {

    L = (List*)malloc(sizeof(List)); 
    /*Sets all values*/ 
    L->first = NULL;
   
    L->size = 0;
        
}

void Insert (Item X, int position, List *L) {
	
	/*Copies Values*/
	
	int i = 0;
	
	ListNode * current;
	
    current = (ListNode*)malloc(sizeof(ListNode));

    current->nextNode = L->first;
    L->first = current;
	while( i < position)
	{
	
	    if (current->nextNode == NULL)
	    {
	    
            ListNode * empty;
            empty = (ListNode*)malloc(sizeof(ListNode));
	        empty->items.name =(char*)malloc(sizeof(char)*MAXNAMESIZE);
	        
	    	strcpy(empty->items.name,"Empty");
            
            empty->items.grade = 0;
	        empty->nextNode = NULL;
	        
	        L->size++;
	        current->nextNode = empty;
	    
	        printf("Create value: %d\n",i);
	    
	    }
	    else if(current->nextNode != NULL)
	    {
	        i++;
	        current = current->nextNode;
            printf("here\n");
        }
    }
	
	strcpy(current->items.name,X.name);
	current->items.grade=X.grade;
	
	printf("Inserting: %d\n",current->items.grade);
}

void Remove (int position, List *L){
    
    ListNode * current;
	ListNode * temp;
	
	int i;
	
    current = (ListNode*)malloc(sizeof(ListNode));
    temp = (ListNode*)malloc(sizeof(ListNode));
	
    current->nextNode = L->first;
    
    temp = current;

    for(i = 0; i<position-1; i++);
    {
	
        current = current->nextNode;
	
	}
	
	temp = current->nextNode;
	
	current->nextNode = temp->nextNode;
	
    free(temp);

}

int Full (List *L) {

    printf("here");

	return 0;
}

int Empty (List *L) {

    ListNode * current;
    
    int size;
    int i;
    current = (ListNode*)malloc(sizeof(ListNode));

    current->nextNode = L->first;
    
    i = 0;
    size = Size(L);
    
	for( i = 0; i< size; i++)
    {
    
    
        printf("Loop :%d\n",current->items.grade);  
        
/*        if (current->items.grade != 0)
        {
        
            printf("here\n");
            return(1);
        
        }
        
        current = current->nextNode;
*/        
    }
    
    free(current);

        return (0);
}
int Size (List *L) {
	
	static int count;	
	
	count = L->size;
	
	return count;
  
} 

void Peek (int position, List *L, Item *X) {
	
	int i = 0;
		
	ListNode * current;
	
	current =(ListNode*)malloc(sizeof(ListNode));

	current->nextNode = L->first;
    current= current->nextNode; 

	for( i = 0; i< position; i++)
	{
        current= current->nextNode; 
        printf("%d\n",i);
        printf("Looking at each value %d\n",current->items.grade);
    } 
    printf("Exit\n");
    X->grade = current->items.grade;
    X->name = current->items.name;
    printf("In peek %d\n",X->grade);
    printf("In peek %s\n",X->name);
    
    free(current);
}

void Destroy (List *L) {
	
	ListNode * current; 
    ListNode * temp;
    
    current =(ListNode*)malloc(sizeof(ListNode));
    temp = (ListNode*)malloc(sizeof(ListNode));


	while ( current->nextNode != NULL)
	{

	    temp = current;
	    free(temp);
	    current = current->nextNode;

	}
 
    free(current);
	free(L);
}