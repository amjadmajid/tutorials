#include <stdio.h>
#include <stdlib.h>

// To enable debugging define the MACRO in this way
#define DEBUG(fmt, ...) fprintf(stderr, fmt,__VA_ARGS__);

// To disable debugging degine the MACRO in this way
//#define DEBUG(fmt, ...)

int addNums(int a, int b)
{
DEBUG ("add the numbers: %d and %d\n", a,b)
return a+b;
}

int main(int argc, char *argv[])
{
int arg1 =0, arg2 = 0 ;

if (argc > 1)
  arg1 = atoi(argv[1]);
  DEBUG ("The first argument is : %d\n", arg1)

if (argc == 3)
  arg2 = atoi(argv[2]);
  DEBUG ("The second argument is : %d\n", arg2)


printf("The sum of the numbers is %d\n", addNums(arg1,arg2) );

return (0);
}
