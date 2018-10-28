#ifndef INPUT_RAZIONAL
#define INPUT_RAZIONAL

#include <windows.h>
typedef struct fr
{
    long m;// числитель
    long n;// знаменатель
}fraction;

fraction input(char *number);
void wholeNumerator(const char *number, fraction *drob, long *i);
void wholeDenominator(const char *number, fraction *drob, long *i);
void skipingSpaces(const char *number, long *i);
int isMixedFraction(const char *number,fraction *drob, long *i);
void isOrdinaryFraction(const char *number,fraction *drob, long *i);
void signDefinition(const char *number, int *sign, long *i);
void isFiniteDecimalSequence(const char *number, fraction *drob, long *i);
int numberOfDigits(long difference);
void isInfinitePeriodicFraction(const char *number, fraction *drob, long *i);
void isExponentaStyle(const char *number, fraction *drob, long *i);
int nod(fraction drob);
void reduction(fraction *drob);
void newNumber(char *number);


#endif // INPUT_RAZIONAL
