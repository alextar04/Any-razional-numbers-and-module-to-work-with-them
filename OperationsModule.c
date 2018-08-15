#include "input.h"
#include <windows.h>
#include <stdio.h>

void enteringNumbers(char *number, fraction *a, fraction *b)
{
    *a = input(number);
    number[0] = '\0';
    *b = input(number);
}

void addition(fraction a, fraction b, fraction *result)
{
    result->n = a.n * b.n; // создаем общий знаменатель
    a.m *=(result->n/a.n);
    b.m *=(result->n/b.n);
    result->m = a.m + b.m; //после приведения к общему знаменателю можно сложить дроби
    reduction(result);//Сокращние дроби
}

void subtraction(fraction a, fraction b, fraction *result)
{
    result->n = a.n * b.n; // создаем общий знаменатель
    a.m *=(result->n/a.n);
    b.m *=(result->n/b.n);
    result->m = a.m - b.m; //после приведения к общему знаменателю можно вычесть дроби
    reduction(result);//Сокращние дроби
}

void multiplication(fraction a, fraction b, fraction *result)
{
    result->m = a.m * b.m; // перемножим числители дробей
    result->n = a.n * b.n; // перемножим знаменатели дробей
    reduction(result);//Сокращние дроби
}

void division(fraction a, fraction b, fraction *result)
{
    int sign = 1;
    if (a.m < 0)
        if (b.m > 0) sign = -1;
    if (a.m > 0)
        if (b.m < 0) sign = -1;

    result->m = sign * abs(a.m * b.n); //умножение числителя первой дроби со знаменателем второй
   result->n = sign * abs(a.n * b.m); //умножение знаменателя первой дроби с числителем второй
    reduction(result);//Сокращние дроби
}


int main () {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char number[100];
    fraction a,b,result;
    enteringNumbers(number, &a, &b);

      addition(a,b,&result);
    printf("Результат сложения: %li/%li\n",result.m,result.n);
      subtraction(a,b,&result);
    printf("Результат вычитания: %li/%li\n",result.m,result.n);
      multiplication(a,b,&result);
    printf("Результат умножения: %li/%li\n",result.m,result.n);
      division(a,b,&result);
    printf("Результат деления: %li/%li",result.m,result.n);

    return 0;
}