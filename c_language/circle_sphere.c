/*
Calculate the area and circumference of a circle, 
and the volume of a sphere of a give radius
*/

#include <stdio.h>

#define PI    3.1415926

double area (double r)
{
	return (PI * r * r) ; // pi * r^2
}

double circumference(double r)
{
	return (2.0 * PI * r); // 2*pi*r
}

double sphereVol(double r)
{
	return (4.0/3.0 * PI * r * r * r) ; // 3/4 * pi * r^3
}

int main(int argc, char const *argv[])
{
	printf("radius = 1: %.4f %.4f %.4f\n", 
		area(1.0), circumference(1.0), sphereVol(1.0));

	printf("radius = 5.5: %.4f %.4f %.4f\n", 
		area(5.5), circumference(5.5), sphereVol(5.5));
	return 0;
}