#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "input.h"


void wholeNumerator(const char *number, fraction *drob, long *i) //формирование числителя only
{
    long j = *i;

    while((j < strlen(number))&&((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
    {
        drob->m = (drob->m)*10 + (number[j]-'0');
        j++;
    }
    *i = j;
}

void wholeDenominator(const char *number, fraction *drob, long *i) //формирование знаментеля only
{
    long j = *i;

    while(((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
    {
        drob->n = (drob->n)*10 + (number[j]-'0');
        j++;
    }
    *i = j;
}

void skipingSpaces(const char *number, long *i)
{
    long g = *i;
    while ((g<strlen(number))&&(number[g]<=' ')) //пропуск пробелов
        g++;
    *i = g;
}


int isMixedFraction(const char *number,fraction *drob, long *i)
{
    long g = *i;
    wholeNumerator(number, drob, &g);
    if (number[g] == '+')
    {
        g++;//Пропуск "плюса"
        long integerPart = drob->m;
        drob->m = 0;
        wholeNumerator(number, drob, &g); //как целые

        //Считывание части после '/'
        g++;
        wholeDenominator(number, drob, &g);
        if (drob->m > drob->n) {
            return -1;
        }
        (drob->m)+=(integerPart*(drob->n));
    }
    *i = g;
}

void isOrdinaryFraction(const char *number,fraction *drob, long *i) // Для обыкновенной дроби
{
    long j = *i;
    wholeNumerator(number, drob, &j);
    //Пропуск '/'
    j++;
    wholeDenominator(number, drob, &j);
}


void signDefinition(const char *number, int *sign, long *i)
{
    long j = *i;
    if (number[j] == '-') {
        *sign = -1;
        j++;
    }
    *i = j;
}

void isFiniteDecimalSequence(const char *number, fraction *drob, long *i) //конечная десятичная последовательность
{
    long j = *i;
    wholeNumerator(number, drob, &j);
    long integerPart = drob->m;
    drob->m = 0;
    long realPart=0;
    if ((number[j] == '.')||(number[j] == ','))
    {
        long jOld = j; //старое j, чтобы узнать знаменатель
        j++;
        wholeNumerator(number, drob, &j);
        double denominator = pow(10 , (j - jOld-1));
        realPart = drob->m;
        drob->m+=(denominator*integerPart);
        drob->n = (long)denominator;
    }
    *i = j;
}

int numberOfDigits(long difference)
{
    int count = 0;
    while (difference/10 != 0)
    {
        difference/=10;
        count++;
    }
    count++;
    return count;
}

void isInfinitePeriodicFraction(const char *number, fraction *drob, long *i) {
    long j = *i;
    long period = 0;

    wholeNumerator(number, drob, &j);
    //Пропуск '.'
    j++;
    //Считываем часть после '.'
    wholeDenominator(number, drob, &j);
    long realPart = drob->n;

    long jOld = j;
    if (number[j++] == '(') {
        while (number[j]!=')') {
            period = period * 10 + (number[j] - '0');
            j++;
        }

        long naturalCount = (long) pow(10, (j - jOld - 1)) * realPart + period;
        long difference = naturalCount - realPart;
        long newDenominator = 0;
        for (int i = 0; i < (j - jOld - 1); i++) {
            newDenominator = 10 * newDenominator + 9;
        }
        int countDif = numberOfDigits(difference);
        int countDen = numberOfDigits(newDenominator);
        for (int q=countDen; q<countDif; q++)
            newDenominator *=10;
        drob->m = drob->m * newDenominator + difference;
        drob->n = newDenominator;
        j++;
    }
    *i = j;
}


void isExponentaStyle(const char *number, fraction *drob, long *i)
{
    long j = *i;
    wholeNumerator(number, drob, &j);
    //Пропуск '.'
    j++;
    wholeDenominator(number, drob, &j);
    if ((number[j] == 'e')||(number[j]=='E')) {
        j++;
        long degree = 0;
        int sign = 1;
        if (number[j] == '-') {
            sign = -1;
            j++;
        }
        if (number[j] == '+'){
            j++;
        }
        while (((number[j] - '0') >= 0) && ((number[j] - '0') <= 9)) {
            degree = degree * 10 + (number[j] - '0');
            j++;
        }

        double multiplier = pow(10, degree);
        if (sign < 0) drob->n*=multiplier;
        else drob->m*=multiplier;
    }
    *i = j;
}

int nod(fraction drob) //Ищем НОД по алгоритму Евклида
{
    int a = drob.m;
    int b = drob.n;
    while (b)
    {
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

void reduction(fraction *drob)
{
    int divider = nod(*drob);
    drob->m/=abs(divider);
    drob->n/=abs(divider);
}

void newNumber(char *number)
{
    puts("Ошибка ввода, введите рациональное число снова!");
    printf("%s - не рациональное число!", number);
    number[0] = '\0';
    gets(number);
}

void intPart(const char *number, long *i){
    long j = *i;
    int len = strlen(number);
    while((j<len)&&((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
        j++;
    *i = j;
}

int typeNumber(const char *number, long i){
    long j = i;
    int len = strlen(number);//Длина числа

    intPart(number, &j);
    if (j == len) return 1; //Тип числа - целое(натуральное)

    if (number[j] == '/'){
        j++;
        intPart(number, &j);
        if (j == len) return 2; //Тип числа - обыкновенная дробь
    }

    if (number[j] == '+'){
        j++;
        intPart(number, &j);
        if (number[j] == '/'){
            j++;
            intPart(number, &j);
            if (j == len) return 3; //Тип числа - Смешанная дробь
        }
    }

    if (number[j] == '.'){
        j++;
        intPart(number, &j);
        if (j == len) return 4; //Тип числа - конечная десятичная последовательность
        else{
            if (number[j] == '('){
                j++;
                intPart(number, &j);
                if (number[j] == ')') return 5;//Тип числа - бесконечная периодическая дробь
            } else{
                if ((number[j] == 'e') || (number[j] == 'E')){
                    j++;
                    if ((number[j] == '+') || (number[j] == '-'))
                        j++;
                    intPart(number, &j);
                    if (j == len) return 6; //Тип числа - рациональное число, заданное через E(e)
                }
            }
        }
    }
    return -1; //Ошибка ввода
}

fraction input(char *number) {
    fraction drob;
    drob.m = 0; //числитель
    drob.n = 0; //знаменатель

    long i = 0; //Позиция каретки
    int sign = 1;
    skipingSpaces(number, &i);
    signDefinition(number, &sign, &i); //Определение знака

    int errorFlag = 0; //сообщение об ошибке
    int type = typeNumber(number, i);
    switch (type) {
        case 1:
            wholeNumerator(number, &drob, &i);
            break;
        case 2:
            isOrdinaryFraction(number, &drob, &i);
            break;
        case 3:
            isMixedFraction(number, &drob, &i);
            break;
        case 4:
            isFiniteDecimalSequence(number, &drob, &i);
            break;
        case 5:
            isInfinitePeriodicFraction(number, &drob, &i);
            break;
        case 6:
            isExponentaStyle(number, &drob, &i);
            break;
        default:
            newNumber(number);
            break;
    }
    drob.m *= sign; //Учтем знак перед числом
    if (drob.n == 0) drob.n = 1;
    return drob;
}