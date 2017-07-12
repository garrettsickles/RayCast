#include "ray.h"

#include <math.h>
#include <stdint.h>

static const uint64_t NO_INTERSECT[4] = { 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF8000000000000, 0x7FF0000000000000 };

__m256d RayIntoSphere(__m256d origin, __m256d direction, __m256d center, double radius)
{
	double time;

	// offset = center - origin
	__m256d displacement = _mm256_sub_pd(origin, center);

	// Insert radius into unused displacement parameter
	displacement.m256d_f64[3] = radius;

	// Direction length squared
	__m256d av = _mm256_mul_pd(direction, direction);
	double a = av.m256d_f64[0] + av.m256d_f64[1] + av.m256d_f64[2];

	// Direction (dot) Displacement
	__m256d bv = _mm256_mul_pd(direction, displacement);
	double b = 2.0 * (bv.m256d_f64[0] + bv.m256d_f64[1] + bv.m256d_f64[2]);

	// Displacement length squared and radius sqaured
	__m256d cv = _mm256_mul_pd(displacement, displacement);
	double c = cv.m256d_f64[0] + cv.m256d_f64[1] + cv.m256d_f64[2] - cv.m256d_f64[3];

	// Discriminant
	__m256d dv = _mm256_mul_pd(_mm256_set_pd(a, b, a, b), _mm256_set_pd(2.0, -1.0, c, b));
	double discriminant = dv.m256d_f64[0] - 4.0 * dv.m256d_f64[1];

	// Initialize to invalid intersect
	__m256d intersection = _mm256_load_pd((const double*)(NO_INTERSECT));

	// Ray misses sphere
	if (discriminant < 0.0)
	{
		return intersection;
	}

	// Ray intersects sphere
	else
	{
		time = dv.m256d_f64[2];

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

	time = time / dv.m256d_f64[3];

	// Calculate intersection
	intersection = _mm256_fmadd_pd(direction, _mm256_set1_pd(time), origin);
	intersection.m256d_f64[3] = time;

	return intersection;
}