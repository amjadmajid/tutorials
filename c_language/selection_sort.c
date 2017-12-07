/*
Selection sort algorithm in c
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {

int list[] = {10, 5, 6, 3, 4, 11, 9, 7, 2};

int temp_max = 0, len  = sizeof(list) / sizeof(int) ;

// Loop until no swap is needed
for (int j = 0; j < len ; j++)
{
    // Iterate through array to find min value
    int i = j+1 , min = list[j], pos = j;
    while(i < len)
    {
        if (list[i] < min)
        {
            min = list[i];
            pos = i;
        }
        i++;
    }

        temp_max = list[j];
        list[j] = min;
        list[pos] = temp_max;
}
        for (int i=0; i < 9; i++)
            printf("%d ", list[i]);
        printf("\n");


    return 0;
}
