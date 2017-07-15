#include <stdio.h>

#include "ray.h"

int main()
{
	double radius = 1.0;
	__m256d sphere = { 0.1, 0.1, 0.1, 1.0};
	__m256d origin = { 0.2, 0.3, 0.4, 0.0 };
	__m256d direction = { 0.5, 0.2, -0.1, 0.0};

	__m256d intersection = RayIntoSphere(origin, direction, sphere);
	printf("RayIntoSphere: <%.4lf, %.4lf, %.4lf, %.4lf>\n", intersection.m256d_f64[0], intersection.m256d_f64[1], intersection.m256d_f64[2], intersection.m256d_f64[3]);

	return 0;
}