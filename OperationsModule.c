#include "input.h"
#include <windows.h>
#include <stdio.h>

void consoleOrTxtInput(char *number){
    puts("Выберите 1 - для ввода с клавиатуры, 2 - для ввода с файла");
    int choose;
    scanf("%d", &choose);
    if (choose == 1){ //Считаем с клавиатуры
        fflush(stdin);
        gets(number);
        //scanf("%s", number);
    } else { //Считаем с файла
        FILE* fp = fopen("C:\\Users\\AT\\CLionProjects\\KoursWork\\input.txt", "rb");//Открываем на чтение
        if (fp == NULL)
            puts("Ошибка открытия файла");
        fgets(number, 100,fp);
        fclose(fp);
    }
}


char enteringNumbers(char *number, fraction *a, fraction *b)
{
    int i = 0;//Позиция каретки
    consoleOrTxtInput(number);//Считываем с клавиатуры или Файла
    //gets(number);//Считаем выражение
    *a = input(number, &i); //Считаем 1 число
    skipingSpaces(number, &i);//Пропустим пробелы
    char operation = number[i]; //Считаем операцию
    i++;
    *b = input(number, &i); //Считаем 2 число
    return operation;
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
    char operationIs = enteringNumbers(number, &a, &b); //Название операции

    switch (operationIs) { //Выбор необходимой операции
        case '+':
            addition(a, b, &result);
            printf("Результат сложения: %li/%li\n", result.m, result.n);
            break;
        case '-':
            subtraction(a, b, &result);
            printf("Результат вычитания: %li/%li\n", result.m, result.n);
            break;
        case '*':
            multiplication(a, b, &result);
            printf("Результат умножения: %li/%li\n", result.m, result.n);
            break;
        case '/':
            division(a, b, &result);
            printf("Результат деления: %li/%li", result.m, result.n);
            break;
        default: puts("Выполнение операции невозможно");
    }

    return 0;
}
