#ifndef RAZIONALSLAU_GAUSSSLAU_H
#define RAZIONALSLAU_GAUSSSLAU_H
#include "input.h"
#include "OperationsModule.h"
typedef char *num;

void output1(fraction **matr, int countStrings, int countColumns);
int consoleOrTxtInput(int choose, fraction **matrS);
int matrFractions(fraction** matrS);
void swapString(fraction **a, fraction **b);
int compare(fraction a, fraction max);
int searchColMaxElem(fraction **matr, int k, int countStrings);
int directGauss(fraction **matr, int countStrings, int countColumns);
fraction summa(fraction **matr, int k, fraction *x, int countStrings);
void reverseGaussMuchSolving(fraction **matr, int countString, int countColumns);
fraction* reverseGauss(fraction **matr, int countStrings, int countColumns);
void solvingSlau(fraction **matr, int countStrings, int countColumns);
#endif //RAZIONALSLAU_GAUSSSLAU_H
