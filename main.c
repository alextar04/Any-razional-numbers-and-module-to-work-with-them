#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100
typedef struct fr
{
    long m;// числитель
    long n;// знаменатель
}fraction;

void wholeNumerator(const char *number, fraction *drob, long *i) //формирование числителя only
{
    long j = *i;

    while(((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //перевод строки в число
    {
        drob->m = (drob->m)*10 + (number[j]-'0');
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
    if ((number[i] != ' ')&&(number[i] != '\n')&&(number[i] != EOF) && (number[i] != 'e') && (number[i] != 'E') && (number[i] != '.') && (number[i] != ',') && (number[i] != '/'))
        return 1;//Если постронний символ
    return 0;
}

int isMixedFraction(const char *number,fraction drob, long *i)
{
    long g = *i;
    g++;
    if (number[g] == ' ')
    {
        long integerPart = drob.m;
        drob.m = 0;
        g++;
        wholeNumerator(number, &drob, g); //как целые
        if (number[g] != '/')
            return 0;
        g++;
        wholeDenominator(number, drob, g);
        if (drob.m > drob.n)
            return 0;
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

void signDefinition(const char *number, int *sign, long *i)
{
    long j = *i;
    if (number[j] == '-') {
        *sign = -1;
        j++;
    }
    *i = j;
}

long isFiniteDecimalSequence(const char *number, fraction drob, long *i) //конечная десятичная последовательность
{
    long j = *i;
    long integerPart = drob.m;
    long realPart=0;
    if ((number[j] == '.')||(number[j] == ','))
    {
        long jOld = j; //старое j чтобы узнать знаменатель
        wholeNumerator(number, &drob, j);
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
        if ((number[j] != '\n')||(number[j] != EOF)) //ошибка ввода, какие то сторонние символы
            return 0;

        double multiplier = sign  * pow(10, degree);
        if (sign < 0) drob.n*=multiplier;
        else drob.m*=multiplier;
    } else
 return 0;
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

void reduction(fraction drob)
{
    int divider = nod(drob);
    drob.m/=divider;
    drob.n/=divider;
}

void representationOfNumber()
{
        char number[MAXSIZE];
        gets(number);
        fraction drob;

    long i=0;//позиция каретки
    int sign = 1;
    drob.m = 0; //числитель
    drob.n = 1; //знаменатель

    do { //Этот кусок кода - тупо ввод обыкновенного числа
        skipingSpaces(number, &i);
        signDefinition(number, &sign, &i); //Определение знака
        wholeNumerator(number, &drob, &i); //Все числа изначально считываем как целые
        if (isAnotherSymbols(number, i))//Допустимы ли в воде следующие члены или попросить новый ввод
        {
                puts("Ошибка ввода, введите рациональное число снова!");
                gets(number);
        }
        else {
            isOrdinaryFraction(number, drob, &i); //для обыкновенной дроби
            if (!( isMixedFraction(number, drob, &i))) //для смешанной дроби))
            {
                puts("Ошибка ввода, введите рациональное число снова!");
                gets(number);
            } else {
                long realPart = isFiniteDecimalSequence(number, drob, &i); //конечная десятичная последовательность
                if (!(isInfinitePeriodicFraction(number, drob, &i, realPart)))  //бесконечная периодическая дробь))
                {
                    puts("Ошибка ввода, введите рациональное число снова!");
                    gets(number);
                } else
                {
                    if (!(isMultiplicationAndDegree(number, drob, &i, realPart))) // когда задано в виде умножения на 10 в степени
                    {
                        puts("Ошибка ввода, введите рациональное число снова!");
                        gets(number);
                    } else {
                        if (!(isExponentaStyle(number, drob, &i, realPart)))  // задание рационального числа через экспоненту
                        {
                            puts("Ошибка ввода, введите рациональное число снова!");
                            gets(number);
                        }
                    }
                }
            }
        }
    }
    while (number);
    reduction(drob);//Сокращние дроби
    drob.m*=sign; //Учтем знак перед числом
    printf("%lo / %lo",drob.m,drob.n);
}

int main() {
    representationOfNumber();
    return 0;
}
