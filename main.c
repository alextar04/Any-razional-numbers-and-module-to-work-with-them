#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
typedef struct fr
{
    long m;// числитель
    long n;// знаменатель
}fraction;

void naturalOrWhole(char *number, fraction drob, long *i) //формирование числителя only
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

int CheckForTheNumber(const char *number, long *i)
{
    long j = *i;
    if ((number[j] != ' ')&&(number[j] != '\n')&&(number[j] != EOF))
        return 0;
    return 1;
}

void skipingSpaces(long *i)
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

void representationOfNumber()
{
        char number[MAXSIZE];
        gets(number);
        fraction drob;

    long i=0;//позиция каретки
    drob.n = 1; //знаменатель

    do {
        skipingSpaces(&i);
        signDefinition(number, drob, i); //Определение знака
        naturalOrWhole(number, drob, &i); //Все числа изначально считываем как целые
        if (!(CheckForTheNumber(number, &i)))//Есть ли после считанных цифр другие символы
        {
            puts("Введите рациональное число снова!");
            gets(number);
        }
        else break;
    }
    while (number);

    //system ("pause");
}

int main() {
    representationOfNumber();
    return 0;
}
