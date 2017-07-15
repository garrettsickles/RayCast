#include "ray.h"
#include "platform.h"
 
#include <math.h>

Vector4 RayIntoSphere(Vector4 origin, Vector4 direction, Vector4 sphere)
{
	double a, b, c, discriminant, time;
	Vector4 displacement, av, bv, cv, dv, intersection;

	// displacement = origin - sphere 
	displacement = _mm256_sub_pd(origin, sphere);

	// Insert radius into unused displacement parameter
	T(displacement) = T(sphere);

	// Direction length squared
	av = _mm256_mul_pd(direction, direction);
	a = X(av) + Y(av) + Z(av);

	// Direction (dot) Displacement
	bv = _mm256_mul_pd(direction, displacement);
	b = 2.0 * (X(bv) + Y(bv) + Z(bv));

	// Displacement length squared and radius sqaured
	cv = _mm256_mul_pd(displacement, displacement);
	c = X(cv) + Y(cv) + Z(cv) - T(cv);

	// Discriminant
	dv = _mm256_mul_pd(_mm256_set_pd(a, b, a, b), _mm256_set_pd(2.0, -1.0, c, b));
	discriminant = X(dv) - 4.0 * Y(dv);

	// Initialize to invalid intersect
	intersection = _mm256_load_pd(NO_INTERSECT);

	// Ray misses sphere
	if (discriminant < 0.0)
	{
		return intersection;
	}

	// Ray intersects sphere
	else
	{
		time = Z(dv);
		if (discriminant > 0.0)
		{
			if (c < 0.0) time += sqrt(discriminant);
			else         time -= sqrt(discriminant);
		}
	}

	time = time / T(dv);

	// Calculate intersection
	intersection = _mm256_fmadd_pd(direction, _mm256_set1_pd(time), origin);
	T(intersection) = time;

	return intersection;
}