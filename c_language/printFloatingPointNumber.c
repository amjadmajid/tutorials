#include <stdio.h>

int main(void){
  printf("To print a floating point number use %%f\nFor example %f\n", 0.123);
  printf("To print a floating point number in scientific notation use %%e\nFor example %e\n", 0.123);
  printf("To let the program to decide weather to use a scientific notation or not use %%g\nFor example %g , %g\n", 0.0123, 0.00000123);
return 0;
}
