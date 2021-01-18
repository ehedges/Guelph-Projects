/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: November 28th
	Assignment: 4
***************************/

#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

void initializeMenu(head * tree, FILE * ptr);
/********************************************
Purpose: create tree from file.
In:  header, file
Out: tree
*********************************************/

void findMenu(head * tree);
/********************************************
Purpose: find string in tree.
In:  tree
Out: nothing
*********************************************/

void insertMenu(head * tree);
/********************************************
Purpose: input single string into tree.
In:  tree
Out: tree
*********************************************/

void removeMenu(head * tree);
/********************************************
Purpose: remove 1 thing from tree.
In:  tree
Out: tree
*********************************************/

int heightMenu(head * tree);
/********************************************
Purpose: height of tree.
In:  tree
Out: int
*********************************************/

int sizeMenu(head * tree);
/********************************************
Purpose: size of tree.
In:  tree
Out: int
*********************************************/

void freqMenu(head * tree);
/********************************************
Purpose: find frequency in tree.
In:  tree
Out: nothing
*********************************************/

