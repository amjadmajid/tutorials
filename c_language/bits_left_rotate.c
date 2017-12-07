#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t rotate(uint16_t num, uint16_t shBits);


int main(void) 
{   
   uint16_t num = 0x0088, res;
   printf("%x\n", num);
   res =  rotate(num, 3);
   printf("%x\n", res);
    return 0;
}

uint16_t rotate(uint16_t num, uint16_t shBits)
{
	shBits = ( (shBits < 0) ? -shBits : shBits) ; // make sure that n is not a negative number
	shBits = shBits % 16; // ensure that the shift value is less than 32

	// move shBits most significant bits to the right (LSBs)
	// 0x0088 >> (16 - 3) => 0000 0000 0000 0100
	// bits = 0000 0000 0000 0100
	uint16_t  bits = num >> (16 - shBits);

	// (num = 0x0088) >> 3 =>0x0011
	num >>= shBits;
	
	printf("num %x\n", num);
	printf("Bits %x\n", bits);
	shBits <<= num; // postion the shifted bints to the right location
	num |=shBits;
	printf("num %x\n", num);
	return (num); 
}