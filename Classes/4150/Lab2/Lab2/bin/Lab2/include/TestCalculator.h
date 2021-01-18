#ifndef _TEST_CALCULATOR_
#define _TEST_CALCULATOR_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*

*The driver is the main testing driver you will need to fill out. 
*The driver calls the testAdd, testSubtract, testMultiply and testDivide with the values a, b, expctedSum, expectedDifference, expectedProduct
and expectedQuotient respectively.

*The driver must have 2 goto statements per function. One for success and one for failure. If the function succeeds goto the success label for that 
function and print that it succeeded. If the function fails goto the fail label and print that it failed. You will need 8 goto statements in total
with 8 unique goto labels.


*/
void driver(double expectedSum, double expcetedDifference, double expectedProduct, double expectedQuotient, double a, double b);

/*
    testAdd compares expectedResult with the result of the add function pointer taking in the parameters a and b.
    If the results of add does equals expected result, then testAdd returns 0. Else it returns -1
*/
int testAdd(double expectedResult, double a, double b, double(*add)(double a, double b));

/*
    testSubtract compares expectedResult with the result of the subtract function pointer taking in the parameters a and b.
    If the results of subtract does equals expectedResult, then testSubtract returns 0. Else it returns -1
*/
int testSubtract(double expectedResult, double a, double b, double(*subtract)(double a, double b));

/*
    testMultiply compares expectedResult with the result of the multiply function pointer taking in the parameters a and b.
    If the results of multiply does equals expected result, then testMultiply returns 0. Else it returns -1
*/
int testMultiply(double expectedResult, double a, double b, double(*multilpy)(double a, double b));

/*
    testDivide compares expectedResult with the result of the divide function pointer taking in the parameters a and b.
    If the results of divide does equals expected result, then testDivide returns 0. Else it returns -1
*/
int testDivide(double expectedResult, double a, double b, double(*divide)(double a, double b));



#endif