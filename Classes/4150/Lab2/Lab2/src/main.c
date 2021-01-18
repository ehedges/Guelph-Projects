

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Calculator.h"
#include "TestCalculator.h"


/*
    In main, call driver multiple times. Once in which there are all successes and once for each test function such that each one will fail once.
*/

int main(int argc, char* argv[])
{

    driver(2,0,1,1,1,1);
    driver(3,0,1,1,1,1);
    driver(2,2,1,1,1,1);
    driver(2,0,2,1,1,1);
    driver(2,0,1,2,1,1);


    return 0;
}