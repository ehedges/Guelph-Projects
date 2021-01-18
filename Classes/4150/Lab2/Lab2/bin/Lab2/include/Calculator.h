#ifndef _CALCULATOR_
#define _CALCULATOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

 struct calculator
{

    //function pointers for add, subtract, multiply and divide
    double (*add)(double a, double b);
    double (*subtract)(double a, double b);
    double (*multiply)(double a, double b);
    double (*divide)(double a, double b);
}; typedef struct calculator Calculator;

//Calculator constructor
Calculator* newCalculator( void );

//adds a and b
double add(double a, double b);

//subtracts b from a
double subtract(double a, double b);

//multiply a and b
double multiply(double a, double b);

//a is the numerator, b is the denominator
double divide(double a, double b);

#endif