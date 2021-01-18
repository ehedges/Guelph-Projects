/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: September 26th
	Assignment: 1
***************************/

#include <stdio.h>

/********************************************
Purpose: Calculate Ackermann's Function.
In: 2 integers
Out: A value of Ackermann's Function.
*********************************************/

int ackermann(int first, int second)
{

	if(first > 0 && second > 0)
	{

		return(ackermann(first-1,ackermann(first,second-1)));
		
	}
	if(first > 0)
	{

		return(ackermann(first-1,1));

	}
	if(second >= 0)
	{

		return(second+1);

	}

	return(-42);

}