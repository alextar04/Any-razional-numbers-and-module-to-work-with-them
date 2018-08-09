#include <stdio.h>
#include <string.h>
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

void isfiniteDecimalSequence(const char *number, fraction drob, long *i) //конечная десятичная последовательность
{
    long j = *i;
    if ((number[j] == '.')||(number[j] == ','))
    {
        wholeNumerator(number,drob, i);
    }
    *i = j;
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
    isfiniteDecimalSequence(number, drob, &i); //конечная десятичная последовательность

    //system ("pause");
}

int main() {
    representationOfNumber();
    return 0;
}
