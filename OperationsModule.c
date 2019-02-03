#include "input.h"
#include "OperationsModule.h"
#include <windows.h>
#include <stdio.h>

fraction addition(fraction a, fraction b)
{
    fraction result;
    unsigned int NOD = nod(a.n,b.n);
    unsigned int NOK = (a.n * b.n)/NOD;
    a.m *= (NOK/a.n);
    b.m *= (NOK/b.n);
    result.m = a.m + b.m;
    result.n = NOK;
    reduction(&result);//Сокращние дроби*/
    return result;
}

fraction subtraction(fraction a, fraction b)
{

    fraction result;
    unsigned int NOD = nod(a.n,b.n);
    unsigned int NOK = (a.n * b.n)/NOD;
    a.m *= (NOK/a.n);
    b.m *= (NOK/b.n);
    result.m = a.m - b.m;
    result.n = NOK;
    reduction(&result);//Сокращние дроби*/
    return result;
}

fraction multiplication(fraction a, fraction b)
{
    fraction result;
    int NOD = nod(a.m,b.n);
    a.m/=abs(NOD);
    b.n/=abs(NOD);
    int NOD1 = nod(b.m,a.n);
    b.m/=abs(NOD1);
    a.n/=abs(NOD1);
    result.m = a.m * b.m; // перемножим числители дробей
    result.n = a.n * b.n; // перемножим знаменатели дробей
    reduction(&result);//Сокращние дроби*/
    return result;
}

fraction division(fraction a, fraction b)
{
    fraction result;
    unsigned long temp = b.n;
    b.n = b.m;
    b.m = temp;
    result = multiplication(a, b);
    reduction(&result);//Сокращние дроби
    return result;
}
