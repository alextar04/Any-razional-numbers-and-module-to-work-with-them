#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "input.h"


void wholeNumerator(const char *number, fraction *drob, long *i) //������������ ��������� only
{
    long j = *i;

    while((j < strlen(number))&&((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //������� ������ � �����
    {
        drob->m = (drob->m)*10 + (number[j]-'0');
        j++;
    }
    *i = j;
}

void wholeDenominator(const char *number, fraction *drob, long *i) //������������ ���������� only
{
    long j = *i;

    while(((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //������� ������ � �����
    {
        drob->n = (drob->n)*10 + (number[j]-'0');
        j++;
    }
    *i = j;
}

void skipingSpaces(const char *number, long *i)
{
    long g = *i;
    while ((g<strlen(number))&&(number[g]<=' ')) //������� ��������
        g++;
    *i = g;
}


int isMixedFraction(const char *number,fraction *drob, long *i)
{
    long g = *i;
    wholeNumerator(number, drob, &g);
    if (number[g] == '+')
    {
        g++;//������� "�����"
        long integerPart = drob->m;
        drob->m = 0;
        wholeNumerator(number, drob, &g); //��� �����

        //���������� ����� ����� '/'
        g++;
        wholeDenominator(number, drob, &g);
        if (drob->m > drob->n) {
            return -1;
        }
        (drob->m)+=(integerPart*(drob->n));
    }
    *i = g;
}

void isOrdinaryFraction(const char *number,fraction *drob, long *i) // ��� ������������ �����
{
    long j = *i;
    wholeNumerator(number, drob, &j);
    //������� '/'
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

void isFiniteDecimalSequence(const char *number, fraction *drob, long *i) //�������� ���������� ������������������
{
    long j = *i;
    wholeNumerator(number, drob, &j);
    long integerPart = drob->m;
    drob->m = 0;
    long realPart=0;
    if ((number[j] == '.')||(number[j] == ','))
    {
        long jOld = j; //������ j, ����� ������ �����������
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
    //������� '.'
    j++;
    //��������� ����� ����� '.'
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
    //������� '.'
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

int nod(fraction drob) //���� ��� �� ��������� �������
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
    puts("������ �����, ������� ������������ ����� �����!");
    printf("%s - �� ������������ �����!", number);
    number[0] = '\0';
    gets(number);
}

void intPart(const char *number, long *i){
    long j = *i;
    int len = strlen(number);
    while((j<len)&&((number[j]-'0') >= 0)&&((number[j]-'0') <= 9)) //������� ������ � �����
        j++;
    *i = j;
}

int typeNumber(const char *number, long i){
    long j = i;
    int len = strlen(number);//����� �����

    intPart(number, &j);
    if (j == len) return 1; //��� ����� - �����(�����������)

    if (number[j] == '/'){
        j++;
        intPart(number, &j);
        if (j == len) return 2; //��� ����� - ������������ �����
    }

    if (number[j] == '+'){
        j++;
        intPart(number, &j);
        if (number[j] == '/'){
            j++;
            intPart(number, &j);
            if (j == len) return 3; //��� ����� - ��������� �����
        }
    }

    if (number[j] == '.'){
        j++;
        intPart(number, &j);
        if (j == len) return 4; //��� ����� - �������� ���������� ������������������
        else{
            if (number[j] == '('){
                j++;
                intPart(number, &j);
                if (number[j] == ')') return 5;//��� ����� - ����������� ������������� �����
            } else{
                if ((number[j] == 'e') || (number[j] == 'E')){
                    j++;
                    if ((number[j] == '+') || (number[j] == '-'))
                        j++;
                    intPart(number, &j);
                    if (j == len) return 6; //��� ����� - ������������ �����, �������� ����� E(e)
                }
            }
        }
    }
    return -1; //������ �����
}

fraction input(char *number) {
    fraction drob;
    drob.m = 0; //���������
    drob.n = 0; //�����������

    long i = 0; //������� �������
    int sign = 1;
    skipingSpaces(number, &i);
    signDefinition(number, &sign, &i); //����������� �����

    int errorFlag = 0; //��������� �� ������
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
    drob.m *= sign; //����� ���� ����� ������
    if (drob.n == 0) drob.n = 1;
    return drob;
}