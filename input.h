#ifndef INPUT_RAZIONAL
#define INPUT_RAZIONAL
typedef struct fr
{
    long m;// числитель
    long n;// знаменатель
}fraction;

fraction input(char *number, int *j);
void wholeNumerator(const char *number, fraction *drob, long *i);
void wholeDenominator(const char *number, fraction *drob, long *i);
void skipingSpaces(const char *number, long *i);
int isAnotherSymbols(const char *number, long i);
int isMixedFraction(const char *number,fraction *drob, long *i, int *errorFlag);
void isOrdinaryFraction(const char *number,fraction *drob, long *i);
int errorInput(const char *number, long i);
int errorInput1(const char *number, long i);
void signDefinition(const char *number, int *sign, long *i);
long isFiniteDecimalSequence(const char *number, fraction *drob, long *i);
int numberOfDigits(long difference);
int isInfinitePeriodicFraction(const char *number, fraction *drob, long *i, long realPart, int *errorFlag);
int isMultiplicationAndDegree(const char *number, fraction *drob, long *i, long realPart, int *errorFlag);
int isExponentaStyle(const char *number, fraction *drob, long *i, long realPart, int *errorFlag);
int nod(fraction drob);
void reduction(fraction *drob);
void newNumber(char *number);


#endif // INPUT_RAZIONAL
