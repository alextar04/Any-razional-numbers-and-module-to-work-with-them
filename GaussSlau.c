#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "input.h"
#include "OperationsModule.h"
#include "GaussSlau.h"
typedef char *num;

void output1(fraction **matr, int countStrings, int countColumns){
    for (int i=0; i<countStrings; i++){
        for (int j=0; j<countColumns; j++){
            printf("%li/%li  ", matr[i][j].m, matr[i][j].n);
        }
        printf("\n");
    }
}

int consoleOrTxtInput(int choose, fraction **matrF){

    if (choose == 1){ //Считаем с клавиатуры
        fflush(stdin);
        puts("Введите число неизвестных: ");
        int countStrings, countColumns;
        scanf("%d", &countStrings);
        countColumns = countStrings + 1;

        puts("Введите коэфициенты уравнений со свободными членами: ");
        for (int i = 0; i<countStrings; i++){
            for (int j = 0; j<countColumns; j++){
                num *temp = (num *)malloc(100 * sizeof(char));
                scanf("%s", temp); //т.r scanf считывает до пробела
                matrF[i][j] = input(temp);
                reduction(&matrF[i][j]);
            }
        }
        return countStrings;

    } else { //Считаем с файла
        FILE* fp = fopen("test.txt", "rb");//Открываем на чтение
        if (fp == NULL){
            puts("Ошибка открытия файла");
            return 0;
        }

        int j_1 = 0;
        char a;
        a = getc(fp);
        fseek(fp, 0,0);
        while (a != '\r'){
            num *temp = (num *)malloc(100 * sizeof(char));
            fscanf(fp, "%s", temp);
            matrF[0][j_1] = input(temp);
            reduction(&matrF[0][j_1]);
            j_1++;
            a = getc(fp);
        };
        int countStrings = j_1 - 1;
        int countColumns = j_1;

        for (int i = 1; i<countStrings; i++) {
            for (int j = 0; j < countColumns; j++) {
                num *temp = (num *)malloc(100 * sizeof(char));
                fscanf(fp, "%s", temp); //т.r scanf считывает до пробела
                matrF[i][j] = input(temp);
                reduction(&matrF[i][j]);
            }
            fseek(fp, 1, SEEK_CUR); //переход на новую строку
        }
        fclose(fp);
        return countStrings;
    }
}

int matrFractions(fraction** matrF){
    //Заполним матрицу
    puts("Выберите 1 - для ввода с клавиатуры, 2 - для ввода с файла");
    int choose;
    scanf("%d", &choose);
    int size = consoleOrTxtInput(choose, matrF);
    return size;
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
            fraction temp = matr[k][k];
            if (matr[k][k].m == 0){
                temp.m = 1;
                temp.n = 1;
            }
            fraction multipilersStep = division(matr[i][k], temp);
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

void reverseGaussMuchSolving(fraction **matr, int countStrings, int countColumns){
    fraction *result;
    result = (fraction *)malloc(countStrings * sizeof(fraction)); //Массив дробей(ответ)

    int k = countStrings-1;
    while(matr[k][k].m == 0){
        matr[k][k].m = 1;
        matr[k][countColumns-1].m = 1;
        k--;
    }


    result = reverseGauss(matr, countStrings, countColumns); //Обратный ход метода Гаусса
    puts("Частное решение Слау: ");
    for (int i=0; i<countStrings; i++) //Вывод решения
        printf("x%d = %li/%li  \n", i+1, result[i].m, result[i].n);

}


void solvingSlau(fraction **matr, int countStrings, int countColumns){
    fraction *result;
    result = (fraction *)malloc(countStrings * sizeof(fraction)); //Массив дробей(ответ)
    directGauss(matr, countStrings, countColumns); //Прямой ход метода Гаусса
    puts("Результат прямого хода Гаусса ");
    output1(matr, countStrings, countColumns);
    if ((matr[countStrings-1][countColumns-2].m == 0)&&(matr[countStrings-1][countColumns-1].m != 0)){
        puts("Система не имеет решений!");
        return;
    }
    if ((matr[countStrings-1][countColumns-2].m == 0)&&(matr[countStrings-1][countColumns-1].m == 0)){
        puts("Система имеет бесконечное число решений ");
        reverseGaussMuchSolving(matr, countStrings,countColumns);
        return;
    }
    result = reverseGauss(matr, countStrings, countColumns); //Обратный ход метода Гаусса
    puts("Решение Слау: ");
    for (int i=0; i<countStrings; i++) //Вывод решения
        printf("x%d = %li/%li  ", i+1, result[i].m, result[i].n);
}
