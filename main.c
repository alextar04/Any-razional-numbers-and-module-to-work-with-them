#include <stdio.h>
typedef struct commonfration
{
    long m;
    long n;
}commonFraction;

void representationOfNumber()
{
    puts("Press 1 if rational is natural or integer"); //Если число целое или натуральное
    puts("Press 2 if rational is common fraction"); //Если число обыкновенная дробь
    puts("Press 3 if rational is mixed number"); //Если смешанное число
    puts("Press 4 if rational is final decimal fraction or infinite periodic"); //Если конечная десятичная дробь или бесконечная периодическая дробь
    puts("Press any key if it's no rational number or for exit");
    static int choose;
    scanf("%d", &choose);
    switch (choose)
    {
   1:function1();
        break;
   2:function2();
        break;
   3:function3();
        break;
   4:function4();
        break;
    }
    system ("pause");
}

int main() {
    representationOfNumber();
    return 0;
}