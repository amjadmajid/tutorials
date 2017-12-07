#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i = 12345 , j = 0,k=0;

    while( i != 0 )
    {
    	j=i%10;
        k = k *10 + j;
        i /=10;
    }

    printf("%d\n", k);
    return 0;
}