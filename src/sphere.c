#include "implementation.h"
#include "raycast.h"

RAYCAST_FUNCTION(RAY_INTO_SPHERE)(Vector4 origin, Vector4 direction, Vector4 sphere)
{
	double a, b, c, discriminant, time;
	Vector4 displacement, buffer, intersection;

	// displacement = origin - sphere 
	displacement = _mm256_sub_pd(origin, sphere);

	// Insert radius into unused displacement parameter
	T(displacement) = T(sphere);

	// Direction length squared
	{
		Vector4 temp = _mm256_mul_pd(direction, direction);
		a = X(temp) + Y(temp) + Z(temp);
	}

	// Direction dot Displacement
	{
		Vector4 temp = _mm256_mul_pd(direction, displacement);
		b = X(temp) + Y(temp) + Z(temp);
	}

	// Displacement length squared and radius sqaured
	{
		Vector4 temp = _mm256_mul_pd(displacement, displacement);
		c = X(temp) + Y(temp) + Z(temp) - T(temp);
	}

	// Discriminant
	buffer = _mm256_mul_pd(_mm256_set_pd(a, b, a, b), _mm256_set_pd(1.0, -1.0, c, b));
	discriminant = X(buffer) - Y(buffer);

	// Ray misses sphere
	if (discriminant < 0.0)
	{
		return _mm256_load_pd(NO_INTERSECT);
	}

	// Ray intersects sphere
	else
	{
		time = Z(buffer);
		if (discriminant > 0.0)
		{
			if (c < 0.0) time += sqrt(discriminant);
			else         time -= sqrt(discriminant);
		}
	}

	#if defined(_RAYCAST_CULL_BACKSHOOT_)
		// No backwards rays, otherwise this is a line intersection algorithm
		if (time < 0.0)
		{
			return _mm256_load_pd(NO_INTERSECT);
		}
	#endif

	time = time / T(buffer);

	// Compute intersection
	intersection = _mm256_fmadd_pd(direction, _mm256_set1_pd(time), origin);
	T(intersection) = time;

	return intersection;
}