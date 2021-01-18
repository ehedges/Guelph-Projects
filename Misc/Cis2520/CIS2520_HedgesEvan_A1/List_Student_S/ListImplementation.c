#include "ListInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* some code here (e.g., #include directives, static functions) */

void Initialize (List *L) {



    List * temp;
    int i = 0;
    
    temp = (List *)malloc(sizeof(List));
    
    temp->size = 0;
    /*Sets all values*/        
    
    for(i = 0; i< MAXLISTSIZE; i++)
    {

        strcpy(L->items[i].name," ");
        L->items[i].grade = 0;
        printf("%s\n",L->items[i].name);
    }
    
}

void Insert (Item X, int position, List *L) {
	
	/*Copies Values*/
	strcpy(L->items[position].name,X.name);
	L->items[position].grade=X.grade;
	
}

void Remove (int position, List *L){
    /*Removes the value*/
    strcpy(L->items[position].name," ");
    L->items[position].grade = 0;

}

int Full (List *L) {
	
	int full;
	
	full = Size(L);
    
    if (full >= MAXLISTSIZE)
    {   
    
        return 1;
    
    }
	return 0;
}

int Empty (List *L) {
	
	int i;

    for(i = 0; i < MAXLISTSIZE; i++)
    {

       if (L->items[i].grade != 0)
       { 
	   
	        return 0;
       
       }
       
    }
    
    return 1;
}
int Size (List *L) {
	
	int i;
	
	int count;
	
	count = 0;
	
	for (i = 0;i < MAXLISTSIZE; i++)
	{

       if (L->items[i].grade != 0)
	   {
	   
	       count++;
	   }
	   

	}
	
	return count; /* change this */
} 

void Peek (int position, List *L, Item *X) {
	
        X->grade = L->items[position].grade;  
        strcpy(X->name,L->items[position].name);
        
}

void Destroy (List *L) {
	
	free(L);
}