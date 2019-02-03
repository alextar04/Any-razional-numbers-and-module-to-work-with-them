#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "input.h"
#include "OperationsModule.h"
#include "GaussSlau.h"
typedef char *num;
#define MAXSIZE 100

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //Матрица дробей
    fraction **matr = (fraction **)malloc(MAXSIZE * sizeof(fraction*));
    for (int row = 0; row < MAXSIZE; row++) {
        matr[row] = (fraction *)malloc(MAXSIZE * sizeof(fraction));
    }

    //Матрица дробей
    int countStrings = matrFractions(matr);
    int countColumns = countStrings+1;


    puts("Матрица дробей: ");
    output1(matr, countStrings, countColumns);
    puts("***********************************");
    //Решение слау
    solvingSlau(matr, countStrings, countColumns);
    puts("");
    system ("pause");
    return 0;
}
