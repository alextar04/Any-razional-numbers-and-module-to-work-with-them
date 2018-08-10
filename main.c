#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100
typedef struct fr
{
    long m;// числитель
    long n;// знаменатель
}fraction;

void wholeNumerator(const char *number, fraction drob, long *i) //формирование числителя only
{
    long j = *i;
 j++;

    while(((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
    {
        drob.m = drob.m*10 + (number[j]-'0');
        j++;
    }
    *i = j;
}

void wholeDenominator(const char *number, fraction drob, long *i) //формирование знаментеля only
{
    long j = *i;
    j++;

    while(((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
    {
        drob.n = drob.n*10 + (number[j]-'0');
        j++;
    }
    *i = j;
}

int isAnotherSymbols(const char *number, long i)
{
    i++;
    if ((number[i] != ' ')&&(number[i] != '\n')&&(number[i] != EOF) && (number[i] != 'e') && (number[i] != 'E') && (number[i] != '.') && (number[i] != ',') && (number[i] != '/'))
        return 1;//Если постронний символ
    return 0;
}

void isMixedFraction(const char *number,fraction drob, long *i)
{
    long g = *i;
    g++;
    if (number[g] == ' ')
    {
        long integerPart = drob.m;
        drob.m = 0;
        g++;
        wholeNumerator(number, drob, g); //как целые
        //Написать код для проверки на '/'
        g++;
        wholeDenominator(number, drob, g);
        //Написать код для проверки больше числитель или знаменатель '/'
        drob.m+=(integerPart*drob.n);
    }
    *i = g;
}

void isOrdinaryFraction(const char *number,fraction drob, long *i) // Для обыкновенной дроби
{
 if (number[*i] == '/') wholeDenominator(number, drob, i);
}

void skipingSpaces(const char *number, long *i)
{
    long g = *i;
    while ((g<strlen(number))&&(number[g]<=' ')) //пропуск пробелов
        g++;
    *i = g;
}

void signDefinition(const char *number, fraction drob, long i)
{
    if (number[i] == '-')
        drob.m = -1;
}

long isfiniteDecimalSequence(const char *number, fraction drob, long *i) //конечная десятичная последовательность
{
    long j = *i;
    long integerPart = drob.m;
    long realPart=0;
    if ((number[j] == '.')||(number[j] == ','))
    {
        long jOld = j; //старое j чтобы узнать знаменатель
        wholeNumerator(number,drob, j);
        long denominator = 10 * (j - jOld);
        realPart = drob.m;
        drob.m+=(denominator*integerPart);
    }
    *i = j;
    return realPart;
}

int isInfinitePeriodicFraction(const char *number, fraction drob, long *i, long realPart) {
    long j = *i;
    long period = 0;
    long jOld = j;
    if (number[j++] == '(')
        while (((number[j] - '0') >= 0) && ((number[j] - '0') <= 9)) {
            period = period*10 + (number[j]-'0');
            j++;
        }
    if (number[j] != ')') {
        return 0;//попросить новый ввод
    }
    long naturalCount = 10*(j-jOld+1)*realPart + period;
    long difference = naturalCount - realPart;
    long newDenominator = 0;
    for (int i = 0; i<(j - jOld+1); i++)
    {
        newDenominator = 10*newDenominator + 9;
    }
    drob.m = (drob.m - realPart)+difference;
    drob.n = newDenominator;
    *i = j;
}

int isMultiplicationAndDegree(const char *number, fraction drob, long *i, long realPart)
{
    skipingSpaces(number, i);
    long j = *i;
    int degree=0;
    if (number[j] == '*')
    {
        skipingSpaces(number, &j);
        if ((number[j] != 1)&&(number[j++] != 0))
            return 0;
    }
    j++;
    char sign = number[j];
    if ((number[j] != '-')&&(number[j] != '+')&&(number[j]<='0')&&(number[j]>='9'))
        return 0;
    j++;
    while(((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
    {
        degree = degree*10 + (number[j]-'0');
        j++;
    }
    double multiplier = pow(10, sign * degree);
    if (sign == '-') drob.n*=multiplier;
    else drob.m*=multiplier;
}

int isExponentaStyle(const char *number, fraction drob, long *i, long realPart)
{
    long j = *i;
    if ((number[j] == 'e')||(number[j]=='E')) {
        j++;
        long degree = 0;
        int sign = 1;
        if (number[j] == '-') {
             sign = -1;
        }
        j++;

        while (((number[j] - '0') >= 0) && ((number[j] - '0') <= 9)) {
            degree = degree * 10 + (number[j] - '0');
            j++;
        }
        
        double multiplier = sign  * pow(10, degree);
        if (sign < 0) drob.n*=multiplier;
        else drob.m*=multiplier;
    } else
 return 0;
}

void representationOfNumber()
{
        char number[MAXSIZE];
        gets(number);
        fraction drob;

    long i=0;//позиция каретки
    drob.m = 0; //числитель
    drob.n = 1; //знаменатель

    do { //Этот кусок кода - тупо ввод обыкновенного числа
        skipingSpaces(number, &i);
        signDefinition(number, drob, i); //Определение знака
        wholeNumerator(number, drob, &i); //Все числа изначально считываем как целые
        if (isAnotherSymbols(number, i))//Допустимы ли в воде следующие члены или попросить новый ввод
        {
                puts("Ошибка ввода, введите рациональное число снова!");
                gets(number);
        }
        else break;
    }
    while (number);

    isOrdinaryFraction(number, drob, &i); //для обыкновенной дроби
    isMixedFraction(number, drob, &i); //для смешанной дроби
    long realPart = isfiniteDecimalSequence(number, drob, &i); //конечная десятичная последовательность
    isInfinitePeriodicFraction(number, drob, &i, realPart);  //бесконечная периодическая дробь
    isMultiplicationAndDegree(number, drob, &i, realPart); // когда задано в виде умножения на 10 в степени
    isExponentaStyle(number,drob,&i,realPart);// задание рационального числа через экспоненту


    //Сократить дробь;
}

int main() {
    representationOfNumber();
    return 0;
}
