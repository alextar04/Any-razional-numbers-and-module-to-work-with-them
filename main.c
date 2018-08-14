#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <eaptypes.h>

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

int isAnotherSymbols(const char *number, long i)
{
    if ((number[i] != ' ')&&(number[i] != '\n')&&(number[i] != EOF) && (number[i] != 'e') && (number[i] != 'E') && (number[i] != '.') && (number[i] != ',') && (number[i] != '/'))
        return 1;//Если постронний символ
    return 0;
}

int isMixedFraction(const char *number,fraction *drob, long *i, int *errorFlag)
{
    long g = *i;
    if (number[g] == ' ')
    {
        skipingSpaces(number, &g);
        if ((number[g]-'0'<0)||(number[g]-'0'>9)) {
            *errorFlag = 1;
            return 0;
        }
        long integerPart = drob->m;
        drob->m = 0;
        wholeNumerator(number, drob, &g); //как целые
        if (number[g] != '/') {
            *errorFlag = 1;
            return 0;
        }
        g++;
        wholeDenominator(number, drob, &g);
        if (drob->m > drob->n) {
            *errorFlag = 1;
            return 0;
        }
        (drob->m)+=(integerPart*(drob->n));
    }
    *i = g;
}

void isOrdinaryFraction(const char *number,fraction *drob, long *i) // Для обыкновенной дроби
{
 if (number[*i] == '/')
 { int j = *i;
 j++;
 *i=j;
     wholeDenominator(number, drob, i);
 }
}

int errorInput(const char *number, long i)
{
    if ((number[i] != '.')&&(number[i] != ',')) return 1;
    else return 0;
}

int errorInput1(const char *number, long i)
{
if ((number[i] != '(')&&(number[i] != 'e')&&(number[i] != 'E')&&(number[i] != '*')) return 1;
else return 0;
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

long isFiniteDecimalSequence(const char *number, fraction *drob, long *i) //конечная десятичная последовательность
{
    long j = *i;
    long integerPart = drob->m;
    drob->m = 0;
    long realPart=0;
    if ((number[j] == '.')||(number[j] == ','))
    {
        long jOld = j; //старое j чтобы узнать знаменатель
        j++;
        wholeNumerator(number, drob, &j);
        double denominator = pow(10 , (j - jOld-1));
        realPart = drob->m;
        drob->m+=(denominator*integerPart);
        drob->n = (long)denominator;
    }
    *i = j;
    return realPart;
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

int isInfinitePeriodicFraction(const char *number, fraction *drob, long *i, long realPart, int *errorFlag) {
    long j = *i;
    long period = 0;
    long jOld = j;
    if (number[j++] == '(') {
        while (((number[j] - '0') >= 0) && ((number[j] - '0') <= 9)) {
            period = period * 10 + (number[j] - '0');
            j++;
        }
        if (number[j] != ')') {
            *errorFlag = 1;
            return 0;//попросить новый ввод
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
        drob->m = ((drob->m - realPart) / drob->n) * newDenominator + difference;
        drob->n = newDenominator;
        j++;
    }
    *i = j;
}

int isMultiplicationAndDegree(const char *number, fraction *drob, long *i, long realPart, int *errorFlag)
{
    skipingSpaces(number, i);
    long j = *i;
    int degree=0;
    j--;
    if (number[j] == '*') {
        skipingSpaces(number, &j);
        j++;
        if ((number[j] != '1') && (number[j + 1] != '0')) {
            *errorFlag = 1;
            return 0;
        }

        j += 2;
        int sign;
        if (number[j]== '+') sign = 1;
        else sign = -1;
        if ((number[j] != '-') && (number[j] != '+')) {
            *errorFlag = 1;
            return 0;
        }
        j++;
        while (((number[j] - '0') >= 0) && ((number[j] - '0') <= 9)) //перевод строки в число
        {
            degree = degree * 10 + (number[j] - '0');
            j++;
        }
        double multiplier = pow(10,degree);
        if (sign == -1) (drob->n) *= multiplier;
        else (drob->m) *= multiplier;
    }
    *i = j;
}

int isExponentaStyle(const char *number, fraction *drob, long *i, long realPart, int *errorFlag)
{
    long j = *i;
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
        if (number[j] != '\0') //ошибка ввода, какие то сторонние символы
        {
            *errorFlag = 1;
             return 1;
        }

        double multiplier = pow(10, degree);
        if (sign < 0) drob->n*=multiplier;
        else drob->m*=multiplier;
    } else {
        *errorFlag = 1;
        return 1;
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
    drob->m/=divider;
    drob->n/=divider;
}

void newNumber(char *number)
{
    puts("Ошибка ввода, введите рациональное число снова!");
    number[0] = '\0';
    gets(number);
}

void representationOfNumber()
{
        char number[MAXSIZE];
        gets(number);
        fraction drob;

    long i=0;//позиция каретки
    int sign = 1;
    drob.m = 0; //числитель
    drob.n = 0; //знаменатель
    int errorFlag = 0; //сообщение об ошибке

    do { //Этот кусок кода - тупо ввод обыкновенного числа
        skipingSpaces(number, &i);
        signDefinition(number, &sign, &i); //Определение знака
        wholeNumerator(number, &drob, &i); //Все числа изначально считываем как целые
        if ((number[i] == '\0')) break;
        if (isAnotherSymbols(number, i))//Допустимы ли в воде следующие члены или попросить новый ввод
            newNumber(number);
        else {
                isMixedFraction(number, &drob, &i, &errorFlag); //для смешанной дроби
            if ((number[i] == '\0')) break;
             if (errorFlag)
                newNumber(number); //сообщение об ошибке и ввод нового числа
             else
            {
              isOrdinaryFraction(number, &drob, &i); //для обыкновенной дроби
              if ((number[i] == '\0')) break;
                if (errorInput(number, i))
                    newNumber(number);
                else {
                    long realPart = isFiniteDecimalSequence(number, &drob, &i); //конечная десятичная последовательность
                    if ((number[i] == '\0')) break;
                      if (errorInput1(number, i))
                        newNumber(number);
                      else
                      {
                      isInfinitePeriodicFraction(number, &drob, &i, realPart, &errorFlag); //бесконечная периодическая дробь
                           if ((number[i] == '\0')) break;
                             if (errorFlag)
                             newNumber(number);
                             else {
                               isMultiplicationAndDegree(number, &drob, &i, realPart, &errorFlag); // когда задано в виде умножения на 10 в степени
                                 if ((number[i] == '\0')) break;
                                 if (errorFlag) newNumber(number);
                                 else {
                                   isExponentaStyle(number, &drob, &i, realPart, &errorFlag);  // задание рационального числа через экспоненту
                                     if ((number[i] == '\0')) break;
                                     if (errorFlag)
                                         newNumber(number);
                          }
                      }
                    }
                }
            }
        }
    }
    while (number);
    reduction(&drob);//Сокращние дроби
    drob.m*=sign; //Учтем знак перед числом
    if (drob.n == 0) drob.n = 1; //натуральное
    printf("%d/%d",drob.m,drob.n);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    representationOfNumber();
    return 0;
}
