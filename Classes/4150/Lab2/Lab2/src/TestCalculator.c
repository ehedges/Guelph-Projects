

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Calculator.h"
#include "TestCalculator.h"
#include <assert.h>
#include <stdio.h>

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

void driver(double expectedSum, double expcetedDifference, double expectedProduct, double expectedQuotient, double a, double b)
{
    Calculator* testCalculator = newCalculator();

    int testResult = 0;
    float testValue = 0;

    printf("**********Testing**********\n");

    printf("**********Add**********\nA = %f\nB = %f\nExpected Sum = %f \nExecuting Add...\n",a,b,expectedSum);

    testResult = testAdd(expectedSum, a,b,testCalculator->add);
    testValue = testCalculator->add(a,b);

    if (testResult == 0)
    {

        goto addPassed; 

    }
    else if (testResult == -1)
    {

        goto addFailed;

    }

    subtractStart:

    printf("**********Subtract**********\nA = %f\nB = %f\nExpected Difference = %f \nExecuting Subtract...\n",a,b,expcetedDifference);

    testResult = testSubtract(expcetedDifference, a,b,testCalculator->subtract);

    if (testResult == 0)
    {

        goto subtractPassed;

    }
    else if (testResult == -1)
    {

        goto subtractFailed;

    }

    multiplyStart:

    printf("**********Multiply**********\nA = %f\nB = %f\nExpected Product = %f \nExecuting Multiply...\n",a,b,expectedProduct);

    testResult = testMultiply(expectedProduct, a,b,testCalculator->multiply);

    if (testResult == 0)
    {

        goto multiplyPassed;

    }
    else if (testResult == -1)
    {

        goto multiplyFailed;

    }

    divideStart:

    printf("**********Divide**********\nA = %f\nB = %f\nExpected Sum = %f \nExecuting Divide...\n",a,b,expectedQuotient);

    testResult = testDivide(expectedQuotient,a,b,testCalculator->divide);

    if (testResult == 0)
    {

        goto dividePassed;

    }
    else if (testResult == -1)
    {

        goto divideFailed;

    }

    addPassed:
    printf (GREEN "Add Passed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expectedSum,testValue);
    goto subtractStart;

    addFailed:
    printf (RED "Add Failed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expectedSum,testValue);
    goto subtractStart;

    subtractPassed:
    printf (GREEN "Subtract Passed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expcetedDifference,testValue);
    goto multiplyStart;

    subtractFailed:
    printf (RED "Subtract Failed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expcetedDifference,testValue);
    goto multiplyStart;

    multiplyPassed:
    printf (GREEN "Multiply Passed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expectedProduct,testValue);
    goto divideStart;

    multiplyFailed:
    printf (RED "Multiply Failed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expectedProduct,testValue);
    goto divideStart;

    dividePassed:
    printf (GREEN "Divide Passed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expectedQuotient,testValue);

    goto finishProgram;

    divideFailed:
    printf (RED "Divide Failed: A = %f, B = %f, Returned = %f, Actual = %f \n" RESET ,a,b,expectedQuotient,testValue);

    finishProgram:

    printf("Tests Complete\n\n\n");

    return;
}

int testSubtract(double expectedResult, double a, double b, double (*subtract)(double a, double b))
{
    double result = subtract(a,b);  
    
    if (result != expectedResult)
    {

        return -1;

    }


    return 0;
}

int testAdd(double expectedResult, double a, double b, double (*add)(double a, double b))
{
    double result = add(a,b);
    
    if (result != expectedResult)
    {

        return -1;

    }

    return 0;
}

int testMultiply(double expectedResult, double a, double b, double (*multilpy)(double a, double b))
{
    double result = multiply(a,b);  
    
    if (result != expectedResult)
    {

        return -1;

    }

    return 0;
}

int testDivide(double expectedResult, double a, double b, double (*divide)(double a, double b))
{
    double result = divide(a,b);  
    
    if (result != expectedResult)
    {

        return -1;

    }
    return 0;
}
