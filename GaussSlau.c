#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "input.h"
#include "OperationsModule.h"
#include "GaussSlau.h"
typedef char num[100];

void output(num **matr, int countStrings, int countColumns){
    for (int i=0; i<countStrings; i++){
        for (int j=0; j<countColumns; j++){
            printf("%s  ", matr[i][j]);
        }
        printf("\n");
    }
}

void output1(fraction **matr, int countStrings, int countColumns){
    for (int i=0; i<countStrings; i++){
        for (int j=0; j<countColumns; j++){
            printf("%li/%li  ", matr[i][j].m, matr[i][j].n);
        }
        printf("\n");
    }
}

void consoleOrTxtInput(int choose, num **matrS, int countStrings, int countColumns){
    if (choose == 1){ //������� � ����������
        fflush(stdin);
        puts("������� ����������� ��������� �� ���������� �������: ");
        for (int i = 0; i<countStrings; i++){
            for (int j = 0; j<countColumns; j++){
                scanf("%s", &matrS[i][j]); //�.r scanf ��������� �� �������
            }
        }
    } else { //������� � �����
        FILE* fp = fopen("C:\\Users\\AT\\CLionProjects\\RazionalSlau\\input.txt", "rb");//��������� �� ������
        for (int i = 0; i<countStrings; i++) {
            for (int j = 0; j < countColumns; j++) {
                fscanf(fp, "%s", &matrS[i][j]); //�.r scanf ��������� �� �������
            }
            fseek(fp, 1, SEEK_CUR); //������� �� ����� ������
        }
        fclose(fp);
    }
}

void matrStrings(num** matrS,int countStrings, int countColumns){
    //�������� �������
    puts("�������� 1 - ��� ����� � ����������, 2 - ��� ����� � �����");
    int choose;
    scanf("%d", &choose);
    consoleOrTxtInput(choose, matrS, countStrings, countColumns);
}

fraction** matrFractions(num** matrS, int countStrings, int countColumns){ //��������� ������� ������
    fraction **matrF = (fraction **)malloc(countStrings * sizeof(fraction*)); //������� ������
    for (int row = 0; row < countStrings; row++) {
        matrF[row] = (fraction *)malloc(countColumns * sizeof(fraction));
    }

    for (int i=0; i<countStrings; i++){
        for (int j=0; j<countColumns; j++) {
            matrF[i][j] = input((matrS[i][j]));
            reduction(&matrF[i][j]);
        }
    }
    return matrF;
}

int compare(fraction a, fraction max){ //��������� ������
    fraction result;
    result.n = a.n * max.n; // ������� ����� �����������
    a.m *=(result.n/a.n);
    max.m *=(result.n/max.n);
    return (a.m > max.m)?1:0;
}

void swapString(fraction **a, fraction **b)
{
    int *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int searchColMaxElem(fraction **matr, int k, int countStrings){
    fraction max = matr[k][k];
    int iMax = 0;
    for (int i=k; i<countStrings; i++){
        int result = compare(matr[i][k], max);
        if (result){
            max = matr[i][k];
            iMax = i;
        }
    }
    if ((max.m != matr[k][k].m)||(max.n != matr[k][k].n)){
        swapString(&(matr[iMax]), &(matr[k]));
        return 1;
    }
    return 0; //��� ������ �����
}

int directGauss(fraction **matr, int countStrings, int countColumns){
    int count = 0; //���������� �������� ������������
    for (int k = 0; k<(countStrings-1);k++){ //����������� n-1 ���
        int res = searchColMaxElem(matr, k, countStrings);
        if (res) count++; //������������� ���������� �������� ������������
        for (int i=k+1; i<countStrings; i++) {
            fraction multipilersStep = division(matr[i][k], matr[k][k]);
            reduction(&multipilersStep);
            multipilersStep.m *= -1;
            for (int j = k; j < countColumns; j++) {
                fraction arg1 = multiplication(matr[k][j], multipilersStep);
                reduction(&arg1);
                matr[i][j] = addition(matr[i][j], arg1);
                reduction(&matr[i][j]);
            }
        }
    }
    return count;
}

fraction summa(fraction **matr, int k, fraction *x, int countStrings){
    fraction sum;
    sum.m = 0;
    sum.n = 1; //������������� �����
    for (int j=k+1; j<countStrings; j++){
        fraction arg1 = multiplication(matr[k][j], x[j]);
        reduction(&arg1);
        sum = addition(sum, arg1);
        reduction(&sum);
    }

    return sum;
}

fraction* reverseGauss(fraction **matr, int countStrings, int countColumns){
    fraction *x = (fraction *)malloc(countStrings * sizeof(fraction)); //������ ������(�����)
    int i = 0;
    for (int k=countStrings-1; k >= 0; --k){
        fraction sum = summa(matr, k, x, countStrings);
        x[k] = subtraction(matr[k][countStrings], sum);
        reduction(&x[k]);
        x[k] = division(x[k], matr[k][k]);
        reduction(&x[k]);
    }
    return x;
}

void solvingSlau(fraction **matr, int countStrings, int countColumns){
    fraction *result;
    result = (fraction *)malloc(countStrings * sizeof(fraction)); //������ ������(�����)
    directGauss(matr, countStrings, countColumns); //������ ��� ������ ������
    puts("��������� ������� ���� ������ ");
    output1(matr, countStrings, countColumns);
    result = reverseGauss(matr, countStrings, countColumns); //�������� ��� ������ ������
    puts("������� ����: ");
    for (int i=0; i<countStrings; i++) //����� �������
        printf("%li/%li  ", result[i].m, result[i].n);
}