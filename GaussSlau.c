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
    if (choose == 1){ //Считаем с клавиатуры
        fflush(stdin);
        puts("Введите коэфициенты уравнений со свободными членами: ");
        for (int i = 0; i<countStrings; i++){
            for (int j = 0; j<countColumns; j++){
                scanf("%s", &matrS[i][j]); //т.r scanf считывает до пробела
            }
        }
    } else { //Считаем с файла
        FILE* fp = fopen("C:\\Users\\AT\\CLionProjects\\RazionalSlau\\input.txt", "rb");//Открываем на чтение
        for (int i = 0; i<countStrings; i++) {
            for (int j = 0; j < countColumns; j++) {
                fscanf(fp, "%s", &matrS[i][j]); //т.r scanf считывает до пробела
            }
            fseek(fp, 1, SEEK_CUR); //переход на новую строку
        }
        fclose(fp);
    }
}

void matrStrings(num** matrS,int countStrings, int countColumns){
    //Заполним матрицу
    puts("Выберите 1 - для ввода с клавиатуры, 2 - для ввода с файла");
    int choose;
    scanf("%d", &choose);
    consoleOrTxtInput(choose, matrS, countStrings, countColumns);
}

fraction** matrFractions(num** matrS, int countStrings, int countColumns){ //Получение матрицы дробей
    fraction **matrF = (fraction **)malloc(countStrings * sizeof(fraction*)); //Матрица дробей
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

int compare(fraction a, fraction max){ //Сравнение дробей
    fraction result;
    result.n = a.n * max.n; // создаем общий знаменатель
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
    return 0; //Нет обмена строк
}

int directGauss(fraction **matr, int countStrings, int countColumns){
    int count = 0; //Количество реальных перестановок
    for (int k = 0; k<(countStrings-1);k++){ //Выполняется n-1 раз
        int res = searchColMaxElem(matr, k, countStrings);
        if (res) count++; //Увеличивается количество реальных перестановок
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
    sum.n = 1; //Инициализация суммы
    for (int j=k+1; j<countStrings; j++){
        fraction arg1 = multiplication(matr[k][j], x[j]);
        reduction(&arg1);
        sum = addition(sum, arg1);
        reduction(&sum);
    }

    return sum;
}

fraction* reverseGauss(fraction **matr, int countStrings, int countColumns){
    fraction *x = (fraction *)malloc(countStrings * sizeof(fraction)); //Массив дробей(ответ)
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
    result = (fraction *)malloc(countStrings * sizeof(fraction)); //Массив дробей(ответ)
    directGauss(matr, countStrings, countColumns); //Прямой ход метода Гаусса
    puts("Результат прямого хода Гаусса ");
    output1(matr, countStrings, countColumns);
    result = reverseGauss(matr, countStrings, countColumns); //Обратный ход метода Гаусса
    puts("Решение Слау: ");
    for (int i=0; i<countStrings; i++) //Вывод решения
        printf("%li/%li  ", result[i].m, result[i].n);
}