/**************************
	Name : Evan Hedges 
	ID: 0898140
	Date: September 26th
	Assignment: 1
***************************/

#include <stdio.h>
#include <stdlib.h>

/*****************************************************
Purpose: Calculate an approximate root with recursion.
In: 2 doubles
Out: Returns a double.
******************************************************/

double newtonRec(double num, double accurate, double answer)
{

	float test;
	test = answer*answer-num;

	if(test < 0)
	{

		test = -test;
	
	}

	if(test > accurate)
	{

		answer = (answer+(num/answer))/2;
		answer = newtonRec(num,accurate,answer);

	}	

	return(answer);

}

/*************************************************
Purpose: Calculate an approximate root by looping.
In: 2 doubles
Out: Returns a double.
**************************************************/

double newtonLoop(double num, double accurate)
{
	
	int loop = 0;

	double answer = 0;
	double test = 0;
	
	answer = num/2;

	while (loop == 0)
	{

		test = answer*answer-num;

		if(test < 0)
		{

			test = -test;

		}

		if(test <= accurate)
		{

			return(answer);

		}
		
		answer = (answer+(num/answer))/2;

	}

	return(-42);

}