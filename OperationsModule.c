#include "input.h"
#include "OperationsModule.h"
#include <windows.h>
#include <stdio.h>

fraction addition(fraction a, fraction b)
{
    fraction result;
    result.n = a.n * b.n; // создаем общий знаменатель
    a.m *=(result.n/a.n);
    b.m *=(result.n/b.n);
    result.m = a.m + b.m; //после приведения к общему знаменателю можно сложить дроби
    reduction(&result);//Сокращние дроби
    return result;
}

fraction subtraction(fraction a, fraction b)
{
    fraction result;
    result.n = a.n * b.n; // создаем общий знаменатель
    a.m *=(result.n/a.n);
    b.m *=(result.n/b.n);
    result.m = a.m - b.m; //после приведения к общему знаменателю можно вычесть дроби
    reduction(&result);//Сокращние дроби
    return result;
}

fraction multiplication(fraction a, fraction b)
{
    fraction result;
    result.m = a.m * b.m; // перемножим числители дробей
    result.n = a.n * b.n; // перемножим знаменатели дробей
    reduction(&result);//Сокращние дроби
    return result;
}

fraction division(fraction a, fraction b)
{
    fraction result;
    int sign = 1;
    if (a.m < 0)
        if (b.m > 0) sign = -1;
    if (a.m > 0)
        if (b.m < 0) sign = -1;

    result.m = sign * abs(a.m * b.n); //умножение числителя первой дроби со знаменателем второй
    result.n = abs(a.n * b.m); //умножение знаменателя первой дроби с числителем второй
    reduction(&result);//Сокращние дроби

    return result;
}

