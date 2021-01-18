

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Calculator.h"

Calculator* newCalculator( void )
{
    Calculator * c = calloc(1, sizeof(Calculator));
    c->add = add;
    c->divide = divide;
    c->multiply = multiply;
    c->subtract = subtract;
    return c;
}

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a*b;
}

double divide(double a, double b)
{
    return a/b;
}