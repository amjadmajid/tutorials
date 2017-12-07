#include <stdio.h>

int main(void){
  printf("To print a hexadecimal number use %%x\nFor example %x\n", 0x123F);
  printf("To print a hexadecimal number with leading 0x use %%#x\nFor example %#x\n", 0x123F);
  printf("To print an uppercase hexadecimal number use %%X\nFor example %X\n", 0x123F);
  printf("To print an hexadecimal number with leading 0X use %%#X\nFor example %#X\n", 0x123F);
return 0;
}
