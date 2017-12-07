#include <stdio.h>

#define DEBUG
// another way to define the MACRO `DEBUG` is
// gcc -D DEBUG <prog.c>

int addNums(int a, int b, int c)
{
return a+b+c;
}

int main()
{
int a,b,c,readNums;

printf("%s", "Please enter three numbers to be added:" );
readNums = scanf("%d %d %d", &a, &b, &c);

#ifdef DEBUG
  fprintf(stderr, "The number of read arguments are: %d\n" , readNums);
  fprintf(stderr, "The numbers are: a=%d, b=%d and c=%d\n", a , b, c);
#endif

printf("The sum of the numbers is %d\n", addNums(a,b,c) );

return (0);
}
