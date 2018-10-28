#ifndef RAZIONALSLAU_GAUSSSLAU_H
#define RAZIONALSLAU_GAUSSSLAU_H
#include "input.h"
#include "OperationsModule.h"
typedef char num[100];

void output1(fraction **matr, int countStrings, int countColumns);
void consoleOrTxtInput(int choose, num **matrS, int countStrings, int countColumns);
void matrStrings(num** matrS,int countStrings, int countColumns);
void swapString(fraction **a, fraction **b);
fraction** matrFractions(num** matrS, int countStrings, int countColumns);
int compare(fraction a, fraction max);
int searchColMaxElem(fraction **matr, int k, int countStrings);
int directGauss(fraction **matr, int countStrings, int countColumns);
fraction summa(fraction **matr, int k, fraction *x, int countStrings);
fraction* reverseGauss(fraction **matr, int countStrings, int countColumns);
void solvingSlau(fraction **matr, int countStrings, int countColumns);
#endif //RAZIONALSLAU_GAUSSSLAU_H
