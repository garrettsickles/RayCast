#include "ray.h"
#include "platform.h"
 
#include <math.h>
#include <stdint.h>

static const uint64_t NO_INTERSECT[4] = { 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF0000000000000 };

Vector4 RayIntoSphere(Vector4 origin, Vector4 direction, Vector4 center, double radius)
{
	double time;

	// offset = center - origin
	Vector4 displacement = _mm256_sub_pd(origin, center);

	// Insert radius into unused displacement parameter
	T(displacement) = radius;

	// Direction length squared
	Vector4 av = _mm256_mul_pd(direction, direction);
	double a = X(av) + Y(av) + Z(av);

	// Direction (dot) Displacement
	Vector4 bv = _mm256_mul_pd(direction, displacement);
	double b = 2.0 * (X(bv) + Y(bv) + Z(bv));

	// Displacement length squared and radius sqaured
	Vector4 cv = _mm256_mul_pd(displacement, displacement);
	double c = X(cv) + Y(cv) + Z(cv) - T(cv);

	// Discriminant
	Vector4 dv = _mm256_mul_pd(_mm256_set_pd(a, b, a, b), _mm256_set_pd(2.0, -1.0, c, b));
	double discriminant = X(dv) - 4.0 * Y(dv);

	// Initialize to invalid intersect
	Vector4 intersection = _mm256_load_pd((const double*)(NO_INTERSECT));

	// Ray misses sphere
	if (discriminant < 0.0)
	{
		return intersection;
	}

	// Ray intersects sphere
	else
	{
		time = Z(dv);

		// Two roots
		if (discriminant > 0.0)
		{
			if (c < 0.0)
			{
				time += sqrt(discriminant);
			}
			else
			{
				time -= sqrt(discriminant);
			}
		}

	}

	time = time / T(dv);

	// Calculate intersection
	intersection = _mm256_fmadd_pd(direction, _mm256_set1_pd(time), origin);
	T(intersection) = time;

	return intersection;
}