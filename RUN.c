#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "input.h"
#include "OperationsModule.h"
#include "GaussSlau.h"
typedef char num[100];

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    puts("Введите количество неизвестных: ");
    int countStrings;
    scanf("%d", &countStrings);
    int countColumns;
    countColumns=countStrings+1;

    num **matrBuf = (num **)malloc(countStrings * sizeof(num*));
    for (int row = 0; row < countStrings; row++) {
        matrBuf[row] = (num *)malloc(countColumns * sizeof(num));
    }
    matrStrings(matrBuf, countStrings,countColumns); //Матрица строк

    fraction **matr = (fraction **)malloc(countStrings * sizeof(fraction*)); //Матрица дробей
    for (int row = 0; row < countStrings; row++) {
        matr[row] = (fraction *)malloc(countColumns * sizeof(fraction));
    }
    matr = matrFractions(matrBuf, countStrings, countColumns);//Матрица дробей
    puts("Матрица дробей: ");
    output1(matr, countStrings, countColumns);
    puts("***********************************");
    //Решение слау
    solvingSlau(matr, countStrings, countColumns);
    puts("");
    system ("pause");
    return 0;
}